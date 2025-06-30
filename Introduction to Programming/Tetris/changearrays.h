void Changearrays(int squares[][2], int squares_copy[][2])
{
    for (int k = 0; k < 4; k++)
    {
        for (int j = 0; j < 2; j++)
        {
            squares_copy[k][j] = squares[k][j];
        }
    }
}
