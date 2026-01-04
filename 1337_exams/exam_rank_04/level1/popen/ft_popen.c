#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int ft_popen(const char file, char const argv[], char type)
{
    if (!file || !argv || (type != 'r' && type != 'w'))
        return -1;
    int fd[2];
    pid_t pid;
    if (pipe(fd) < 0)
        return -1;
    pid = fork();
    if (pid < 0)
        return (-1);
    if (type == 'r')
    {
        if (pid == 0)
        {
            close(fd[0]);
            dup2(fd[1], 1);
            close(fd[1]);
            execvp(file, argv);
            exit(1);
        }
        close(fd[1]);
        return(fd[0]);
    }
    else if (type == 'w')
    {
        if (pid == 0)
        {
            close(fd[1]);
            dup2(fd[0], 0);
            close(fd[0]);
            execvp(file, argv);
            exit(1);
        }
        close(fd[0]);
        return(fd[1]); 
    }
    return (-1);
}

int main (int ac, char **av)
{
    int fd = ft_popen("ls", (char*[]){"ls", NULL}, 'r');
}
