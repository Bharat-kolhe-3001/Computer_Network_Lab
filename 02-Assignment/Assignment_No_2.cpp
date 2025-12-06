#include <iostream>
using namespace std;

int main() {
    int data[4];    
    int code[7];      
 
    //Enter 4 Bit 
    cout << "Enter 4-bit data (from left to right):\n";
    for (int i = 0; i < 4; i++) {
        cout << "Enter bit " << i + 1 << ": "; 
        cin >> data[i];
    }

    
    code[2] = data[0];  
    code[4] = data[1];  
    code[5] = data[2]; 
    code[6] = data[3];  

    
    code[0] = code[2] ^ code[4] ^ code[6]; 
    code[1] = code[2] ^ code[5] ^ code[6]; 
    code[3] = code[4] ^ code[5] ^ code[6]; 

 
    cout << "\7-bit Hamming Code: ";
    for (int i = 0; i < 7; i++) {
        cout << code[i];
    }
    cout << endl;

    int received[7]; 
    cout << "\nEnter the received 7-bit code (with or without error):\n";
    for (int i = 0; i < 7; i++) {
        cout << "Bit " << i << ": ";
        cin >> received[i];
    }


    int p1 = received[0] ^ received[2] ^ received[4] ^ received[6];
    int p2 = received[1] ^ received[2] ^ received[5] ^ received[6];
    int p4 = received[3] ^ received[4] ^ received[5] ^ received[6];

    int errorPos = (p4 * 4) + (p2 * 2) + (p1 * 1);

    if (errorPos == 0) {
        cout << "\nNo error detected in received data." << endl;

    } else {
        cout << "\nError detected at position: " << errorPos << endl;
   
        received[errorPos - 1] ^= 1;

        cout << "Corrected Code: ";
        for (int i = 0; i < 7; i++) {
            cout << received[i];
        }
        cout << endl;
    }


    cout << "\nOriginal 4-bit Data was: ";
    cout << received[2] << received[4] << received[5] << received[6] << endl;

    return 0;

}




