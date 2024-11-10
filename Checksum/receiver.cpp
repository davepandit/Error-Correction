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

// Function to verify the checksum at the receiver side
bool verifyChecksum(string receivedData, string checksum, int segmentSize) {
    // Append the received checksum to the data
    string totalData = receivedData + checksum;

    // Calculate the checksum of the total data
    string calculatedChecksum = calculateChecksum(totalData, segmentSize);

    // A valid checksum will result in "1111111111111111"
    return calculatedChecksum == string(segmentSize, '1');
}

int main() {
    string data, receivedChecksum;
    int segmentSize = 16; // Segment size of 16 bits

    // Input the message and checksum from the sender
    cout << "Enter the received binary message: ";
    cin >> data;

    cout << "Enter the received checksum: ";
    cin >> receivedChecksum;

    // At Receiver Side: Verify the checksum
    bool isValid = verifyChecksum(data, receivedChecksum, segmentSize);

    if (isValid) {
        cout << "No error detected. The message is valid." << endl;
    } else {
        cout << "Error detected in the received message." << endl;
    }

    return 0;
}
