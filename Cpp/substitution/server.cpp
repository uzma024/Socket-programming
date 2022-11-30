#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
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

        if (strcmp(read_buffer, "Exit") == 0)
        {
            cout << "Closing connection\n\n\n" << endl;
            break;
        }

        int key=2;
        char* decrypted= Decrypt(read_buffer,key);

        cout << "[Client]: " << read_buffer<<endl;
        cout << "[Decrypted]: " << decrypted<<endl;

        cout << "\nEnter the message: ";
        cin.getline(send_buffer, 1024);

        int key2=2;
        char* finalMessage= Encrypt(send_buffer,key2);

        send(newSocket, finalMessage, strlen(finalMessage), 0);
        cout << endl;
    }
    close(newSocket);
    shutdown(nSocket, SHUT_RDWR);
    return 0;
}