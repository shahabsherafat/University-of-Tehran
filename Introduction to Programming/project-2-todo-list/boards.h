#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <io.h>
#include <windows.h>

typedef struct Boards
{
    char *name;
    struct Boards *next;
}Board;

int Countboards(FILE *Boardsfile){
    int counter = 0;
    char c;
    
    c = fgetc(Boardsfile);
    while (c != EOF){
        if (c == ','){
            counter ++;
        }
        c = fgetc(Boardsfile);
    }

    return counter;
}

Board *Createboardnode(void){
    Board *board;
    board = (Board*)malloc(sizeof(Board));
    board->next = NULL;
    return board;
}

int Printboards(Board head ,int num_of_boards){
    Board *temp = &head;
    
    int i = 0;
    if (num_of_boards == 0){
        system("color 4");
        printf("You have no boards!\n");
        Sleep(2000);
        system("color A");
        system("cls");
        return 0;
    }
    printf("Your Boards:\n");
    while (i < num_of_boards){
        temp = temp->next;
        printf("%d.%s\n" , i+1 , temp -> name);
        if (temp->next == NULL){
            break;
        }
        i++;
    }
    printf("%d.Get Back To The Boards Menu\n" , num_of_boards + 1);

    int x=0;
    fflush(stdin);
    while (1){
        printf("Which board do you wanna enter?(Enter it's number) : ");scanf("%d" , &x);
        if (!(x>=1 && x<=(num_of_boards+1))){
            printf("Wrong choice number , try again!\n");
            fflush(stdin);
            continue;
        }
        break;
    }

    return (x);
}

int Boardsmenu(void){
    printf("What can I do for you?\n");
    printf("1.View Boards\n");
    printf("2.Add A New Board\n");
    printf("3.Omit A Board\n");
    printf("4.Exit the app\n");
    int order;
    printf("Enter your choice : ");
    scanf("%d" , &order);
    fflush(stdin);
    return order;
}

int Omitboard(Board *head ,int *num_of_boards , Board **end){
    system("cls");
    int boardnum;
    Board *temp = head;
    printf("Which board do you wanna omit(Enter its number)?\n");
    boardnum = Printboards(*head,*num_of_boards);
    if (boardnum == *num_of_boards + 1 || boardnum == 0){
        system("cls");
        return 0;
    }
    
    FILE *newboards;
    newboards = fopen("Boardsfile.csv" , "w");
    for (int i = 0;i < boardnum-1;i++){
        temp = temp->next;
    }
    Board *deleted = temp->next;
    temp->next = (temp->next)->next;
    //Fixing the function if the user has omitted the last board.
    if (boardnum == *num_of_boards){
        (*end) = temp;
    }
    //Fixing the function if the user has omitted the first board.
    if (*num_of_boards==1){
        (*end) = Createboardnode();
        head->next = (*end);
    }

    *num_of_boards = *num_of_boards - 1;
    //Writing the new boards on the file.
    temp = head;
    for(int i = 0;i<*num_of_boards;i++){
        temp = temp->next;
        fprintf(newboards , "%s," , temp -> name);
    }
    fclose(newboards);

    system("cls");
    system("color 6");
    printf("The board < %s > was successfully omitted!" , deleted -> name);
    Sleep(2000);
    system("color A");
    system("cls");
    //Freeing the omited board.
    int deletednamelen = strlen(deleted->name);
    char cmd[deletednamelen + 7];
    sprintf(cmd,"del /q %s",deleted->name);
    system(cmd);
    rmdir(deleted->name);
    free(deleted->name);
    free(deleted);
    return 1;
}

int Addnewboard(Board **end , Board head , int *num_of_boards){
    char *boardname = (char *)malloc(1) , singlechar;
    int namelen = 0;
    Board *temp = &head , *newend = Createboardnode();
    printf("Enter your new board's name:\n");
    fflush(stdin);
    singlechar = getchar();
    if(singlechar == '\n' || singlechar == ' ' || singlechar == '/' || singlechar == '\\' || singlechar == '?' || 
            singlechar == ':' || singlechar == '*' || singlechar == '?' || singlechar == '"'
             || singlechar == '<' || singlechar == '>' || singlechar == '|'){
        printf("Wrong boardname format!\n");
        free(boardname);
        return 0;
    }
    while(1){
        if (singlechar == ','){
            printf("Wrong boardname format!\n");
            free(boardname);
            return 0;
        }
        if (singlechar == '\n'){
            break;
        }
        namelen++;
        boardname = (char *)realloc(boardname , namelen + 1);
        boardname[namelen-1] = singlechar;
        singlechar = getchar();
    }
    boardname[namelen] = '\0';
    //Searching the boards list to check if the board with that name already exists or not.
    for (int i = 0;i<*num_of_boards;i++){
        temp = temp -> next;
        if (!strcmp(boardname , temp -> name)){
            system("color 4");
            printf("This board already exists,you can't add it!\n");
            Sleep(2000);
            system("color A");
            free(boardname);
            system("cls");
            return 0;
        }
    }
    if (*num_of_boards == 0){
        (*end)->name = boardname;
    }
    else{
        newend -> name = boardname;(*end) -> next = newend;(*end) = newend;
    }
    //Adding the new board to the file of boards.
    FILE *Boardsfile = fopen("Boardsfile.csv" , "a+");
    fprintf(Boardsfile , "%s," , boardname);
    fclose(Boardsfile);

    mkdir(boardname);
    system("cls");
    system("color 6");
    printf("Your new board was successfully added!\n");(*num_of_boards) ++;
    Sleep(2000);
    system("color A");
    system("cls");
    return 1;
}

int Manageboards(void){
    FILE *Boardsfile = fopen("Boardsfile.csv" , "a+");
    int num_of_boards = Countboards(Boardsfile),boardlength = 1,order = 0;
    char singlechar;
    Board head , *temp ,*end , *freed;;
    fseek(Boardsfile,0,SEEK_SET);//Countboards function has moved my file curser to the end of file.

    //**************************************
    //Creating the nodes of the linked list.
    temp = Createboardnode();
    head.next = temp;
    end = head.next;
    for (int i = 0;i<num_of_boards-1;i++){
        end = Createboardnode();
        temp->next = end;
        temp = end;
    }
    //Allocating memmory to each board's elemets.
    temp = &head;
    for (int i = 0;i<num_of_boards;i++){
        temp = temp -> next;
        temp->name = (char*)malloc(0);
    }
    //Reading information.
    singlechar = fgetc(Boardsfile);
    temp = &head;
    for (int i = 0;i<num_of_boards;i++){
        temp = temp -> next;
        boardlength = 1;
        while (singlechar != ','){
            temp -> name = (char*)realloc(temp -> name , boardlength + 1);
            temp -> name[boardlength - 1] = singlechar;
            boardlength++;
            singlechar = fgetc(Boardsfile);
        }
        boardlength--;
        singlechar = fgetc(Boardsfile);
        temp -> name[boardlength] = '\0';
    }
    //**************************************
    int flag = 1;
    while(flag){
        order = Boardsmenu();
        switch (order)
        {
        case 1:
            system("cls");
            order = Printboards(head , num_of_boards);
            if (order == num_of_boards+1){
                system("cls");
                continue;
            }
            else if (order == 0){
                continue;
            }
            else{
                system("cls");
                temp = &head;
                for (int i = 0;i<order;i++){
                    temp = temp -> next;
                }
                chdir(temp->name);
                system("color 5");
                printf("You have entered the board < %s >!" , temp -> name);
                Sleep(2000);
                system("color A");
                system("cls");
                flag = 0;
            }
            break;
        case 2:
            fclose(Boardsfile);
            Addnewboard(&end , head , &num_of_boards);
            Boardsfile = fopen("Boardsfile.csv" , "a+");
            break;
        case 3:
            fclose(Boardsfile);
            Omitboard(&head,&num_of_boards,&end);
            Boardsfile = fopen("Boardsfile.csv" , "a+");
            break;
        case 4:
            //Freeing
            temp = &head;
            for (int i = 0;i<num_of_boards;i++){
                freed = temp;
                temp = temp -> next;
                free(temp -> name);
                free(freed);
            }
            free(temp);
            fclose(Boardsfile);
            return -1;
        default:
            system("color 4");
            printf("We have no other options,choose one of these four!\n");
            Sleep(2000);
            system("color A");
            system("cls");
            break;
        }
    }
    //Closing files and freeing allocated memories.
    temp = &head;
    for (int i = 0;i<num_of_boards;i++){
        freed = temp;
        temp = temp -> next;
        free(temp -> name);
        free(freed);
    }
    free(temp);
    fclose(Boardsfile);
    return 0;
}

//I should have a dynamic array for my boards and when I wanted to remove any board from it,I should delete the 
//corresponding name to that board from my array.After that in the last step I gotta rewrite the boardsnames file 
//according to my array.
