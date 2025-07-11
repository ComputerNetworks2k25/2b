#include <iostream>
#include <string>
using namespace std;


string xorOperation(const string& a, const string& b) {
    string result = "";
    for (int i = 0; i < a.length(); i++) {
        result += (a[i] == b[i]) ? '0' : '1';
    }
    return result;
}

string crcDivision(string data, string polynomial) {
    int polyLen = polynomial.length();
    string rem = data.substr(0, polyLen);

    for (int i = polyLen; i < data.length(); i++) {
        if (rem[0] == '1') {
            rem = xorOperation(rem, polynomial);
        } else {
            rem = xorOperation(rem, string(polyLen, '0'));
        }
        rem = rem.substr(1) + data[i];
    }

    if (rem[0] == '1') {
        rem = xorOperation(rem, polynomial);
    } else {
        rem = xorOperation(rem, string(polyLen, '0'));
    }

    return rem.substr(1);  
}

string appendCRC(string data, string polynomial) {
    string paddedData = data + string(polynomial.length() - 1, '0');
    string crc = crcDivision(paddedData, polynomial);
    cout<<"Remainder is "<<crc<<endl;
    return data + crc;
}


bool detectError(string receivedData, string polynomial) {
    string rem = crcDivision(receivedData, polynomial);
    return (rem != string(polynomial.length() - 1, '0'));
}

int main() {
    string data, polynomial;

    cout << "Enter the data (binary): ";
    cin >> data;

    cout << "Enter the polynomial (binary): ";
    cin >> polynomial;

    string dataWithCRC = appendCRC(data, polynomial);
    cout << "Data with CRC (transmitted): " << dataWithCRC << endl;

    string receivedData;
    cout << "Enter received data (binary): ";
    cin >> receivedData;

    if (detectError(receivedData, polynomial)) {
        cout << "Error detected in received data." << endl;
    } else {
        cout << "No error detected in received data." << endl;
    }

    return 0;
}
