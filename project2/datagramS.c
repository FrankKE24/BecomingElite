#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define PORT 5050

int main(int argc, char const *argv[])
{
    int sock, new_sock;
    struct sockaddr_in server;
    int addrlen = sizeof(server);
    int opt = 1;

    
    if((sock = socket(AF_INET, SOCK_STREAM, 0)) == 0){
        perror("SOcket creation failed!");
        return -1;
    }

    if((setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)))){
        perror("Set sockopt");
        exit(EXIT_FAILURE);
    }

    server.sin_family = AF_INET;
    server.sin_addr.s_addr  = INADDR_ANY;
    server.sin_port = htons(PORT);

    if((bind(sock, (struct sockaddr *)&server, sizeof(server))) < 0){
        fprintf(stderr, "Bind failed!");
        return -1;
    }
    /*
    struct sockaddr is a generic structure that is used in various socket functions.
     It is a placeholder for protocol-specific address structures like struct sockaddr_in 
     (IPv4) or struct sockaddr_in6 (IPv6).
     
     (struct sockaddr *)&server_addr converts the address of server_addr (which is of type
      struct sockaddr_in) to a pointer of type struct sockaddr *. This allows the function 
      to accept the address structure while maintaining type safety.*/

    if(listen(sock, 10) < 0){
        fprintf(stderr, "Listen");
        return -1;
    }

    printf("Server is listening on port %d\n", PORT);
    printf("Waiting for response\n");

    if((new_sock = accept(sock, (struct sockaddr *)&server, &addrlen)) < 0 ){
        perror("accept");
        exit(EXIT_FAILURE);
    }

    char buffer[20];
    char *server_mssg = "Hallo from server";
    printf("Message received: ");
    recv(new_sock, buffer, sizeof(buffer), 0);
    printf("%s\n", buffer);

    send(new_sock, server_mssg, strlen(server_mssg), 0);

    while (1)
    {     
        char reply[16];
        printf("Message received: ");
        recv(new_sock, reply, sizeof(reply), 0);
        printf("%s\n", reply);
        char reply2[16];

        ///send(new_sock, server_mssg, strlen(server_mssg), 0);
        printf("Response: "); 
        scanf("%15s", reply2);
        send(new_sock, reply2, strlen(reply2), 0);

    }




    return 0;
}
