#include <stdio.h>
#include <stdlib.h>
#define ARRAYLENGTH 20000

/*  swap: interchange v[i] and v[j] */
void swap(int v[], long int i, long int j)
{
    int temp;

    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

/* quicksort: sort v[left]...v[right] into increasing order */
void quicksort(int v[], long int left, long int right)
{
    long int i, last_swapped_pos;

    if (left >= right) /* do nothing if array contains */
        return;        /* fewer than 2 elements */
    swap(v, left, (left + right)/2); /*  move partition elem to v[0] */
    last_swapped_pos = left;
    for (i = left + 1; i <= right; i++) /* partition */
        if (v[i] < v[left])
            swap(v, ++last_swapped_pos, i);
    swap(v, left, last_swapped_pos);      /* restore partition elem */
    quicksort(v, left, last_swapped_pos-1);
    quicksort(v, last_swapped_pos+1, right);
}

int main()
{
    FILE *output;
    long int i;
    int array[ARRAYLENGTH];

    for (i = 0; i < ARRAYLENGTH; i++)
    {
        array[i] = rand() % 100;
    }

    output = fopen("output", "w");
    fprintf(output, "Initial array:\n");
    for (i = 0; i < ARRAYLENGTH; i++)
        fprintf(output, "%d, ", array[i]);
    fprintf(output, "%d\n\n", array[i]);

    quicksort(array, 0, ARRAYLENGTH-1);

    fprintf(output, "Sorted:\n");
    for (i = 0; i < ARRAYLENGTH-1; i++)
        fprintf(output, "%d, ", array[i]);
    fprintf(output, "%d\n", array[i]);
}
