#include <stdio.h>

int mod(int a, int b)
{
    int r = a % b;
    return r < 0 ? r + b : r;
}

void caesar(char *text, int n)
{
    for (int i = 0; text[i] != 0; i++)
    {
        if (text[i] >= 'a' && text[i] <= 'z')
            text[i] = mod((text[i] + n - 'a'), 26) + 'a';
        if (text[i] >= 'A' && text[i] <= 'Z')
            text[i] = mod((text[i] + n - 'A'), 26) + 'A';
    }
}

int main()
{
    FILE *f = fopen("./sifra.txt", "r");

    printf("Ciphered text: ");

    char text[1024][1024];
    char buf[1024];

    int n = 0;
    while (fgets(buf, sizeof(buf), f))
    {
        caesar(buf, 1);
        printf("%s", buf);
        sprintf(text[n++], "%s", buf);
    }

    fclose(f);

    FILE *output = fopen("output.txt", "w");
    for (int i = 0; i < n; i++)
    {
        fprintf(output, "%s", text[i]);
    }
    fclose(output);

    printf("Deciphered text: ");
    for (int i = 0; i < n; i++)
    {
        caesar(text[i], -1);
        printf("%s", text[i]);
    }

    return 0;
}
