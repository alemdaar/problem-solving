#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include <sys/types.h>


size_t size;
float best_route;
int c;
int visited[11];
float (*arr)[2];

float    distance(float a[2], float b[2])
{
    return sqrtf((b[0] - a[0]) * (b[0] - a[0]) + (b[1] - a[1]) * (b[1] - a[1]));
}

int all_visited()
{
    int i = 0;
    while (i < size)
    {
        if (visited[i] == 0)
            return 0;
        i++;
    }
    return 1;
}

void tsp(int where, float did, int level)
{
    if (all_visited())
    {
        did += distance(arr[where], arr[0]);
        if (c == 0)
        {
            best_route = did;
            c = 1;
            printf ("best_route : %f\n", best_route);
        }
        else if (did < best_route)
        {
            best_route = did;
            printf ("best_route : %f\n", best_route);
        }
        return;
    }

    for (int next = 0; next < size; next++)
    {
        // printf ("next %d\n", next);
        if (visited[next] || where == next)
        {
            continue;
        }
        did += distance(arr[where], arr[next]);
        visited[next] = 1;
        // printf ("level %d, did : %f, where %d, next %d\n", level, did, where, next);
        tsp (next, did, level + 1);
        visited[next] = 0;
        did -= distance(arr[where], arr[next]);
    }
    return ;
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
        visited[i++] = 0;
    visited[0] = 1;
    arr = array;
    visited[0] = 1;
    c = 0;
    printf ("size : %zu\n", size);
    tsp(0, 0, 0);
    printf("%.2f\n", best_route);
    free(array);
    return (0);
}


