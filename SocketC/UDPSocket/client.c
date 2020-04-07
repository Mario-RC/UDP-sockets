
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define IP_ADDRESS "127.0.0.1"
#define SERVPORT 5000
#define BUFFER_SIZE 1024

#pragma pack(1)

typedef struct payload_t {
    uint32_t id;
    float temp;
    char msg;
} payload;

#pragma pack()

int main(int argc, char*argv[]) {

    int clientSock, nread, nsent;
    struct sockaddr_in saddr;
    socklen_t sddrSize = sizeof(saddr);
    char buff[BUFFER_SIZE];

    if ((clientSock = socket(AF_INET,SOCK_DGRAM,0)) < 0) {
        printf("ERROR: Socket creation failed\n");
        exit(1);
    }

    bzero((char *) &saddr, sddrSize);
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(SERVPORT);
    
    // Convert IPv4 and IPv6 addresses from text to binary form
    if(inet_pton(AF_INET, IP_ADDRESS, &saddr.sin_addr) <= 0) {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }
    // saddr.sin_addr.s_addr = htonl(INADDR_ANY);
    // saddr.sin_addr.s_addr = inet_addr("127.0.0.1");
   
    if ((connect(clientSock, (struct sockaddr *)&saddr, sddrSize)) < 0) {
        printf("ERROR: Connection failed\n");
        exit(1);
    } // end if
    printf("Connected to (%s, %d)\n", inet_ntoa(saddr.sin_addr), htons(saddr.sin_port));

    while (1) {
        bzero(buff, BUFFER_SIZE);
        printf("\nSent message: ");
        fgets(buff,sizeof(buff),stdin);

        if ((nsent=sendto(clientSock,(char*)buff,strlen(buff)-1,0,(struct sockaddr*)&saddr,sddrSize)) < 0) {
            printf("Can't send message.\n");
            exit(1);
        }
        printf("sent %d bytes to (%s, %d)\n", nsent, inet_ntoa(saddr.sin_addr), htons(saddr.sin_port));

        bzero(buff, BUFFER_SIZE);
        if ((nread=recvfrom(clientSock,(char*)buff,BUFFER_SIZE,0,(struct sockaddr*)&saddr,&sddrSize)) < 0) {
            printf("Can't recieve message.\n");
            exit(1);
        }
        printf("\nReceived message: %s", buff);
        printf("\nreceived %d bytes from (%s, %d)\n", nread, inet_ntoa(saddr.sin_addr), htons(saddr.sin_port));
    } // end while

    close(clientSock);
    return (0);

} // end main
