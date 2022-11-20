#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

using namespace std;
#define port 8080

char* encrypt(char* m,char* keyword){
    int n=strlen(m);

    string key="";
    while(key.length()<n){
        key+=keyword;
    }
    key=key.substr(0,n);

    char *ans = (char*)malloc(sizeof(char) * (n + 1));

    for(int i=0;i<n;i++){
        if(m[i]==' '){
            ans[i]=m[i];
        }else if(m[i]>='a' && m[i]<='z'){
            ans[i]='a' + ((key[i]-'a') + (m[i]-'a'))%26;
        }else{
            ans[i]='a' + ((key[i]-'a') + (m[i]-'A'))%26;
        }
    }
    // cout<<"Ans "<<ans<<endl;
    return ans;
}

char* decrypt(char*m,char*keyword){
    int n=strlen(m);

    string key="";
    while(key.length()<n){
        key+=keyword;
    }
    key=key.substr(0,n);

    char *ans = (char*)malloc(sizeof(char) * (n + 1));

    for(int i=0;i<n;i++){
        if(m[i]==' '){
            ans[i]=m[i];
        }else if(m[i]>='a' && m[i]<='z'){
            ans[i]= 'a'+ ((m[i]-'a') - (key[i]-'a') +26)%26;
        }else{
            ans[i]= 'a'+ ((m[i]-'a') - (key[i]-'a') +26)%26;
        }
    }
    // cout<<"Ans "<<ans<<endl;
    return ans;
}


int main()
{
    cout<<"\n******************************************\n";
    cout<<"* Welcome to the Server Side of the Chat *";
    cout<<"\n******************************************\n";

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
    if (setsockopt(nSocket, SOL_SOCKET, SO_REUSEADDR , &opt, sizeof(opt)))
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

        // time_t t1 = time(NULL);
        // char *receivalTime = substr(ctime(&t1), 11, 19);
        // char *clientSentTime = substr(read_buffer, 0, 8);

        // char *receivedMessage = substr(read_buffer, 8, strlen(read_buffer));
        if (strcmp(read_buffer, "Exit") == 0)
        {
            cout << "Closing connection\n\n\n" << endl;
            break;
        }

        char* keyword="key";
        char* decrypted= decrypt(read_buffer,keyword);

        cout << "[Client]: " << read_buffer<<endl;
        cout << "[Decrypted]: " << decrypted<<endl;

        cout << "\nEnter the message: ";
        cin.getline(send_buffer, 1024);

        // char* keyword2="laz";
        char* finalMessage= encrypt(send_buffer,keyword);

        send(newSocket, finalMessage, strlen(finalMessage), 0);
        cout << endl;
    }
    close(newSocket);
    shutdown(nSocket, SHUT_RDWR);
    return 0;
}