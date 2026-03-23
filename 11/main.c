#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    FILE *f = fopen("mz.txt", "r");

    char *data[1024];
    int capital_count = 0;

    char buf[1024];
    int line_idx = 0;
    while (fgets(buf, sizeof(buf), f))
    {
        buf[strcspn(buf, "\n")] = 0;
        data[line_idx] = malloc(1024);
        int i;

        for (i = 0; buf[i] != 0; i++)
        {
            data[line_idx][i] = buf[i];

            if (buf[i] >= 'A' && buf[i] <= 'Z')
                capital_count++;
        }
        data[line_idx][i] = 0;

        sprintf(data[line_idx] + i, " %d", i);

        line_idx++;
    }

    printf("Capital count: %d\n", capital_count);

    fclose(f);
    f = fopen("mz.txt", "w");
    for (int i = 0; i < line_idx; i++)
    {
        fprintf(f, "%s\n", data[i]);
        free(data[i]);
    }

    fclose(f);

    return 0;
}
