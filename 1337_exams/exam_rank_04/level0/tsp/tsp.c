#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include <sys/types.h>


ssize_t size;
float     (*arr)[2];
int     visited[11];
float   best_route;
int c = 0;

float    distance(float a[2], float b[2])
{
    return sqrtf((b[0] - a[0]) * (b[0] - a[0]) + (b[1] - a[1]) * (b[1] - a[1]));
}

ssize_t    file_size(FILE *file)
{
    char    *buffer = NULL;
    size_t    n = 0;
    ssize_t ret;

    errno = 0;

    for (ret = 0; getline(&buffer, &n, file) != -1; ret++);

    free(buffer);
    if (errno || fseek(file, 0, SEEK_SET))
        return -1;
    return ret;
}

int        retrieve_file(float (*array)[2], FILE *file)
{
    int tmp;
    for (size_t i = 0; (tmp = fscanf(file, "%f, %f\n", array[i] + 0, array[i] + 1)) != EOF; i++)
        if (tmp != 2)
        {
            errno = EINVAL;
            return -1;
        }
    if (ferror(file))
        return -1;
    return 0;
}

int all_visited()
{
    int i = 0;
    while (i < size)
    {
        // printf ("..\n");
        if (visited[i] == 0)
            return 0;
        i++;
    }
    return 1;
}

void tsp(int level, int where, float did)
{
    // printf ("level : %d\n", level);
    if (all_visited())
    {
        // printf ("1\n");
        did += distance(arr[where], arr[0]);
        if (c == 0)
        {
            best_route = did;
            c = 1;
        }
        else
        {
            if (did < best_route)
                best_route = did;
        }
        did -= distance(arr[where], arr[0]);
        return ;
    }
    // printf ("1\n");
    int next = 0;
    while (next < size)
    {
        if (visited[next] || where == next)
        {
            next++;
            continue;
        }
        visited[next] = 1;
        did += distance(arr[where], arr[next]);
        tsp(level + 1, next, did);
        did -= distance(arr[where], arr[next]);
        visited[next] = 0;
        next++;
    }
    return ;
}

int        main(int ac, char **av)
{
    char *filename = "stdin";
    FILE *file = stdin;
    if (ac > 1)
    {
        filename = av[1];
        file = fopen(filename, "r");
    }

    if (!file)
    {
        fprintf(stderr, "Error opening %s: %m\n", filename);
        return 1;
    }

    size = file_size(file);
    if (size == -1)
    {
        fprintf(stderr, "Error reading %s: %m\n", filename);
        fclose(file);
        return 1;
    }

    float (*array)[2] = calloc(size, sizeof (float [2]));
    if (!array)
    {
        fprintf(stderr, "Error: %m\n");
        fclose(file);
        return 1;
    }

    if (retrieve_file(array, file) == -1)
    {
        fprintf(stderr, "Error reading %s: %m\n", av[1]);
        fclose(file);
        free(array);
        return 1;
    }
    if (ac > 1)
        fclose(file);
    int i = 0;
    while (i < 11)
    {
        visited[i] = 0;
        i++;
    }
    visited[0] = 1;
    c = 0;
    arr = array;
    tsp(0, 0, 0);
    printf("%.2f\n", best_route);
    free(array);
    return (0);
}
