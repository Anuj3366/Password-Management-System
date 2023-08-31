#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

void enterwebsite(char *website);
void enterusername(char *website, char *username, char *password);
void enterpassword(char *website, char *username, char *password);
bool passwordstrength(char *password);
bool idexists(char *website, char *username);
bool passwordexists(char *website, char *username, char *password);
void savepassword(char *website, char *username, char *password);
void generatepassword(char *website, char *username);
void retrievepassword(char *website, char *username);

void enterwebsite(char *website)
{
    printf("Enter the website's URL: ");
    while (scanf("%s", website) == 0 || strcmp(website, "exit") == 0)
    {
        printf("Please enter a valid website's URL.\n");
        printf("Enter the website's URL: ");
    }
    while (strlen(website) <= 6 || (strstr(website, "https://") == NULL && strstr(website, "www.") == NULL))
    {
        if (strcmp(website, "exit") == 0)
        {
            printf("Exiting...\n");
            exit(0);
        }
        printf("The website's URL is not valid. Please enter a valid website's URL.\n");
        printf("Enter the website's URL: ");
        scanf("%s", website);
    }
}

void enterusername(char *website, char *username, char *password)
{
    printf("Enter the Username : ");
    scanf("%s", username);
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
            printf("Retrieving...\n");
            retrievepassword(website, username);
            exit(0);
        }
    }
}

void enterpassword(char *website, char *username, char *password)
{
    printf("Enter the Password (8-10 characters with letters, digits, and special characters): ");
    scanf("%s", password);
    if (strcmp(password, "exit") == 0)
    {
        printf("Exiting...\n");
        return;
    }
    while ((strlen(password) < 8 || strlen(password) > 10) || !passwordstrength(password) || passwordexists(website, username, password))
    {
        printf("Invalid input or password already exists, please enter a valid password or write exit to exit : ");
        scanf("%s", password);
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
            if (sscanf(line, "%99[^||]||%99[^||]||%s", website2, username2, password2) == 3)
            {
                if (strcmp(website2, website) == 0 && strcmp(username2, username) == 0)
                {
                    fprintf(file2, "%s||%s||%s\n", website, username, password);
                }
                else
                {
                    fprintf(file2, "%s||%s||%s\n", website2, username2, password2);
                }
            }
        }
        fclose(file);
        fclose(file2);
        remove("passwords.xls");
        rename("passwords2.xls", "passwords.xls");
        printf("Password Saved Successfully\n");
        exit(0);
        return;
    }
}

bool passwordstrength(char *password)
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

bool idexists(char *website, char *username)
{
    FILE *file = fopen("passwords.xls", "r");
    char line[300];
    while (fgets(line, sizeof(line), file))
    {
        char website2[100];
        char username2[100];
        char password2[100];
        if (sscanf(line, "%99[^||]||%99[^||]||%s", website2, username2, password2) == 3)
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

bool passwordexists(char *website, char *username, char *password)
{
    FILE *file = fopen("passwords.xls", "r");
    char line[300];
    while (fgets(line, sizeof(line), file))
    {
        char website2[100];
        char username2[100];
        char password2[100];
        if (sscanf(line, "%99[^||]||%99[^||]||%s", website2, username2, password2) == 3)
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

void savepassword(char *website, char *username, char *password)
{
    FILE *file = fopen("passwords.xls", "w");
    fprintf(file, "%s||%s||%s\n", website, username, password);
    fclose(file);
    printf("Password Saved Successfully\n");
}

void generatepassword(char *website, char *username)
{
    FILE *file = fopen("passwords.xls", "w");
    char charset[] = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$^&*_+:?></'=~";
    int length = 10;
    char password[length + 1];
    srand(time(NULL));
    for (int i = 0; i < length; i++)
    {
        password[i] = charset[rand() % (sizeof(charset) - 1)];
    }
    password[length] = '\0';
    printf("Your password is %s for the username %s & website %s. Now saving it\n", password, username, website);
    savepassword(website, username, password);
}

void retrievepassword(char *website, char *username)
{
    FILE *file = fopen("passwords.xls", "r");
    char line[300];
    while (fgets(line, sizeof(line), file))
    {
        char website2[100];
        char username2[100];
        char password2[100];
        if (sscanf(line, "%99[^||]||%99[^||]||%s", website2, username2, password2) == 3)
        {
            if (strcmp(website2, website) == 0 && strcmp(username2, username) == 0)
            {
                printf("website : %s , Username : %s , Password : %s\n", website2, username2, password2);
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
    system("clear");
    printf("Welcome to the Password Management System.\n\n");
    int choice;
    while (1)
    {
        printf("\n\n");
        printf("Please select an option:\n");
        printf("0. To exit from here type exit or 0, type \"exit\" to return to this menu at any time.\n");
        printf("1. Save a new password and save it securely.\n");
        printf("2. View an existing stored password.\n");
        printf("3. Generate a new strong password.\n");
        printf("\n\n");
        printf("Enter your choice : ");
        if (scanf("%d", &choice) != 1)
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
            enterusername(website, username, password);
            enterpassword(website, username, password);
            savepassword(website, username, password);
            break;
        case 2:
            enterwebsite(website);
            printf("Enter the Username : ");
            scanf("%s", username);
            retrievepassword(website, username);
            break;
        case 3:
            enterwebsite(website);
            enterusername(website, username, password);
            printf("Generating Password...\n");
            generatepassword(website, username);
            break;
        default:
            printf("Invalid Choice\n");
            break;
        }
        system("clear");
    }
    return 0;
}