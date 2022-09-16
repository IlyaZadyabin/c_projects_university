#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <time.h>

int comp_count = 0;
int move_count = 0;

int low_high(const void *a, const void *b)
{
    if(*(long long int*)a > *(long long int*)b)
        return 1;
    else if (*(long long int*)a < *(long long int*)b)
        return -1;
    else
        return 0;
}

int high_low(const void *a, const void *b)
{
    if(*(long long int*)a > *(long long int*)b)
        return -1;
    else if (*(long long int*)a < *(long long int*)b)
        return 1;
    else
        return 0;
}

void generate_array(long long int *a, long long *b, int n, int var)
{
    int i;
    for(i = 0; i < n; i++)
        a[i] = (rand() * rand() * rand() * rand() * rand() );

    switch(var)
    {
        case 1:
            qsort(a, n, sizeof(long long int), low_high);
            break;
        case 2:
            qsort(a, n, sizeof(long long int), high_low);
            break;
    }
    for(i = 0; i < n; i++)
        b[i] = a[i];
}

int partition (long long int *a, int begin, int end)
{
    long long int tmp, pivot;
    int i, j;
    pivot = a[end];
    i = begin - 1;

    for (j = begin; j <= end - 1; j++)
    {
        comp_count++;
        if (a[j] <= pivot)
        {
            i++;
            if(a[j] != a[i])
            {
                tmp = a[i];
                a[i] = a[j];
                a[j] = tmp;
                move_count++;
            }
        }
    }

    if(a[i+1] != a[end])
    {
        tmp = a[i + 1];
        a[i+1] = a[end];
        a[end] = tmp;
        move_count++;
    }

    return i + 1;
}

void quick_sort(long long int *a, int begin, int end)
{
    if (begin < end)
    {
        int pivot_idx = partition(a, begin, end);

        quick_sort(a, begin, pivot_idx - 1);
        quick_sort(a, pivot_idx + 1, end);
    }
}

void selection_sort(long long int *a, int n)
{
    int i, j, min_idx;
    long long int tmp;
    for(j = 0; j < n - 1; j++)
    {
        min_idx = j;
        for(i = j + 1; i < n; i++)
        {
            comp_count++;
            if(a[i] < a[min_idx])
                min_idx = i;
        }

        if(min_idx != j)
        {
            tmp = a[j];
            a[j] = a[min_idx];
            a[min_idx] = tmp;
            move_count++;
        }
    }
}

void check(long long int *a, int n)
{
    int i;
    for(i = 1; i < n; i++)
    {
        if(a[i] < a[i-1])
        {
            printf("NOT SORTED\n");
            return;
        }
    }
    printf("SORTED\n");
}

int main(void)
{
    int i, n;
    srand(time(NULL));
    scanf("%d", &n);
    long long int *a = (long long int*) malloc(n * sizeof(long long int));
    long long int *b = (long long int*) malloc(n * sizeof(long long int));

    generate_array(a, b, n, 1);

    printf("Before the sorting\n");
   // for(i = 0; i < n; i++)
     //  printf("%lli ", a[i]);
    printf("\n-----------------\nAfter the sorting:\n\n");

    quick_sort(a, 0, n - 1);
    check(a, n);
    printf("QuickSort:\n");
    
    //for(i = 0; i < n; i++)
       // printf("%lli ", a[i]);
    

    printf("\nComparison counter = %d\n", comp_count);
    printf("Exchange counter = %d\n", move_count);
    printf("-----------------\n");

    comp_count = 0;
    move_count = 0;

    selection_sort(b, n);
    check(b, n);

    printf("SelectionSort:\n");
   // for(i = 0; i < n; i++)
    //    printf("%lli ", b[i]);

    printf("\nComparison counter = %d\n", comp_count);
    printf("Exchange counter = %d\n", move_count);
    free(a);
    free(b);
    return 0;
}
