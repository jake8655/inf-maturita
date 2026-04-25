#include <errno.h>
#include <limits.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PRICE_PER_MIN 0.1

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

typedef struct
{
    size_t hours;
    size_t minutes;
    size_t seconds;
} Call;

void dump_calls(Call calls[], size_t n)
{
    for (size_t i = 0; i < n; i++)
        printf("%zu:%zu:%zu\n", calls[i].hours, calls[i].minutes, calls[i].seconds);
}

size_t count_all_secs(Call calls[], size_t n)
{
    size_t secs = 0;
    for (size_t i = 0; i < n; i++)
        secs += calls[i].seconds + calls[i].minutes * 60 + calls[i].hours * 60 * 60;

    return secs;
}

Call format_secs(size_t secs)
{
    size_t hours = secs / (60 * 60);
    size_t minutes = (secs % (60 * 60)) / 60;
    size_t seconds = secs - hours * 60 * 60 - minutes * 60;

    return (Call){.hours = hours, .minutes = minutes, .seconds = seconds};
}

float calc_price(size_t secs)
{
    size_t minutes = secs / 60 + (secs % 60 != 0 ? 1 : 0);

    return minutes * PRICE_PER_MIN;
}

int main()
{
    Call calls[100];
    size_t calls_size = 0;

    char buf[20];
    while (1)
    {
        printf("Enter call length (h:m:s, EMPTY to stop): ");
        if (!fgets(buf, sizeof(buf), stdin))
        {
            fprintf(stderr, "ERROR: Could not read from stdin.\n");
            return 1;
        }
        if (buf[0] == '\n')
            break;

        buf[strcspn(buf, "\n")] = 0;

        char *tok;
        char *bufptr = buf;
        size_t i = 0;
        Call call;
        while ((tok = strsep(&bufptr, ":")))
        {
            if (i % 3 == 0)
                call.hours = str_to_int(tok);
            else if (i % 3 == 1)
                call.minutes = str_to_int(tok);
            else
                call.seconds = str_to_int(tok);

            i++;
        }
        calls[calls_size++] = call;
    }

    dump_calls(calls, calls_size);
    size_t total_seconds = count_all_secs(calls, calls_size);
    printf("Total seconds %zu\n", total_seconds);

    Call total_time = format_secs(total_seconds);
    printf("Total time %zu:%zu:%zu\n", total_time.hours, total_time.minutes, total_time.seconds);

    float total_price = calc_price(total_seconds);
    printf("Total price %.2f€\n", total_price);

    return 0;
}
