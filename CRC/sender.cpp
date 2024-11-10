#include <bits/stdc++.h>
using namespace std;

int main() {
    string msg, crc, encoded;
    
    cout << "Enter the message: ";
    getline(cin, msg);
    
    // Print the message to check
    cout << "Message is: " << msg << endl;
    
    // Fix the input buffer issue before taking the next line input
    cout << "Enter the polynomial: ";
    getline(cin, crc);
    
    // Print the polynomial to check
    cout << "Polynomial is: " << crc << endl;

    int m = msg.length(), n = crc.length();
    encoded += msg;
    //add some zeroes to the encoded msg
    for(int i = 1; i <= n-1; i++){
        encoded += '0';
    }
    //perform the xor operation 
    for(int i = 0; i <= encoded.length() - n;){
        for(int j = 0; j < n; j++){
            encoded[i + j] = encoded[i + j] == crc[j] ? '0' : '1';
        }
        //check only when i == 1
        for(; i < encoded.length() && encoded[i] != '1'; i++);
    }
    cout << "The transferrable msg is: "<<msg + encoded.substr(encoded.length() - n + 1);    
    return 0;
}
