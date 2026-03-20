#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int *data;
    int size;
} Int_Array;

void print_int_array(Int_Array *array)
{
    for (int i = 0; i < array->size; i++)
    {
        printf("%d%s", array->data[i], i < array->size - 1 ? ", " : "\n");
    }
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

Int_Array get_input_numbers()
{
    char buf[1024];
    printf("Input a list of numbers separated by spaces: ");
    fgets(buf, sizeof(buf), stdin);
    buf[strcspn(buf, "\n")] = 0;

    char *bufptr = buf;
    char *tokens[1024];
    char *token;
    int n = 0;
    while ((token = strsep(&bufptr, " ")))
    {
        tokens[n] = strdup(token);
        n++;
    }

    int *numbers = malloc(sizeof(int) * 1024);

    for (int i = 0; i < n; i++)
    {
        numbers[i] = str_to_int(tokens[i]);
    }

    return (Int_Array){.data = numbers, .size = n};
}

int find_first(Int_Array *array)
{
    char buf[1024];
    printf("Number to find: ");
    fgets(buf, sizeof(buf), stdin);
    int n = str_to_int(buf);

    int i;
    int index = -1;
    for (i = 0; i < array->size; i++)
    {
        if (array->data[i] == n)
        {
            index = i;
            break;
        }
    }

    return index;
}

int find_last(Int_Array *array)
{
    char buf[1024];
    printf("Number to find: ");
    fgets(buf, sizeof(buf), stdin);
    int n = str_to_int(buf);

    int i;
    int index = -1;
    for (i = array->size - 1; i >= 0; i--)
    {
        if (array->data[i] == n)
        {
            index = i;
            break;
        }
    }

    return index;
}

Int_Array find_all(Int_Array *array)
{
    char buf[1024];
    printf("Number to find: ");
    fgets(buf, sizeof(buf), stdin);
    int n = str_to_int(buf);

    int i;
    int *indices = malloc(sizeof(int) * 1024);
    int j = 0;
    for (i = 0; i < array->size; i++)
    {
        if (array->data[i] == n)
        {
            indices[j++] = i;
        }
    }

    return (Int_Array){.data = indices, .size = j};
}

int main()
{
    Int_Array numbers = get_input_numbers();
    print_int_array(&numbers);

    int f_index = find_first(&numbers);
    if (f_index == -1)
    {
        printf("Number not found\n");
    }
    else
    {
        printf("Number found at position: %d\n", f_index);
    }

    int l_index = find_last(&numbers);
    if (l_index == -1)
    {
        printf("Number not found\n");
    }
    else
    {
        printf("Number found at position: %d\n", l_index);
    }

    Int_Array indices = find_all(&numbers);
    if (indices.size == 0)
    {
        printf("Number not found\n");
    }
    else
    {
        printf("Number found at positions: ");
        print_int_array(&indices);
    }

    free(numbers.data);
    free(indices.data);

    return 0;
}
