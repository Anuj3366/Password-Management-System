// making just a basic password manager first
// navigate using website name not username as a person can have multiple accounts with same username
// add privacy while writing password
// add encryption and decryption to the saved password and give option to make its key to the user
// add a feature where it can work with html and looks good
// add encrypted password to the exel file instead of text and provide a option to import it to browser
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

void savepassword(char username[], char password[])
{
    FILE *file = fopen("password.xls", "a");
    fprintf(file, "%s:%s\n", username, password);
    fclose(file);
    printf("Password Saved Successfully\n");
}

void generatepassword(char username[])
{
    FILE *file = fopen("password.xls", "a");
    char pass[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$^&*_+|:?></'=~";
    int length = 10;
    char password[length];
    srand(time(NULL));
    for (int i = 0; i < length; i++)
    {
        password[i] = pass[rand() % strlen(pass)];
    }
    password[length] = '\0';
    printf("Your password is %s for the username %s. Now saving it\n", password, username);
    savepassword(username, password);
}

void retrievepassword(char username[])
{
    FILE *file = fopen("password.xls", "r");
    char line[200];
    while (fgets(line, sizeof(line), file))
    {
        char username2[100];
        char password2[100];
        if (sscanf(line, "%99[^:]%99s", username2, password2) == 2)
        {
            if (strcmp(username, username2) == 0)
            {
                printf("The password for %s is %s\n", username, password2);
                fclose(file);
                return;
            }
        }
    }
    fclose(file);

    printf("Password not found, would you like to generate it? (1 for yes, any other number for no)\n");
    int choice;
    scanf("%d", &choice);
    if (choice == 1)
    {
        generatepassword(username);
        return;
    }
    printf("Exiting...\n");
}

int main()
{
    printf("Do you want to create a new password or view an existing one?\n");
    printf("1. Save a new password\n");
    printf("2. View an existing password\n");
    printf("3. Generate a new Strong Password\n");
    printf("4. Exit\n");
    int choice;
    while (choice != 4)
    {
        printf("\n\n");
        printf("Enter your choice : ");
        scanf("%d", &choice);
        printf("\n");
        char username[100];
        char password[100];
        switch (choice)
        {
        case 1:
            printf("Enter the Username : ");
            scanf("%s", username);
            printf("Enter the Password : ");
            scanf("%s", password);
            printf("\n");
            savepassword(username, password);
            break;
        case 2:
            printf("Enter the Username : ");
            scanf("%s", username);
            retrievepassword(username);
            break;
        case 3:
            printf("Enter the Username : ");
            scanf("%s", username);
            printf("Generating Password...\n");
            generatepassword(username);
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
