/*Write a program to sort frames using appropriate sorting techniques*/

#include <iostream>
#include <string>
#include <algorithm>
#include <ctime>
using namespace std;

struct Frame {
    int fnum;
    string content;
};

// Bubble Sort
void sorting(int n, Frame F[]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (F[j].fnum > F[j + 1].fnum) {
                // Swap
                swap(F[j], F[j + 1]);
            }
        }
    }
}

int main() {
    srand(time(0));          // for random shuffle

    int n;
    cout << "Enter the number of frames: ";
    cin >> n;

    Frame F[n];

    cout << "Enter the frame details:\n";
    for (int i = 0; i < n; i++) {
        cout << "\nEnter frame number: ";
        cin >> F[i].fnum;
        cout << "Enter frame content: ";
        cin >> F[i].content;
    }

    // Shuffle the frames randomly
    random_shuffle(F, F + n);

    // Display before sorting
    cout << "\nBefore Sorting (Shuffled frames):\n";
    for (int i = 0; i < n; i++)
        cout << F[i].content << " ";

    // Sort
    sorting(n, F);

    // Display after sorting
    cout << "\n\nAfter Sorting the frames:\n";
    for (int i = 0; i < n; i++)
        cout << F[i].content << " ";

    cout << endl;
    return 0;
}