#include <stdio.h>
#include <math.h>

// Function to perform modular exponentiation (base^exp % mod)
int modExp(int base, int exp, int mod) {
    int result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        exp = exp >> 1;
        base = (base * base) % mod;
    }
    return result;
}

// Function to simulate Diffie-Hellman key exchange
void diffieHellman(int p, int g, int a, int b) {
    // Alice's calculation
    int A = modExp(g, a, p);

    // Bob's calculation
    int B = modExp(g, b, p);

    // Shared secret calculation
    int secretA = modExp(B, a, p);
    int secretB = modExp(A, b, p);

    printf("Alice's public key (A): %d\n", A);
    printf("Bob's public key (B): %d\n", B);
    printf("Shared secret calculated by Alice: %d\n", secretA);
    printf("Shared secret calculated by Bob: %d\n", secretB);
}

// Main function
int main() {
    int choice;
    int p, g, a, b;

    printf("Enter 1 to initiate Diffie-Hellman or 2 to exit: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            printf("Enter prime modulus (p): ");
            scanf("%d", &p);
            printf("Enter base (g): ");
            scanf("%d", &g);
            printf("Enter Alice's private key (a): ");
            scanf("%d", &a);
            printf("Enter Bob's private key (b): ");
            scanf("%d", &b);

            diffieHellman(p, g, a, b);
            break;
        case 2:
            printf("Exiting...\n");
            break;
        default:
            printf("Invalid choice\n");
            break;
    }

    return 0;
}
