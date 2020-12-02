#include <stdio.h>
#include "means.h"
#include "variance.h"

int main(void)
{
    int a[5] = {1,2,3,4,5}, n=5;

    printf("means = %d\n", means(a, n));
    printf("variance = %d\n", variance(a, n));

    return 0;
}