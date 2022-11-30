#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <regex>
using namespace std;
#define port 8080

void datatype(char* s){
    string ans="";
    if(regex_match(s,regex("[a-zA-Z_0-9]"))){
        ans="Alphanumeric";
    }
    else if(regex_match(s,regex("[0-9]+.[0-9]+"))){
        ans="Float";
    }
    else if(regex_match(s,regex("[0-9]+"))){
        ans="Integer";
    }
    else{
        ans="Unknown";
    }
   cout<<ans;
}


int main()
{
    cout << "\n******************************************\n";
    cout << "* Welcome to the Server Side of the Chat *";
    cout << "\n******************************************\n";
    struct sockaddr_in srv;
    int nSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (nSocket < 0)
    {
        cout << "Error in creating socket" << endl;
        return 0;
    }
    cout << "Socket created" << endl;
    // Forcefully attaching socket to the port 8080
    int opt = 1;
    if (setsockopt(nSocket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    srv.sin_family = AF_INET;
    srv.sin_port = htons(port);
    srv.sin_addr.s_addr = INADDR_ANY;
    int nRet = ::bind(nSocket, (struct sockaddr *)&srv, sizeof(srv));
    // cout<<"Bind: "<<nRet<<endl;
    if (nRet < 0)
    {
        cout << "Error in binding" << endl;
        return 0;
    }
    cout << "Binded Successfully" << endl;
    nRet = listen(nSocket, 3);
    if (nRet < 0)
    {
        cout << "Error in listening" << endl;
        return 0;
    }
    cout << "Listening" << endl;
    int nLen = sizeof(srv);
    int newSocket = accept(nSocket, (struct sockaddr *)&srv, (socklen_t *)&nLen);
    if (newSocket < 0)
    {
        cout << "Error in accepting" << endl;
        return 0;
    }
    cout << "Accepted" << endl;
    while (1)
    {
        char read_buffer[1024] = {0};
        char send_buffer[1024] = {0};
        if (read(newSocket, read_buffer, 1024) < 0)
        {
            cout << "Error in reading" << endl;
            return 0;
        }
        
        if (strcmp(read_buffer, "Exit") == 0)
        {
            cout << "Closing connection\n\n\n"
                 << endl;
            break;
        }
        cout << "[Client]: " << read_buffer << endl;
        datatype(read_buffer);
        
        // cout << "\nEnter the message: ";
        // cin.getline(send_buffer, 1024);
        
        // send(newSocket, send_buffer, strlen(send_buffer), 0);
        // cout << endl;
    }
    close(newSocket);
    shutdown(nSocket, SHUT_RDWR);
    return 0;
}
// g++ --std=c++17 -Wall -Wextra server.cpp && ./a.out