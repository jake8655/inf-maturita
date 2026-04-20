#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LIMIT 15
#define CONTAINER_MAX 100

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
    int container = CONTAINER_MAX;
    int total_weight = 0;
    int total_fees = 0;

    while (1)
    {
        printf("Zadaj hmotnost batoziny (kg) (x pre koniec): ");
        if (!fgets(buf, sizeof(buf), stdin))
        {
            fprintf(stderr, "ERROR: failed to read from stdin.\n");
            return 1;
        }
        if (buf[0] == 'x')
            break;

        int weight = str_to_int(buf);
        int fee = (weight > LIMIT) * (weight - LIMIT);
        printf("Poplatok: %d,00 eur\n", fee);

        total_weight += weight;
        total_fees += fee;

        if (container - weight < 0)
        {
            printf("Do noveho kontajnera.\n");
            container = CONTAINER_MAX;
        }
        container -= weight;
    }

    printf("Celkova hmotnost: %dkg\n", total_weight);
    printf("Celkove poplatky: %d,00 eur\n", total_fees);

    return 0;
}
