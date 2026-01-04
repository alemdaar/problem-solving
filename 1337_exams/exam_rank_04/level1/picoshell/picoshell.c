#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sysexits.h>
#include <string.h>


int picoshell(char **cmds[])
{
    if(!cmds || !*cmds)
        return 1;
    int i = 0;
    int fd[2];
    int pid;
    int tmp = -1;
    int exitcode = 0;   
    int st;

    while(cmds[i])
    {
        if(cmds[i + 1])
            pipe(fd);
        pid = fork();
        if(pid == -1)
        {
            close(fd[0]);
            close(fd[1]);
            return 1;
        }
        if(pid == 0)
        {
            if (i == 0)
            {
                // first
                if(cmds[i + 1])
                {
                    dup2(fd[1], 1);
                    close(fd[1]);
                    close(fd[0]);
                }
                execvp(cmds[i][0], cmds[i]);
                exit(1);
            }
            else if (!cmds[i + 1])
            {
                // last
                dup2(tmp, 0);
                close(tmp);
                execvp(cmds[i][0], cmds[i]);
                exit(1);
            }
            else
            { //meddle
                dup2(tmp, 0);
                close(tmp);
                dup2(fd[1], 1);
                close(fd[0]);
                close(fd[1]);
                execvp(cmds[i][0], cmds[i]);
                exit(1);
            }
        }
        else
        {
            if(cmds[i + 1])
                close(fd[1]);
            if(tmp != -1)
                close(tmp);
            tmp = fd[0];
        }
        i++;
    }
    while(wait(&st) > 0)
    ;
    return(exitcode);
}

// int main(int argc, char **argv)
// {
// 	int cmds_size = 1;
// 	for (int i = 1; i < argc; i++)
// 	{
// 		if (!strcmp(argv[i], "|"))
// 			cmds_size++;
// 	}
// 	char ***cmds = calloc(cmds_size + 1, sizeof(char **));
// 	if (!cmds)
// 	{
// 		dprintf(2, "Malloc error: %m\n");
// 		return 1;
// 	}
// 	cmds[0] = argv + 1;
// 	int cmds_i = 1;
// 	for (int i = 1; i < argc; i++)
// 		if (!strcmp(argv[i], "|"))
// 		{
// 			cmds[cmds_i] = argv + i + 1;
// 			argv[i] = NULL;
// 			cmds_i++;
// 		}
// 	int ret = picoshell(cmds);
// 	if (ret)
// 		perror("picoshell");
// 	free(cmds);
// 	return ret;
// }

// int main()
// {
//     char *cmd1[] = {"ls", "-l", NULL};
//     char *cmd2[] = {"wc", "-l", NULL};
//     char *cmd3[] = {"cat", "-e", NULL};
//     // char *cmd4[] = {"cat", "-e", NULL};
//     char **cmd[] = {cmd1, cmd2, cmd3,  NULL};
//     int code = picoshell(cmd);
//     printf("exit code %d\n", code );
//     // pause();