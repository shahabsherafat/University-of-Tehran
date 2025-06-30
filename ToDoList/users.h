#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include <io.h>


typedef struct Users
{
    char *username;
    char *password;
} User;
int Searchuser(User *usersarray , int numofusers , char *username , char *password , int entertype){
    switch (entertype)
    {
    case 0://checking for the signup state
        for (int i = 0 ;i < numofusers ;i++){
            if (!strcmp(usersarray[i].username , username)){
                return 0;//If the username is already taken,it'll return 0;
            }
        }
        return 1;//If the username is not already taken,it'll return 1;
    
    case 1://checking for the login state
        for (int i = 0 ;i < numofusers ;i++){
            if (!strcmp(usersarray[i].username , username) && !strcmp(usersarray[i].password , password)){
                return 2;//If the username and password correspond,it'll return 2;
            }
        }
        return 3;//If the username and password don't correspond,it'll return 3;
    }
}
void Loginorsignup()
{
    char *entertype = (char *)malloc(1), *username = (char *)malloc(1), *password = (char *)malloc(1);
    int counter = 1, flag = 0 , singlechar , state = 0 , numofusers = 0;
    char check;
    FILE *Usersfile;
    User *usersarray = (User *)malloc(sizeof(User));

    Usersfile = fopen("Usersfile.csv", "a+");

    usersarray[numofusers].username = (char*)malloc(1);
    usersarray[numofusers].password = (char*)malloc(1);
    counter = 1;
    singlechar = getc(Usersfile);
    while (singlechar != EOF)
    {
        if (singlechar != ' ' && singlechar != ','){
            switch (state%2)
            {
            case 0:
                usersarray[numofusers].username = (char*)realloc(usersarray[numofusers].username , counter + 1);
                usersarray[numofusers].username[counter - 1] = (char)singlechar;
                counter ++;
                break;
            
            case 1:
                usersarray[numofusers].password = (char*)realloc(usersarray[numofusers].password , counter + 1);
                usersarray[numofusers].password[counter - 1] = (char)singlechar;
                counter ++;
                break;
            }
        }
        if (singlechar == ' '){
            usersarray[numofusers].username[counter-1] = '\0';
            counter = 1;
            state ++;
        }
        if (singlechar == ','){
            usersarray[numofusers].password[counter-1] = '\0';
            numofusers ++;
            usersarray = (User *)realloc(usersarray , sizeof(User) * (numofusers+1));
            usersarray[numofusers].username = (char*)malloc(1);
            usersarray[numofusers].password = (char*)malloc(1);
            counter = 1;
            state ++;
        }
        singlechar = getc(Usersfile);
    }
    /*********************************************************************/
    //Getting the information faze!
    /*********************************************************************/
    printf("Welcome!\nPlease enter your information to enter UTBOARD!\n");
    while (78){
        entertype = (char *)realloc(entertype, 7);
        counter = 1;

        fflush(stdin);
        scanf("%6s", entertype);
        if (strcmp("signup", entertype) != 0 && strcmp("login", entertype) != 0)
        {
            printf("Wrong input format,please try again!\n");
            fflush(stdin);
            continue;
        }

        check = getchar();
        if (check != ' ')
        {
            printf("Wrong input format,please try again!\n");
            fflush(stdin);
            continue;
        }
        check = getchar();
        if (check != '<')
        {
            printf("Wrong input format,please try again!\n");
            fflush(stdin);
            continue;
        }
        check = getchar();
        while (1)
        {
            if (check == ' ' || check == '\n' || check == ',' || check == '/' || check == '\\' || check == '?' || 
            check == ':' || check == '*' || check == '?' || check == '"' || check == '<' || check == '|')
            {
                flag = 1;
                break;
            }
            if (check == '>')
            {
                break;
            }
            username = (char *)realloc(username, counter + 1);
            username[counter - 1] = check;
            check = getchar();
            counter++;
        }
        if (flag || counter == 1)
        {
            printf("Wrong input format,please try again!\n");
            fflush(stdin);
            flag = 0;
            free(username);
            username = (char *)malloc(0);
            continue;
        }
        username[counter - 1] = '\0';
        counter = 1;

        check = getchar();
        if (check != ' ')
        {
            printf("Wrong input format,please try again!\n");
            fflush(stdin);
            continue;
        }
        check = getchar();
        if (check != '<')
        {
            printf("Wrong input format,please try again!\n");
            fflush(stdin);
            continue;
        }
        check = getchar();
        while (1)
        {
            if (check == ' ' || check == '\n' || check == ',')
            {
                flag = 1;
                break;
            }
            if (check == '>')
            {
                break;
            }
            password = (char *)realloc(password, counter + 1);
            password[counter - 1] = check;
            check = getchar();
            counter++;
        }
        if (flag || counter == 1)
        {
            printf("Wrong input format,please try again!\n");
            fflush(stdin);
            flag = 0;
            free(password);
            password = (char *)malloc(0);
            continue;
        }
        password[counter - 1] = '\0';
        /*Signup and login evaluating and problem fixings*/
        if (!strcmp(entertype, "signup"))
        {
            state = Searchuser(usersarray ,numofusers , username , NULL , 0);
            if (state == 0){
                printf("This username already exists,please choose another one :)\n");
                printf("Enter your information and entertype exactly how you used to!\n");
                continue;
            }
            else{
                system("color 5");
                printf("Successfully enrolled!\n");
                fprintf(Usersfile, "%s %s,", username, password);
                printf("Welcome %s!\n" , username);
                mkdir(username);
                chdir(username);
                Sleep(2000);
                system("color A");
                system("cls");
                break;
            }
        }
        if (!strcmp(entertype, "login"))
        {
            state = Searchuser(usersarray ,numofusers , username , password , 1);
            if (state == 2){
                system("color 5");
                printf("Successfully logged in!\n");
                printf("Welcome %s!\n" , username);
                chdir(username);
                Sleep(2000);
                system("color A");
                system("cls");
                break;
            }
            else{
                printf("The entered username and password don't match or no account exists with this username,please try again :)\n");
                printf("Enter your information and entertype exactly how you used to!\n");
                continue;
            }
        }
        break;
    }


    //FREEING THE ALLOCATED MEMORIES AND CLOSING THE USERSFILE,THEY ARE A LOT!!!
    for (int i = 0 ;i <= numofusers ;i++){
        free(usersarray[i].username);
        free(usersarray[i].password);
    }
    free(usersarray);
    free(entertype);free(username);free(password);
    fclose(Usersfile);
}