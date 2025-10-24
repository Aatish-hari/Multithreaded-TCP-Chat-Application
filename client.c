#include"utils.h"

int main(){
    WSADATA wsa;
    WSAStartup(MAKEWORD(2,2), &wsa); // Initialize Winsock 

    SOCKET clientsock = creatingTCPIPv4socket() ;

    int port = 2000;
    char* ip = "127.0.0.1";
    struct sockaddr_in *clientaddress = creatingIPv4address("127.0.0.1" , port);

    if (!clientaddress) {
    printf("Invalid address\n");
    return 1;
    }

    int result = connect(clientsock , (struct sockaddr*)clientaddress , sizeof(*clientaddress));


    if(result == 0){
        printf("connection successful with server at port %d\n",port);
    }
    else {
        printf("connection failed with server %d\n",result);
    }
    

    char name[50];  // Allocate a buffer
    printf("Enter your name: ");
    fgets(name, sizeof(name), stdin);
    char line[1024];
    char buffer[1024];
    while (true) {
        listeningandprintingotherclientsmessagesonnewThread(clientsock);
        printf("Enter Message (type 'exit' to exit):");
        fgets(line, sizeof(line), stdin);
        line[strcspn(line, "\n")] = 0;  // remove trailing newline
        snprintf(buffer, sizeof(buffer), "%s :- %s", name, line);
        if (strcmp(line, "exit") == 0) {
            break;
        }
        int amountsend = send(clientsock, buffer, (int)strlen(buffer), 0);    
    }

     closesocket(clientsock);
    return 0;
}