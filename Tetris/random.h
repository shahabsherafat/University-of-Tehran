int Random(void)
{ // Randomizing the entrance shape in each step.
    srand(clock() + time(NULL));
    return rand() % 4;
}