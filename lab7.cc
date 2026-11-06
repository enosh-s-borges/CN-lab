/*Write  a  program  for  simple  RSA  algorithm  to  encrypt  and  decrypt  the 
data*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

long long modPow(long long base, long long exp, long long mod) {
    long long res = 1;
    base %= mod;
    while (exp > 0) {
        if (exp & 1) res = (res * base) % mod;
        base = (base * base) % mod;
        exp >>= 1;
    }
    return res;
}

class RSA {
    long long p, q, N, phi, e, d;
public:
    RSA() {
        // reasonably large primes that fit in long long
        p = 61;
        q = 53;
        cout << "Prime number p is " << p << endl;
        cout << "Prime number q is " << q << endl;

        N = p * q;
        phi = (p - 1) * (q - 1);

        e = 17;
        while (__gcd(e, phi) != 1) e++;
        cout << "Public key is " << e << endl;

        for (d = 1; d < phi; d++)
            if ((e * d) % phi == 1) break;
        cout << "Private key is " << d << endl;
    }

    vector<long long> encrypt(string msg) {
        vector<long long> enc;
        for (char c : msg)
            enc.push_back(modPow((long long)c, e, N));
        return enc;
    }

    string decrypt(vector<long long> enc) {
        string dec = "";
        for (long long val : enc)
            dec += (char)modPow(val, d, N);
        return dec;
    }
};

int main() {
    RSA rsa;
    string text;

    cout << "Enter the plain text: ";
    getline(cin, text);

    cout << "Encrypting string: " << text << endl;

    vector<long long> encrypted = rsa.encrypt(text);

    cout << "Encrypted message: ";
    for (long long val : encrypted)
        cout << val << " ";
    cout << endl;

    string decrypted = rsa.decrypt(encrypted);
    cout << "Decrypted string: " << decrypted << endl;

    return 0;
}