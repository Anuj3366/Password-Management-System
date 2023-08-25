#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

void savepassword(char url[], char username[], char password[]) {
    FILE *file = fopen("passwords.xls", "a");
    fprintf(file, "%s||%s||%s\n", url, username, password);
    fclose(file);
    printf("Password Saved Successfully\n");
}

void generatepassword(char url[], char username[]) {
    FILE *file = fopen("passwords.xls", "a");
    char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$^&*_+:?></'=~";
    int length = 10;
    char password[length + 1];
    srand(time(NULL));
    for (int i = 0; i < length; i++) {
        password[i] = charset[rand() % (strlen(charset))];
    }
    password[length] = '\0';
    printf("Your password is %s for the username %s & URL %s. Now saving it\n", password, username, url);
    savepassword(url, username, password);
}

void retrievepassword(char url[], char username[]) {
    FILE *file = fopen("passwords.xls", "r");
    char line[300];
    while (fgets(line, sizeof(line), file)) {
        char url2[100];
        char username2[100];
        char password2[100];
        if (sscanf(line, "%99[^||]||%99[^||]||%99s", url2, username2, password2) == 3) {
            if (strcmp(url2, url) == 0 && strcmp(username2, username) == 0) {
                printf("URL : %s , Username : %s , Password : %s\n", url2, username2, password2);
                fclose(file);
                return;
            }
        }
    }
    fclose(file);
    printf("Password not found, would you like to generate it? (1 for Yes and Anything else for No)\n");
    int choice;
    scanf("%d", &choice);
    if (choice == 1) {
        generatepassword(url, username);
        return;
    }
    printf("Exiting...\n");
}

int main() {
    printf("Do you want to create a new password or view an existing one?\n");
    printf("1. Save a new password\n");
    printf("2. View an existing password\n");
    printf("3. Generate a new Strong Password\n");
    printf("4. Exit\n");
    int choice;
    while (choice != 4) {
        printf("\n\n");
        printf("Enter your choice : ");
        scanf("%d", &choice);
        printf("\n");
        char url[100];
        char username[100];
        char password[100];
        switch (choice) {
            case 1:
                printf("Enter the URL: ");
                scanf("%s", url);
                printf("Enter the Username : ");
                scanf("%s", username);
                printf("Enter the Password : ");
                scanf("%s", password);
                printf("\n");
                savepassword(url, username, password);
                break;
            case 2:
                printf("Enter the URL : ");
                scanf("%s", url);
                printf("Enter the Username : ");
                scanf("%s", username);
                retrievepassword(url, username);
                break;
            case 3:
                printf("Enter the URL : ");
                scanf("%s", url);
                printf("Enter the Username : ");
                scanf("%s", username);
                printf("Generating Password...\n");
                generatepassword(url, username);
                break;
            case 4:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid Choice\n");
                break;
        }
    }

    return 0;
}
