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
		long int swap_pos;

		/* randomized quicksort, not just quicksort */
		if (right - left + 1) { /* avoid mod by 0 */
			swap_pos = rand() % (right-left+1);  /* anywhere in [left .. right] */
			swap(v, v[left], v[swap_pos]);
		}

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

/* print_array: print array to file, with optional starting message */
int print_array(FILE *f, int *array, char *starting_message)
{
    long int i;

    if (!f) {
        fprintf(stderr, "Error: trying to print to nonexistant file\n");
        return EXIT_FAILURE;
    }

    if (!array) {
        fprintf(stderr, "Error: trying to print nonexistant array\n");
        return EXIT_FAILURE;
    }

    if (starting_message) {
        fprintf(f, "%s\n", starting_message);
    }

    for (i = 0; i < ARRAYLENGTH-1; i++)
        fprintf(f, "%d, ", array[i]);
    fprintf(f, "%d\n\n", array[i]);

    return EXIT_SUCCESS;
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
    print_array(output, array, "Initial array:");

    quicksort(array, 0, ARRAYLENGTH-1);

    print_array(output, array, "Sorted:");
    fclose(output);
}
