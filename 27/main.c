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

size_t gcd(size_t a, size_t b)
{
    if (a == b)
        return a;
    if (a > b)
        return gcd(a - b, b);
    return gcd(a, b - a);
}

int main()
{
    FILE *f = fopen("./zlomky.txt", "r");

    char buf[20];
    while (fgets(buf, sizeof(buf), f))
    {
        size_t numerators[2];
        size_t numerators_len = 0;
        size_t denomirators[2];
        size_t denomirators_len = 0;

        char *bufptr = buf;
        char *tok;
        size_t i = 0;
        while ((tok = strsep(&bufptr, " ")))
        {
            size_t num = str_to_int(tok);
            if (i % 2 == 0)
                numerators[numerators_len++] = num;
            else
                denomirators[denomirators_len++] = num;
            i++;
        }

        size_t numerator = numerators[0] * numerators[1];
        size_t denominator = denomirators[0] * denomirators[1];
        size_t fraction_gcd = gcd(numerator, denominator);

        numerator /= fraction_gcd;
        denominator /= fraction_gcd;

        printf("%zu/%zu\n", numerator, denominator);
    }

    fclose(f);

    return 0;
}
