#include <iostream>
#include <map>
#include <string>
using namespace std;

void Encrypt(string &s,map<char, string>New_Map){
    string ans="";
    for(int i=0;i<s.length();i++){
        char c=s[i];
        if(c>='a' && c<='z'){
            c = (s[i] - 'a' + 'A');
        }
        ans+=New_Map[c];
    }
    s=ans;
}

void Decrypt(string &s,map<char, string>New_Map){
    string ans="";
    for(int i=0;i<s.length()-4;i+=5){
        string temp=s.substr(i,5);
        for(auto x:New_Map){
            if(x.second==temp){
                ans+=x.first;
                break;
            }
        }
    }
    s=ans;
}

 

int main(){

    map<char, string>New_Map;
    New_Map={
        {'A', "aaaaa"}, {'B', "aaaab"}, {'C', "aaaba"}, {'D', "aaabb"}, {'E', "aabaa"},
        {'F', "aabab"}, {'G', "aabba"}, {'H', "aabbb"}, {'I', "abaaa"}, {'J', "abaab"},
        {'K', "ababa"}, {'L', "ababb"}, {'M', "abbaa"}, {'N', "abbab"}, {'O', "abbba"},
        {'P', "abbbb"}, {'Q', "baaaa"}, {'R', "baaab"}, {'S', "baaba"}, {'T', "baabb"},
        {'U', "babaa"}, {'V', "babab"}, {'W', "babba"}, {'X', "babbb"}, {'Y', "bbaaa"}, {'Z', "bbaab"}};

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
                Encrypt(s,New_Map);
                cout<<"Encrypted message is: "<<s<<endl;
                break;
            case 2:
                Decrypt(s,New_Map);
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
// g++ --std=c++17 -Wall -Wextra Baconian.cpp && ./a.out