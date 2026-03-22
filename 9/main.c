#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 12

int main()
{
    FILE *f = fopen("mzdy.txt", "r");
    int db[N][3];

    for (int i = 0; i < N; i++)
    {
        char buf[1024];
        fgets(buf, sizeof(buf), f);
        buf[strcspn(buf, "\n")] = 0;

        char *bufptr = buf;
        char *token;
        int j = 0;
        while ((token = strsep(&bufptr, " ")))
            db[i][j++] = atoi(token);
    }

    for (int i = 0; i < 3; i++)
    {
        int sum = 0;
        for (int j = 0; j < N; j++)
            sum += db[j][i];
        char *name = i == 0 ? "Otec" : i == 1 ? "Mama" : "Syn";
        printf("%s ma %d rocny zarobok\n", name, sum);
    }

    int sum = 0;
    for (int i = 0; i < N; i++)
    {
        sum += db[i][2];
        if (sum >= 500)
        {
            printf("Syn splatil dlh v %d. mesiaci\n", i + 1);
            break;
        }
    }

    fclose(f);

    return 0;
}
