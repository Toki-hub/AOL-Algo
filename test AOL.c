#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SHIFT_KEY 8

// Function to encrypt a string using the Caesar cipher
void encryptString(char *input, char *output) {
    int i = 0;
    char ch;

    while (input[i] != '\0') {
        ch = input[i];

        // Encrypt uppercase letters
        if (isupper(ch)) {
            output[i] = ((ch - 'A' - SHIFT_KEY + 26) % 26) + 'A';
        }
        // Encrypt lowercase letters
        else if (islower(ch)) {
            output[i] = ((ch - 'a' - SHIFT_KEY + 26) % 26) + 'a';
        }
        // Leave non-alphabetic characters unchanged
        else {
            output[i] = ch;
        }

        i++;
    }

    output[i] = '\0'; // Null-terminate the encrypted string
}

int main() {
    char input[101];   // Input string buffer
    char output[101];  // Encrypted string buffer

    printf("Enter a string (5-100 characters): ");
    fgets(input, sizeof(input), stdin);

    // Remove trailing newline character if present
    size_t length = strlen(input);
    if (length > 0 && input[length - 1] == '\n') {
        input[length - 1] = '\0';
    }

    // Validate input length
    length = strlen(input);
    if (length < 5 || length > 100) {
        printf("Error: String must be between 5 and 100 characters long.\n");
        return 1;
    }

    // Encrypt the string
    encryptString(input, output);

    // Display the result
    printf("Encrypted string: %s\n", output);

    return 0;
}
