/*Write  a  program  for  congestion  control  using  leaky  bucket  algorithm 
and token bucket algorithm.*/
//token bucket algorithm

#include <iostream>
using namespace std;

int main() {
    int token_remaining = 0;
    int token_requested, token_sent;
    int bucket_capacity, token_gen_rate, n;

    cout << "Enter the bucket capacity\n";
    cin >> bucket_capacity;
    cout << "Enter the Token generation rate (Rate at which tokens are sent to the bucket)\n";
    cin >> token_gen_rate;
    cout << "Enter the number of Cycles the host computer sends the Tokens to the bucket(at constant rate)\n";
    cin >> n;

    cout << "Time_t\tTokens Requested\tTokens Sent\tTokens Remaining in bucket\n";

    for (int i = 0; i < n; i++) {
        token_requested = token_gen_rate;
        if (token_requested + token_remaining > bucket_capacity) {
            token_sent = bucket_capacity - token_remaining;
            token_remaining = bucket_capacity;
        } else {
            token_sent = token_requested;
            token_remaining += token_requested;
        }
        cout << i + 1 << "\t\t" << token_requested << "\t\t" << token_sent
             << "\t\t" << token_remaining << endl;
    }
    return 0;
}