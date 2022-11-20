// 20 July 2022
#include <iostream>
#include <string.h>
#include <vector>
#include <map>
using namespace std;

vector <char> Dictionary={'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
vector <char> DictionaryCaps={'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};


void Encrypt(string &s,int k){
    string temp;

    int n=s.length();
    for (int i=0;i<n;i++){
        if(s[i]>='a' && s[i]<='z' ){
            int val=s[i]-'a';
            temp+=(Dictionary[(val+k)%26]);
        }else if(s[i]>='A' && s[i]<='Z' ){
            int val=s[i]-'A';
            temp+=(DictionaryCaps[(val+k)%26]);
        }else{
            temp+=s[i];
        }
    }
    s=temp;
    // return temp;
}

void Decrypt(string &s,int k){
    string temp;
    int n=s.length();
    for (int i=0;i<n;i++){
        if(s[i]>='a' && s[i]<='z'){
            int val=s[i]-'a';
            val-=k;
            if(val<0)val+=26;
            temp+=(Dictionary[val]);
        }else if(s[i]>='A' && s[i]<='Z' ){
            int val=s[i]-'A';
            val-=k;
            if(val<0)val+=26;
            temp+=(DictionaryCaps[val]);
        }else{
            temp+=s[i];
        }
    }
    s=temp;
    // return temp;
}

int main(){
    string s;
    cout<<"\nEnter your message:";
    fflush(stdin);
    getline(cin,s);
    // cin>>s;
    

    int key;
    cout<<"\nEnter encryption key:";
    cin>>key;
    // cout<<"\n\n";


    vector <char> v;

    

    int choice=-1;

    while(choice!=3){
        cout<<"\n\nMessage Encryption"<<endl;
        cout<<"------------------"<<endl;
        cout<<"1. Encrypt"<<endl;
        cout<<"2. Decrypt"<<endl;
        cout<<"3. Break"<<endl;
        cout<<"------------------"<<endl;
        cout<<"\nEnter your choice: ";
        cin>>choice;

        switch(choice){
        case 1:
            Encrypt(s,key);
            cout<<"Encrypted message is: "<<s<<endl;
            break;
        case 2:
            cout<<"Enter decryption key:"<<endl;
            int key2;
            cin>>key2;
            Decrypt(s,key2);
            cout<<"\nDecrypted message is: "<<s<<endl;
            break;
        case 3:
            cout<<"Terminating Program...\n"<<endl;
            break;
        
        default:
            cout<<"Invalid Choice.\n"<<endl;
            break;
        }
    }

    

    
    return 0;
}
// g++ --std=c++17 -Wall -Wextra ciphers.cpp && ./a.out

// Japan is a country.
// 1

