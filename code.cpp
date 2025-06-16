#include <iostream>
#include <string>
using namespace std;

string xorOperation(string a, string b) {
    string result = "";
    int n = a.length();
    for (int i = 0; i < n; i++) {
        result += (a[i] == b[i]) ? '0' : '1';
    }
    return result;
}

string crcDivision(string data, string polynomial) {
    int polyLength = polynomial.length();
    string rem = data.substr(0, polyLength);
    for (int i = polyLength; i <= data.length(); i++) {
        if (rem[0] == '1')
            rem = xorOperation(rem, polynomial);
        else
            rem = xorOperation(rem, string(polyLength, '0'));
        if (i < data.length())
            rem = rem.substr(1) + data[i];
    }
    return rem;
}

string appendCRC(string data, string polynomial) {
    string paddedData = data + string(polynomial.length() - 1, '0');
    string crc = crcDivision(paddedData, polynomial);
    return data + crc;
}

bool detectError(string receivedData, string polynomial) {
    string rem = crcDivision(receivedData, polynomial);
    return (rem != string(polynomial.length(), '0'));
}

int main() {
    string data, polynomial;

    cout << "Enter the data (binary): ";
    cin >> data;

    cout << "Enter the polynomial (binary): ";
    cin >> polynomial;

    string dataWithCRC = appendCRC(data, polynomial);
    cout << "Data with CRC: " << dataWithCRC << endl;

    cout << "Enter received Data (binary) to check for errors: ";
    string receivedData;
    cin >> receivedData;

    if (!detectError(receivedData, polynomial)) {
        cout << "No error detected" << endl;
    } else {
        cout << "Error detected" << endl;
    }

    return 0;
}