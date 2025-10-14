#include "utils.h"

struct acceptedclient acceptedclientsarray[10];                     //this is global//
int countofacceptedclients = 0;

SOCKET creatingTCPIPv4socket(){
    return socket(AF_INET , SOCK_STREAM,0);
}

struct sockaddr_in* creatingIPv4address(char *ip , int port){
    struct sockaddr_in *address = malloc(sizeof(struct sockaddr_in));

    address->sin_port = htons(port);         //makes sure the port number is stored in the “network-standard” format (big-endian) so any other machine on the network can interpret it correctly
    address->sin_family = AF_INET;                //address family is IPv4
    if(strlen(ip) == 0){
        address->sin_addr.s_addr = INADDR_ANY;
    }
    else{
    inet_pton(AF_INET ,ip, &address->sin_addr.s_addr);
    }
    return address;
}

struct acceptedclient* acceptedclientsocket(SOCKET serversock){
    struct sockaddr_in clientaddress;
    int clientaddresssize = sizeof(struct sockaddr_in);
    SOCKET acceptedclientsock = accept(serversock , (struct sockaddr*)&clientaddress , &clientaddresssize);

    struct acceptedclient* acceptedsock = malloc(sizeof(struct acceptedclient));

    acceptedsock->address = clientaddress;
    acceptedsock->acceptedsocket = acceptedclientsock;
    acceptedsock->acceptedsuccess=acceptedclientsock>0;

    if(!acceptedsock->acceptedsuccess){
        acceptedsock->error = acceptedclientsock;
    }
    return acceptedsock;
}


void reciveandprintdata(struct acceptedclient* clientsocket){
     char buffer[1024];
    while(true){
        int reciveddata = recv(clientsocket->acceptedsocket, buffer, 1024 - 1, 0);  // int (not size_t), room for \0
        if(reciveddata <= 0){  // FIX: Check FIRST
            if(reciveddata < 0){  // Log error
               int err = WSAGetLastError();
                printf("\nRecv error on client: %d (likely disconnect)\n", err);
            }
            break;  // Exit loop cleanly
        }
         buffer[reciveddata] = 0;
         printf("\n%s", buffer);
        sendreciveddatatootherclients(buffer,clientsocket->acceptedsocket);
    }
    
    closesocket(clientsocket->acceptedsocket);
}

// === THREAD WRAPPER: this is the only new function added ===
void *reciveandprintdata_wrapper(void *arg) {
    struct acceptedclient *clientsocket = (struct acceptedclient *)arg;
    reciveandprintdata(clientsocket);
    return NULL;
}



void startacceptingIncomingconnections(SOCKET serversock){
    while(true){
    struct acceptedclient* clientsocket = acceptedclientsocket(serversock); 
    acceptedclientsarray[countofacceptedclients++] = *clientsocket;
    reciveingandprintinginSeperatethread(clientsocket);
    }
      //call every new socket connections process of reciving and printing in seperate thread.
}


void reciveingandprintinginSeperatethread(struct acceptedclient* clientsocket){
    pthread_t th;
    pthread_create(&th , NULL , reciveandprintdata_wrapper, clientsocket);
}

void sendreciveddatatootherclients(char*buffer,SOCKET clientsock){
    for(int i = 0 ; i<countofacceptedclients ; i++){
        if(acceptedclientsarray[i].acceptedsocket != clientsock){ //not sending itself, though everyone else
            send(acceptedclientsarray[i].acceptedsocket,buffer,strlen(buffer),0);
        }
    }
}

void *listenandwrite(void *arg) {
    SOCKET clientsock = *(SOCKET *)arg;
     char buffer[1024];
    while(true){

        size_t reciveddata = recv(clientsock , buffer , 1024 , 0);
        if(reciveddata>0){
             buffer[reciveddata] = 0;
        printf("\n%s", buffer);
         sendreciveddatatootherclients(buffer,clientsock);
        }
       
        if(reciveddata == 0){
            break;
        }
        
    }
    
    closesocket(clientsock);
}

//can use reciveandprintdata in place of this.
void listeningandprintingotherclientsmessagesonnewThread(SOCKET clientsock){
    pthread_t newth;
    SOCKET *pclientsock = malloc(sizeof(SOCKET));
    *pclientsock = clientsock;
    pthread_create(&newth,NULL,listenandwrite,pclientsock);
}

