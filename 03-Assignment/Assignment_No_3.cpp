#include <iostream>
using namespace std;

int received_frames[100];
int total_frames;

void send_frame_SR(int frame_index, int error_index) {
    cout << "Sending Frame " << frame_index + 1 << endl;
  //condition  for error checking
    if (frame_index == error_index) {
        cout << "[ NACK ] Frame " << frame_index + 1 << " negative  ACK." << endl;
    } else {
        cout << "[ ACK ] Frame " << frame_index + 1 << " Sending successfully." << endl;
    }

    received_frames[frame_index] = frame_index + 1; 
}
 //function for send frame GBN
void send_frame_GBN(int total_frames, int error_index) {
    for (int i = 0; i < total_frames; i++) {
        cout << "Sending Frame " << i + 1 << endl;

        if (i == error_index) {
            cout << "Error in Frame " << i + 1 << endl;
            cout << "Re-Transmitting From Frame " << i + 1 
                 << " to " << total_frames << endl;

            for (int j = i; j < total_frames; j++) {
                cout << "Sending Frame " << j + 1 << endl;
                received_frames[j] = j + 1;
            }
            return; 
        }

        received_frames[i] = i + 1;
    }
}

int main() {
    cout << "Enter total number of frames: ";
    cin >> total_frames;
     int flag=0;

    int error_index;
    cout << "Enter error frame index (-2 if no error): ";
    cin >> error_index;

    int choice;
    cout << "\nSelect ARQ Protocol:\n";
    cout << "1. Go-Back-N\n";
    cout << "2. Selective Repeat\n";
    cout << "Enter choice: ";
    cin >> choice;

    switch (choice) {
        case 1:
            cout << "\n[ Protocol ] :: Go-Back-N\n";
            if (error_index >= 0 && error_index < total_frames)
                send_frame_GBN(total_frames, error_index);
            else
                send_frame_GBN(total_frames, -1); 
            break;

        case 2:
            cout << "\n[ Protocol ] :: Selective Repeat\n";
           
            for (int i = 0; i < total_frames; i++) {
                if (error_index >= 0 && error_index < total_frames){
                    send_frame_SR(i, error_index);
                    flag=1;
            }
                else
                    send_frame_SR(i, -1); 
            }
           if(flag=1){
                cout << "\n\n[ ACK ] Frame " << error_index << " Sending successfully." << endl;
           }
            
            break;

        default:
            cout << "Invalid choice.\n";
    }

    cout << "\n[ Receiver ]:: \n";
    for (int i = 0; i < total_frames; i++) {
        cout << "Received Frame[" << i << "] = " << received_frames[i] << endl;
    }

    return 0;
}


