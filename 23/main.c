#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long str_to_long(char *str)
{
    char *endptr;
    errno = 0;
    long num = strtol(str, &endptr, 10);
    int len = strlen(str);

    if (errno == ERANGE || endptr == str || (*endptr && *endptr != str[len - 1]))
    {
        fprintf(stderr, "ERROR: Not a number: %s\n", str);
        exit(1);
    }

    return num;
}

int str_to_int(char *str)
{
    long num = str_to_long(str);
    if (num > INT_MAX)
    {
        fprintf(stderr, "ERROR: Number too large: %ld", num);
        exit(1);
    }

    return (int)num;
}

typedef struct
{
    int x;
    int y;
} Point;

void dump_points(Point points[], int size)
{
    for (int i = 0; i < size; i++)
        printf("Point(X: %d, Y: %d)\n", points[i].x, points[i].y);
}

int main()
{
    FILE *f = fopen("./body.txt", "r");

    Point points[10];
    int points_size = 0;

    char buf[10];
    while (fgets(buf, sizeof(buf), f))
    {
        char *bufptr = buf;
        char *x = strsep(&bufptr, " ");

        Point point = {.x = str_to_int(x), .y = str_to_int(bufptr)};
        points[points_size++] = point;
    }
    fclose(f);

    dump_points(points, points_size);

    int max_x = 0, max_y = 0;
    int min_x = INT_MAX, min_y = INT_MAX;

    for (int i = 0; i < points_size; i++)
    {
        if (points[i].x < min_x)
            min_x = points[i].x;
        if (points[i].y < min_y)
            min_y = points[i].y;

        if (points[i].x > max_x)
            max_x = points[i].x;
        if (points[i].y > max_y)
            max_y = points[i].y;
    }

    int width = max_x - min_x;
    int height = max_y - min_y;

    printf("Rectangle(w: %d, h: %d)\n", width, height);

    return 0;
}
