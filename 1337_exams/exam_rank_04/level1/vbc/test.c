







char *line;


int f3()
{
    char c = *line;
    int r = 0;
    if (c == 0)
        // err
    if (c == 0)
        // err
}

int f2()
{
    int r = f3();
    while (*line == '*')
    {
        line++;
        r += f3();
    }
    return (r);
}
int f1()
{
    int r = f2();
    while (*line == '+')
    {
        line++;
        r += f2();
    }
    return (r);
}
int main (int ac, char **av)
{
    if (ac < 2)
        return ;
    line = av[1];
    int result =  f1();
    if (*line != 0)
        error_msg(*line, 0);
}