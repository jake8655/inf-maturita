#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 10

typedef struct
{
    int length;
    int difficulty;
} Route;

void print_routes(Route *routes)
{
    for (int i = 0; i < N; i++)
    {
        printf("%d %d\n", routes[i].length, routes[i].difficulty);
    }
}

int main()
{
    FILE *f = fopen("trasa.txt", "r");

    Route routes[N];

    for (int i = 0; i < N; i++)
    {
        char buf[1024];
        fgets(buf, sizeof(buf), f);
        buf[strcspn(buf, "\n")] = 0;

        char *bufptr = buf;
        char *first = strsep(&bufptr, " ");
        int length = atoi(first);
        int difficulty = atoi(bufptr);

        routes[i] = (Route){.length = length, .difficulty = difficulty};
    }

    fclose(f);

    print_routes(routes);

    int total_len = 0;
    int len_per_dif[5] = {0};
    int max_len = 0;
    int max_len_dif;
    for (int i = 0; i < N; i++)
    {
        total_len += routes[i].length;
        len_per_dif[routes[i].difficulty - 1] += routes[i].length;

        if (routes[i].length > max_len)
        {
            max_len = routes[i].length;
            max_len_dif = routes[i].difficulty;
        }
    }

    printf("Total length: %d\n", total_len);

    for (int i = 0; i < 5; i++)
    {
        printf("Length of all difficulty %d: %d\n", i + 1, len_per_dif[i]);
    }

    printf("Difficulty of longest route: %d\n", max_len_dif);

    return 0;
}
