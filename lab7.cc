/*Write  a  program  for  simple  RSA  algorithm  to  encrypt  and  decrypt  the 
data*/

#include <iostream>
#include <cstdlib>
#include <ctime>
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
        srand(time(0));
        // small primes for lab (instead of 1024-bit)
        p = 61; q = 53;
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
    long long encrypt(long long msg) {
        return modPow(msg, e, N);
    }
    long long decrypt(long long msg) {
        return modPow(msg, d, N);
    }
};

int main() {
    RSA rsa;
    long long msg;
    cout << "Enter the plain text (number): ";
    cin >> msg;
    cout << "Encrypting: " << msg << endl;
    long long enc = rsa.encrypt(msg);
    cout << "Encrypted: " << enc << endl;
    long long dec = rsa.decrypt(enc);
    cout << "Decrypted: " << dec << endl;
    return 0;
}