#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int *buffer;
int *used;
int size;
int res;


int done_before(int index, int count)
{
    int i = 0;
    while (i < count)
    {
        if (index == used[i])
            return 0;
        i++;
    }
    return 1;

}

void subset(int level, int count, int sum, int i)
{
    if (level == size)
        return ;
    while (i < size)
    {
        if (done_before(i, count))
        {
            sum += buffer[i];
            used[level] = i;
            count++;
            if (sum == res)
            {
                int z = 0;
                while (z < count)
                {
                    printf ("%d", buffer[used[z]]);
                    if (z < count - 1)
                        printf (", ");
                    else
                        printf ("\n");
                    z++;
                }
            }
            subset(level + 1, count, sum, i + 1);
            count--;
            sum -= buffer[i];
            used[i] = -1;
        }
        i++;
    }
    
}
int main (int ac, char **av)
{
    if (ac < 2)
        return 1;
    size = ac - 2;
    if (size == 0)
        return 0;
    int b[size];
    int i = 0;
    while (i < size)
    {
        b[i] = atoi(av[i + 2]);
        i++;
    }
    buffer = b;
    int u[size];
    used = u;
    res = atoi(av[1]);
    subset(0, 0, 0, 0);
}