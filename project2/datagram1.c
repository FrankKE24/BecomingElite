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
    struct sockaddr_in client_addr;
    int sock;

    if((sock = socket(AF_INET ,SOCK_STREAM, 0)) <0){
        fprintf(stderr, "Couldn't create socket!");
        exit(EXIT_FAILURE);
    }

    client_addr.sin_family = AF_INET;
    client_addr.sin_port = htons(PORT);

    if((inet_pton(AF_INET, "127.0.0.1", &client_addr.sin_addr)) <0){
        perror("Inavlid ADDRESS");
        return -1;
    }

    if((connect(sock, (struct sockaddr *)&client_addr, sizeof(client_addr)) < 0 )){
        perror("Connection failed!");
        return -1;
    }
    char *client_mssg = "Hallo from client";
    char buffer[20];
    size_t send_message, recieved_mssg;
    send_message = send(sock, client_mssg, strlen(client_mssg), 0);
    printf("Message from client sent\n");

    printf("Received meassage: ");
    recieved_mssg = recv(sock, buffer, sizeof(buffer), 0);
    printf("%s\n", buffer);
    while (1)
    {
        char response[16];
        printf("Response: ");
        scanf("%15s", response);
        send_message = send(sock, response, strlen(response), 0);
        printf("Reply sent\n");
    
        char response2[16];
        printf("Received message: ");
        recieved_mssg = recv(sock, response2, sizeof(response2), 0);
        printf("%s\n", response2);
    }
    
    //shutdown(sock, 0);

    return 0;
}
