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

int Z(int x)
{
    x = x / 2;
    int Z = x;
    return Z;
}

int main()
{
    printf("Zadaj cislo: ");
    char buf[1024];
    if (!fgets(buf, sizeof(buf), stdin))
    {
        fprintf(stderr, "ERROR: Failed to read from stdin\n");
        return 1;
    }

    int a = str_to_int(buf);
    int y;
    while (a > 1)
    {
        y = Z(a) + 2;
        a = a / 2;
    }
    printf("%d\n", y);

    return 0;
}
