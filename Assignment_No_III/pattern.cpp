#include <iostream>
using namespace std;


void goBackN(int totalFrames) {
    int ackValue;
    int resendFrom =0; 

    for (int frame = 1; frame <= totalFrames; frame++) {
        cout << "Sending frame " << frame << endl;
        cout << "Enter ACK for frame " << frame << " (1=Received, 0=Lost): ";
        cin >> ackValue;

        if (ackValue == 0) { 
            cout << "Acknowledgement not received for frame " << frame << endl;
            resendFrom = frame;
            break;
        } else {
            cout << "Acknowledgement received for frame " << frame << endl;
        }
    }

    if (resendFrom != 0) {
        cout << "\nResending from frame " << resendFrom << endl;
        for (int frame = resendFrom; frame <= totalFrames; frame++) {
            cout << "Sending frame " << frame << endl;
            cout << "Acknowledgement received for frame " << frame << endl;
        }
    }
}


void selectiveRepeat(int totalFrames) {
    int ackValue;
    int lostFrame = -1;

    for (int frame = 1; frame <= totalFrames; frame++) {
        cout << "Sending frame " << frame << endl;
        cout << "Enter ACK for frame " << frame << " (1=Received, 0=Lost): ";
        cin >> ackValue;

        if (ackValue == 0) {
            cout << "Acknowledgement: -1 (Lost)" << endl;
            lostFrame = frame;
        } else {
            cout << "Acknowledgement received for frame " << frame << endl;
        }
    }

    if (lostFrame != -1) {
        cout << "\nResending frame " << lostFrame << endl;
        cout << "Acknowledgement received for frame " << lostFrame << endl;
    }
}

int main() {
    int totalFrames, menuChoice;
    cout << "Enter total number of frames: ";
    cin >> totalFrames;

    do {
        cout << "\nMenu:\n1. Go-Back-N\n2. Selective Repeat\n3. Exit\nChoice: ";
        cin >> menuChoice;
     switch (menuChoice)
     {
     case 1:
          goBackN(totalFrames);
          break;

     
      case 2:
          selectiveRepeat(totalFrames);
          break;


      case 3:
         cout<<"Exiting....";
          break;

     default:
          break;
     }

    } while (menuChoice != 3);

    return 0;
}
