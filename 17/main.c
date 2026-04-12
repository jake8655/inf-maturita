#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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

void print_arr(int arr[], int n)
{
    for (int i = 0; i < n; i++)
        printf("%d%s", arr[i], i < n - 1 ? ", " : "\n");
}

int gcd(int a, int b)
{
    if (a % b == 0)
        return b;

    return gcd(b, a % b);
}

int main()
{
    printf("Array length: ");

    char buf[1024];
    fgets(buf, sizeof(buf), stdin);
    int n = str_to_int(buf);

    int arr[n];
    srand(time(NULL));

    for (int i = 0; i < n; i++)
    {
        arr[i] = 100 + rand() % 100;
    }

    print_arr(arr, n);

    int gcd_arr = gcd(arr[0], arr[1]);
    printf("GCD of first 2 elements: %d\n", gcd_arr);

    for (int i = 2; i < n; i++)
    {
        gcd_arr = gcd(gcd_arr, arr[i]);
    }

    printf("GCD of all elements: %d\n", gcd_arr);

    return 0;
}
