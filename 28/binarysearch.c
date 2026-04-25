int binary_search(int arr[], int n, int val)
{
    int low = 0;
    int high = n - 1;

    while (low <= high)
    {
        int middle = (low + high) / 2;
        if (arr[middle] == val)
            return middle;
        if (arr[middle] > val)
            high = middle - 1;
        else
            low = middle + 1;
    }

    return -1;
}
