#include <stdio.h>

int b = 0;

int ballance(char *str)
{
    int i = 0;
    int unopened = 0;
    int unclosed = 0;
    while (str[i])
    {
        if (str[i] == '(')
            unclosed ++;
        else if (str[i] == ')')
        {
            if (unclosed > 0)
                unclosed --;
            else
                unopened ++;
        }
        i++;
    }
    return (unclosed + unopened);
}

void rip(int level, char *str, int c)
{
    if (b == c && !ballance(str))
    {
        puts(str);
        return ;
    }
    int i = level;
    while (str[level])
    {
        if (str[level] == '(' || str[level] == ')')
        {
            char tmp = str[level];
            str[level] = ' ';
            rip(level + 1, str, c + 1);
            str[level] = tmp;
        }
        level++;
    }
}

int main (int ac, char** av)
{
    if (ac != 2)
    {
        printf ("err \n");
        return (1);
    }
    b = ballance(av[1]);
    rip(0, av[1], 0);
}
