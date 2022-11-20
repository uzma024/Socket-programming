// 16 Nov 2022
#include <iostream>
#include <string.h>
#include <vector>
using namespace std;

vector <vector <char>> createMatrix(string s){

    // Creating matrix for encryption
    vector <vector <char>> matrix(5, vector<char>(5,0));
    vector <int> v(26,0);

    int r=0,c=0;
    for(int i=0;i<s.length();i++){
        if(s[i]==' ')continue;
        if(s[i]<='A' && s[i]>='Z'){
            s[i]='a'+(s[i]-'A');
        }

        matrix[r][c]=s[i];
        c++;
        if(c==5){
            r++;
            c=0;
        }
        v[s[i]-'a']=1;
    }

    v[9]=1; //ignoring j

    int i=0;
    while(r<5){
        while(c<5){
            while(i<26 && v[i]==1){
                i++;
            }
            if(i<26){
                v[i]=1;
                matrix[r][c]='a'+i;
                c++;
            }
        }
        c=0;
        r++;
    }

    // for(int i=0;i<5;i++){
    //     for(int j=0;j<5;j++){
    //         cout<<matrix[i][j]<<" ";
    //     }
    //     cout<<endl;
    // }

    return matrix;
}

string encryption(vector <vector <char>> matrix, string plainText){
    // playFair encryption

    if(plainText.length()%2==1){
        plainText+='x';
    }
    for(int i=0;i<plainText.length()-1;i+=2){
        if(plainText[i]=='j'){
            plainText[i]='i';
        }
        if(plainText[i+1]=='j'){
            plainText[i+1]='i';
        }
        if(plainText[i]==plainText[i+1]){
            plainText[i+1]='x';
        }
    }


    cout<<plainText<<endl;
    string encrypted="";
    
    for(int i=0;i<plainText.length();i+=2){
        int first[2],second[2];
        for(int r=0;r<5;r++){
            for(int c=0;c<5;c++){
                if(matrix[r][c]==plainText[i]){
                    first[0]=r;
                    first[1]=c;
                }
                if(matrix[r][c]==plainText[i+1]){
                    second[0]=r;
                    second[1]=c;
                }
            }
        }

        if(first[0]==second[0]){
            int x=first[0];
            int y=(first[1]+1)%5;
            encrypted+=(matrix[x][y]);
            y=(second[1]+1)%5;
            encrypted+=(matrix[x][y]);
        }else if(first[1]==second[1]){
            int y=first[1];
            int x=(first[0]+1)%5;
            encrypted+=(matrix[x][y]);
            x=(second[0]+1)%5;
            encrypted+=(matrix[x][y]);
        }else{
        // row remains same, column swaps
            encrypted+=matrix[first[0]][second[1]];
            encrypted+=matrix[second[0]][first[1]];
        }

    }
    return encrypted;
}


string decryption(vector <vector <char>> matrix, string encrypted){
    // Decrypting

    if(encrypted.length()%2==1){
        cout<<"Wrong message...\n encrypted message size cannot be odd\n\n";
    }

    // cout<<encrypted<<endl;
    string decrypted="";
    
    for(int i=0;i<encrypted.length();i+=2){
        int first[2],second[2];
        for(int r=0;r<5;r++){
            for(int c=0;c<5;c++){
                if(matrix[r][c]==encrypted[i]){
                    first[0]=r;
                    first[1]=c;
                }
                if(matrix[r][c]==encrypted[i+1]){
                    second[0]=r;
                    second[1]=c;
                }
            }
        }

        if(first[0]==second[0]){
            int x=first[0];
            int y=(first[1]-1+5)%5;
            decrypted+=(matrix[x][y]);
            y=(second[1]-1+5)%5;
            decrypted+=(matrix[x][y]);
        }else if(first[1]==second[1]){
            int y=first[1];
            int x=(first[0]-1+5)%5;
            decrypted+=(matrix[x][y]);
            x=(second[0]-1+5)%5;
            decrypted+=(matrix[x][y]);
        }else{
        // row remains same, column swaps
            decrypted+=matrix[first[0]][second[1]];
            decrypted+=matrix[second[0]][first[1]];
        }
    }
    return decrypted;
}

int main(){
    char matrix [5][5];

    cout<<"Enter key: ";
    string s;
    cin>>s;

    cout<<"Enter plainText: ";
    string plainText;
    cin>>plainText;

    
    string encrypted=(encryption(createMatrix(s),plainText));
    cout<<"\nEncrypted message is: "<<encrypted<<endl;
    
    string decrypted=(decryption(createMatrix(s),encrypted));
    cout<<"\nDecrypted message is: "<<decrypted<<"\n\n";

    return 0;
}
// g++ --std=c++17 -Wall -Wextra playcipher.cpp && ./a.out