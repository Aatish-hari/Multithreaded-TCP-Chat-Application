#ifndef UTILS_H
#define UTILS_H
#define _GNU_SOURCE
#include <winsock2.h>   // Core Winsock functions (socket, bind, listen, etc.)
#include <ws2tcpip.h>   // For modern extensions (IPv6, getaddrinfo, inet_pton, etc.)
#include <stdio.h> 
#include<malloc.h>
#include <stdlib.h>
#include <stdbool.h>
#include<memory.h>
#include<pthread.h>

struct acceptedclient{
    SOCKET acceptedsocket;
    struct sockaddr_in address;
    int error;
    bool acceptedsuccess;
};

struct sockaddr_in* creatingIPv4address(char *ip , int port);

SOCKET creatingTCPIPv4socket();

void reciveandprintdata(struct acceptedclient* clientsocket);

struct acceptedclient* acceptedclientsocket(SOCKET serversock);

void startacceptingIncomingconnections(SOCKET serversock);

void acceptconnectionsandrecivedataAndprint(SOCKET serversock);

void reciveingandprintinginSeperatethread(struct acceptedclient* clientsocket);

void sendreciveddatatootherclients(char*buffer,SOCKET clientsock);

void listeningandprintingotherclientsmessagesonnewThread(SOCKET clientsock);
#endif //UTILS_H
