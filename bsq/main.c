#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

typedef struct info {
    ssize_t size_line;
    int graph[2];
    int len;
    int lines;
    char empty;
    char obstacles;
    char full;
} info;

int is_printable(char c)
{
    if (c >= ' ' && c <= 126)
        return 1;
    return 0;
}
int mystrlen(char *c)
{
    int i = 0;
    while(c[i])
        i++;
    return i;
}

int check(char **map, info *data, int j, int i)
{
    if (data->lines - 1 < data->len + j || data->size_line - 1 < data->len + i)
        return 0;
    int y = 0;
    while (y < data->len + 1)
    {
        int tmp = i;
        int x = 0;
        while (x < data->len + 1)
        {
            if(map[j+y][i+x] != data->empty)
                return 0;
            x++;
        }
        y++;
    }
    data->graph[0] = j;
    data->graph[1] = i;
    data->len++;
    return 1;
}

int f(FILE *stream)
{
    info data;
    char nl;
    if (fscanf(stream, "%d%c%c%c%c", &data.lines, &data.empty, &data.obstacles, &data.full, &nl) != 5)
        return (printf ("fscanf != 5\n"), 1);
    if (nl != '\n')
        return (printf ("nl != nl\n"), 1);
    if (!(is_printable(data.empty) && is_printable(data.full) && is_printable(data.obstacles)))
        return (printf ("keys not printable\n"), 1);
    if (data.empty == data.full || data.empty == data.obstacles || data.full == data.obstacles)
        return (printf ("keys same\n"), 1);
    // 
    char **map = malloc(sizeof(char *) * data.lines + 1);
    if (!map)
        return (printf ("malloc failed map**\n"), 1);
    size_t tmp;
    data.size_line = getline(&map[0], &tmp, stream);
    if (data.size_line == -1)
        return (printf ("getline failed\n"), free(map), 1);
    int i = 1; // '1' because weve read the first line already
    while (i < data.size_line)
    {
        ssize_t r = getline(&map[i], &tmp, stream);
        if (feof(stream))
        {
            // printf("Reached EOF\n");
            break;
        }
        else if (ferror(stream))
        {
            return (printf ("getline failed 2\n"), free(map), 1);
            perror("getline");
        }
        if (data.size_line != r) {
            if (map[i][r - 1] == '\n') {
                return (printf ("lines arent equal\n"), free(map), 1);
            }
        }
        i++;
    }
    char *buffer = NULL;
    tmp = 0;
    if (i != data.lines || getline(&buffer, &tmp, stream) > 0)
        return (printf ("i'%d' != data.size_line'%zd' or getline still reads\n", i, data.size_line), free(map), 1);
    
    if (data.size_line > 1)
    {
        data.size_line --;
        i = 0;
        while (map[i])
        {
            map[i][data.size_line] = 0;
            i++;
        }
    }
    // 
    int j = 0;
    i = 0;
    i = 0;
    data.graph[0] = -1;
    data.graph[1] = -1;
    data.len = 0;
    while (j < data.lines)
    {
        while (i < data.size_line)
        {
            if (map[j][i] == data.empty)
                while (check(map, &data, j, i) == 1);
            i++;
        }
        j++;
    }
    // printf ("x : %d\n", data.graph[1]);
    // printf ("y : %d\n", data.graph[0]);
    // printf ("len : %d\n", data.len);
    int x = data.graph[1];
    int y = data.graph[0];
    j = 0;
    while (j < data.lines)
    {
        i = 0;
        while (i < data.size_line)
        {
            if (i >= x && i < x + data.len && j >= y && j < y + data.len)
                printf("%c", data.full);
            else
                printf("%c", map[j][i]);
            i++;
        }
        printf("\n");
        j++;
    }
    return 0;
}

int main (int ac, char **av)
{
    if (ac == 1)
        f(stdin);
    else if (ac == 2)
    {
        FILE *stream = fopen(*(++av), "r");
        if (stream)
        {
            f(stream);
            fclose(stream);
        }
    }
    else {
        printf ("too many ac\n");
    }
    return 0;
}

