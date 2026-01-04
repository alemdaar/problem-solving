#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include <sys/types.h>

// add these variable
ssize_t size;
float     (*arr)[2];
int     visited[11];
float   best_route = 999999999999999;


float    distance(float a[2], float b[2])
{
    return sqrtf((b[0] - a[0]) * (b[0] - a[0]) + (b[1] - a[1]) * (b[1] - a[1]));
}

int all_visited()
{
    for (int i = 0; i < size; i++)
    {
        if (!visited[i])
            return (false);
    }
    return (true);
}

void tsp(int   where , float distance_acc)
{
    if (all_visited())
    {
        distance_acc += distance(arr[where], arr[0]);
        if (distance_acc < best_route)
            best_route = distance_acc;
    }
    for (int i = 0; i < size; i++)
    {
        if (visited[i])
            continue;
        distance_acc += distance(arr[where], arr[i]);
        visited[i] = true;
        tsp(i, distance_acc);
        distance_acc += distance(arr[where], arr[i]);
        visited[i] = false;
    }
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

    ssize_t size = file_size(file);
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
    // for (int i = 0; i < size; i++)
    //     visited[i] = false;
    tsp(0, 0);
    printf("%.2f\n", tsp(array, size)); // recplace with :
    // printf("%.2f\n", best_route); // recplace with :
    free(array);
    return (0);
}