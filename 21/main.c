#include <stdio.h>

void algorithm(int arr[])
{
    int x = 0;
    int p = arr[x];

    for (int i = 1; i < 8; i++)
    {
        int y = x + i;
        if (y > 8)
            y -= 8;
        arr[x] = arr[y];
        x = y;
    }
    arr[x] = p;
}

void print_arr(int arr[], int n)
{
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int main()
{
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8};
    int n = sizeof(arr) / sizeof(int);
    algorithm(arr);
    print_arr(arr, n);

    return 0;
}
