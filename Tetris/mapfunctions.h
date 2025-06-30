void Printmap(char map[HEIGHT][WIDTH + 26])
{ // A function to print the game map after any change.
    HWND console = GetConsoleWindow();
    MoveWindow(console, 300, 100, 1000, 375, TRUE);
    printf("\t\t\t\t\t  %s", map);
    // for (int i = 0 ; i < HEIGHT; i++){
    //     printf("\t\t\t\t\t  ");
    //     for (int j = 0 ; j < WIDTH ; j++){
    //         printf("%c",map[i][j]);
    //     }
    //     printf("\n");
    // } At first I wanted to print my map using for loop but it wasn't optimized at all so I changed it.
}

void Generateemptymap(char map[HEIGHT][WIDTH + 26])
{ // It's gonna be used only once:)
    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH - 1; j++)
        {
            if (j == 0 || j == WIDTH - 2)
            {
                if (i != HEIGHT - 1)
                    map[i][j] = '|';
                else
                    map[i][j] = '-';
            }
            else if (i == HEIGHT - 1)
            {

                map[i][j] = '-';
            }
            else
            {
                map[i][j] = ' ';
            }
        }
    }
    for (int i = 0; i < HEIGHT - 1; i++)
    {
        map[i][WIDTH - 1] = ' ';
        map[i][WIDTH] = ' ';
        map[i][WIDTH + 1] = ' ';
        map[i][WIDTH + 2] = ' ';
        map[i][WIDTH + 3] = ' ';
        map[i][WIDTH + 4] = ' ';
        map[i][WIDTH + 5] = ' ';
        map[i][WIDTH + 6] = ' ';
        map[i][WIDTH + 7] = ' ';
        map[i][WIDTH + 8] = ' ';
        map[i][WIDTH + 9] = ' ';
        map[i][WIDTH + 10] = ' ';
        map[i][WIDTH + 11] = ' ';
        map[i][WIDTH + 12] = ' ';
        map[i][WIDTH + 13] = ' ';
        map[i][WIDTH + 14] = ' ';
        map[i][WIDTH + 15] = ' ';
        map[i][WIDTH + 16] = ' ';
        map[i][WIDTH + 17] = ' ';

        map[i][WIDTH + 18] = '\n';
        map[i][WIDTH + 19] = '\t';
        map[i][WIDTH + 20] = '\t';
        map[i][WIDTH + 21] = '\t';
        map[i][WIDTH + 22] = '\t';
        map[i][WIDTH + 23] = '\t';
        map[i][WIDTH + 24] = ' ';
        map[i][WIDTH + 25] = ' ';
    }
    map[10][WIDTH + 7] = 'N';
    map[10][WIDTH + 8] = 'E';
    map[10][WIDTH + 9] = 'X';
    map[10][WIDTH + 10] = 'T';
    map[10][WIDTH + 12] = 'S';
    map[10][WIDTH + 13] = 'H';
    map[10][WIDTH + 14] = 'A';
    map[10][WIDTH + 15] = 'P';
    map[10][WIDTH + 16] = 'E';
    map[10][WIDTH + 17] = ':';

    map[HEIGHT - 1][WIDTH - 1] = '\n';
    map[HEIGHT - 1][WIDTH] = '\0';
}

void Upgrademap(char map[HEIGHT][WIDTH + 26], int squares[][2], int *num, int score, int next_shape_num)
{ // Updating the map is necessary.
    if (score != -1)
    {
        char a = (score % 10) + 48;
        score /= 10;
        char b = (score % 10) + 48;
        score /= 10;
        char c = (score % 10) + 48;
        score /= 10;
        map[5][WIDTH + 7] = 'S';
        map[5][WIDTH + 8] = 'C';
        map[5][WIDTH + 9] = 'O';
        map[5][WIDTH + 10] = 'R';
        map[5][WIDTH + 11] = 'E';
        map[5][WIDTH + 13] = ':';
        map[5][WIDTH + 15] = c;
        map[5][WIDTH + 16] = b;
        map[5][WIDTH + 17] = a;
    }

    if (next_shape_num != -1)
    {
        for (int i = 11; i <= 12; i++)
        {
            for (int j = 8; j <= 15; j++)
            {
                map[i][WIDTH + j] = ' ';
            }
        }
        switch (next_shape_num)
        {
        case 0:
            map[11][WIDTH + 11] = '[';
            map[11][WIDTH + 12] = ']';
            map[12][WIDTH + 9] = '[';
            map[12][WIDTH + 10] = ']';
            map[12][WIDTH + 11] = '[';
            map[12][WIDTH + 12] = ']';
            map[12][WIDTH + 13] = '[';
            map[12][WIDTH + 14] = ']';
            break;
        case 1:
            map[11][WIDTH + 11] = '[';
            map[11][WIDTH + 12] = ']';
            map[11][WIDTH + 13] = '[';
            map[11][WIDTH + 14] = ']';
            map[12][WIDTH + 11] = '[';
            map[12][WIDTH + 12] = ']';
            map[12][WIDTH + 13] = '[';
            map[12][WIDTH + 14] = ']';
            break;
        case 2:
            map[11][WIDTH + 11] = '[';
            map[11][WIDTH + 12] = ']';
            map[11][WIDTH + 9] = '[';
            map[11][WIDTH + 10] = ']';
            map[12][WIDTH + 11] = '[';
            map[12][WIDTH + 12] = ']';
            map[12][WIDTH + 13] = '[';
            map[12][WIDTH + 14] = ']';
            break;
        case 3:
            map[11][WIDTH + 8] = '[';
            map[11][WIDTH + 9] = ']';
            map[11][WIDTH + 10] = '[';
            map[11][WIDTH + 11] = ']';
            map[11][WIDTH + 12] = '[';
            map[11][WIDTH + 13] = ']';
            map[11][WIDTH + 14] = '[';
            map[11][WIDTH + 15] = ']';
            break;
        }
    }

    for (int i = 0; i < *num; i++)
    {
        map[squares[i][0]][squares[i][1]] = '[';
        map[squares[i][0]][squares[i][1] + 1] = ']';
    }
}