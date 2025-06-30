#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <io.h>
#include <windows.h>

typedef struct Lists{
    char *name;
    int num_of_tasks;
    struct Lists *next;
}List;

int Countlists(FILE *Listsfile){
    int counter = 0;
    char c;
    
    c = fgetc(Listsfile);
    while (c != EOF){
        if (c == ','){
            counter ++;
        }
        c = fgetc(Listsfile);
    }

    fseek(Listsfile,0,SEEK_SET);//Countlists function has moved my file curser to the end of file.

    return counter;
}

List *Createlistnode(void){
    List *list;
    list = (List*)malloc(sizeof(List));
    list->next = NULL;
    return list;
}

int Printlists(List head ,int num_of_lists){
    List *temp = &head;
    
    int i = 0;
    if (num_of_lists == 0){
        system("color 4");
        printf("You have no lists!\n");
        Sleep(2000);
        system("color A");
        system("cls");
        return 0;
    }
    printf("Your Lists:\n");
    while (i < num_of_lists){
        temp = temp->next;
        printf("%d.%s\n" , i+1 , temp -> name);
        if (temp->next == NULL){
            break;
        }
        i++;
    }
    printf("%d.Get Back To The Lists Menu\n" , num_of_lists + 1);

    int x=0;
    fflush(stdin);
    while (1){
        printf("Which list do you wanna enter?(Enter it's number) : ");scanf("%d" , &x);
        if (!(x>=1 && x<=(num_of_lists+1))){
            printf("Wrong choice number , try again!\n");
            fflush(stdin);
            continue;
        }
        break;
    }

    return (x);
}

int Listsmenu(void){
    printf("What can I do for you?\n");
    printf("1.View Lists\n");
    printf("2.Add A New List\n");
    printf("3.Omit A List\n");
    printf("4.Get Back To The Boards Menu\n");

    int order;
    printf("Enter your choice : ");
    scanf("%d" , &order);
    fflush(stdin);
    return order;
}

int Omitlist(List *head ,int *num_of_lists , List **end){
    system("cls");
    int listnum;
    List *temp = head;
    printf("Which list do you wanna omit(Enter its number)?\n");
    listnum = Printlists(*head,*num_of_lists);
    if (listnum == *num_of_lists + 1 || listnum == 0){
        system("cls");
        return 0;
    }
    
    FILE *newlists;
    newlists = fopen("Listsfile.csv" , "w");
    for (int i = 0;i < listnum-1;i++){
        temp = temp->next;
    }
    List *deleted = temp->next;
    temp->next = (temp->next)->next;
    //Fixing the function if the user has omitted the last list.
    if (listnum == *num_of_lists){
        (*end) = temp;
    }
    //Fixing the function if the user has omitted the first list.
    if (*num_of_lists==1){
        (*end) = Createlistnode();
        head->next = (*end);
    }

    *num_of_lists = *num_of_lists - 1;
    //Writing the new lists on the file.
    temp = head;
    for(int i = 0;i<*num_of_lists;i++){
        temp = temp->next;
        fprintf(newlists , "%s," , temp -> name);
    }
    fclose(newlists);

    system("cls");
    system("color 6");
    printf("The list < %s > was successfully omitted!" , deleted -> name);
    Sleep(2000);
    system("color A");
    system("cls");
    //Freeing the omited list.
    int deletednamelen = strlen(deleted->name);
    char deletedlist[deletednamelen + 4];
    sprintf(deletedlist,"%s.csv",deleted->name);
    remove(deletedlist);
    free(deleted->name);
}

int Addnewlist(List **end , List head , int *num_of_lists){
    char *listname = (char *)malloc(1) , singlechar;
    int namelen = 0;
    List *temp = &head , *newend = Createlistnode();
    printf("Enter your new list's name:\n");
    fflush(stdin);
    singlechar = getchar();
    if(singlechar == '\n' || singlechar == ' ' || singlechar == '/' || singlechar == '\\' || singlechar == '?' || 
            singlechar == ':' || singlechar == '*' || singlechar == '?' || singlechar == '"' ||
             singlechar == '<' || singlechar == '>' || singlechar == '|'){
        printf("Wrong listname format!\n");
        free(listname);
        return 0;
    }
    while(1){
        if (singlechar == ','){
            printf("Wrong listname format!\n");
            free(listname);
            return 0;
        }
        if (singlechar == '\n'){
            break;
        }
        namelen++;
        listname = (char *)realloc(listname , namelen + 1);
        listname[namelen-1] = singlechar;
        singlechar = getchar();
    }
    listname[namelen] = '\0';
    //Searching the lists list to check if the list with that name already exists or not.
    for (int i = 0;i<*num_of_lists;i++){
        temp = temp -> next;
        if (!strcmp(listname , temp -> name)){
            system("color 4");
            printf("This list already exists,you can't add it!\n");
            Sleep(2000);
            free(listname);
            system("color A");
            system("cls");
            return 0;
        }
    }
    if (*num_of_lists == 0){
        (*end)->name = listname;
    }
    else{
        newend -> name = listname;(*end) -> next = newend;(*end) = newend;
    }
    //Adding the new list to the file of lists.
    FILE *Listsfile = fopen("Listsfile.csv" , "a+");
    fprintf(Listsfile , "%s," , listname);
    fclose(Listsfile);

    int newlistnamelen = strlen(listname);
    char fileofnewlist[newlistnamelen + 4];
    sprintf(fileofnewlist,"%s.csv",listname);
    FILE *newlistfile = fopen(fileofnewlist,"w");
    fclose(newlistfile);

    system("cls");
    system("color 6");
    printf("Your new list was successfully added!\n");(*num_of_lists) ++;
    Sleep(2000);
    system("color A");
    system("cls");
    return 1;
}

int Managelists(int *orderandnumoflists){
    FILE *Listsfile = fopen("Listsfile.csv" , "a+");
    int num_of_lists = Countlists(Listsfile),listlength = 1,order = 0;
    List head , *temp ,*end;
    char singlechar;
    //**************************************
    //Creating the nodes of the linked list.
    temp = Createlistnode();
    head.next = temp;
    end = head.next;
    for (int i = 0;i<num_of_lists-1;i++){
        end = Createlistnode();
        temp->next = end;
        temp = end;
    }
    //Allocating memmory to each list's elemets.
    temp = &head;
    for (int i = 0;i<num_of_lists;i++){
        temp = temp -> next;
        temp->name = (char*)malloc(0);
    }
    //Reading information.
    singlechar = fgetc(Listsfile);
    temp = &head;
    for (int i = 0;i<num_of_lists;i++){
        temp = temp -> next;
        listlength = 1;
        while (singlechar != ','){
            temp -> name = (char*)realloc(temp -> name , listlength + 1);
            temp -> name[listlength - 1] = singlechar;
            listlength++;
            singlechar = fgetc(Listsfile);
        }
        listlength--;
        singlechar = fgetc(Listsfile);
        temp -> name[listlength] = '\0';
    }
    //**************************************

    int flag = 1;
    while(flag){
        order = Listsmenu();
        switch (order)
        {
        case 1:
            system("cls");
            order = Printlists(head , num_of_lists);
            if (order == num_of_lists+1){
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
                printf("You have entered the list < %s >!" , temp -> name);
                Sleep(2000);
                system("color A");
                system("cls");
                orderandnumoflists[0] = order;orderandnumoflists[1] = num_of_lists;
                return 1;
                flag = 0;
            }
            break;
        case 2:
            fclose(Listsfile);
            Addnewlist(&end , head , &num_of_lists);
            Listsfile = fopen("Listsfile.csv" , "a+");
            break;
        case 3:
            fclose(Listsfile);
            Omitlist(&head,&num_of_lists,&end);
            Listsfile = fopen("Listsfile.csv" , "a+");
            break;
        case 4:
            chdir("..");
            system("cls");
            orderandnumoflists[0] =-1;
            return 0;
            break;
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

    //Closing files and freeing allocated memories.
    List *freed;
    temp = &head;
    for (int i = 0;i<num_of_lists;i++){
        freed = temp;
        temp = temp -> next;
        free(temp -> name);
        free(freed);
    }
    free(temp);
    fclose(Listsfile);
    return 0;

}