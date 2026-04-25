#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define MESSAGE_LENGTH 160

int main()
{
    FILE *input = fopen("./sprava.txt", "r");

    char buf[1024];
    char lines[1024][1024];
    size_t lines_count = 0;

    while (fgets(buf, sizeof(buf), input))
    {
        size_t len = 0, spaces = 0;
        for (size_t i = 0; buf[i] != '\n'; i++)
        {
            len++;
            if (isspace(buf[i]))
                spaces++;
        }
        // Remove newline
        buf[len] = 0;

        printf("%s - messages: %zu, spaces: %zu\n", buf, 1 + len / MESSAGE_LENGTH, spaces);
        strncpy(lines[lines_count++], buf, len + 1);
    }
    fclose(input);
    printf("-----------------------------------\n");

    FILE *output = fopen("./kratka.txt", "w");
    for (size_t i = 0; i < lines_count; i++)
    {
        char *tok;
        char *lineptr = lines[i];
        while ((tok = strsep(&lineptr, " ")))
        {
            if (!tok[0])
                continue;

            printf("%c%s", toupper(tok[0]), tok + 1);
            fprintf(output, "%c%s", toupper(tok[0]), tok + 1);
        }
        printf("\n");
        fprintf(output, "\n");
    }
    fclose(output);

    return 0;
}
