#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <time.h>

#include "uthash-master/src/utlist.h"
#include "uthash-master/src/uthash.h"

#define PORT 9000
#define MAX_CLIENTS 10
#define TIMEOUT_SECS 30
#define MAX_MSG_LEN 256


typedef struct {
    int socket_fd;
    char ip[INET6_ADDRSTRLEN];
    time_t last_active;
    char username[32];
    int bytes_received;
    char last_msg[MAX_MSG_LEN];
    UT_hash_handle hh;
} session_t;

session_t *sessions = NULL;

// Add or update a session
void add_session(int socket_fd, const char *ip) {
    session_t *s = malloc(sizeof(session_t));
    s->socket_fd = socket_fd;
    strncpy(s->ip, ip, sizeof(s->ip));
    s->last_active = time(NULL);
    HASH_ADD_INT(sessions, socket_fd, s);
    printf("[+] New session: %s (fd=%d)\n", ip, socket_fd);
}

// Remove a session
void remove_session(int socket_fd) {
    session_t *s;
    HASH_FIND_INT(sessions, &socket_fd, s);
    if (s) {
        HASH_DEL(sessions, s);
        close(s->socket_fd);
        printf("[-] Disconnected: %s (fd=%d)\n", s->ip, socket_fd);
        free(s);
    }
}

int main() {
    int server_fd, new_socket, max_sd, activity, sd;
    struct sockaddr_in address;
    socklen_t addrlen = sizeof(address);
    fd_set readfds;

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    bind(server_fd, (struct sockaddr *)&address, sizeof(address));
    listen(server_fd, 3);

    printf("TCP server listening on port %d...\n", PORT);

    while (1) {
        FD_ZERO(&readfds);
        FD_SET(server_fd, &readfds);
        max_sd = server_fd;

        session_t *s, *tmp;
        HASH_ITER(hh, sessions, s, tmp) {
            FD_SET(s->socket_fd, &readfds);
            if (s->socket_fd > max_sd)
                max_sd = s->socket_fd;
        }

        activity = select(max_sd + 1, &readfds, NULL, NULL, NULL);

        //chec kfo rtimeouts
        time_t now = time(NULL);
        HASH_ITER(hh, sessions, s, tmp){
            if(now - s->last_active > TIMEOUT_SECS){
                printf("[!] Timeout: %s (fd=%d)\n", s->ip, s->socket_fd);
                remove_session(s->socket_fd);
            }
        }

        if (FD_ISSET(server_fd, &readfds)) {
            new_socket = accept(server_fd, (struct sockaddr *)&address, &addrlen);
            if (new_socket < 0) {
                perror("accept");
                exit(EXIT_FAILURE);
            }

            char ip_str[INET_ADDRSTRLEN];
            inet_ntop(AF_INET, &(address.sin_addr), ip_str, sizeof(ip_str));
            add_session(new_socket, ip_str);
        }

        HASH_ITER(hh, sessions, s, tmp) {
            if (FD_ISSET(s->socket_fd, &readfds)) {
                char buffer[1024];
                int valread = read(s->socket_fd, buffer, sizeof(buffer));
                if (valread == 0) {
                    remove_session(s->socket_fd);
                } else {
                    buffer[valread] = '\0';
                    strncpy(s->last_msg, buffer, MAX_MSG_LEN);
                    s->bytes_received += valread;
                    s->last_active = time(NULL);
                    printf("[Received from %s]: %s", s->ip, buffer);
                
                    if (strlen(s->username) == 0) {
                        snprintf(s->username, sizeof(s->username), "user_%d", s->socket_fd);
                        printf("    Assigned username: %s\n", s->username);
                    }
                }
            }
        }
    }

    return 0;
}

/*typedef struct {
    int socket_fd;
    char ip[INET6_ADDRSTRLEN];
    time_t last_active;
    UT_hash_handle hh;
} session_t;

session_t *sessions = NULL;

// Add or update a session
void add_session(int socket_fd, const char *ip) {
    session_t *s = malloc(sizeof(session_t));
    s->socket_fd = socket_fd;
    strncpy(s->ip, ip, sizeof(s->ip));
    s->last_active = time(NULL);
    HASH_ADD_INT(sessions, socket_fd, s);
    printf("[+] New session: %s (fd=%d)\n", ip, socket_fd);
}

// Remove a session
void remove_session(int socket_fd) {
    session_t *s;
    HASH_FIND_INT(sessions, &socket_fd, s);
    if (s) {
        HASH_DEL(sessions, s);
        close(s->socket_fd);
        printf("[-] Disconnected: %s (fd=%d)\n", s->ip, socket_fd);
        free(s);
    }
}

int main() {
    int server_fd, new_socket, max_sd, activity, sd;
    struct sockaddr_in address;
    socklen_t addrlen = sizeof(address);
    fd_set readfds;

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    bind(server_fd, (struct sockaddr *)&address, sizeof(address));
    listen(server_fd, 3);

    printf("TCP server listening on port %d...\n", PORT);

    while (1) {
        FD_ZERO(&readfds);
        FD_SET(server_fd, &readfds);
        max_sd = server_fd;

        session_t *s, *tmp;
        HASH_ITER(hh, sessions, s, tmp) {
            FD_SET(s->socket_fd, &readfds);
            if (s->socket_fd > max_sd)
                max_sd = s->socket_fd;
        }

        activity = select(max_sd + 1, &readfds, NULL, NULL, NULL);

        if (FD_ISSET(server_fd, &readfds)) {
            new_socket = accept(server_fd, (struct sockaddr *)&address, &addrlen);
            if (new_socket < 0) {
                perror("accept");
                exit(EXIT_FAILURE);
            }

            char ip_str[INET_ADDRSTRLEN];
            inet_ntop(AF_INET, &(address.sin_addr), ip_str, sizeof(ip_str));
            add_session(new_socket, ip_str);
        }

        HASH_ITER(hh, sessions, s, tmp) {
            if (FD_ISSET(s->socket_fd, &readfds)) {
                char buffer[1024];
                int valread = read(s->socket_fd, buffer, sizeof(buffer));
                if (valread == 0) {
                    remove_session(s->socket_fd);
                } else {
                    buffer[valread] = '\0';
                    printf("[Received from %s]: %s\n", s->ip, buffer);
                }
            }
        }
    }

    return 0;
}


















































/*struct my_struct {
    int id;            /* we'll use this field as the key /
    char name[10];
    UT_hash_handle hh; /* makes this structure hashable /
};

struct my_struct *users = NULL;

void add_user(struct my_struct *s) {
    HASH_ADD_INT( users, id, s );
}

struct my_struct *find_user(int user_id) {
    struct my_struct *s;

    HASH_FIND_INT( users, &user_id, s );
    return s;
}

void delete_user(struct my_struct *user) {
    HASH_DEL( users, user);
}*/