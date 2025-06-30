int Getkey(void)
{

    switch (getch())
    {
    case 'd':
    case 'D':
        return 1;
    case 'a':
    case 'A':
        return 2;
    case ' ':
        return 3;
    case 's':
    case 'S':
        return 4;
    default:
        return 5;
    }
}
int Isfull(char map[HEIGHT][WIDTH + 26])
{
    int flag = 0;
    int row = 0;
    for (int i = HEIGHT - 2; i >= 0; i--)
    {
        for (int j = 1; j <= WIDTH - 3; j++)
        {
            if (map[i][j] == ' ')
            {
                break;
            }
            if (j == WIDTH - 3)
            {
                row = i;
                flag = 1;
            }
        }
        if (flag)
            break;
    }
    if (flag)
    {
        for (; row >= 1; row--)
        {
            for (int column = 1; column <= WIDTH - 3; column++)
            {
                map[row][column] = map[row - 1][column];
            }
        }
    }
    return flag;
}
