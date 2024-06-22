include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to find the modulo inverse of a number a under modulo m using Extended Euclidean Algorithm
int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1)
            return x;
    }
    return -1;
}

// Function to calculate determinant of a 2x2 matrix
int determinant(int key[2][2]) {
    return key[0][0] * key[1][1] - key[0][1] * key[1][0];
}

// Function to find the inverse of a 2x2 matrix under modulo 26
void matrixInverse(int key[2][2], int inverse[2][2]) {
    int det = determinant(key);
    int detInv = modInverse(det, 26);
    
    if (detInv == -1) {
        printf("Inverse doesn't exist\n");
        exit(1);
    }
    
    inverse[0][0] = (key[1][1] * detInv) % 26;
    inverse[0][1] = (-key[0][1] * detInv) % 26;
    inverse[1][0] = (-key[1][0] * detInv) % 26;
    inverse[1][1] = (key[0][0] * detInv) % 26;
    
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            if (inverse[i][j] < 0) {
                inverse[i][j] += 26;
            }
        }
    }
}

// Function to encrypt the plaintext using the key matrix
void encrypt(int key[2][2], char *plaintext, char *ciphertext) {
    int pt[2];
    int ct[2];

    for (int i = 0; i < strlen(plaintext); i += 2) {
        pt[0] = plaintext[i] - 'A';
        pt[1] = plaintext[i + 1] - 'A';

        for (int j = 0; j < 2; j++) {
            ct[j] = 0;
            for (int k = 0; k < 2; k++) {
                ct[j] += key[j][k] * pt[k];
            }
            ct[j] %= 26;
        }

        ciphertext[i] = ct[0] + 'A';
        ciphertext[i + 1] = ct[1] + 'A';
    }
    ciphertext[strlen(plaintext)] = '\0';
}

// Function to decrypt the ciphertext using the inverse key matrix
void decrypt(int key[2][2], char *ciphertext, char *plaintext) {
    int inverse[2][2];
    matrixInverse(key, inverse);

    int ct[2];
    int pt[2];

    for (int i = 0; i < strlen(ciphertext); i += 2) {
        ct[0] = ciphertext[i] - 'A';
        ct[1] = ciphertext[i + 1] - 'A';

        for (int j = 0; j < 2; j++) {
            pt[j] = 0;
            for (int k = 0; k < 2; k++) {
                pt[j] += inverse[j][k] * ct[k];
            }
            pt[j] %= 26;
        }

        plaintext[i] = pt[0] + 'A';
        plaintext[i + 1] = pt[1] + 'A';
    }
    plaintext[strlen(ciphertext)] = '\0';
}

int main() {
    int key[2][2];
    char plaintext[100];
    char ciphertext[100];
    int choice;

    printf("Enter 2x2 key matrix (values should be between 0 and 25):\n");
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            scanf("%d", &key[i][j]);
            if (key[i][j] < 0 || key[i][j] > 25) {
                printf("Invalid key value. It should be between 0 and 25.\n");
                return 1;
            }
        }
    }

    do {
        printf("\nMenu:\n");
        printf("1. Encrypt\n");
        printf("2. Decrypt\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // To consume newline character

        switch (choice) {
            case 1:
                printf("Enter plaintext (uppercase, even length): ");
                fgets(plaintext, sizeof(plaintext), stdin);
                plaintext[strcspn(plaintext, "\n")] = 0; // Remove newline character
                if (strlen(plaintext) % 2 != 0) {
                    printf("Plaintext length should be even. Exiting...\n");
                    exit(1);
                }
                encrypt(key, plaintext, ciphertext);
                printf("Encrypted text: %s\n", ciphertext);
                break;
            case 2:
                printf("Enter ciphertext (uppercase, even length): ");
                fgets(ciphertext, sizeof(ciphertext), stdin);
                ciphertext[strcspn(ciphertext, "\n")] = 0; // Remove newline character
                if (strlen(ciphertext) % 2 != 0) {
                    printf("Ciphertext length should be even. Exiting...\n");
                    exit(1);
                }
                decrypt(key, ciphertext, plaintext);
                printf("Decrypted text: %s\n", plaintext);
                break;
            case 3:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice!\n");
        }
    } while (choice != 3);

    return 0;
}
