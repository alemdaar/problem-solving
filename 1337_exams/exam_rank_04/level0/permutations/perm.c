#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

int safe(int level, char *buffer, int index, char *str, int nb)
{
    // printf ("safe -> level %d - index : %d\n", level, index);
    int i = 0;
    while (i < level)
    {
        // printf ("%d == %d\n", buffer[i], i);
        if (str[index] == buffer[i])
            return (0);
        i++;
    }
    return (1);
}

void perm(int level, char *buffer, char *str, int nb)
{
    // printf ("1\n");
    // printf ("perm -> level %d\n", level);
    if (level == nb){
        printf ("%s\n", buffer);
        return ;
    }
    // printf ("2\n");
    int i = 0;
    while (i < nb)
    {
        if (!safe(level, buffer, i, str, nb))
        {
            i++;
            continue;
        }
        buffer[level] = str[i];
        perm(level + 1, buffer, str, nb);
        i++;
    }
    return ;
}

int    main(int ac, char **av)
{
    if (ac < 2){
        printf ("less than 2 !");
        return (1);
    }
    int nb = strlen(av[1]);
    char buffer[nb];
    perm(0, buffer, av[1], nb);
}
