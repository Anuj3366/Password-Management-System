#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>

int key;

int make_key(char *password);
int enter_website(char *website);
int systemusername(char *system_username);
int systempassword(char *system_password);
int enter_username(char *filename, char *website, char *username, char *password);
int enter_password(char *filename, char *website, char *username, char *password);
bool passwordstrength(char *password);
bool username_check(char *filename, char *first);
bool password_check(char *filename, char *third);
bool id_check(char *filename, char *first, char *second);
void encrypt(char *third);
void decrypt(char *third);
void user_save(char *filename, char *first, char *second);
void password_save(char *filename, char *first, char *second, char *third);
void updating(char *filename, char *website, char *username, char *password);
void generate_password(char *filename, char *website, char *username, char *password);
void retrieve_password(char *filename, char *website, char *username, char *password);

int systemusername(char *system_username)
{
    FILE *file = fopen("user.txt", "a+");
    printf("Please enter your system's username: ");
    scanf("%s", system_username);
    while (getchar() != '\n')
        ; // Consume characters until a newline is encountered
    fclose(file);
    return 0;
}

int systempassword(char *system_password)
{
    printf("Please enter your system's password: ");
    scanf("%s", system_password);
    while (getchar() != '\n')
        ; // Consume characters until a newline is encountered
    return 0;
}

void user_save(char *filename, char *first, char *second)
{
    FILE *file = fopen(filename, "a+");
    fprintf(file, "%s||%s||\n", first, second);
    fclose(file);
}

int enter_website(char *website)
{
    printf("Enter the website's URL: ");
    scanf("%s", website);
    while (getchar() != '\n')
        ; // Consume characters until a newline is encountered
    if (strcmp(website, "exit") == 0)
    {
        printf("\nExiting...\n");
        return 1;
    }
    int i = 1;
    while (strlen(website) <= 6 || (strstr(website, "https://") == NULL && strstr(website, "www.") == NULL))
    {
        printf("\nThe website's URL is not valid. Please enter a valid website's URL.\n");
        printf("Enter the website's URL: ");
        scanf("%s", website);
        while (getchar() != '\n')
            ; // Consume characters until a newline is encountered
        if (strcmp(website, "exit") == 0)
        {
            printf("\nExiting...\n");
            return 1;
        }
        i++;
        if (i == 5)
        {
            printf("\nYou have entered an invalid website's URL 5 times. Please try again later.\n");
            printf("\nExiting...\n");
            return 1;
        }
    }
    return 0;
}

int enter_username(char *filename, char *website, char *username, char *password)
{
    printf("Enter the Username : ");
    scanf("%s", username);
    while (getchar() != '\n')
        ; // Consume characters until a newline is encountered
    if (strcmp(username, "exit") == 0)
    {
        printf("\nExiting...\n");
        return 1;
    }
    if (id_check(filename, website, username))
    {
        printf("\nThe username already exists. Would you like to Update it (press `1`) or retrieve it (Any other Number) or to retrieve and exit (any letters)?\n");
        printf("Enter your choice : ");
        int choice;
        scanf("%d", &choice);
        while (getchar() != '\n')
            ; // Consume characters until a newline is encountered
        if (choice == 1)
        {
            return 0;
        }
        else
        {
            printf("\nRetrieving...\n");
            retrieve_password(filename, website, username, password);
            return 1;
        }
    }
}

int enter_password(char *filename, char *website, char *username, char *password)
{
    printf("Enter the Password (Minimum 8 to 99 characters with Capital letter ,Small letters, digits, and special characters): ");
    scanf("%s", password);
    while (getchar() != '\n')
        ; // Consume characters until a newline is encountered
    if (strcmp(password, "exit") == 0)
    {
        printf("\nExiting...\n");
        return 1;
    }
    while (strlen(password) < 8 || !passwordstrength(password) || password_check(filename, password))
    {
        printf("\nInvalid input or password already exists, please enter a valid password or write exit to exit : ");
        scanf("%s", password);
        while (getchar() != '\n')
            ; // Consume characters until a newline is encountered
        if (strcmp(password, "exit") == 0)
        {
            printf("\nExiting...\n");
            return 1;
        }
    }
    if (id_check(filename, website, username))
    {
        updating(filename, website, username, password);
        return 1;
    }
    return 0;
}

void updating(char *filename, char *website, char *username, char *password)
{
    printf("\nUpdating...\n");
    FILE *file = fopen(filename, "r");
    FILE *file2 = fopen("passwords2.txt", "a");
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
                encrypt(password);
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
    remove(filename);
    rename("passwords2.txt", filename);
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
            printf("Invalid character %c. Only special characters like \"!\", \"@\", \"#\", \"$\", \"^\", \"&\", \"*\", \"(\", \")\", \"_\", \"+\", \"=\", and \"-\" are allowed in the password.\n", password[i]);
            return false;
        }
        if (a > 0 && b > 0 && c > 0 && d > 0)
        {
            return true;
        }
    }
    return false;
}

bool username_check(char *filename, char *first)
{
    FILE *file = fopen(filename, "r");
    char line[306];
    while (fgets(line, sizeof(line), file))
    {
        char first_check[100];
        char second_check[100];
        char third_check[100];

        if (sscanf(line, "%99[^||]||%99[^||]||%99s", first_check, second_check, third_check) == 3)
        {
            if (strcmp(first_check, first) == 0)
            {
                fclose(file);
                return true;
            }
        }
        else if (sscanf(line, "%99[^||]||%99[^||]", first_check, second_check) == 2)
        {
            if (strcmp(first_check, first) == 0)
            {
                fclose(file);
                return true;
            }
        }
    }
    fclose(file);
    return false;
}

bool id_check(char *filename, char *first, char *second)
{
    FILE *file = fopen(filename, "r");
    char line[306];
    while (fgets(line, sizeof(line), file))
    {
        char first_check[100];
        char second_check[100];
        char third_check[100];

        if (sscanf(line, "%99[^||]||%99[^||]||%99s", first_check, second_check, third_check) == 3)
        {
            if (strcmp(first_check, first) == 0 && strcmp(second_check, second) == 0)
            {
                fclose(file);
                return true;
            }
        }
        else if (sscanf(line, "%99[^||]||%99[^||]", first_check, second_check) == 2)
        {
            if (strcmp(first_check, first) == 0 && strcmp(second_check, second) == 0)
            {
                fclose(file);
                return true;
            }
        }
    }
    fclose(file);
    return false;
}

bool password_check(char *filename, char *third)
{
    FILE *file = fopen(filename, "r");
    char line[306];
    while (fgets(line, sizeof(line), file))
    {
        char first_check[100];
        char second_check[100];
        char third_check[100];
        if (sscanf(line, "%99[^||]||%99[^||]||%s", first_check, second_check, third_check) == 3)
        {   
            decrypt(third_check);
            if (strcmp(third_check, third) == 0)
            {
                fclose(file);
                return true;
            }
        }
        else if (sscanf(line, "%99[^||]||%99[^||]", first_check, second_check) == 2)
        {
            if (strcmp(second_check, third) == 0)
            {
                fclose(file);
                return true;
            }
        }
    }
    fclose(file);
    return false;
}

int make_key(char *password){
    int making_key = 0;
    for(int i = 0;i<strlen(password);i++){
        making_key += password[i];
    }
    key = making_key;
}

void encrypt(char *third){
    int key1 = make_key(key);
    for(int i = 0;i<strlen(third); i++){
        third[i] = third[i] + key;
    }
}

void decrypt(char *third){
    int key1 = make_key(key);
    for(int i = 0;i<strlen(third); i++){
        third[i] = third[i] - key;
    }
}

void password_save(char *filename, char *first, char *second, char *third)
{
    FILE *file = fopen(filename, "a+");
    encrypt(third);
    fprintf(file, "%s||%s||%s\n", first, second, third);
    fclose(file);
}

void generate_password(char *filename, char *website, char *username, char *password)
{
    FILE *file = fopen(filename, "a+");
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
    printf("Your password for the username %s and website %s is %s. Saving it now.\n", username, website, password);
    if (id_check(filename, website, username))
    {
        updating(filename, website, username, password);
    }
    else
    {
        password_save(filename, website, username, password);
    }
    sleep(5);
}

void retrieve_password(char *filename, char *website, char *username, char *password)
{
    FILE *file = fopen(filename, "r");
    char line[306];
    while (fgets(line, sizeof(line), file))
    {
        char website2[100];
        char username2[100];
        char password2[100];
        if (sscanf(line, "%99[^||]||%99[^||]||%s", website2, username2, password2) == 3)
        {
            if (strcmp(website2, website) == 0 && strcmp(username2, username) == 0)
            {
                decrypt(password2);
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
    while (getchar() != '\n')
        ; // Consume characters until a newline is encountered
    if (choice == 1)
    {
        generate_password(filename, website, username, password);
        return;
    }
    printf("Exiting...\n");
}

int main()
{
    system("clear");
    printf("\033[1mWelcome to the Password Management System.\033[0m\n\n");
    printf("\033[1mPlease note that this program is not secure. It is intended for demonstration purposes only.\033[0m\n\n\n");

    printf("\033[1mWould you like to:\033[0m\n");
    printf("1. Create a new account\n");
    printf("2. Log in to an existing account\n\n");

    int operationResult; // creating a variable to store the result of the operation
    int choice;
    int attempts = 0;
    while (1)
    {
        printf("\033[1m\nEnter your choice (1 or 2): \033[0m");
        attempts++;
        if (scanf("%d", &choice) != 1 || (choice != 1 && choice != 2))
        {

            while (getchar() != '\n')
                ; // Consume characters until a newline is encountered
            if (attempts == 5)
            {
                printf("\033[1m\nYou've entered an invalid input 5 times. It seems you might be having difficulty. Please try again later.\033[0m \n");
                exit(0);
            }

            printf("\033[1m\nInvalid input. valid choice are (1 or 2)\033[0m ");
        }
        else
        {
            break;
        }
    }

    printf("\n");

    char system_username[100]; // = "user";
    char system_password[100]; // = "1234";

    char filename[100] = "user.txt";

    if(choice == 1)
    {
        operationResult = systemusername(system_username);
        attempts = 1;
        while (username_check(filename, system_username))
        {
            if (attempts == 5)
            {
                printf("You've entered an invalid input 5 times. It seems you might be having difficulty. Please try again later.\n");
                return 0;
            }
            printf("Username already exists.");
            operationResult = systemusername(system_username);
            attempts++;
        }
        attempts = 0;
        printf("\nWARNING your password should only consist of positive numbers and should not be shared as it is used to encrypt and decrypt your passwords. WARNING\n");
        while (1)
        {
            if (attempts == 5)
            {
                printf("You've entered an invalid input 5 times. It seems you might be having difficulty. Please try again later.\n");
                exit(0);
            }
            operationResult = systempassword(system_password);
            attempts++;
            int i;
            for (i = 0; i < strlen(system_password); i++)
            {
                if (system_password[i] < '0' || system_password[i] > '9' || strlen(system_password) < 4)
                {
                    printf("\nInvalid input.");
                    break;
                }
            }
            if (i == strlen(system_password))
            {
                break;
            }
        }
        user_save(filename, system_username, system_password);
    }
    else
    {
        operationResult = systemusername(system_username);
        attempts = 1;
        while (!username_check(filename, system_username))
        {
            if (attempts == 5)
            {
                printf("You've entered an invalid input 5 times. It seems you might be having difficulty. Please try again later.\n");
                return 0;
            }
            printf("Username does not exist.");
            operationResult = systemusername(system_username);
            attempts++;
        }
        attempts = 0;
        while (1)
        {
            operationResult = systempassword(system_password);
            if (password_check(filename, system_password))
            {
                break;
            }
            else
            {
                printf("\nInvalid password.");
            }
        }
    }

    // makeing key
    make_key(system_password);

    // naming the file for the user to store passwords
    char file[100];
    strcpy(file, system_username);
    strcat(file, "_passwords.txt");

    // creating a file if it doesn't exist
    FILE *file2 = fopen(file, "a+");
    fclose(file2);



    while (1)
    {
        system("clear");
        printf("\n\n\033[1m%s\033[0m\n\n", "Please select an option:");
        printf("\033[1m%s\033[0m\n\n", "To exit , type 'exit' at any time to return to this menu.");
        printf("\033[1m%s\033[0m\n\n", "1. Save a new password (Press 1).");
        printf("\033[1m%s\033[0m\n\n", "2. View an existing stored password (Press 2).");
        printf("\033[1m%s\033[0m\n", "3. Generate a new strong password (Press 3).");
        printf("\n\n\n\033[1m%s\033[0m", "Enter your choice: ");

        if (scanf("%d", &choice) != 1)
        {
            // Exiting on invalid input
            printf("Exiting...\n");
            return 0;
        }
        while (getchar() != '\n')
            ; // Consume characters until a newline is encountered

        printf("\n");

        char website[100];
        char username[100];
        char password[100];

        switch (choice)
        {
        case 0:
            // Exiting gracefully
            printf("\nExiting...\n");
            return 0;
        case 1:
            // Saving a new password
            operationResult = enter_website(website);
            if (operationResult == 1)
            {
                break;
            }
            operationResult = enter_username(file, website, username, password);
            if (operationResult == 1)
            {
                break;
            }
            operationResult = enter_password(file, website, username, password);
            if (operationResult == 1)
            {
                break;
            }
            password_save(file, website, username, password);
            break;
        case 2:
            // Viewing an existing password
            operationResult = enter_website(website);
            if (operationResult == 1)
            {
                break;
            }
            printf("Enter the Username : ");
            scanf("%s", username);
            while (getchar() != '\n')
                ; // Consume characters until a newline is encountered
            retrieve_password(file, website, username, password);
            break;
        case 3:
            // Generating a new strong password
            operationResult = enter_website(website);
            if (operationResult == 1)
            {
                break;
            }
            operationResult = enter_username(file, website, username, password);
            if (operationResult == 1)
            {
                break;
            }
            printf("Generating Password...\n");
            generate_password(file, website, username, password);
            break;
        default:
            // Exiting on an unknown choice
            printf("Exiting...\n");
            return 0;
        }

        // Sleep for 5 seconds before clearing the screen and presenting the menu again
        sleep(5);
    }
    return 0;
}