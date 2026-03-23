#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    FILE *f1 = fopen("vyraz.txt", "r");
    FILE *f2 = fopen("nevyraz.txt", "w");

    int valid = 0;

    char line[1024];
    int line_count = 0;
    // Loop through lines
    while (fgets(line, sizeof(line), f1))
    {
        bool skip = false;

        line_count++;
        line[strcspn(line, "\n")] = 0;

        // Loop through each character in line
        int i;
        int plus_idx = 0;
        int sum = 0;
        for (i = 0; line[i] != 0; i++)
        {
            if (line[i] == '+')
            {
                if (i == 0)
                {
                    fprintf(f2, "%s\n", line);
                    skip = true;
                    break;
                }

                plus_idx = i;
            }
            else
            {
                sum += atoi(&line[i]);
            }
        }

        if (skip)
            continue;

        if (plus_idx == i - 1)
        {
            fprintf(f2, "%s\n", line);
            continue;
        }

        if (line_count == 1)
            printf("Line 1 result: %d\n", sum);

        valid++;
    }

    fclose(f1);
    fclose(f2);

    printf("Correct: %d\n", valid);

    return 0;
}
