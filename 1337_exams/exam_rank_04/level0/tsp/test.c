#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include <sys/types.h>


size_t size;
int visited[11];
float (*arr)[2];
float   best_route = 999999999999999;

float    distance(float a[2], float b[2])
{
    return sqrtf((b[0] - a[0]) * (b[0] - a[0]) + (b[1] - a[1]) * (b[1] - a[1]));
}

int all_v()
{
    for (size_t i = 0; i < size; i++)
    {
        if (visited[i] == false)
            return false;
        i++;
    }
    return false;
}

void tsp(int where, int distance_acc)
{
    if (all_v())
    {
        distance_acc += distance(arr[where], arr[0]);
        if (distance_acc < best_route)
            best_route = distance_acc;
    }
    for (size_t i = 0; i < size; i++)
    {
        if (visited[i])
            continue;
        distance_acc += distance(arr[where], arr[i]);
        visited[i] = true;
        tsp(i, distance);
        visited[i] = false;
        distance_acc += distance(arr[where], arr[i]);
    }
    
}