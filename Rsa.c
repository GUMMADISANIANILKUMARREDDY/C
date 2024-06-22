#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Function to compute the greatest common divisor
int gcd(int a, int b) {
    while (b != 0) {
        int t = b;
        b = a % b;
        a = t;
    }
    return a;
}

// Function to compute modular exponentiation (a^b % c)
long long mod_exp(long long a, long long b, long long c) {
    long long result = 1;
    a = a % c;
    while (b > 0) {
        if (b % 2 == 1)
            result = (result * a) % c;
        b = b >> 1;
        a = (a * a) % c;
    }
    return result;
}

// Function to compute the multiplicative inverse of e modulo phi using the extended Euclidean algorithm
int mod_inverse(int e, int phi) {
    int t = 0, newt = 1;
    int r = phi, newr = e;
    while (newr != 0) {
        int quotient = r / newr;
        int temp = t;
        t = newt;
        newt = temp - quotient * newt;
        temp = r;
        r = newr;
        newr = temp - quotient * newr;
    }
    if (r > 1) return -1; // e is not invertible
    if (t < 0) t += phi;
    return t;
}

int main() {
    int p, q, e, message;

    // User input for primes p and q, public exponent e, and message
    printf("Enter prime number p: ");
    scanf("%d", &p);
    printf("Enter prime number q: ");
    scanf("%d", &q);
    printf("Enter public exponent e: ");
    scanf("%d", &e);
    printf("Enter message to encrypt (as an integer): ");
    scanf("%d", &message);

    // Calculate n = p * q
    int n = p * q;

    // Calculate the totient of n
    int phi = (p - 1) * (q - 1);

    // Calculate private key exponent d
    int d = mod_inverse(e, phi);
    if (d == -1) {
        printf("Error: public exponent e is not invertible modulo phi(n).\n");
        return 1;
    }

    // Print the public and private keys
    printf("Public Key: (e = %d, n = %d)\n", e, n);
    printf("Private Key: (d = %d, n = %d)\n", d, n);

    // Encrypt the message
    int encrypted_message = mod_exp(message, e, n);
    printf("Encrypted Message: %d\n", encrypted_message);

    // Decrypt the message
    int decrypted_message = mod_exp(encrypted_message, d, n);
    printf("Decrypted Message: %d\n", decrypted_message);

    return 0;
}
