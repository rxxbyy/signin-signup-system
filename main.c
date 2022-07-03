/*
    Simple exercise program to administrate user's sign up and sign in
    using file's functions from <stdio.h>.

    date: July 03, 2022.
    author: Manuel Rubio (rxxbyy)
*/
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

/*
 Function prototypes
*/
bool searchUser(char *username);
void registerUser(char *username, char *password);
bool logInUser(char *username, char *password);

/*
 Symbolic constants
*/
#define MAX_USERNAME_LEN 50 /* max input length for a username */
#define MAX_PASSWORD_LEN 100 /* max input length for a password */
#define USERS_FILENAME "users.dat" /* filename where users going to be saved */


int main(void)
{
    char inputUsername[MAX_USERNAME_LEN]; /* string to input a username */
    char inputPassword[MAX_PASSWORD_LEN]; /* string to input a password */
    int menuOption; /* input the menu selection */
    bool activeUser = false;

    printf("M A I N  P A G E\n");
    
    /* starting the program mainloop */
    while (!activeUser) {
        printf("Select an option:\n"
            "1 - Sign Up\n"
            "2 - Sign In\n"
            "3 - Exit Program\n? ");
        scanf("%d", &menuOption);

        bool userExists;
        switch (menuOption) {
            case 1:
                do {
                    printf("Enter a username: ");
                    scanf("%50s", inputUsername);

                    userExists = searchUser(inputUsername);
                    if (userExists) { /* if the input username already exists, we ask for another username  */
                        printf("There's an user with that username. "
                            "Try another one.\n");
                    }

                } while (userExists);

                printf("Set up your password: ");
                scanf("%100s", inputPassword);

                registerUser(inputUsername, inputPassword);

                break;
            case 2:
                do {
                    printf("Enter your username: ");
                    scanf("%50s", inputUsername);

                    userExists = searchUser(inputUsername);
                    if (!userExists) { /* if the username isn't found, we ask for another username */
                        printf("User does not found. "
                        "Try another username.\n");
                    }

                } while (!userExists);

                printf("Enter your password: ");
                scanf("%100s", inputPassword);

                /* we call to `logInUser` function that will return true if the 
                    user was successfully logged in (credentials matched). It will return
                    false otherwise. */
                if (logInUser(inputUsername, inputPassword)) {
                    printf("Welcome, %50s!\n", inputUsername);
                    activeUser = true;
                } else {
                    printf("Incorrect password\n");
                }

                break;
            
            default:
                exit(0);
        }
    }

    return 0;
}

/* Check if `targetUsername` argument matches a username in 
    our users file */
bool searchUser(char *targetUsername)
{
    char username[MAX_USERNAME_LEN];
    FILE *usersFile;

    if ( (usersFile = fopen(USERS_FILENAME, "r")) != NULL) {

        /* reading the users file until EOF */
        while (!feof(usersFile)) {
            fscanf(usersFile, "%s %s\n", username, NULL);

            if (strcmp(username, targetUsername) == 0) {
                fclose(usersFile);

                return true;
            }
        }

        fclose(usersFile);
    }

    return false;
}

/* Write the username and password passed by argument
in users file */
void registerUser(char *username, char *password)
{
    FILE *usersFile;

    if ( (usersFile = fopen(USERS_FILENAME, "a+")) == NULL ) {
        fprintf(stderr, "Can't open user's file\n");
    } else {
        fprintf(usersFile, "%s %s\n", username, password);
    }

    fclose(usersFile);
}

/* It returns if user credentials matches in the users file */
bool logInUser(char *targetUsername, char *targetPassword)
{
    char username[MAX_USERNAME_LEN];
    char password[MAX_PASSWORD_LEN];

    FILE *usersFile;

    if ( (usersFile = fopen(USERS_FILENAME, "r")) == NULL ) {
        fprintf(stderr, "Can't open user's file\n");
    } else {
        /* Reading users file until EOF */
        while (!feof(usersFile)) {
            fscanf(usersFile, "%s %s", username, password);

            if (strcmp(username, targetUsername) == 0 &&
                strcmp(password, targetPassword) == 0) {
                    fclose(usersFile);
                    return true;
                }
        }

        fclose(usersFile);

        return false;
    }
}