#include <iostream>
#include <string>
#include <cmath>
using namespace std;

string decToBin(int n) {
    string bin = "";
    for (int i = 7; i >= 0; i--) {
        bin += ((n >> i) & 1) ? '1' : '0';
    }
    return bin;
}

int binToDec(string bin) {
    int val = 0;
    for (int i = 0; i < 8; i++) {
        val = val * 2 + (bin[i] - '0');
    }
    return val;
}

void splitIP(string ipStr, int arr[4]) {
    string part = "";
    int j = 0;
    for (int i = 0; i <= ipStr.size(); i++) {
        if (ipStr[i] == '.' || i == ipStr.size()) {
            arr[j++] = stoi(part);
            part = "";
        } else {
            part += ipStr[i];
        }
    }
}

void printIP(int arr[4]) {
    cout << arr[0] << "." << arr[1] << "." << arr[2] << "." << arr[3];
}

int countBits(int mask[4]) {
    int bits = 0;
    bool stop = false;
    for (int i = 0; i < 4 && !stop; i++) {
        string bin = decToBin(mask[i]);
        for (char c : bin) {
            if (c == '1' && !stop) {
                bits++;
            } else {
                stop = true;
                break;
            }
        }
    }
    return bits;
}

int main() {
    string ipStr, maskStr;
    int ip[4], mask[4], net[4], broad[4];
    int first[4], last[4];

    cout << "Enter IP Address:- ";
    cin >> ipStr;
    cout << "Enter Subnet Mask:- ";
    cin >> maskStr;

    splitIP(ipStr, ip);
    splitIP(maskStr, mask);

    for (int i = 0; i < 4; i++) {
        net[i] = ip[i] & mask[i];
    }

    for (int i = 0; i < 4; i++) {
        broad[i] = net[i] | (~mask[i] & 255);
    }

    for (int i = 0; i < 4; i++) {
        first[i] = net[i];
        last[i] = broad[i];
    }
    first[3] += 1;
    last[3] -= 1;

    int subnetBits = countBits(mask);
    int hostBits = 32 - subnetBits;
    int hostsPerSubnet = pow(2, hostBits) - 2;
    int numberOfSubnets = pow(2, subnetBits);

    cout << "\nNetwork ID: ";
    printIP(net);

    cout << "\nBroadcast Address: ";
    printIP(broad);

    cout << "\nHost Range: ";
    printIP(first);
    cout << " - ";
    printIP(last);

    cout << "\nNumber of Subnet Bits: " << subnetBits;
    cout << "\nNumber of Host Bits: " << hostBits;
    cout << "\nNumber of Hosts per Subnet: " << hostsPerSubnet;
    cout << "\nNumber of Subnets possible: " << numberOfSubnets;

    cout << endl;
    return 0;
}
