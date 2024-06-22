#include <stdio.h>
#include <string.h>

void encrypt(char text[], int key) {
    for (int i = 0; i < strlen(text); i++) {
        if (text[i] >= 'a' && text[i] <= 'z') {
            text[i] = (text[i] + key - 'a') % 26 + 'a';
        } else if (text[i] >= 'A' && text[i] <= 'Z') {
            text[i] = (text[i] + key - 'A') % 26 + 'A';
        }
    }
}

void decrypt(char text[], int key) {
    encrypt(text, 26 - key);
}

int main() {
    char text[100];
    int key, choice;

    printf("Enter text: ");
    scanf("%s", text);

    printf("Enter key: ");
    scanf("%d", &key);

    printf("Menu:\n1. Encrypt\n2. Decrypt\nEnter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            encrypt(text, key);
            printf("Encrypted text: %s\n", text);
            break;
        case 2:
            decrypt(text, key);
            printf("Decrypted text: %s\n", text);
            break;
        default:
            printf("Invalid choice.\n");
    }

    return 0;
}
