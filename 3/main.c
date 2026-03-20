#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct
{
    int *data;
    int size;
} Int_Array;

void print_int_array(Int_Array *array)
{
    for (int i = 0; i < array->size; i++)
        printf("%d%s", array->data[i], i < array->size - 1 ? ", " : "\n");
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

Int_Array generate_numbers()
{
    char buf[1024];
    printf("Array length: ");
    fgets(buf, sizeof(buf), stdin);
    int n = str_to_int(buf);

    srandom(time(NULL));

    int *numbers = malloc(sizeof(int) * 1024);
    for (int i = 0; i < n; i++)
    {
        int previous = i > 0 ? numbers[i - 1] : 0;
        numbers[i] = (random() % 101) + previous;
    }

    return (Int_Array){.data = numbers, .size = n};
}

typedef struct
{
    int idx;
    int iter_count;
} BS_Result;

BS_Result binary_search(Int_Array *array)
{
    char buf[1024];
    printf("Number to find: ");
    fgets(buf, sizeof(buf), stdin);
    int n = str_to_int(buf);

    int l = 0;
    int r = array->size - 1;
    int i = 0;
    while (l <= r)
    {
        i++;
        int m = (l + r) / 2;

        if (array->data[m] == n)
            return (BS_Result){.idx = m, .iter_count = i};
        if (n > m)
            l = m + 1;
        else
            r = m - 1;
    }

    return (BS_Result){.idx = -1, .iter_count = i};
}

int main()
{
    Int_Array numbers = generate_numbers();
    print_int_array(&numbers);

    BS_Result result = binary_search(&numbers);
    free(numbers.data);
    if (result.idx == -1)
        printf("Number not found.\n");
    else
        printf("Number found at index: %d\n", result.idx);
    printf("iter count %d\n", result.iter_count);

    return 0;
}
