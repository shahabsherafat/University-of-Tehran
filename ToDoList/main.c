#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include "users.h"
#include "boards.h"
#include "lists.h"
#include "tasks.h"


int main(){
    int orderandnumoflists[2] , tasksorder = 0 , boardorder = 0;
    system("cls");
    system("color A");
    Loginorsignup();
    while(1){
        boardorder = Manageboards();
        if (boardorder == -1){
            system("cls");
            printf("Have a nice time!");
            Sleep(2000);
            system("color 7");
            return 0;
        }
        while(1){
            Managelists(orderandnumoflists);
            if (orderandnumoflists[0] == -1){
                break;;
            }
            tasksorder = Managetasks(orderandnumoflists[0] , orderandnumoflists[1]);
            if (tasksorder == -1){
                continue;
            }
        }
    }
    return 0;
}