#include <errno.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char **data;
    int size;
} String_Array;

typedef struct
{
    int *data;
    int size;
} Int_Array;

void print_str_array(String_Array *array)
{
    for (int i = 0; i < array->size; i++)
    {
        printf("%s%s", array->data[i], i < array->size - 1 ? ", " : "\n");
    }
}

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
        long num = str_to_long(tokens[i]);
        if (num >= INT_MAX)
        {
            fprintf(stderr, "ERROR: Number too large: %ld", num);
            exit(1);
        }
        numbers[i] = (int)num;
    }

    return (Int_Array){.data = numbers, .size = n};
}

int get_array_largest_element(Int_Array *array)
{
    int max = array->data[0];
    for (int i = 0; i < array->size; i++)
    {
        if (array->data[i] > max)
        {
            max = array->data[i];
        }
    }

    return max;
}

long exponentiate_largest(Int_Array *array)
{
    int max = get_array_largest_element(array);
    char buf[1024];
    printf("Enter the power: ");
    fgets(buf, sizeof(buf), stdin);
    long n = str_to_long(buf);

    return powl(max, n);
}

Int_Array get_even_indices(Int_Array *array)
{
    int *indices = malloc(sizeof(int) * 1024);

    int n = 0;
    for (int i = 0; i < array->size; i++)
    {
        if (array->data[i] % 2 == 0)
        {
            indices[n++] = i;
        }
    }

    return (Int_Array){.data = indices, .size = n};
}

int main()
{
    Int_Array numbers = get_input_numbers();
    print_int_array(&numbers);

    int max = get_array_largest_element(&numbers);
    printf("Largest number: %d\n", max);

    long result = exponentiate_largest(&numbers);
    printf("Result = %ld\n", result);

    Int_Array even_indices = get_even_indices(&numbers);
    printf("Even indices: ");
    print_int_array(&even_indices);

    free(numbers.data);
    free(even_indices.data);

    return 0;
}
