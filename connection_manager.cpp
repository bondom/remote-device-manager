#include "connection_manager.h"
#include <stdio.h>

ConnectionManager::ConnectionManager() {
    SendSocket = INVALID_SOCKET;
    connectionOpened = false;
}

int ConnectionManager::openClientSocket(unsigned short port) {
    WSADATA wsaData;

    //----------------------
    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        wprintf(L"WSAStartup failed with error: %d\n", iResult);
        return 1;
    }

    //---------------------------------------------
    // Create a socket for sending data
    SendSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (SendSocket == INVALID_SOCKET) {
        wprintf(L"socket failed with error: %ld\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }

    ReceiverAddr.sin_family = AF_INET;
    ReceiverAddr.sin_port = htons(port);
    ReceiverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    connectionOpened = true;
    return 0;
};

int ConnectionManager::sendData(const char text[]) {
    wprintf(L"Sending a datagram to the receiver...\n");
    iResult = sendto(
            SendSocket,
            text,
            strlen(text),
            0,
            (SOCKADDR *) & ReceiverAddr, sizeof
            (ReceiverAddr));
    if (iResult == SOCKET_ERROR) {
        wprintf(L"sendto failed with error: %d\n", WSAGetLastError());
        closesocket(SendSocket);
        WSACleanup();
        return 1;
    }
}

int ConnectionManager::closeSocket() {
    //---------------------------------------------
    // When the application is finished sending, close the socket.
    wprintf(L"Finished sending. Closing socket.\n");
    iResult = closesocket(SendSocket);
    if (iResult == SOCKET_ERROR) {
        wprintf(L"closesocket failed with error: %d\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }
    //---------------------------------------------
    // Clean up and quit.
    wprintf(L"Exiting.\n");
    WSACleanup();
    connectionOpened = false;
    return 0;
}

bool ConnectionManager::isConnectionOpened() {
    return this->connectionOpened;
}
