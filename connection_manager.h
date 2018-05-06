#ifndef CONNECTION_MANAGER_H
#define CONNECTION_MANAGER_H


#include <winsock2.h>

class ConnectionManager {

private:
    SOCKET  SendSocket;
    SOCKADDR_IN ReceiverAddr;
    bool connectionOpened;
    int iResult;
public:
    ConnectionManager();
    int openClientSocket(unsigned short port);
    int sendData(const char text[]);
    int closeSocket();
    bool isConnectionOpened();
};

#endif // CONNECTION_MANAGER_H
