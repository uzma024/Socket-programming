// 20 Aug 2022
#include <iostream>
#include <string.h>
using namespace std;

void Encrypt(string &s){
    int key;
    cout<<"\nEnter encryption key:"<<endl;
    cin>>key;

    char box[key][key];
    int i=0;
    for (int j=0;j<key; j++){
        for (int k=0;k<key;k++){
            if(i<s.length()){
                box[j][k]=s[i];
                i++;
            }else{
                box[j][k]='*';
            }
        }
    }

    string ans="";
    for(int j=0;j<key;j++){
        for (int k=0;k<key;k++){
            ans+=box[k][j];
        }
    }
    s=ans;
    return;
}

void Decrypt(string &s){
    cout<<"Enter decryption key" <<endl;
    int key;
    cin>>key;

    char box[key][key];
    int i=0;
    for (int j=0;j<key;j++){
        for (int k=0; k<key;k++){
            if(i<s.length()){
                box[k][j]=s[i];
                i++;
            }else{
                box[k][j]='*';
            }
        }
    }

    string ans="";
    for (int j=0;j<key;j++){
        for (int k=0;k<key;k++){
            if(box[j][k]=='*'){
                continue;
            }else{
                ans+=box[j][k];
            }
        }
    }
    s=ans;
    return;
}

int main(){

    string s;
    cout<<"Enter your message(without space & special chars) : "<<endl;
    cin>>s;
    int choice=-1;

    while (choice!=3){
        cout<<"Menue:"<<endl;
        cout<<"------------------"<<endl;
        cout<<"1. Encrypt."<<endl;
        cout<<"2. Decrypt"<<endl;
        cout<<"3. Break"<<endl;
        cout<<"------------------\n"<<endl;

        cout<<"Enter your choice: ";
        cin>>choice;

        switch(choice){
            case 1:
                Encrypt(s);
                cout<<"Encrypted message is: "<<s<<endl;
                break;
            case 2:
                Decrypt(s);
                cout<<"Decrypted message is: "<<s<<endl;
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
// g++ --std=c++17 -Wall -Wextra transposition.cpp && ./a.out