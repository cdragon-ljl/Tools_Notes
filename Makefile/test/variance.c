#include "variance.h"
#include "means.h"

int variance(int a[], int n)
{
    int sum = 0, i;
    int m = means(a, n);
    for(i = 0; i < n; i++)
    {
        sum += (a[i] - m) * (a[i] - m);
    }

    return sum / n;
}