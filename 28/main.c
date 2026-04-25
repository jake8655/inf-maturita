#include "binarysearch.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void dump_names(char (*names)[1024], size_t n)
{
    for (size_t i = 0; i < n; i++)
        printf("%s\n", names[i]);
}

int compare(const void *a, const void *b)
{
    return (*(int *)a) - (*(int *)b);
}

int main()
{
    FILE *f = fopen("./mena.txt", "r");

    size_t long_count = 0;
    char names[1024][1024];
    size_t names_count = 0;

    char buf[1024];
    while (fgets(buf, sizeof(buf), f))
    {
        size_t len = strnlen(buf, 1024);
        // Remove newline
        buf[len - 1] = 0;

        if (len > 8)
        {
            long_count++;
        }
        buf[8] = 0;
        strncpy(names[names_count++], buf, 9);
    }

    fclose(f);

    dump_names(names, names_count);

    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int n = sizeof(arr) / sizeof(int);
    int key = 2;
    int idx = binary_search(arr, n, key);
    int *item = bsearch(&key, arr, n, sizeof(int), compare);
    int idx2 = item - arr;
    printf("%d = %d\n", idx, idx2);

    return 0;
}
