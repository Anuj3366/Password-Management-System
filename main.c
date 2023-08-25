#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

void savepassword(char username[], char password[])
{
    FILE *file = fopen("passwords.txt", "a");
    fprintf(file, "%s:%s\n", username, password);
    fclose(file);
    printf("Password Saved Successfully\n");
}

int main()
{
    printf("Do you want to create a new password or view an existing one?\n");
    printf("1. Save a new password\n");
    printf("2. View an existing password\n");
    printf("3. Genereate a new Strong Password\n");
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
        // case 2:
        //     printf("Enter the Username :");
        //     scanf("%s", username);
        //     retrievepassword(username);
        //     break;
        // case 3:
        //     printf("Enter the Username :");
        //     scanf("%s", username);
        //     printf("Generating Password...\n");
        //     generatepassword(username);
        case 4:
            printf("Exiting...\n");
            break;
        default:
            printf("Invalid Choice\n");
            break;
        }
    }
}