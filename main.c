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
    printf("Enter the Password (Minimum 8 to 99 characters with Capital letter ,Small letters, digits, and special characters): ");
    scanf("%s", password);
    if (strcmp(password, "exit") == 0)
    {
        printf("\nExiting...\n");
        return 1;
    }
    while (strlen(password) < 8 || !passwordstrength(password) || passwordexists(website, username, password))
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
    if (length < 8)
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
        else if (strchr("!@#$^&*()_+=-~", password[i]))
        {
            d++;
        }
        else
        {
            printf("Invalid character \"%c\". Only special characters like \"!\", \"@\", \"#\", \"$\", \"^\", \"&\", \"*\", \"(\", \")\", \"_\", \"+\", \"=\", and \"-\" are allowed in the password.\n", password[i]);
            return false;
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
    char charset1[] = "0123456789";
    char charset2[] = "abcdefghijklmnopqrstuvwxyz";
    char charset3[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char charset4[] = "!@#$^&*()_+=-~";
    int length = 10;
    srand(time(NULL));
    password[0] = charset1[rand() % (sizeof(charset1) - 1)];
    password[1] = charset2[rand() % (sizeof(charset2) - 1)];
    password[2] = charset3[rand() % (sizeof(charset3) - 1)];
    password[3] = charset4[rand() % (sizeof(charset4) - 1)];
    for (int i = 4; i < length; i++)
    {
        password[i] = charset[rand() % (sizeof(charset) - 1)];
    }
    for (int i = 0; i < length; i++)
    {
        int j = rand() % length;
        char temp = password[i];
        password[i] = password[j];
        password[j] = temp;
    }
    password[length] = '\0';
    printf("Your password for the username %s and website %s is %s. I'm saving it now.\n", username, website, password);
    if (idexists(website, username))
    {
        updating(website, username, password);
    }
    else
    {
        savepassword(website, username, password);
    }
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
    printf("Enter your choice : ");
    scanf("%d", &choice);
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

    // int width = 150;
    // for(int i = 21;i<(width)/2;i++)
    // {
    //     printf(" ");
    // }

    printf("\033[1m%s\033[0m\n\n", "Welcome to the Password Management System.\n");
    printf("\033[1m%s\033[0m\n", "Please remember that this is a password management system, not a password manager. This means that you can only store one password per website, and it is case-sensitive.\n\n");
    int b;
    int choice;
    while (1)
    {
        printf("\n\n");
        printf("\033[1m%s\033[0m\n", "Please select an option:\n");
        printf("\033[1m%s\033[0m\n", "To exit, type Anything or 0. You can also type \"exit\" at any time to return to this menu.\n");
        printf("\033[1m%s\033[0m\n", "1. Save a new password (Press 1).\n");
        printf("\033[1m%s\033[0m\n", "2. View an existing stored password (Press 2).\n");
        printf("\033[1m%s\033[0m\n", "3. Generate a new strong password (Press 3).\n");
        printf("\n\n");
        printf("\033[1m%s\033[0m", "Enter your choice: ");

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