#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

bool passwordstrength(char url[], char username[], char password[])
{
    bool isStrong = true;
    printf("Checking if the password is strong enough... ");
    int length = strlen(password);
    if (length < 8)
    {
        return false;
    }
    else
    {
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
    }
    return true;
}


bool idexists(char url[], char username[], char password[]){
    FILE *file = fopen("passwords.xls", "r");
    char line[310];
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

bool passwordexists(char url[], char username[], char password[]){
    FILE *file = fopen("passwords.xls", "r");
    char line[310];
    while (fgets(line, sizeof(line), file))
    {
        char url2[100];
        char username2[100];
        char password2[100];
        if (sscanf(line, "%99[^||]||%99[^||]||%99s", url2, username2, password2) == 3)
        {
            if (strcmp(password2, password))
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
    while(idexists(url, username, password) && passwordstrength(url, username, password)){
        printf("Password already exists or is not strong enough, please enter a new password : ");
        scanf("%s",password);
    }
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
    while(idexists(url, username, password) && passwordstrength(url, username, password)){
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
    char line[310];
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
