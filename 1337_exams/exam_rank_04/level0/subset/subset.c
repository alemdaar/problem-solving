#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int is_safe(int *buffer, int index, int buffer_size)
{
    int i  = 0;
    while (i < buffer_size)
    {
        if (buffer[i] == index - 2)
            return (0);
        i++;
    }
    return (1);

}

void powerset(int level, char **str, int *buffer, int sum, int nb, int size, int buffer_size, int i)
{
    if (level == size)
        return ;
    while (i < size)
    {
        if (!is_safe(buffer, i, buffer_size))
        {
            i++;
            continue;
        }
        
        nb += atoi(str[i]);
        buffer[level] = i - 2;
        buffer_size ++;
        if (nb == sum)
        {
            int z = 0;
            while (z < buffer_size)
            {
                printf ("%d", atoi(str[buffer[z] + 2]));
                if (z < buffer_size  - 1)
                    printf (" ");
                z++;
            }
            printf ("\n");
        }
        
        int ll = level + 1;
        powerset(ll, str, buffer, sum, nb, size, buffer_size, i);
        buffer_size --;
        nb -= atoi(str[i]);
        i++;
    }
}

int main (int ac, char **av)
{
    if (ac < 3)
    {
        printf ("ac < 3\n");
        return 1;
    }
    int sum = atoi(av[1]);
    int buffer[ac - 2];
    powerset(0, av, buffer, sum, 0, ac, 0, 2);
    return (0);
}
