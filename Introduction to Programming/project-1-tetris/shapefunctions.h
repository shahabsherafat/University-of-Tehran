void Putshape(int squares[][2], int *num, int shape_num)
{
    switch (shape_num)
    {
    case 0:
        squares[*num][0] = 1;
        squares[*num][1] = 13;
        squares[*num + 1][0] = 1;
        squares[*num + 1][1] = 15;
        squares[*num + 2][0] = 1;
        squares[*num + 2][1] = 17;
        squares[*num + 3][0] = 0;
        squares[*num + 3][1] = 15;
        *num += 4;
        break;
    case 1:
        squares[*num][0] = 1;
        squares[*num][1] = 13;
        squares[*num + 1][0] = 1;
        squares[*num + 1][1] = 15;
        squares[*num + 2][0] = 0;
        squares[*num + 2][1] = 13;
        squares[*num + 3][0] = 0;
        squares[*num + 3][1] = 15;
        *num += 4;
        break;
    case 2:
        squares[*num][0] = 1;
        squares[*num][1] = 15;
        squares[*num + 1][0] = 1;
        squares[*num + 1][1] = 17;
        squares[*num + 2][0] = 0;
        squares[*num + 2][1] = 13;
        squares[*num + 3][0] = 0;
        squares[*num + 3][1] = 15;
        *num += 4;
        break;
    case 3:
        squares[*num][0] = 0;
        squares[*num][1] = 11;
        squares[*num + 1][0] = 0;
        squares[*num + 1][1] = 13;
        squares[*num + 2][0] = 0;
        squares[*num + 2][1] = 15;
        squares[*num + 3][0] = 0;
        squares[*num + 3][1] = 17;
        *num += 4;
        break;
    }
}

int Movedown(char map[HEIGHT][WIDTH + 26], int squares[][2], int *num)
{
    int squares_copy[4][2];
    Changearrays(squares, squares_copy);

    for (int i = 0; i < *num; i++)
    {
        if (map[squares[i][0] + 1][squares[i][1]] == ' ' && map[squares[i][0] + 1][squares[i][1] + 1] == ' ')
        {
            squares[i][0]++;
            map[squares[i][0] - 1][squares[i][1]] = ' ';
            map[squares[i][0] - 1][squares[i][1] + 1] = ' ';
        }
        else
        {
            for (int k = 0; k < 4; k++)
            {
                if (squares_copy[k][0] == 0)
                    return 2;
            }
            Changearrays(squares_copy, squares);
            return 0;
        }
        if (i == *num - 1)
            return 1;
    }
}

int Moveleftright(char map[HEIGHT][WIDTH + 26], int squares[][2], int *num, int direction)
{
    int squares_copy[4][2];
    Changearrays(squares, squares_copy);

    switch (direction)
    {
    case 1: // Move to right
        for (int i = *num - 1; i >= 0; i--)
        {
            if (map[squares[i][0]][squares[i][1] + 2] == ' ' && map[squares[i][0]][squares[i][1] + 3] == ' ')
            {
                map[squares[i][0]][squares[i][1]] = ' ';
                map[squares[i][0]][squares[i][1] + 1] = ' ';
                squares[i][1] += 2;
            }
            else
            {
                Changearrays(squares_copy, squares);
                return 0;
            }
        }
        break;
    case 2: // Move to left
        for (int i = 0; i < *num; i++)
        {
            if (map[squares[i][0]][squares[i][1] - 1] == ' ' && map[squares[i][0]][squares[i][1] - 2] == ' ')
            {
                map[squares[i][0]][squares[i][1]] = ' ';
                map[squares[i][0]][squares[i][1] + 1] = ' ';
                squares[i][1] -= 2;
            }
            else
            {
                Changearrays(squares_copy, squares);
                return 0;
            }
        }
        break;
    }
    return 1;
}

int Rotate(char map[HEIGHT][WIDTH + 26], int squares[][2], int *num, int shape_num, int *num_of_rotations)
{
    int k = *num_of_rotations;
    // I'll switch between the cases of shapenums to customize the rotation operation for each shape separately.
    // And for each shape,I gotta know which situation it is currently,so I got num of squares variable pointer.
    switch (shape_num)
    {
    case 0:
        if (*num_of_rotations % 4 == 0)
        {
            if (map[squares[1][0] + 1][squares[1][1]] == ' ' && map[squares[1][0] + 1][squares[1][1] + 1] == ' ')
            {
                map[squares[0][0]][squares[0][1]] = ' ';
                map[squares[0][0]][squares[0][1] + 1] = ' ';
                squares[0][0] = squares[1][0] + 1;
                squares[0][1] = squares[1][1];
            }
            else
            {
                return 0;
            }
            k += 1;
        }
        else if (*num_of_rotations % 4 == 1)
        {
            if (map[squares[1][0]][squares[1][1] - 2] == ' ' && map[squares[1][0]][squares[1][1] - 1] == ' ')
            {
                map[squares[1][0]][squares[1][1]] = ' ';
                map[squares[1][0]][squares[1][1] + 1] = ' ';
                map[squares[2][0]][squares[2][1]] = ' ';
                map[squares[2][0]][squares[2][1] + 1] = ' ';
                map[squares[3][0]][squares[3][1]] = ' ';
                map[squares[3][0]][squares[3][1] + 1] = ' ';
                squares[1][1] -= 2;
                squares[2][1] -= 2;
                squares[3][1] += 2;
                squares[3][0] += 1;
            }
            else
            {
                return 0;
            }
            k += 1;
        }
        else if (*num_of_rotations % 4 == 2)
        {
            if (map[squares[2][0] - 1][squares[2][1]] == ' ' && map[squares[2][0] - 1][squares[2][1] + 1] == ' ')
            {
                map[squares[3][0]][squares[3][1]] = ' ';
                map[squares[3][0]][squares[3][1] + 1] = ' ';
                squares[3][0] = squares[2][0] - 1;
                squares[3][1] = squares[2][1];
            }
            else
            {
                return 0;
            }
            k += 1;
        }
        else
        {
            if (map[squares[2][0]][squares[2][1] + 2] == ' ' && map[squares[2][0]][squares[2][1] + 3] == ' ')
            {
                map[squares[2][0]][squares[2][1]] = ' ';
                map[squares[2][0]][squares[2][1] + 1] = ' ';
                map[squares[1][0]][squares[1][1]] = ' ';
                map[squares[1][0]][squares[1][1] + 1] = ' ';
                map[squares[0][0]][squares[0][1]] = ' ';
                map[squares[0][0]][squares[0][1] + 1] = ' ';
                squares[2][1] += 2;
                squares[1][1] += 2;
                squares[0][1] -= 2;
                squares[0][0] -= 1;
            }
            else
            {
                return 0;
            }
            k += 1;
        }
        break;
    case 1:
        break;
    case 2:
        if (*num_of_rotations % 4 == 0 || *num_of_rotations % 4 == 2)
        {
            if (map[squares[1][0] - 1][squares[1][1]] == ' ' && map[squares[1][0] - 1][squares[1][1] + 1] == ' ' && map[squares[1][0] - 2][squares[1][1]] == ' ' && map[squares[1][0] - 2][squares[1][1] + 1] == ' ')
            {
                map[squares[1][0]][squares[1][1]] = ' ';
                map[squares[1][0]][squares[1][1] + 1] = ' ';
                map[squares[2][0]][squares[2][1]] = ' ';
                map[squares[2][0]][squares[2][1] + 1] = ' ';

                squares[2][0] = squares[1][0] - 1;
                squares[2][1] = squares[1][1];
                squares[3][0] = squares[1][0] - 2;
                squares[3][1] = squares[1][1];
                squares[1][0] = squares[0][0] - 1;
                squares[1][1] = squares[0][1];
            }
            else
            {
                return 0;
            }
            k += 1;
        }
        else if (*num_of_rotations % 4 == 1 || *num_of_rotations % 4 == 3)
        {
            if (map[squares[0][0]][squares[0][1] + 2] == ' ' && map[squares[0][0]][squares[0][1] + 3] == ' ' && map[squares[1][0]][squares[1][1] - 2] == ' ' && map[squares[1][0]][squares[1][1] - 1] == ' ')
            {
                map[squares[3][0]][squares[3][1]] = ' ';
                map[squares[3][0]][squares[3][1] + 1] = ' ';
                map[squares[2][0]][squares[2][1]] = ' ';
                map[squares[2][0]][squares[2][1] + 1] = ' ';

                squares[2][0] = squares[0][0] - 1;
                squares[2][1] = squares[0][1] - 2;
                squares[3][0] = squares[1][0];
                squares[3][1] = squares[1][1];
                squares[1][0] = squares[0][0];
                squares[1][1] = squares[0][1] + 2;
            }
            else
            {
                return 0;
            }
            k += 1;
        }
        break;
    case 3:
        if (*num_of_rotations % 4 == 0 || *num_of_rotations % 4 == 2)
        {
            if (map[squares[1][0] - 1][squares[1][1]] == ' ' && map[squares[1][0] - 1][squares[1][1] + 1] == ' ' && map[squares[1][0] - 2][squares[1][1]] == ' ' && map[squares[1][0] - 2][squares[1][1] + 1] == ' ' && map[squares[1][0] + 1][squares[1][1]] == ' ' && map[squares[1][0] + 1][squares[1][1] + 1] == ' ')
            {
                map[squares[0][0]][squares[0][1]] = ' ';
                map[squares[0][0]][squares[0][1] + 1] = ' ';
                map[squares[2][0]][squares[2][1]] = ' ';
                map[squares[2][0]][squares[2][1] + 1] = ' ';
                map[squares[3][0]][squares[3][1]] = ' ';
                map[squares[3][0]][squares[3][1] + 1] = ' ';

                squares[2][0] = squares[1][0] - 1;
                squares[2][1] = squares[1][1];
                squares[3][0] = squares[1][0] - 2;
                squares[3][1] = squares[1][1];
                squares[0][0] = squares[1][0] + 1;
                squares[0][1] = squares[1][1];
            }
            else
            {
                return 0;
            }
            k += 1;
        }
        else if (*num_of_rotations % 4 == 1 || *num_of_rotations % 4 == 3)
        {
            if (map[squares[1][0]][squares[1][1] + 2] == ' ' && map[squares[1][0]][squares[1][1] + 3] == ' ' && map[squares[1][0]][squares[1][1] + 4] == ' ' && map[squares[1][0]][squares[1][1] + 5] == ' ' && map[squares[1][0]][squares[1][1] - 2] == ' ' && map[squares[1][0]][squares[1][1] - 1] == ' ')
            {
                map[squares[0][0]][squares[0][1]] = ' ';
                map[squares[0][0]][squares[0][1] + 1] = ' ';
                map[squares[2][0]][squares[2][1]] = ' ';
                map[squares[2][0]][squares[2][1] + 1] = ' ';
                map[squares[3][0]][squares[3][1]] = ' ';
                map[squares[3][0]][squares[3][1] + 1] = ' ';

                squares[2][0] = squares[1][0];
                squares[2][1] = squares[1][1] + 2;
                squares[3][0] = squares[1][0];
                squares[3][1] = squares[1][1] + 4;
                squares[0][0] = squares[1][0];
                squares[0][1] = squares[1][1] - 2;
            }
            else
            {
                return 0;
            }
            k += 1;
        }
        break;
    }
    *num_of_rotations = k;
    return 1;
}
