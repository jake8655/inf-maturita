#include <stdio.h>
#include <string.h>

int main()
{
    FILE *dva = fopen("./dva.txt", "r");
    FILE *zero = fopen("./0.txt", "w");
    FILE *one = fopen("./1.txt", "w");

    int zeros = 0;
    int ones = 0;

    char buf[1024];
    while (fgets(buf, sizeof(buf), dva))
    {
        buf[strcspn(buf, "\n")] = 0;
        printf("%s\n", buf);

        int i;
        for (i = 0; buf[i] != 0; i++)
        {
            if (buf[i] == '0')
                zeros++;
            if (buf[i] == '1')
                ones++;
        }

        if (buf[i - 1] == '0')
            fprintf(zero, "%s\n", buf);
        if (buf[i - 1] == '1')
            fprintf(one, "%s\n", buf);
    }

    printf("Zeros: %d\n", zeros);
    printf("Ones: %d\n", ones);
    fclose(dva);
    fclose(zero);
    fclose(one);

    return 0;
}
