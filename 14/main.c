#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void fill_file()
{
    FILE *f = fopen("./clanok.txt", "w");
    srand(time(NULL));

    for (int i = 0; i < 10; i++)
    {
        int length = rand() % 100;

        for (int j = 0; j < length; j++)
        {
            int isnum = rand() % 2;
            if (isnum)
                fprintf(f, "%d", rand() % 10);
            else
            {
                int iscapital = rand() % 2;
                if (iscapital)
                    fprintf(f, "%c", 'A' + rand() % 26);
                else
                    fprintf(f, "%c", 'a' + rand() % 26);
            }
        }
        fprintf(f, "\n");
    }

    fclose(f);
}

int main()
{
    fill_file();

    FILE *f = fopen("./clanok.txt", "r");
    char buf[1024];

    int numbers = 0;
    int lower = 0;
    int upper = 0;

    while (fgets(buf, sizeof(buf), f))
    {
        buf[strcspn(buf, "\n")] = 0;
        char *bufptr = buf;

        for (; *bufptr != 0; bufptr++)
        {
            if (*bufptr >= '0' && *bufptr <= '9')
                numbers++;
            if (*bufptr >= 'a' && *bufptr <= 'z')
                lower++;
            if (*bufptr >= 'A' && *bufptr <= 'Z')
                upper++;
        }
    }

    printf("Numbers: %d\n", numbers);
    printf("Lowercase letters: %d\n", lower);
    printf("Uppercase letters: %d\n", upper);

    fclose(f);

    return 0;
}
