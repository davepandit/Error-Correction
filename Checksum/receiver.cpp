#include <bits/stdc++.h>
using namespace std;

string calculateChecksum(string data, int segmentSize) {
    int n = data.length();
    unsigned int sum = 0;
    
    // Ensure data length is multiple of segment size
    while (n % segmentSize != 0) {
        data += "0";
        n++;
    }
    
    for (int i = 0; i < n; i += segmentSize) {
        string segment = data.substr(i, segmentSize);
        unsigned int segmentValue = stoul(segment, nullptr, 2);
        sum += segmentValue;
        
        while (sum >= (1u << segmentSize)) {
            sum = (sum & ((1u << segmentSize) - 1)) + (sum >> segmentSize);
        }
    }
    
    sum = ((1u << segmentSize) - 1) - sum;
    string checksum = bitset<16>(sum).to_string();
    return checksum.substr(16 - segmentSize);
}

bool verifyChecksum(string receivedData, string receivedChecksum, int segmentSize) {
    // Combine received data and checksum
    string totalData = receivedData + receivedChecksum;
    
    int n = totalData.length();
    unsigned int sum = 0;
    
    // Process all segments including the checksum
    for (int i = 0; i < n; i += segmentSize) {
        string segment = totalData.substr(i, segmentSize);
        unsigned int segmentValue = stoul(segment, nullptr, 2);
        sum += segmentValue;
        
        while (sum >= (1u << segmentSize)) {
            sum = (sum & ((1u << segmentSize) - 1)) + (sum >> segmentSize);
        }
    }
    
    // The sum should be all 1's if no error
    return sum == ((1u << segmentSize) - 1);
}

int main() {
    string data, receivedChecksum;
    int segmentSize = 16;
    
    cout << "Enter the received binary message: ";
    cin >> data;
    cout << "Enter the received checksum: ";
    cin >> receivedChecksum;
    
    // Validate input
    for (char c : data) {
        if (c != '0' && c != '1') {
            cout << "Error: Message must be binary (0s and 1s only)" << endl;
            return 1;
        }
    }
    for (char c : receivedChecksum) {
        if (c != '0' && c != '1') {
            cout << "Error: Checksum must be binary (0s and 1s only)" << endl;
            return 1;
        }
    }
    
    if (receivedChecksum.length() != segmentSize) {
        cout << "Error: Checksum must be " << segmentSize << " bits long" << endl;
        return 1;
    }
    
    // Debug information
    cout << "\nDebug Information:" << endl;
    cout << "Message Length: " << data.length() << " bits" << endl;
    cout << "Checksum Length: " << receivedChecksum.length() << " bits" << endl;
    
    // Verify checksum
    bool isValid = verifyChecksum(data, receivedChecksum, segmentSize);
    
    if (isValid) {
        cout << "No error detected. The message is valid." << endl;
    } else {
        cout << "Error detected in the received message." << endl;
    }
    
    return 0;
}