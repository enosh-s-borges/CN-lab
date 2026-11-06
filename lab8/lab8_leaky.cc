/*Write  a  program  for  congestion  control  using  leaky  bucket  algorithm 
and token bucket algorithm.*/
//leaky bucket algorithm

#include <iostream>
using namespace std;

int main() {
    int bucket_remaining = 0, sent, received;
    int bucket_capacity, bucket_rate, n;

    cout << "Enter the bucket capacity\n";
    cin >> bucket_capacity;
    cout << "Enter the bucket rate (Rate at which the bucket sends the packets)\n";
    cin >> bucket_rate;
    cout << "Enter the number of packets to be sent\n";
    cin >> n;

    int buf[30];
    cout << "Enter the packets sizes one by one\n";
    for (int i = 0; i < n; i++) {
        cin >> buf[i];
    }

    cout << "Time_t\t\tP_size\t\taccepted\tsent\tremaining\n";

    for (int i = 0; i < n; i++) {
        if (buf[i] != 0) {
            if (bucket_remaining + buf[i] > bucket_capacity)
                received = -1;
            else {
                received = buf[i];
                bucket_remaining += buf[i];
            }
        } else {
            received = 0;
        }

        if (bucket_remaining != 0) {
            if (bucket_remaining < bucket_rate) {
                sent = bucket_remaining;
                bucket_remaining = 0;
            } else {
                sent = bucket_rate;
                bucket_remaining -= bucket_rate;
            }
        } else {
            sent = 0;
        }

        if (received == -1)
            cout << i + 1 << "\t\t" << buf[i] << "\t\t" << "dropped" << "\t\t"
                 << sent << "\t\t" << bucket_remaining << endl;
        else
            cout << i + 1 << "\t\t" << buf[i] << "\t\t" << received << "\t\t"
                 << sent << "\t\t" << bucket_remaining << endl;
    }
    return 0;
}