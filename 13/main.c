#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int bin_to_dec(char *num)
{
    int result = 0;
    for (int i = 0; num[i] != 0; i++)
    {
        result <<= 1;

        if (num[i] == '1')
            result++;
    }

    return result;
}

int dec_to_bin(int num)
{
    int result = 0;

    for (int i = 1; num > 0; i *= 10)
    {
        int remainder = num % 2;
        result += remainder * i;
        num /= 2;
    }

    return result;
}

int main()
{
    FILE *f = fopen("cisla.txt", "r");
    char buf[1024];
    int same = 0;

    while (fgets(buf, sizeof(buf), f))
    {
        buf[strcspn(buf, "\n")] = 0;
        printf("%s\n", buf);
        char *bufptr = buf;
        char *binary = strsep(&bufptr, " ");
        if (bin_to_dec(binary) == atoi(bufptr))
            same++;
    }

    printf("Same: %d\n", same);

    fclose(f);

    return 0;
}
