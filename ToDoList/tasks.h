#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <io.h>
#include <windows.h>
typedef struct Tasks{
    char *name;
    int priority;
    struct Date{
        int year;
        int month;
        int day;
    }deadline;
    struct Tasks *next;
}Task;

int Counttasks(FILE *tasksfile){
    int counter = 0;
    char c;
    
    c = fgetc(tasksfile);
    while (c != EOF){
        if (c == ','){
            counter ++;
        }
        c = fgetc(tasksfile);
    }

    fseek(tasksfile,0,SEEK_SET);//Counttasks function has moved my file curser to the end of file.

    return counter;
}

Task *Createtasknode(){
    Task *task;
    task = (Task*)malloc(sizeof(Task));
    task->next = NULL;
    return task;
}

void Upgradetasksfile(Task head , int num_of_tasks , char *listname){
    FILE *Tasksfile = fopen(listname , "w");
    Task *temp = &head;
    for(int i = 0;i<num_of_tasks;i++){
        temp = temp -> next;
        fprintf(Tasksfile , "%s|" , temp->name);
        fprintf(Tasksfile , "%d|" , temp->priority);
        fprintf(Tasksfile , "%d|" , temp->deadline.year);
        fprintf(Tasksfile , "%d|" , temp->deadline.month);
        fprintf(Tasksfile , "%d," , temp->deadline.day);
    }
    fclose(Tasksfile);
}

void Printtasks(char *listname,Task head,int num_of_tasks){
    Task *temp = &head;
    char *priority;
    printf("Current List : %s\n" , listname);
    for (int i = 0;i<num_of_tasks;i++){
        temp = temp -> next;
        //Converting priority numbers 1 2 and 3 to the names low medium and high.
        switch (temp ->priority)
        {
        case 1:
            priority = "Low";
            break;
        case 2:
            priority = "Medium";
            break;
        case 3:
            priority = "High";
            break;
        }
        printf("%d. Task : %s | Priority : %s | Deadline : %d/%d/%d\n" , i+1 ,temp->name,priority,temp->deadline.year
        ,temp->deadline.month,temp->deadline.day);
    }
    if(num_of_tasks == 0){
        printf("You have no tasks!\n");
    } 
}

int Tasksmenu(void){
    printf("\nWhat can I do for you?\n");
    printf("1.Add a new task\n");
    printf("2.Edit a task\n");
    printf("3.Omit A task\n");
    printf("4.Move a task to another list\n");
    printf("5.Sort tasks by priority\n");
    printf("6.Get Back To The Lists Menu\n");

    int order;
    printf("Enter your choice : ");
    scanf("%d" , &order);
    fflush(stdin);
    return order;
}

int Addnewtask(Task **end , Task head , int *num_of_tasks ,FILE *Tasksfile){
    char *taskname , singlechar;
    int namelen = 0 , priority = 0 , day = 0 , month = 0 , year = 0;
    Task *temp = &head , *newend = Createtasknode();
    //*****************************************
    //Getting different parameters of the task!
    //1.taskname
    while(1){
        printf("Enter your new task's name : ");
        fflush(stdin);
        int flag = 1;
        taskname = (char *)malloc(1);
        while(flag){
            singlechar = getchar();
            if(singlechar == '\n' || singlechar == ' '){
                printf("Wrong taskname format!Please try again\n");
                printf("Enter your new task's name : ");
                continue;
            }
            while(1){
                if (singlechar == ',' || singlechar == '|'){
                    printf("Wrong taskname format!Please try again.\n");
                    printf("Enter your new task's name : ");
                    free(taskname);
                    taskname = (char *)malloc(1);
                    namelen = 0;
                    break;
                }
                if (singlechar == '\n'){
                    flag = 0;
                    break;
                }
                namelen++;
                taskname = (char *)realloc(taskname , namelen + 1);
                taskname[namelen-1] = singlechar;
                singlechar = getchar();
            }
        }
        taskname[namelen] = '\0';
        //Searching the tasks list to check whether the task with that name already exists or not.
        int situation = 0;
        temp = &head;
        for (int i = 0;i<*num_of_tasks;i++){
            temp = temp -> next;
            if (!strcmp(taskname , temp -> name)){
                printf("This task already exists,you can't add it!\n");
                free(taskname);
                situation = 1;
                namelen = 0;
                break;
            }
        }
        if (situation){
            continue;
        }
        break;
    }
    //2.priority
    while (1){
        printf("Enter the task's priority(Low : 1,Medium : 2,High : 3) : \n");
        scanf("%d" , &priority);
        fflush(stdin);
        if (priority != 1 && priority != 2 && priority != 3){
            printf("Wrong priority number,please try again.\n");
        }
        else{
            break;
        }
    }
    //3.deadline
    while (1){
        printf("Enter the task's deadline date with the format (YYYY MM DD) : \n");
        scanf("%d %d %d" , &year , &month , &day);
        fflush(stdin);
        if (year > 2100 || year < 2024 || !(day <= 31 && day >= 1) || !(month <= 12 && month >= 1)){
            printf("Wrong date you entered,please try again!\n");
        }
        else{
            break;
        }
    }
    //*****************************************
    //Adding the new task!
    if (*num_of_tasks == 0){
        (*end)->name = taskname;
        (*end)->priority = priority;
        (*end)->deadline.day = day;
        (*end)->deadline.month = month;
        (*end)->deadline.year = year;
    }
    else{
        newend->name = taskname;
        newend->priority = priority;
        newend->deadline.day = day;
        newend->deadline.month = month;
        newend->deadline.year = year;
        (*end) -> next = newend;(*end) = newend;
    }

    system("cls");
    system("color 6");
    printf("Your new task was successfully added!\n");(*num_of_tasks) ++;
    Sleep(2000);
    system("color A");
    system("cls");
    return 1;
}

int Edittask(int num_of_tasks , Task head){
    int tasknum = 0 , element = 0 , priority = 0;
    int year = 0 , month = 0 , day = 0;
    char *tasknewname , singlechar;
    int namelen = 0;

    if (num_of_tasks == 0){
        system("color 4");
        printf("You have no tasks to edit!");
        Sleep(2000);
        system("color A");
        return 0;
    }
    printf("Which task do you wanna edit?(Enter it's number) : ");
    fflush(stdin);
    scanf("%d" , &tasknum);
    if (!(tasknum <= num_of_tasks && tasknum >= 1)){
        system("color 4");
        printf("Wrong task number(It has to be between %d and %d)!" , 1 , num_of_tasks);
        fflush(stdin);
        Sleep(2000);
        system("color A");
        return 0;
    }
    Task *temp2 = &head , *temp;
    for(int i = 0;i<tasknum;i++){
        temp2 = temp2->next;
    }

    while (1){
        printf("Which element of the task <%s> do you wanna edit?\n",temp2->name);
        printf("Enter your choice(taskname : 1 , priority : 2 , deadline : 3) : ");
        fflush(stdin);
        scanf("%d" , &element);
        if (element != 1 && element != 2 && element != 3){
            printf("Wrong choice number,please try again!\n");
        }
        else
            break;
    }
    switch (element){
        case 1:
            while(1){
                printf("Enter your task's new name : ");
                fflush(stdin);
                int flag = 1;
                tasknewname = (char *)malloc(1);
                while(flag){
                    singlechar = getchar();
                    if(singlechar == '\n' || singlechar == ' '){
                        printf("Wrong taskname format!Please try again\n");
                        printf("Enter your task's new name : ");
                        continue;
                    }
                    while(1){
                        if (singlechar == ',' || singlechar == '|'){
                            printf("Wrong taskname format!Please try again.\n");
                            printf("Enter your new task's name : ");
                            free(tasknewname);
                            tasknewname = (char *)malloc(1);
                            namelen = 0;
                            break;
                        }
                        if (singlechar == '\n'){
                            flag = 0;
                            break;
                        }
                        namelen++;
                        tasknewname = (char *)realloc(tasknewname , namelen + 1);
                        tasknewname[namelen-1] = singlechar;
                        singlechar = getchar();
                    }
                }
                tasknewname[namelen] = '\0';
                //Searching the tasks list to check whether the task with that name already exists or not.
                int situation = 0;
                temp = &head;
                for (int i = 0;i<num_of_tasks;i++){
                    temp = temp -> next;
                    if (!strcmp(tasknewname , temp -> name)){
                        printf("This taskname already exists,you can't add it!\n");
                        free(tasknewname);
                        situation = 1;
                        namelen = 0;
                        break;
                    }
                }
                if (situation){
                    continue;
                }
                break;
            }
            free(temp2 -> name);
            temp2 -> name = tasknewname;
            break;
        case 2:
            while (1){
                printf("Enter the task's new priority(Low : 1,Medium : 2,High : 3) : \n");
                scanf("%d" , &priority);
                fflush(stdin);
                if (priority != 1 && priority != 2 && priority != 3){
                    printf("Wrong priority number,please try again.\n");
                }
                else{
                    break;
                }
            }
            //Optimizing
            if (priority == temp2->priority){
                break;
            }
            temp2 -> priority = priority;
            break;
        case 3:
            while (1){
                printf("Enter the task's deadline date with the format (YYYY MM DD) : \n");
                scanf("%d %d %d" , &year , &month , &day);
                fflush(stdin);
                if (year > 2100 || year < 2024 || !(day <= 31 && day >= 1) || !(month <= 12 && month >= 1)){
                    printf("Wrong date you entered,please try again!\n");
                }
                else{
                    break;
                }
            }
            //Optimizing
            if (year == temp2->deadline.year && month == temp2->deadline.month && day == temp2->deadline.day){
                break;
            }
            temp2->deadline.year = year;temp2->deadline.month = month;temp2->deadline.day = day;
            break;
    }
    system("cls");
    system("color 6");
    printf("The task was successfully edited!");
    Sleep(2000);
    system("color A");
    return 1;
}

int Omittask(Task *head , int *num_of_tasks ,Task **end){
    int tasknum = 0;
    Task *formertask = head;
    if (*num_of_tasks == 0){
        system("color 4");
        printf("You have no tasks to omit!");
        Sleep(2000);
        system("color A");
        return 0;
    }
    printf("Which task do you wanna omit?(Enter it's number) : ");
    fflush(stdin);
    scanf("%d" , &tasknum);
    if (!(tasknum <= *num_of_tasks && tasknum >= 1)){
        printf("Wrong task number(It has to be between %d and %d)!" , 1 , *num_of_tasks);
        fflush(stdin);
        Sleep(2000);
        return 0;
    }
    
    for(int i = 0;i<tasknum-1;i++){
        formertask = formertask -> next;
    }

    Task *deleted = formertask->next;
    formertask->next = (formertask->next)->next;
    //Fixing the function if the user has omitted the last task.
    if (tasknum == *num_of_tasks){
        (*end) = formertask;
    }
    //Fixing the function if the user has omitted the first task.
    if (*num_of_tasks==1){
        (*end) = Createtasknode();
        head->next = (*end);
    }
    (*num_of_tasks) --;
    system("cls");
    system("color 6");
    printf("The task < %s > was successfully omitted!" , deleted -> name);
    Sleep(2000);
    system("color A");
    //Freeing the omited task.
    free(deleted->name);
    free(deleted);
    return 1;
}

int Movetask(Task *head , int *num_of_tasks , char **listsarray , int num_of_lists , Task **end){
    //This function contains an adding and an omitting.
    int tasknum = 0 , listnum = 0;
    Task *formertask = head;
    if (*num_of_tasks == 0){
        system("color 4");
        printf("You have no tasks to move!");
        Sleep(2000);
        system("color A");
        return 0;
    }
    printf("Which task do you wanna move?(Enter it's number) : ");
    fflush(stdin);
    scanf("%d" , &tasknum);
    if (!(tasknum <= *num_of_tasks && tasknum >= 1)){
        system("color 4");
        printf("Wrong task number(It has to be between %d and %d)!" , 1 , *num_of_tasks);
        fflush(stdin);
        Sleep(2000);
        system("color A");
        return 0;
    }
    for(int i = 0;i<tasknum-1;i++){
        formertask = formertask -> next;
    }
    printf("Your lists : \n");
    for(int i = 1;i<=num_of_lists;i++){
        printf("%d.%s\n" , i , *(listsarray + (i - 1)));
    }
    printf("Which list do you wanna move the task <%s> to?(Enter it's number) : " , formertask -> next -> name);
    fflush(stdin);
    scanf("%d" , &listnum);
    if (!(listnum <= num_of_lists && listnum >= 1)){
        printf("Wrong task number(It has to be between %d and %d)!" , 1 , num_of_lists);
        fflush(stdin);
        Sleep(2000);
        return 0;
    }
    char listname[strlen(listsarray[listnum - 1]) + 4];
    sprintf(listname , "%s.csv" , listsarray[listnum - 1]);
    FILE *targetlist = fopen(listname , "a+");
    //I gotta check whether this task already exists in the targetlist or not!
    //******************************
    int targetlistnum_of_tasks = 0 , tasknamelen = 1;
    targetlistnum_of_tasks = Counttasks(targetlist);
    char *currenttaskname , singlechar;
    singlechar = fgetc(targetlist);
    for (int i = 0;i<targetlistnum_of_tasks;i++){
        currenttaskname = (char *)malloc(0);
        tasknamelen = 1;
        while (1){
            if (singlechar == '|'){
                tasknamelen--;
                currenttaskname[tasknamelen] = '\0';
                if(!strcmp(currenttaskname , formertask -> next -> name)){
                    system("cls");
                    system("color 4");
                    printf("There is a task with this name in your target list,can't add it!");
                    Sleep(3000);
                    system("color A");
                    free(currenttaskname);
                    fclose(targetlist);
                    return 0;
                }
                while (singlechar != ','){
                    singlechar = fgetc(targetlist);
                }
                singlechar = fgetc(targetlist);
                free(currenttaskname);
                break;
            }
            currenttaskname = (char*)realloc(currenttaskname , tasknamelen + 1);
            currenttaskname[tasknamelen - 1] = singlechar;
            tasknamelen++;
            singlechar = fgetc(targetlist);
        }
    }
    //******************************
    fprintf(targetlist , "%s|" , formertask -> next -> name);
    fprintf(targetlist , "%d|" , formertask -> next -> priority);
    fprintf(targetlist , "%d|" , formertask -> next -> deadline.year);
    fprintf(targetlist , "%d|" , formertask -> next -> deadline.month);
    fprintf(targetlist , "%d," , formertask -> next -> deadline.day);
    //**************************************
    Task *deleted = formertask->next;
    formertask->next = (formertask->next)->next;
    //Fixing the function if the user has omitted the last task.
    if (tasknum == *num_of_tasks){
        (*end) = formertask;
    }
    //Fixing the function if the user has omitted the first task.
    if (*num_of_tasks==1){
        (*end) = Createtasknode();
        head->next = (*end);
    }
    (*num_of_tasks) --;
    system("cls");
    system("color 6");
    printf("The task < %s > was successfully moved to the list < %s >!" , deleted -> name , listsarray[listnum - 1]);
    Sleep(2000);
    system("color A");
    //Freeing the omited task.
    free(deleted->name);
    free(deleted);
    fclose(targetlist);
    return 1;
}

int Sortbypriority(Task *head , int num_of_tasks , Task **end){
    Task *temp , *prev , *nextnode;
    int flag = 1;
    if (num_of_tasks == 0){
        system("cls");
        system("color 4");
        printf("You have no tasks to sort!");
        Sleep(2000);
        system("color A");
        return 0;
    }
    if (num_of_tasks == 1){
        system("cls");
        system("color 6");
        printf("You have only one task!");
        Sleep(2000);
        system("color A");
        return 0;
    }
    while(flag){
        flag = 0;
        temp = head -> next;
        prev = head;
        nextnode = temp -> next;
        int i = 0;
        while(1){
            if (nextnode == NULL){
                break;
            }
            if((temp->priority) < (nextnode->priority)){
                if (nextnode->next == NULL){
                    (*end) = temp;
                }
                flag = 1;
                prev -> next = nextnode;
                temp -> next = nextnode -> next;
                nextnode -> next = temp;

                prev = nextnode;
                nextnode = temp -> next;
                continue;
            }
            prev = temp;
            temp = temp -> next;
            nextnode = temp -> next;
            printf("%d" , i);
            i++;
        }
    }
    system("cls");
    system("color 6");
    printf("Your tasks are successfully sorted by priority!");
    Sleep(2000);
    system("color A");
    return 1;
}

int Managetasks(int listnum , int num_of_lists){
    //To manage tasks,I need to have an array of lists!
    FILE *Listsfile = fopen("Listsfile.csv" , "a+") , *Tasksfile;
    int tasknamelen = 1,order = 0,num_of_tasks = 1,listlength = 1;
    char *listsarray[num_of_lists];
    char singlechar;

    //**************************************
    //Allocating memmory to each array's elemets.
    for (int i = 0;i<num_of_lists;i++){
        listsarray[i] = (char*)malloc(0);
    }
    //Reading information.
    singlechar = fgetc(Listsfile);
    for (int i = 0;i<num_of_lists;i++){
        listlength = 1;
        while (singlechar != ','){
            listsarray[i] = (char*)realloc(listsarray[i] , listlength + 1);
            listsarray[i][listlength - 1] = singlechar;
            listlength++;
            singlechar = fgetc(Listsfile);
        }
        listlength--;
        singlechar = fgetc(Listsfile);
        listsarray[i][listlength] = '\0';
    }
    fclose(Listsfile);
    int len = strlen(listsarray[listnum - 1]) + 4;
    char listname[len];
    sprintf(listname,"%s.csv",listsarray[listnum - 1]);
    //****************************************
    Tasksfile = fopen(listname , "a+");
    num_of_tasks = Counttasks(Tasksfile);
    //**************************************
    //Creating the nodes of the linked list.
    Task head , *temp ,*end;
    temp = Createtasknode();
    head.next = temp;
    end = head.next;
    for (int i = 0;i<num_of_tasks-1;i++){
        end = Createtasknode();
        temp->next = end;
        temp = end;
    }
    //Allocating memmory to each task's elemets.
    temp = &head;
    for (int i = 0;i<num_of_tasks;i++){
        temp = temp -> next;
        temp->name = (char*)malloc(0);
    }
    //Reading information.
    singlechar = fgetc(Tasksfile);
    temp = &head;
    for (int i = 0;i<num_of_tasks;i++){
        temp = temp -> next;
        tasknamelen = 1;
        while (singlechar != '|'){
            temp -> name = (char*)realloc(temp -> name , tasknamelen + 1);
            temp -> name[tasknamelen - 1] = singlechar;
            tasknamelen++;
            singlechar = fgetc(Tasksfile);
        }
        tasknamelen--;
        temp -> name[tasknamelen] = '\0';
        
        fscanf(Tasksfile , "%d" , &(temp -> priority));
        singlechar = fgetc(Tasksfile);
        fscanf(Tasksfile , "%d" , &(temp -> deadline.year));
        singlechar = fgetc(Tasksfile);
        fscanf(Tasksfile , "%d" , &(temp -> deadline.month));
        singlechar = fgetc(Tasksfile);
        fscanf(Tasksfile , "%d" , &(temp -> deadline.day));
        singlechar = fgetc(Tasksfile);
        singlechar = fgetc(Tasksfile);
    }
    //We're done!Our linked list for tasks is made!
    //**************************************
    while(1){
        system("cls");
        Printtasks(listsarray[listnum -1] , head , num_of_tasks);
        order = Tasksmenu();
        switch (order)
        {
        case 1:
            Addnewtask(&end , head , &num_of_tasks ,Tasksfile);
            //Adding the new task to the file of tasks.
            fclose(Tasksfile);
            Upgradetasksfile(head,num_of_tasks,listname);
            Tasksfile = fopen(listname , "a+");
            break;
        case 2:
            Edittask(num_of_tasks , head);
            //Upgrading the file.
            fclose(Tasksfile);
            Upgradetasksfile(head,num_of_tasks,listname);
            Tasksfile = fopen(listname , "a+");
            break;
        case 3:
            Omittask(&head , &num_of_tasks , &end);
            //Upgrading the file.
            fclose(Tasksfile);
            Upgradetasksfile(head,num_of_tasks,listname);
            Tasksfile = fopen(listname , "a+");
            break;
        case 4:
            Movetask(&head,&num_of_tasks,listsarray,num_of_lists,&end);
            //Upgrading the file.
            fclose(Tasksfile);
            Upgradetasksfile(head,num_of_tasks,listname);
            Tasksfile = fopen(listname , "a+");
            break;
        case 5:
            Sortbypriority(&head,num_of_tasks,&end);
            fclose(Tasksfile);
            Upgradetasksfile(head,num_of_tasks,listname);
            Tasksfile = fopen(listname , "a+");
            break;
        case 6:
            system("cls");
            return -1;
            break;
        default:
            system("color 4");
            printf("We have no other options,choose one of these five!\n");
            Sleep(2000);
            system("color A");
            system("cls");
            break;
        }
    }
    Task *freed;
    temp = &head;
    for (int i = 0;i<num_of_tasks;i++){
        freed = temp;
        temp = temp -> next;
        free(temp -> name);
        free(freed);
    }
    free(temp);
    fclose(Tasksfile);
}