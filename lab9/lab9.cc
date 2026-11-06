/*Write a program to implement random early detection (RED) 
congestion control algorithm.*/

#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

double calculateDropProbability(int currentQueueLength, int queueSize,
                                double maxProbability, double minProbability, int threshold) {
    double slope = (maxProbability - minProbability) / (queueSize - threshold);
    return minProbability + slope * (currentQueueLength - threshold);
}

void simulateCongestion(int maxPackets, int queueSize, double maxProbability,
                        double minProbability, int threshold) {
    srand(time(0));
    int queueLength = 0;

    for (int i = 0; i < maxPackets; i++) {
        double dropProbability = calculateDropProbability(queueLength, queueSize,
                                                          maxProbability, minProbability, threshold);
        if (queueLength >= threshold && ((double)rand() / RAND_MAX) < dropProbability) {
            cout << "Packet dropped (CONGESTION AVOIDANCE)" << endl;
        } else {
            cout << "Packet accepted " << (i + 1) << endl;
            queueLength++;
        }
    }
}

int main() {
    int maxPackets, queueSize, threshold;
    double maxProbability, minProbability;

    cout << "Enter the maximum number of packets:" << endl;
    cin >> maxPackets;
    cout << "Enter the queue size:" << endl;
    cin >> queueSize;
    cout << "Enter the maximum probability:" << endl;
    cin >> maxProbability;
    cout << "Enter the minimum probability:" << endl;
    cin >> minProbability;
    cout << "Enter the threshold value:" << endl;
    cin >> threshold;

    simulateCongestion(maxPackets, queueSize, maxProbability, minProbability, threshold);
    return 0;
}