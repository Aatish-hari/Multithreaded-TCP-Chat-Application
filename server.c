#include"utils.h"


int main(){
    WSADATA wsa;
    WSAStartup(MAKEWORD(2,2), &wsa); // Initialize Winsock 

    int serverport = 2000;
    char* serverip = "";
    SOCKET serversock = creatingTCPIPv4socket();
    struct sockaddr_in* serveraddress = creatingIPv4address(serverip , serverport);
    int bindingresult = bind(serversock , (struct sockaddr*)serveraddress ,sizeof(*serveraddress) );

    if(bindingresult == 0){
        printf("server socket bind successfull\n");
    }
    else{
        printf("Failed binding %d\n" , bindingresult);
    }

    int listeningresult = listen(serversock , 10);

    if(listeningresult == 0 ){
        printf("server is listening at port %d" , serverport);
    }
    else {
        printf("server failing to listen at port %d, \n" , serverport);
    }


    startacceptingIncomingconnections(serversock);

    shutdown(serversock,SD_BOTH);
    return 0;
}


