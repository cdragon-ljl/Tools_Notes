#include "means.h"

int means(int a[], int n)
{
    int sum = 0, i;
    for(i = 0; i < n; i++)
    {
        sum += a[i];
    }

    return sum / n;
}