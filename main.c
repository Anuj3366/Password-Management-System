#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

void enterwebsite(char website[]);
void enterusername(char website[], char username[], char password[]);
void enterpassword(char website[], char username[], char password[]);
bool passwordstrength(char password[]);
bool idexists(char website[], char username[]);
bool passwordexists(char website[], char username[], char password[]);
void savepassword(char website[], char username[], char password[]);
void generatepassword(char website[], char username[]);
void retrievepassword(char website[], char username[]);

void enterwebsite(char website[])
{
    printf("Enter the website's URL: ");
    scanf("%99s", website);
    while (strstr(website, ".") == NULL || strlen(website) <= 6 ||
           (strstr(website, "https://") == NULL && strstr(website, "www.") == NULL))
    {
        if (strcmp(website, "exit") == 0)
        {
            printf("Exiting...\n");
            return;
        }
        printf("Invalid website's URL, Enter correct website's URL Again: ");
        scanf("%99s", website);
    }
}

void enterusername(char website[], char username[], char password[])
{
    printf("Enter the Username : ");
    scanf("%99s", username);
    if (idexists(website, username))
    {
        printf("id already exists , would you like to overwrite it or retrieve it? (1 for overwrite and any other number for retrieve)\n");
        int choice;
        scanf("%d", &choice);
        if (choice == 1)
        {
            return;
        }
        else
        {
            password = "exit";
            printf("Retrieving...\n");
            retrievepassword(website, username);
            return;
        }
    }
}

void enterpassword(char website[], char username[], char password[])
{
    printf("Enter the Password (8-10 characters with letters, digits, and special characters): ");
    scanf("%99s", password);
    if (strcmp(password, "exit") == 0)
    {
        printf("Exiting...\n");
        return;
    }
    while ((strlen(password) < 8 || strlen(password) > 10) || !passwordstrength(password) || passwordexists(website, username, password))
    {
        printf("Invalid input or password already exists, please enter a valid password or write exit to exit : ");
        scanf("%99s", password);
        if (strcmp(password, "exit") == 0)
        {
            printf("Exiting...\n");
            return;
        }
    }
    if (idexists(website, username))
    {
        printf("Overwriting...\n");
        FILE *file = fopen("passwords.xls", "r");
        FILE *file2 = fopen("passwords2.xls", "a");
        char line[300];
        while (fgets(line, sizeof(line), file))
        {
            char website2[100];
            char username2[100];
            char password2[100];
            if (sscanf(line, "%99[^||]||%99[^||]||%99s", website2, username2, password2) == 3)
            {
                if (strcmp(website2, website) == 0 && strcmp(username2, username) == 0)
                {
                    fprintf(file2, "%99s||%99s||%99s\n", website, username, password);
                }
                else
                {
                    fprintf(file2, "%99s||%99s||%99s\n", website2, username2, password2);
                }
            }
        }
        fclose(file);
        fclose(file2);
        remove("passwords.xls");
        rename("passwords2.xls", "passwords.xls");
        printf("Password Saved Successfully\n");
        return;
    }
}

bool passwordstrength(char password[])
{
    bool isStrong = true;
    int length = strlen(password);
    for (int i = 0; i < length; i++)
    {
        if ((password[i] >= '0' && password[i] <= '9') ||
            (password[i] >= 'a' && password[i] <= 'z') ||
            (password[i] >= 'A' && password[i] <= 'Z') ||
            strchr("!@#$^&*_+:?></'=~", password[i]))
        {
            isStrong = true;
        }
        else
        {
            return false;
        }
    }
    return isStrong;
}

bool idexists(char website[], char username[])
{
    FILE *file = fopen("passwords.xls", "r");
    char line[300];
    while (fgets(line, sizeof(line), file))
    {
        char website2[100];
        char username2[100];
        char password2[100];
        if (sscanf(line, "%99[^||]||%99[^||]||%99s", website2, username2, password2) == 3)
        {
            if (strcmp(website2, website) == 0 && strcmp(username2, username) == 0)
            {
                fclose(file);
                return true;
            }
        }
    }
    fclose(file);
    return false;
}

bool passwordexists(char website[], char username[], char password[])
{
    FILE *file = fopen("passwords.xls", "r");
    char line[300];
    while (fgets(line, sizeof(line), file))
    {
        char website2[100];
        char username2[100];
        char password2[100];
        if (sscanf(line, "%99[^||]||%99[^||]||%99s", website2, username2, password2) == 3)
        {
            if (strcmp(password2, password) == 0)
            {
                fclose(file);
                return true;
            }
        }
    }
    fclose(file);
    return false;
}

void savepassword(char website[], char username[], char password[])
{
    FILE *file = fopen("passwords.xls", "a");
    fprintf(file, "%99s||%99s||%99s\n", website, username, password);
    fclose(file);
    printf("Password Saved Successfully\n");
}

void generatepassword(char website[], char username[])
{
    FILE *file = fopen("passwords.xls", "a");
    char charset[] = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$^&*_+:?></'=~";
    int length = 10;
    char password[length + 1];
    srand(time(NULL));
    for (int i = 0; i < length; i++)
    {
        password[i] = charset[rand() % (sizeof(charset) - 1)];
    }
    password[length] = '\0';
    printf("Your password is %99s for the username %99s & website %99s. Now saving it\n", password, username, website);
    savepassword(website, username, password);
}

void retrievepassword(char website[], char username[])
{
    FILE *file = fopen("passwords.xls", "r");
    char line[300];
    while (fgets(line, sizeof(line), file))
    {
        char website2[100];
        char username2[100];
        char password2[100];
        if (sscanf(line, "%99[^||]||%99[^||]||%99s", website2, username2, password2) == 3)
        {
            if (strcmp(website2, website) == 0 && strcmp(username2, username) == 0)
            {
                printf("website : %99s , Username : %99s , Password : %99s\n", website2, username2, password2);
                fclose(file);
                return;
            }
        }
    }
    fclose(file);
    printf("Password not found, would you like to generate it? (1 for Yes and Any other number for No)\n");
    int choice;
    while (1)
    {
        printf("Enter your choice : ");
        if (scanf("%d", &choice) == 1)
        {
            break;
        }
        else
        {
            printf("Invalid input. Please enter a valid choice.\n");
            while (getchar() != '\n')
                ;
        }
    }
    if (choice == 1)
    {
        generatepassword(website, username);
        return;
    }
    printf("Exiting...\n");
}

int main()
{
    printf("Welcome to the Password Management System.\n\n");
    int choice;
    while (1)
    {
        printf("\n\n");
        printf("Please select an option:\n");
        printf("0. To exit from here type exit or 0, type \"exit\" to return to this menu at any time.\n");
        printf("1. Create a new password and save it securely.\n");
        printf("2. View an existing stored password.\n");
        printf("3. Generate a new strong password.\n");
        printf("\n\n");
        printf("Enter your choice : ");
        if (scanf("%d", &choice) == 0)
        {
            printf("Exiting...\n");
            return 0;
        }
        printf("\n");
        char website[100];
        char username[100];
        char password[100];
        switch (choice)
        {
        case 0:
            printf("Exiting...\n");
            return 0;
        case 1:
            enterwebsite(website);
            if (strcmp(website, "exit") == 0)
                break;
            enterusername(website, username, password);
            if (strcmp(password, "exit") == 0)
                break;
            enterpassword(website, username, password);
            printf("\n");
            if (strcmp(password, "exit") == 0)
                break;
            savepassword(website, username, password);
            break;
        case 2:
            enterwebsite(website);
            if (strcmp(website, "exit") == 0)
                break;
            enterusername(website, username, password);
            if (strcmp(password, "exit") == 0)
                break;
            retrievepassword(website, username);
            break;
        case 3:
            enterwebsite(website);
            if (strcmp(website, "exit") == 0)
                break;
            enterusername(website, username, password);
            printf("Generating Password...\n");
            generatepassword(website, username);
            break;
        default:
            printf("Invalid Choice\n");
            break;
        }
    }
    return 0;
}