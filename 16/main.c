#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char *name;
    char *lastname;
    char *title;
    int publishYear;
} BookData;

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

BookData get_input_book(char *buf)
{
    char *bufptr = buf;
    char *tokens[1024];
    char *token;
    int n = 0;
    while ((token = strsep(&bufptr, ",")))
    {
        tokens[n] = strdup(token);
        n++;
    }

    if (n != 4)
    {
        fprintf(stderr, "ERROR: Invalid input\n");
        exit(1);
    }

    int publishDate = str_to_int(tokens[3]);
    free(tokens[3]);

    BookData book = {.name = tokens[0], .lastname = tokens[1], .title = tokens[2], .publishYear = publishDate};

    return book;
}

int main()
{
    char buf[1024];
    printf("Input book data: name of author, book title, publish year separated by commas (x to stop): ");
    for (;;)
    {
        fgets(buf, sizeof(buf), stdin);
        buf[strcspn(buf, "\n")] = 0;

        if (strcmp(buf, "x") == 0)
            break;

        FILE *f = fopen("./db.csv", "a");
        BookData book = get_input_book(buf);
        fprintf(f, "%s,%s,%s,%d\n", book.name, book.lastname, book.title, book.publishYear);
        fclose(f);
    }

    printf("Enter a lastname to search for: ");
    fgets(buf, sizeof(buf), stdin);
    buf[strcspn(buf, "\n")] = 0;

    char liAuthors[1024][1024];
    int count = 0;

    char fbuf[1024];
    FILE *f = fopen("./db.csv", "r");
    while (fgets(fbuf, sizeof(fbuf), f))
    {
        fbuf[strcspn(fbuf, "\n")] = 0;

        char *fbufptr = fbuf;
        char *tokens[1024];
        char *token;
        int n = 0;
        while ((token = strsep(&fbufptr, ",")))
        {
            tokens[n] = strdup(token);
            n++;
        }

        if (n != 4)
        {
            fprintf(stderr, "ERROR: Invalid file\n");
            exit(1);
        }

        if (strcmp(tokens[1], buf) == 0 && str_to_int(tokens[3]) > 2000)
            printf("%s\n", tokens[2]);

        if (strstr(tokens[1], "li") != NULL)
        {
            sprintf(liAuthors[count++], "%s %s", tokens[0], tokens[1]);
        }

        for (int i = 0; i < n; i++)
            free(tokens[i]);
    }

    printf("Authors with \"li\" in their lastnames:\n");
    for (int i = 0; i < count; i++)
    {
        printf("%s%s", liAuthors[i], i < count - 1 ? ", " : "\n");
    }

    return 0;
}
