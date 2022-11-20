#include <iostream>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

using namespace std;
#define port 8080

// vector <string> mat;
// string alpha="abcdefghijklmnopqrstuvwxyz"

// void fill(){
//     for(int i=0;i<26;i++){
//         string s1=
//     }
// }



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
    cout<<"* Welcome to the Client Side of the Chat *";
    cout<<"\n******************************************\n";
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

        char* keyword="key";

        char* finalMessage = encrypt(send_buffer,keyword);

        // printf("original: %s\nEncrypted: %s \n",send_buffer,finalMessage);
        cout << "[Encrypted]: " << finalMessage<<endl;
        send(nSocket, finalMessage, strlen(finalMessage), 0);
        if (strcmp(send_buffer, "Exit") == 0)
        {
            cout << "\nExiting\n\n\n" << endl;
            break;
        }

        read(nSocket, read_buffer, 1024);
        // time_t t1 = time(NULL);
        // char *receivalTime = substr(ctime(&t1), 11, 19);
        // char *servertSentTime = substr(read_buffer, 0, 8);

        // char *receivedMessage = substr(read_buffer, 8, strlen(read_buffer));
        if (strcmp(read_buffer, "Exit") == 0)
        {
            cout << "Closing connection\n\n\n" << endl;
            break;
        }
        //  char* keyword2="laz";
        char* decrypted= decrypt(read_buffer,keyword);

        cout << "\n[Server]: " << read_buffer<<endl;
        cout << "[Decrypted]: " << decrypted<<endl;

        // cout << "\n[Server]: " << read_buffer<<endl;
        // cout << "[Sent at]: " << servertSentTime<<endl;
        // cout << "[Received at]: " << receivalTime << endl;
        cout << endl;
    }
    close(nSocket);
    return 0;
}
// g++ --std=c++17 -Wall -Wextra client.cpp && ./a.out
// g++ --std=c++17 -Wall -Wextra server.cpp && ./a.out