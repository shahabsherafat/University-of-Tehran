#define HEIGHT 20
#define WIDTH 31
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

#include "startfinish.h"
#include "mapfunctions.h"
#include "random.h"
#include "changearrays.h"
#include "shapefunctions.h"
#include "checkfunctions.h"

int main()
{
    char map[HEIGHT][WIDTH + 26];
    int squares[4][2], num_of_squares = 0; // Squares array only contains the squares of the current shape.
    int key = 0, situation = 0, score = 0, shape_num = 0, num_of_rotations = 0, movedowntime = 500, degrees = 0, next_shape_num = 0;
    degrees = Welcome();
    Generateemptymap(map);
    system("color A");

    shape_num = Random();
    next_shape_num = Random();
    Putshape(squares, &num_of_squares, shape_num);
    Upgrademap(map, squares, &num_of_squares, 0, next_shape_num);
    Printmap(map);
    Sleep(movedowntime);

    while (78)
    {
        while (kbhit())
        {
            key = Getkey();
            if (key == 5)
                break;
            fflush(stdin);

            switch (key)
            {
            case 1:
            case 2:
                if (Moveleftright(map, squares, &num_of_squares, key))
                {
                    Upgrademap(map, squares, &num_of_squares, -1, -1);
                    Printmap(map); // If I keep this printmap enabled ,you can move the shape more :).
                    key = 0;
                }
                else
                {
                    Upgrademap(map, squares, &num_of_squares, -1, -1);
                }
                break;

            case 3:
                if (degrees != 0 && degrees != 1 && degrees != 2)
                {
                    degrees = 0;
                }
                for (int i = 0; i <= degrees; i++)
                {
                    if (Rotate(map, squares, &num_of_squares, shape_num, &num_of_rotations))
                    {
                        Upgrademap(map, squares, &num_of_squares, -1, -1);
                        key = 0;
                    }
                    else
                    {
                        Upgrademap(map, squares, &num_of_squares, -1, -1);
                    }
                }
                break;
            case 4:
                if (movedowntime > 100)
                {
                    movedowntime -= 100;
                    break;
                }
            }
        }

        situation = Movedown(map, squares, &num_of_squares);
        if (situation == 1)
        {
            Upgrademap(map, squares, &num_of_squares, -1, -1);
            Printmap(map);
        }
        else if (situation == 0)
        {
            Upgrademap(map, squares, &num_of_squares, -1, -1);
            while (Isfull(map))
            {
                num_of_squares = 0;
                score += 10;
                Upgrademap(map, squares, &num_of_squares, score, -1);
                
                    system("color C");
                    Sleep(100);
                    system("color 3");
                    Sleep(100);
                    system("color 6");
                    Sleep(100);
                    system("color 9");
                    Sleep(100);
                    system("color 7");
                    Sleep(100);
                  
            system("color A");
            Printmap(map);
                
            }

            movedowntime = 500;
            num_of_squares = 0;
            num_of_rotations = 0;

            shape_num = next_shape_num;
            next_shape_num = Random();
            Putshape(squares, &num_of_squares, shape_num);
            Upgrademap(map, squares, &num_of_squares, -1, next_shape_num);
            Printmap(map);
        }
        else
        {
            Printmap(map);
            Sleep(200);

            system("color 7");
            Finish(score);
            break;
        }

        Sleep(movedowntime);
    }

    return 0;
}