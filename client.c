#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#define PORT 5734

int main(){
    struct sockaddr_in address;
    int dsc = 0;
    struct sockaddr_in serveraddress;
    if((dsc = socket(AF_INET,SOCK_STREAM,0)<0){
        printf("Error.\n");
        return -1;        
    }

    memset(&serveraddress, '0', sizeof(serveraddress));

    serveraddress.sin_family = AF_INET;
    serveraddress.sin_port = htons(PORT);
    serveraddress.sin_addr = inet_addr("127.0.0.1");

    if (connect(dsc, (struct sockaddr *)&serveraddress, sizeof(serveraddress))<0){
        printf("\nError\n");
        return -1;

    }


} 