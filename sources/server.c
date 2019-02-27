#include "game.h"

int read_client(int client)
{
    int n;
    char buffer[256];

    if (client == -1) {
        return -1;
    }

    n = 0;
    memset(buffer, '\0', 256);
    while ((n = recv(client, buffer, 256, 0)) >= 0)
    {
        if (n == 0) {
            return -1;
        }

        printf("received %s", buffer);

        if (buffer[n - 1] == '\n') {
            memset(buffer, '\0', 256);
            break;
        }
    }
    return 0;
}

int server_launch(void)
{
    int serverSocket;
    int client1;
    int client2;
    socklen_t clientAddrLen;
    struct sockaddr_in serverAddr;
    struct sockaddr_in clientAddr;

    // Create server socket
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        perror("Socket()");
        return 1;
    }

    // Define serverAddr
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(SERVER_PORT);
    memset(&(serverAddr.sin_zero), '\0', 8); // zero the rest of the struct

    // Launch server
    if (bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(struct sockaddr)) < 0) {
        perror("Bind()");
        return 1;
    }
    
    // Listen to network for clients
    if (listen(serverSocket, BACKLOG) < 0) {
        perror("Listen()");
        return 1;
    }

    // Accept clients connexion X times
    puts("Waiting clients to connect...");
    client1 = accept(serverSocket, (struct sockaddr *)&clientAddr, &clientAddrLen);
    client2 = accept(serverSocket, (struct sockaddr *)&clientAddr, &clientAddrLen);

    if (client1 < 0 || client2 < 0) {
        perror("Accept()");
        return 1;
    }
    puts("Clients connected");

    // Declaring variable for the select()
    fd_set readfs;
    struct timeval timeout;
    // Select loop
    while (1)
    {
        timeout.tv_sec = 1; // seconds
        timeout.tv_usec = 0; // microseconds

        FD_ZERO(&readfs); // clears a file descriptor set

        FD_SET(client1, &readfs); // adds fd to the set
        FD_SET(client2, &readfs);

        select(client2 + 1, &readfs, NULL, NULL, &timeout);

        if (FD_ISSET(client1, &readfs)) { // tests to see if fd is in the set
            if (read_client(client1) == -1) {
                puts("Client 1 disconnected");
                close(client1);
                client1 = -1;
            }
        } else if (FD_ISSET(client2, &readfs)) {
            if (read_client(client2) == -1) {
                puts("Client 2 disconnected");
                close(client2);
                client2 = -1;
            }
        }

        // Close server if all clients are deconnected
        if (client1 == -1 && client2 == -1) {
            break;
        }
    }
    close(serverSocket);
    return 0;
}