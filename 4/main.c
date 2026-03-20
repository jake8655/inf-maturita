#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

typedef struct
{
    char *data;
    int size;
} Char_Array;

void print_char_array(Char_Array *array)
{
    for (int i = 0; i < array->size; i++)
        printf("%c%s", array->data[i], i < array->size - 1 ? ", " : "\n");
}

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
    if (num >= INT_MAX)
    {
        fprintf(stderr, "ERROR: Number too large: %ld", num);
        exit(1);
    }

    return (int)num;
}

Char_Array generate_letters()
{
    char buf[1024];
    printf("Array length: ");
    fgets(buf, sizeof(buf), stdin);
    int n = str_to_int(buf);

    char *letters = malloc(1024);
    for (int i = 0; i < n; i++)
    {
        int previous = i > 0 ? letters[i - 1] : 97;
        int remaining = 122 - previous;
        int n = MIN(random() % ((random() % 10) + 1), remaining);
        letters[i] = previous + n;
    }

    return (Char_Array){.data = letters, .size = n};
}

Char_Array merge(Char_Array arr1, Char_Array arr2)
{
    char *result = malloc(2048);
    int i = 0, j = 0, k = 0;

    while (i < arr1.size && j < arr2.size)
    {
        if (arr1.data[i] <= arr2.data[j])
        {
            result[k++] = arr1.data[i++];
        }
        else
        {
            result[k++] = arr2.data[j++];
        }
    }

    while (i < arr1.size)
        result[k++] = arr1.data[i++];
    while (j < arr2.size)
        result[k++] = arr2.data[j++];

    return (Char_Array){.data = result, .size = k};
}

int main()
{
    srandom(time(NULL));

    Char_Array arr1 = generate_letters();
    print_char_array(&arr1);

    Char_Array arr2 = generate_letters();
    print_char_array(&arr2);

    Char_Array merged = merge(arr1, arr2);
    print_char_array(&merged);

    free(arr1.data);
    free(arr2.data);
    free(merged.data);

    return 0;
}
