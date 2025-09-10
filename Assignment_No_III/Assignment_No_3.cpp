#include <iostream>
using namespace std;

 int received_frames[100];
 int total_frames;

 
 void send_frame_SR(int frame_data, int frame_index, int error_index) {
    if (frame_index == error_index) {
        cout << "[ No Acknowledgement ] :: Error At Frame " << frame_index << endl;
        cout << "[ Acknowledgement ] :: Re-Transmitting Frame " << frame_index << endl;
        cout << "[ Acknowledgement ] :: Frame Received Successfully :: " << frame_index << endl;
        received_frames[frame_index] = frame_data;
    } else {
        cout << "[ Acknowledgement ] :: Frame Received Successfully :: " << frame_index << endl;
        received_frames[frame_index] = frame_data;
    }
}

 
void send_frame_GBN(int total_frames, int error_index) {
    for (int i = 0; i < total_frames; i++) {
        if (i == error_index) {
            cout << "[ No Acknowledgement ] :: Error At Frame " << i << endl;
            cout << "[ No Acknowledgement ] :: Number Of Bits Discarded :: " << (total_frames-error_index) << endl;
            cout << "[ Acknowledgement ] :: Re-Transmitting From Frame " << i << " to " << total_frames - 1 << endl;
            for (int j = i; j < total_frames; j++) {
                cout << "[ Re-Transmission ] :: Sending Frame " << j << endl;
                cout << "[ Acknowledgement ] :: Frame Received Successfully :: " << j << endl;
                received_frames[j] = j;
            }
            break; 
        } else {
            cout << "[ Acknowledgement ] :: Frame Received Successfully :: " << i << endl;
            received_frames[i] = i;
        }
    }
}

int main() {
   
    cout << "Enter total number of frames: ";
    cin >> total_frames;

    int error_index;
    cout << "Enter error frame index : ";
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
            send_frame_GBN(total_frames, error_index);
            break;

        case 2:
            cout << "\n[ Protocol ] :: Selective Repeat\n";
            for (int i = 0; i < total_frames; i++) {
                send_frame_SR(i, i, error_index);
            }
            break;

        default:
            cout << "Invalid choice.\n";
    }

    cout << "\n[ Receiver ]:: \n";
    for (int i = 0; i < total_frames; i++) {
        cout << "Received Frames[" << i << "] = " << received_frames[i] << endl;
    }

    return 0;
}
