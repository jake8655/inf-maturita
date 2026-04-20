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

int main()
{
    char buf[1024];
    if (!fgets(buf, sizeof(buf), stdin))
    {
        fprintf(stderr, "ERROR: Failed to read from stdin.\n");
    }

    int n = str_to_int(buf);
    char arr[n];
    srand(time(NULL));
    for (int i = 0; i < n; i++)
    {
        arr[i] = (rand() % 26) + (rand() % 2 == 0 ? 'a' : 'A');
    }
    arr[n] = 0;

    printf("%s\n", arr);

    if (!fgets(buf, sizeof(buf), stdin))
    {
        fprintf(stderr, "ERROR: Failed to read from stdin.\n");
    }
    buf[1] = 0;

    int count = 0;
    for (int i = 0; i < n; i++)
    {
        if (arr[i] == buf[0])
            count++;
    }
    printf("%c count: %d\n", buf[0], count);

    for (int i = 0; i < n; i++)
    {
        if (arr[i] >= 'a')
            arr[i] -= 32;
    }

    printf("%s\n", arr);

    return 0;
}
