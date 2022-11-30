#include <iostream>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <vector>

using namespace std;
#define port 8080

vector <char> Dictionary={'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
vector <char> DictionaryCaps={'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};



char* Encrypt(char* s,int k){
    int n=strlen(s);
    // cout<<"n: "<<n<<endl;

    char *ans = (char*)malloc(sizeof(char) * (n + 1));

    for (int i=0;i<n;i++){
        if(s[i]>='a' && s[i]<='z' ){
            int val=s[i]-'a';
            ans[i]=(Dictionary[(val+k)%26]);
        }else if(s[i]>='A' && s[i]<='Z' ){
            int val=s[i]-'A';
            ans[i]=(DictionaryCaps[(val+k)%26]);
        }else{
            ans[i]=s[i];
        }
    }
    // cout<<"Ans "<<ans<<endl;
    return ans;
}

char* Decrypt(char*s,int k){
    int n=strlen(s);
    char *ans = (char*)malloc(sizeof(char) * (n + 1));

    for (int i=0;i<n;i++){
        if(s[i]>='a' && s[i]<='z'){
            int val=s[i]-'a';
            val-=k;
            if(val<0)val+=26;
            ans[i]=(Dictionary[val]);
        }else if(s[i]>='A' && s[i]<='Z' ){
            int val=s[i]-'A';
            val-=k;
            if(val<0)val+=26;
            ans[i]=(DictionaryCaps[val]);
        }else{
            ans[i]=s[i];
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

        int key=2;
        char* finalMessage = Encrypt(send_buffer,key);

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

        int key2=2;
        char* decrypted= Decrypt(read_buffer,key2);

        cout << "\n[Server]: " << read_buffer<<endl;
        cout << "[Decrypted]: " << decrypted<<endl;

    }
    close(nSocket);
    return 0;
}
// g++ --std=c++17 -Wall -Wextra client.cpp && ./a.out
// g++ --std=c++17 -Wall -Wextra server.cpp && ./a.out