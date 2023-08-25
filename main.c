#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Function to generate a random password
void generateRandomPassword(char *password, int length) {
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    srand(time(NULL));

    for (int i = 0; i < length; i++) {
        int index = rand() % (sizeof(charset) - 1);
        password[i] = charset[index];
    }

    password[length] = '\0';
}

// Function to save a password
void savePassword(const char *username, const char *password) {
    FILE *file = fopen("passwords.txt", "a");

    if (file != NULL) {
        fprintf(file, "%s:%s\n", username, password);
        fclose(file);
        printf("Password saved successfully.\n");
    } else {
        printf("Error: Unable to save password.\n");
    }
}

// Function to retrieve passwords
void retrievePasswords(const char *username) {
    FILE *file = fopen("passwords.txt", "r");

    if (file != NULL) {
        char line[100];
        while (fgets(line, sizeof(line), file)) {
            char *storedUsername = strtok(line, ":");
            char *storedPassword = strtok(NULL, "\n");

            if (strcmp(username, storedUsername) == 0) {
                printf("Username: %s, Password: %s\n", storedUsername, storedPassword);
            }
        }
        fclose(file);
    } else {
        printf("Error: Unable to retrieve passwords.\n");
    }
}

int main() {
    char username[50];
    char password[50];

    printf("Welcome to Password-Manager\n");
    printf("Enter your username: ");
    scanf("%s", username);

    generateRandomPassword(password, 10);
    printf("Generated Password: %s\n", password);

    savePassword(username, password);

    printf("Passwords for user %s:\n", username);
    retrievePasswords(username);

    return 0;
}
