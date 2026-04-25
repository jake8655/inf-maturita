#include <stdio.h>
#include <stdlib.h>
#include <time.h>

size_t gen_rand_num()
{
    return (1000 * (1 + (rand() % 9))) + rand() % 1000;
}

size_t symmetric(size_t num)
{
    size_t result = 0;
    while (num > 0)
    {
        size_t digit = num % 10;
        result = result * 10 + digit;
        num /= 10;
    }

    return result;
}

size_t gen_rand_num_starting(size_t digit)
{
    return digit * 1000 + rand() % 1000;
}

size_t contains(size_t arr[], size_t n, size_t val)
{
    for (size_t i = 0; i < n; i++)
        if (arr[i] == val)
            return 1;

    return 0;
}

void dump_nums(size_t arr[], size_t n)
{
    for (size_t i = 0; i < n; i++)
        printf("%zu%s", arr[i], i < n - 1 ? ", " : "\n");
}

int main()
{
    srand(time(NULL));

    size_t num = gen_rand_num();
    printf("Num: %zu\n", num);

    size_t sym = symmetric(num);
    printf("Symmetric: %zu\n", sym);

    size_t first_digit = num / 1000;
    size_t new_nums[4];
    size_t new_nums_size = 0;
    while (new_nums_size != 4)
    {
        size_t new = gen_rand_num_starting(first_digit);
        if (new != num && !contains(new_nums, new_nums_size, new))
            new_nums[new_nums_size++] = new;
    }

    dump_nums(new_nums, new_nums_size);

    return 0;
}
