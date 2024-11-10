#include <bits/stdc++.h>
using namespace std;

// Function to calculate the checksum
string calculateChecksum(string data, int segmentSize) {
    int n = data.length();
    int sum = 0;

    // Process data in segments of size `segmentSize`
    for (int i = 0; i < n; i += segmentSize) {
        string segment = data.substr(i, segmentSize);
        
        // Convert the binary segment to integer
        int segmentValue = stoi(segment, nullptr, 2);
        sum += segmentValue;

        // If there is a carry, wrap it around
        if (sum > (1 << segmentSize) - 1) {
            sum = (sum & ((1 << segmentSize) - 1)) + 1;
        }
    }

    // Calculate the 1's complement of the sum
    sum = ~sum & ((1 << segmentSize) - 1);
    string checksum = bitset<16>(sum).to_string();
    return checksum;
}

int main() {
    string data, checksum;
    int segmentSize = 16; // Segment size of 16 bits

    // Input the message from the sender
    cout << "Enter the binary message to be sent: ";
    cin >> data;

    // Calculate checksum
    checksum = calculateChecksum(data, segmentSize);

    // Output checksum
    cout << "Calculated Checksum: " << checksum << endl;

    // Simulate sending data (data + checksum)
    cout << "Data to send: " << data << endl;
    cout << "Checksum to send: " << checksum << endl;

    return 0;
}
