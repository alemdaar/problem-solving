#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int is_safe(int level, int *buffer, int index, int number_of_queens)
{
    int i = 0;
    // printf ("level %d - index : %d\n", level, index);
    while (i < level)
    {
        // printf ("%d == %d\n", buffer[i], i);
        if (buffer[i] == index)
        {
            return (0);
        }
        if (abs(i - level) == abs(buffer[i] - index))
            return (0);
        i++;
    }
    return (1);
}
void nqueens(int level, int *buffer, int number_of_queens)
{
    if (number_of_queens == level)
    {
        int z = 0;
        while (z < number_of_queens)
        {
            printf ("%d", buffer[z++]);
        }
        printf ("\n");
        return ;
    }
    int i = 0;
    while (i < number_of_queens)
    {
        if (!is_safe(level, buffer, i, number_of_queens))
        {
            i++;
            continue;
        }
        buffer[level] = i;
        nqueens(level + 1, buffer, number_of_queens);
        i++;
    }
    return ;
}
int main (int ac, char **av)
{
    if (ac != 2){
        dprintf (2, "the number of input is incorrect !\nbetter be line \"./program <number of queens>\"");
        return (1);
    }
    int number_of_queens = atoi(av[1]);
    int buffer[number_of_queens];
    buffer[number_of_queens] = 0;
    nqueens(0, buffer, number_of_queens);
}
