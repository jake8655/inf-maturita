#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 5

size_t roll()
{
    return rand() % 6 == 0;
}

void dump_points(size_t points[N][N])
{
    printf("----------------------\n");
    for (size_t i = 0; i < N; i++)
    {
        printf("Hrac %zu: ", i + 1);
        for (size_t j = 0; j < N; j++)
            printf("%zu%s", points[i][j], j == N - 1 ? "\n" : ", ");
    }
    printf("----------------------\n");
}

int main()
{
    srand(time(NULL));

    size_t points[N][N];
    size_t scores[N];

    for (size_t i = 0; i < N; i++)
    {
        size_t curr_points = 0;
        for (size_t j = 0; j < N; j++)
        {
            points[i][j] = roll();
            curr_points += points[i][j];
        }
        scores[i] = curr_points;
    }

    dump_points(points);

    size_t max_wins = 0;
    size_t wins = 0;
    for (size_t i = 0; i < N; i++)
    {
        wins += scores[i];
        if (scores[i] > max_wins)
            max_wins = scores[i];
    }

    printf("Celkovo uspesne: %zu\n", wins);

    size_t winners[N];
    size_t winners_size = 0;
    for (size_t i = 0; i < N; i++)
    {
        if (scores[i] == max_wins)
            winners[winners_size++] = i + 1;
    }

    if (winners_size == 1)
        printf("Vyhral hrac %zu s %zu %s.\n", winners[0], max_wins, max_wins > 1 ? "bodmi" : "bodom");
    else
    {
        printf("Vyhrali hraci ");
        for (size_t i = 0; i < winners_size; i++)
            printf("%zu%s", winners[i], i < winners_size - 1 ? ", " : " ");
        printf("s %zu %s.\n", max_wins, max_wins > 1 ? "bodmi" : "bodom");
    }

    return 0;
}
