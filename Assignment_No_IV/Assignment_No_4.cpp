#include <iostream>
#include <cmath>
using namespace std;

int main() {
    int ipClass, subnetBits;

    cout << "Subnetting Demonstration\n";
    cout << "Enter IP Class (A=1, B=2, C=3): ";
    cin >> ipClass;

    cout << "Enter number of bits borrowed for subnetting: ";
    cin >> subnetBits;

    int defaultMaskBits = 0;
    if (ipClass == 1) defaultMaskBits = 8;  
    else if (ipClass == 2) defaultMaskBits = 16; 
    else if (ipClass == 3) defaultMaskBits = 24; 
    else {
        cout << "Invalid IP class!" << endl;
        return 0;
    }

    int newMaskBits = defaultMaskBits + subnetBits;
    int totalSubnets = pow(2, subnetBits);
    int hostBits = 32 - newMaskBits;
    int hostsPerSubnet = pow(2, hostBits) - 2;

    cout << "\nResults:\n";
    cout << "Default Mask Bits: " << defaultMaskBits << endl;
    cout << "New Subnet Mask Bits: " << newMaskBits << endl;
    cout << "Number of Subnets: " << totalSubnets << endl;
    cout << "Hosts per Subnet: " << hostsPerSubnet << endl;

    // Display subnet mask in dotted decimal form
    unsigned long mask = 0xFFFFFFFF << (32 - newMaskBits);
    cout << "Subnet Mask: ";
    for (int i = 3; i >= 0; i--) {
        cout << ((mask >> (i * 8)) & 0xFF);
        if (i != 0) cout << ".";
    }
    cout << endl;

    return 0;
}
