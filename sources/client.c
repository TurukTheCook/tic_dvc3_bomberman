#include "game.h"

int client_connect(void)
{
    int serverSocket;
    struct sockaddr_in serverAddr;
    char message[256];

    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        perror("socket()");
        exit(errno);
    }

    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(SERVER_PORT);
    memset(&(serverAddr.sin_zero), '\0', 8); // zero the rest of the struct

    if (connect(serverSocket, (struct sockaddr *)&serverAddr, sizeof(struct sockaddr)) < 0) {
        perror("connect()");
        exit(errno);
    }

    while (1)
    {
        memset(message, '\0', 256);
        fgets(message, 256, stdin);
        if (send(serverSocket, message, strlen(message), MSG_NOSIGNAL) < 0) {
            puts("Send failed");
            close(serverSocket);
            return 1;
        }
        printf("Sended %s\n", message);
    }

    close(serverSocket);
    return 0;
}