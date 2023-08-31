#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

void enterurl(char url[]);
void enterusername(char url[],char username[]);
void enterpassword(char url[],char username[],char password[]);
bool passwordstrength(char url[], char username[], char password[]);
bool idexists(char url[], char username[]);
bool passwordexists(char url[], char username[], char password[]);
void savepassword(char url[], char username[], char password[]);
void generatepassword(char url[], char username[]);
void retrievepassword(char url[], char username[]);

void enterurl(char url[])
{
    printf("Enter the URL: ");
    scanf("%s", url);
}

void enterusername(char url[],char username[])
{
    printf("Enter the Username : ");
    scanf("%s", username);
    if (idexists(url, username))
    {
        printf("id already exists , would you like to overwrite it or retrieve it? (1 for overwrite and any other number for retrieve)\n");
        int choice;
        scanf("%d", &choice);
        if (choice == 1)
        {
            printf("Overwriting...\n");
            FILE *file = fopen("passwords.xls", "r");
            FILE *file2 = fopen("passwords2.xls", "a");
            char line[300];
            while (fgets(line, sizeof(line), file))
            {
                char url2[100];
                char username2[100];
                char password2[100];
                if (sscanf(line, "%99[^||]||%99[^||]||%99s", url2, username2, password2) == 3)
                {
                    if (strcmp(url2, url) == 0 && strcmp(username2, username) == 0)
                    {
                        fprintf(file2, "%s||%s||%s\n", url, username);
                    }
                    else
                    {
                        fprintf(file2, "%s||%s||%s\n", url2, username2, password2);
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
        else
        {
            printf("Retrieving...\n");
            retrievepassword(url, username);
            return;
        }
    }
}

void enterpassword(char url[],char username[],char password[]){
    printf("Enter the Password : ");
    scanf("%s", password);
    while (passwordstrength(url, username, password))
    {
        if (strcmp(password, "exit") == 0)
        {
            printf("Exiting...\n");
            return;
        }
        printf("Password is not strong enough, please enter a new password or write exit to exit : ");
        scanf("%s", password);
    }
    while(passwordexists(url, username, password))
    {
        printf("Password already exists , would you like to overwrite it or retrieve it? (1 for overwrite and any other number for retrieve)\n");
        int choice;
        scanf("%d", &choice);
        if (choice == 1)
        {
            printf("Overwriting...\n");
            FILE *file = fopen("passwords.xls", "r");
            FILE *file2 = fopen("passwords2.xls", "a");
            char line[300];
            while (fgets(line, sizeof(line), file))
            {
                char url2[100];
                char username2[100];
                char password2[100];
                if (sscanf(line, "%99[^||]||%99[^||]||%99s", url2, username2, password2) == 3)
                {
                    if (strcmp(url2, url) == 0 && strcmp(username2, username) == 0)
                    {
                        fprintf(file2, "%s||%s||%s\n", url, username, password);
                    }
                    else
                    {
                        fprintf(file2, "%s||%s||%s\n", url2, username2, password2);
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
        else
        {
            printf("Retrieving...\n");
            retrievepassword(url, username);
            return;
        }
    }
    while (passwordstrength(url, username, password) || passwordexists(url, username, password))
    {
        if (strcmp(password, "exit") == 0)
        {
            printf("Exiting...\n");
            return;
        }
        printf("Password or username already exists or is not strong enough, please enter a new password or write exit to exit : ");
        scanf("%s", password);
    }
}

bool passwordstrength(char url[], char username[], char password[])
{
    bool isStrong = true;
    int length = strlen(password);
    for (int i = 0; i < length; i++)
    {
        if (password[i] >= '0' && password[i] <= '9')
        {
            isStrong = true;
        }
        else if (password[i] >= 'a' && password[i] <= 'z')
        {
            isStrong = true;
        }
        else if (password[i] == '!' || password[i] == '@' || password[i] == '#' || password[i] == '$' || password[i] == '%' || password[i] == '^' || password[i] == '&' || password[i] == '*' || password[i] == '(' || password[i] == ')' || password[i] == '-' || password[i] == '_' || password[i] == '+' || password[i] == '=' || password[i] == '{' || password[i] == '}' || password[i] == '[' || password[i] == ']' || password[i] == ':' || password[i] == ';' || password[i] == '"' || password[i] == '\'' || password[i] == '<' || password[i] == '>' || password[i] == ',' || password[i] == '.' || password[i] == '?' || password[i] == '/' || password[i] == '`' || password[i] == '~')
        {
            isStrong = true;
        }
        else if (strstr(password, username) != NULL)
        {
            return false;
        }
        else if (strstr(password, url) != NULL)
        {
            return false;
        }
        else
        {
            return false;
        }
    }
    return isStrong;
}

bool idexists(char url[], char username[])
{
    FILE *file = fopen("passwords.xls", "r");
    char line[300];
    while (fgets(line, sizeof(line), file))
    {
        char url2[100];
        char username2[100];
        char password2[100];
        if (sscanf(line, "%99[^||]||%99[^||]||%99s", url2, username2, password2) == 3)
        {
            if (strcmp(url2, url) == 0 && strcmp(username2, username) == 0)
            {
                return true;
            }
        }
    }
    return false;
}

bool passwordexists(char url[], char username[], char password[])
{
    FILE *file = fopen("passwords.xls", "r");
    char line[300];
    while (fgets(line, sizeof(line), file))
    {
        char url2[100];
        char username2[100];
        char password2[100];
        if (sscanf(line, "%99[^||]||%99[^||]||%99s", url2, username2, password2) == 3)
        {
            if (strcmp(password2, password) == 0)
            {
                return true;
            }
        }
    }
    return false;
}

void savepassword(char url[], char username[], char password[])
{
    FILE *file = fopen("passwords.xls", "a");
    fprintf(file, "%s||%s||%s\n", url, username, password);
    fclose(file);
    printf("Password Saved Successfully\n");
}

void generatepassword(char url[], char username[])
{
    FILE *file = fopen("passwords.xls", "a");
    char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$^&*_+:?></'=~";
    int length = 10;
    char password[length + 1];
    srand(time(NULL));
    while (!passwordstrength(url, username, password))
    {
        for (int i = 0; i < length; i++)
        {
            password[i] = charset[rand() % (strlen(charset))];
        }
        password[length] = '\0';
    }
    printf("Your password is %s for the username %s & URL %s. Now saving it\n", password, username, url);
    savepassword(url, username, password);
}

void retrievepassword(char url[], char username[])
{
    FILE *file = fopen("passwords.xls", "r");
    char line[300];
    while (fgets(line, sizeof(line), file))
    {
        char url2[100];
        char username2[100];
        char password2[100];
        if (sscanf(line, "%99[^||]||%99[^||]||%99s", url2, username2, password2) == 3)
        {
            if (strcmp(url2, url) == 0 && strcmp(username2, username) == 0)
            {
                printf("URL : %s , Username : %s , Password : %s\n", url2, username2, password2);
                fclose(file);
                return;
            }
        }
    }
    fclose(file);
    printf("Password not found, would you like to generate it? (1 for Yes and Any other number for No)\n");
    int choice;
    scanf("%d", &choice);
    if (choice == 1)
    {
        generatepassword(url, username);
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
    int key = 0;
    int realkey = 0;
    // printf("To start enter your key : ");
    // scanf("%d",key);
    // while(key>0){
    //	int a =
    // }
    int choice;
    while (choice != 4)
    {
        printf("\n\n");
        printf("Enter your choice : ");
        scanf("%d", &choice);
        printf("\n");
        char url[100];
        char username[100];
        char password[100];
        switch (choice)
        {
        case 1:
            enterurl(url);
            enterusername(url, username);
            enterpassword(url, username, password);
            printf("\n");
            savepassword(url, username, password);
            break;
        case 2:
            enterurl(url);
            enterusername(url, username);
            retrievepassword(url, username);
            break;
        case 3:
            enterurl(url);
            enterusername(url, username);
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
