#include <bits/stdc++.h>
using namespace std;

// Function to calculate the checksum
string calculateChecksum(string data, int segmentSize) {
    int n = data.length();
    unsigned int sum = 0;
    
    // Ensure data length is multiple of segment size
    while (n % segmentSize != 0) {
        data += "0";  // Pad with zeros if necessary
        n++;
    }
    
    // Process data in segments of size `segmentSize`
    for (int i = 0; i < n; i += segmentSize) {
        string segment = data.substr(i, segmentSize);
        
        // Convert the binary segment to integer
        unsigned int segmentValue = stoul(segment, nullptr, 2);
        sum += segmentValue;
        
        // Handle carry properly
        while (sum >= (1u << segmentSize)) {
            sum = (sum & ((1u << segmentSize) - 1)) + (sum >> segmentSize);
        }
    }
    
    // Calculate the 1's complement of the sum
    sum = ((1u << segmentSize) - 1) - sum;
    
    // Convert to binary string of proper length
    string checksum = bitset<16>(sum).to_string();
    return checksum.substr(16 - segmentSize);  // Return only the required bits
}

int main() {
    string data;
    int segmentSize = 16;
    
    cout << "Enter the binary message to be sent: ";
    cin >> data;
    
    // Validate input
    for (char c : data) {
        if (c != '0' && c != '1') {
            cout << "Error: Input must be binary (0s and 1s only)" << endl;
            return 1;
        }
    }
    
    // Calculate checksum
    string checksum = calculateChecksum(data, segmentSize);
    
    // Output results
    cout << "Calculated Checksum: " << checksum << endl;
    cout << "Data to send: " << data << endl;
    cout << "Checksum to send: " << checksum << endl;
    
    return 0;
}