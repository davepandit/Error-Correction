#include <bits/stdc++.h>
using namespace std;

int main(){
    string crc, encoded;
    cout << "Enter the message: ";
    getline(cin, encoded);
    
    cout << "Message is: " << encoded << endl;

    cout << "Enter the polynomial: ";
    getline(cin, crc);

    cout << "Polynomial is: " << crc << endl;

    for(int i = 0; i <= encoded.length() - crc.length(); ){
        for(int j = 0; j < crc.length(); j++){
            encoded[i + j] = encoded[i + j] == crc[j] ? '0' : '1';
        }
        for(; i < encoded.length() && encoded[i] != '1'; i++);
    }

    for(char i : encoded.substr(encoded.length() - crc.length() + 1)){
        if(i != '0'){
            cout <<"Error";
            return 0;
        }
    }
    cout<< "passed";

    return 0;
}