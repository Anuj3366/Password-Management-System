#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <unistd.h>

int enterwebsite(char *website);
int enterusername(char *website, char *username, char *password);
int enterpassword(char *website, char *username, char *password);
void updating(char *website, char *username, char *password);
bool passwordstrength(char *password);
bool idexists(char *website, char *username);
bool passwordexists(char *website, char *username, char *password);
void savepassword(char *website, char *username, char *password);
void generatepassword(char *website, char *username, char *password);
void retrievepassword(char *website, char *username, char *password);

int enterwebsite(char *website)
{
    printf("Enter the website's URL: ");
    scanf("%s", website);
    if (strcmp(website, "exit") == 0)
    {
        printf("\nExiting...\n");
        return 1;
    }
    while (strlen(website) <= 6 || (strstr(website, "https://") == NULL && strstr(website, "www.") == NULL))
    {
        printf("\nThe website's URL is not valid. Please enter a valid website's URL.\n");
        printf("Enter the website's URL: ");
        scanf("%s", website);
        if (strcmp(website, "exit") == 0)
        {
            printf("\nExiting...\n");
            return 1;
        }
    }
    return 0;
}

int enterusername(char *website, char *username, char *password)
{
    printf("Enter the Username : ");
    scanf("%s", username);
    if (strcmp(username, "exit") == 0)
    {
        printf("\nExiting...\n");
        return 1;
    }
    if (idexists(website, username))
    {
        printf("\nThe username already exists. Would you like to Update it (press `1`) or retrieve it (press anything else)?\n");
        printf("Enter your choice : ");
        int choice;
        scanf("%d", &choice);
        if (choice == 1)
        {
            return 0;
        }
        else
        {
            printf("\nRetrieving...\n");
            retrievepassword(website, username, password);
            return 1;
        }
    }
}

int enterpassword(char *website, char *username, char *password)
{
    printf("Enter the Password (8-10 characters with letters, digits, and special characters): ");
    scanf("%s", password);
    if (strcmp(password, "exit") == 0)
    {
        printf("\nExiting...\n");
        return 1;
    }
    while ((strlen(password) < 8 || strlen(password) > 10) || !passwordstrength(password) || passwordexists(website, username, password))
    {
        printf("\nInvalid input or password already exists, please enter a valid password or write exit to exit : ");
        scanf("%s", password);
        if (strcmp(password, "exit") == 0)
        {
            printf("\nExiting...\n");
            return 1;
        }
    }
    if (idexists(website, username))
    {
        updating(website, username, password);
        return 1;
    }
    return 0;
}

void updating(char *website, char *username, char *password)
{
    printf("\nUpdating...\n");
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
    printf("\nPassword Saved Successfully\n");
}

bool passwordstrength(char *password)
{
    int length = strlen(password);
    if(length < 8 || length > 10)
    {
        return false;
    }
    int a = 0;
    int b = 0;
    int c = 0;
    int d = 0;
    for (int i = 0; i < length; i++)
    {
        if (password[i] >= '0' && password[i] <= '9')
        {
            a++;
        }
        else if (password[i] >= 'a' && password[i] <= 'z')
        {
            b++;
        }
        else if (password[i] >= 'A' && password[i] <= 'Z')
        {
            c++;
        }
        else if (strchr("!@#$^&*_+:?></'=~", password[i]))
        {
            d++;
        }
        else
        {
            continue;
        }
    }
    if (a > 0 && b > 0 && c > 0 && d > 0)
    {
        return true;
    }
    return false;
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
    FILE *file = fopen("passwords.xls", "a+");
    fprintf(file, "%s||%s||%s\n", website, username, password);
    fclose(file);
    printf("\nPassword Saved Successfully\n");
}

void generatepassword(char *website, char *username, char *password)
{
    FILE *file = fopen("passwords.xls", "a+");
    char charset[] = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$^&*_+:?></'=~";
    int length = 10;
    srand(time(NULL));
    if (idexists(website, username))
    {
        updating(website, username, password);
    }
    for (int i = 0; i < length; i++)
    {
        password[i] = charset[rand() % (sizeof(charset) - 1)];
    }
    password[length] = '\0';
    printf("Your password for the username %s and website %s is %s. I'm saving it now.\n", username, website, password);
    savepassword(website, username, password);
    sleep(5);
}

void retrievepassword(char *website, char *username, char *password)
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
    printf("Password not found, would you like to generate it? (Press 1 for Yes and Anything else for No)\n");
    int choice;
    while (1)
    {
        printf("Enter your choice : ");
        scanf("%d", &choice) == 1;
    }
    if (choice == 1)
    {
        generatepassword(website, username, password);
        return;
    }
    printf("Exiting...\n");
}

int main()
{
    system("clear");
    printf("Welcome to the Password Management System.\n\n");
    int b;
    int choice;
    while (1)
    {
        printf("\n\n");
        printf("Please select an option:\n");
        printf("To exit, type 'exit' or '0'. You can also type 'exit' at any time to return to this menu.\n");
        printf("1. Save a new password (Press 1).\n");
        printf("2. View an existing stored password (Press 2).\n");
        printf("3. Generate a new strong password (Press 3).\n");
        printf("\n\n");
        printf("Enter your choice: ");

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
            printf("\nExiting...\n");
            return 0;
        case 1:
            b = enterwebsite(website);
            if (b == 1)
            {
                break;
            }
            b = enterusername(website, username, password);
            if (b == 1)
            {
                break;
            }
            b = enterpassword(website, username, password);
            if (b == 1)
            {
                break;
            }
            savepassword(website, username, password);
            break;
        case 2:
            b = enterwebsite(website);
            if (b == 1)
            {
                break;
            }
            printf("Enter the Username : ");
            scanf("%s", username);
            retrievepassword(website, username, password);
            break;
        case 3:
            b = enterwebsite(website);
            if (b == 1)
            {
                break;
            }
            b = enterusername(website, username, password);
            if (b == 1)
            {
                break;
            }
            printf("Generating Password...\n");
            generatepassword(website, username, password);
            break;
        default:
            printf("Invalid Choice\n");
            break;
        }
        sleep(5);
        system("clear");
    }
    return 0;
}