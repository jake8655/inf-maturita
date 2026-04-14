#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

enum
{
    MAX_LINE = 1024,
    MAX_LINES = 1024,
    ALPHABET = 26
};

int mod(int a, int b)
{
    assert(b > 0);

    int r = a % b;
    return r < 0 ? r + b : r;
}

char *caesar(const char *text, int n)
{
    char *output = malloc(MAX_LINE);
    if (output == NULL)
        return NULL;

    int i;
    for (i = 0; text[i] != 0; i++)
    {
        if (i == MAX_LINE - 1)
            break;

        if (text[i] >= 'a' && text[i] <= 'z')
            output[i] = mod((text[i] - 'a' + n), ALPHABET) + 'a';
        else if (text[i] >= 'A' && text[i] <= 'Z')
            output[i] = mod((text[i] - 'A' + n), ALPHABET) + 'A';
        else
            output[i] = text[i];
    }
    output[i] = 0;

    return output;
}

void free_arr(char **arr, int n)
{
    for (int i = 0; i < n; i++)
        free(arr[i]);
}

int fail_with_cleanup(FILE *f, const char *msg)
{
    if (msg)
        fprintf(stderr, "ERROR: %s\n", msg);
    if (f)
        fclose(f);
    return 1;
}

int read_and_cipher(char **lines, int *count)
{
    FILE *input = fopen("./sifra.txt", "r");
    if (input == NULL)
    {
        fprintf(stderr, "ERROR: file sifra.txt not found\n");
        return 1;
    }

    printf("Ciphered text:\n");

    char buf[MAX_LINE];

    while (fgets(buf, sizeof(buf), input))
    {
        if (*count == MAX_LINES)
            break;

        char *ciphered = caesar(buf, 1);
        if (ciphered == NULL)
            return fail_with_cleanup(input, "failed to cipher text");

        printf("%s", ciphered);
        lines[(*count)++] = ciphered;
    }

    fclose(input);

    return 0;
}

int write_lines(char **lines, int n)
{
    FILE *output = fopen("output.txt", "w");
    if (output == NULL)
        return fail_with_cleanup(NULL, "couldn't open output.txt");

    for (int i = 0; i < n; i++)
    {
        fprintf(output, "%s", lines[i]);
    }
    fclose(output);

    return 0;
}

int print_deciphered(char **lines, int n)
{
    printf("Deciphered text:\n");

    for (int i = 0; i < n; i++)
    {
        char *deciphered = caesar(lines[i], -1);
        if (deciphered == NULL)
        {
            fprintf(stderr, "ERROR: failed to decipher text\n");
            return 1;
        }

        printf("%s", deciphered);
        free(deciphered);
    }

    return 0;
}

int main()
{
    char *lines[MAX_LINES];
    int rc = 1;

    int n = 0;
    if (read_and_cipher(lines, &n) != 0)
        goto cleanup;

    if (write_lines(lines, n) != 0)
        goto cleanup;

    if (print_deciphered(lines, n) != 0)
        goto cleanup;

    rc = 0;

cleanup:
    free_arr(lines, n);
    return rc;
}
