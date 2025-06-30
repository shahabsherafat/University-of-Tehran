int Welcome(void)
{
    char degrees;
    system("CLS");
    HWND console = GetConsoleWindow();
    MoveWindow(console, 300, 100, 1000, 355, FALSE);
    printf("\n\n\n\n\n\t\t\t\t\t ***************************************");
    printf("\n\n\t\t\t\t\t  HELLO,WELCOME TO SHAHAB'S TETRIS GAME!\n\n\t\t\t\t\t\t  PRESS ANY KEY TO START!\n\n\t\t\t\t\t\t   TO ROTATE(DEGREES):\n\t\t\t\t\t        90 : 0 , 180 : 1 , 270 : 2");
    printf("\n\n\t\t\t\t\t ***************************************");
    degrees = getch();
    printf("\t\t\t\t\t  ");
    return ((int)degrees - 48);
}
void Finish(int score)
{
    system("CLS");
    HWND console = GetConsoleWindow();
    MoveWindow(console, 300, 100, 1000, 355, FALSE);
    printf("\n\n\n\n\n\t\t\t\t\t ***********************************");
    printf("\n\n\n\t\t\t\t\t GAME OVER!PRESS ANY KEY TO FINISH!\n\n\t\t\t\t\t\tYOUR SCORE IS : %d\n", score);
    printf("\n\n\t\t\t\t\t ***********************************");
    getch();
}
