#include <iostream>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
using namespace std;
#define port 8080

int main()
{
    cout << "\n******************************************\n";
    cout << "  * Welcome to the Client Side of the Chat *";
    cout << "\n******************************************\n";
    int nSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (nSocket < 0)
    {
        cout << "Error in creating socket" << endl;
        return 0;
    }
    struct sockaddr_in srv;
    srv.sin_family = AF_INET;
    srv.sin_port = htons(port);
    if (inet_pton(AF_INET, "127.0.0.1", &srv.sin_addr) <= 0)
    {
        cout << "Invalid Address" << endl;
        return 0;
    }
    int clientSocket = connect(nSocket, (struct sockaddr *)&srv, sizeof(srv));
    if (clientSocket < 0)
    {
        cout << "Error in connecting" << endl;
        return 0;
    }
    while (1)
    {
        char read_buffer[1024] = {0};
        char send_buffer[1024] = {0};
        cout << "\nEnter the message: ";

        cin.getline(send_buffer, 1024);
        
        send(nSocket, send_buffer, strlen(send_buffer), 0);
        if (strcmp(send_buffer, "Exit") == 0)
        {
            cout << "\nExiting\n\n\n"
                 << endl;
            break;
        }

        read(nSocket, read_buffer, 1024);
        
        if (strcmp(read_buffer, "Exit") == 0)
        {
            cout << "Closing connection\n\n\n"
                 << endl;
            break;
        }
        cout << "\n[Server]: " << read_buffer << endl;
    }
    close(nSocket);
    return 0;
}
// g++ --std=c++17 -Wall -Wextra client.cpp && ./a.out