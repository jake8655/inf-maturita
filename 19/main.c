#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef enum
{
    MALE,
    FEMALE
} Sex;

void print_sex(Sex sex)
{
    printf("Sex: %s\n", sex == MALE ? "Male" : "Female");
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
        fprintf(stderr, "ERROR: Failed to read from stdin\n");
        return 1;
    }

    buf[strcspn(buf, "\n")] = 0;

    if (strlen(buf) != 10)
    {
        fprintf(stderr, "ERROR: Invalid input\n");
        return 1;
    }

    int year, month, day, custom, consumed;

    if (sscanf(buf, "%2d%2d%2d%4d%n", &year, &month, &day, &custom, &consumed) != 4 || consumed != 10)
    {
        fprintf(stderr, "ERROR: Invalid input\n");
        return 1;
    }

    Sex sex = MALE;
    if (month >= 50)
    {
        sex = FEMALE;
        month -= 50;
    }

    print_sex(sex);

    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    int currentYear = t->tm_year % 100;

    if (year <= currentYear)
        year += 100;

    year += 1900;

    printf("Year: %d\n", year);

    currentYear = t->tm_year + 1900;
    int age = currentYear - year;

    printf("Age: %d\n", age);

    return 0;
}
