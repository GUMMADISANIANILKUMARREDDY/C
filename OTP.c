#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to perform one-time pad encryption
void encrypt(char *plaintext, char *key, char *ciphertext) {
    int i;
    for (i = 0; i < strlen(plaintext); i++) {
        ciphertext[i] = ((plaintext[i] - 'a') + (key[i] - 'a')) % 26 + 'a';
    }
    ciphertext[i] = '\0';
}

// Function to perform one-time pad decryption
void decrypt(char *ciphertext, char *key, char *plaintext) {
    int i;
    for (i = 0; i < strlen(ciphertext); i++) {
        plaintext[i] = ((ciphertext[i] - 'a') - (key[i] - 'a') + 26) % 26 + 'a';
    }
    plaintext[i] = '\0';
}

int main() {
    char plaintext[100], key[100], ciphertext[100], choice;
    
    printf("Enter 'e' for encryption or 'd' for decryption: ");
    scanf(" %c", &choice);
    
    switch(choice) {
        case 'e':
            printf("Enter plaintext: ");
            scanf("%s", plaintext);
            printf("Enter key: ");
            scanf("%s", key);
            encrypt(plaintext, key, ciphertext);
            printf("Ciphertext: %s\n", ciphertext);
            break;
        case 'd':
            printf("Enter ciphertext: ");
            scanf("%s", ciphertext);
            printf("Enter key: ");
            scanf("%s", key);
            decrypt(ciphertext, key, plaintext);
            printf("Decrypted plaintext: %s\n", plaintext);
            break;
        default:
            printf("Invalid choice.\n");
    }

    return 0;
}
