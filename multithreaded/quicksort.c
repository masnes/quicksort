#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#define ARRAYLENGTH 200000
#define MAXTHREADS 4
#define MAXRAND 100

typedef struct quicksort_package {
    int *v;
    long int left;
    long int right;
} qpackage;

int allowed_threads = MAXTHREADS-1;
pthread_mutex_t globals_lock = PTHREAD_MUTEX_INITIALIZER;

/*  swap: interchange v[i] and v[j] */
void swap(int v[], long int i, long int j)
{
    int temp;

    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

/* quicksort: sort v[left]...v[right] into increasing order */
void *quicksort(void *q)
{
    int *v;
    int create_threads;
    long int left, right;
    long int i, last_swapped_pos;
    pthread_t left_thread, right_thread;
    qpackage *package;
    qpackage leftpkg;
    qpackage rightpkg;

    package = q;

    v = package->v;
    left = package->left;
    right = package->right;

    /* only deal with threading overhead if it's likely to be necessary */
    if (allowed_threads > 0) {
        while(pthread_mutex_lock(&globals_lock))
            ;
        if (allowed_threads > 1) {
            create_threads = 2;
            allowed_threads -= 2;
        } else if (allowed_threads > 0) {
            create_threads = 1;
            allowed_threads--;
        } else 
            create_threads = 0;
        while(pthread_mutex_unlock(&globals_lock))
            fprintf(stderr, "Failure giving up lock\n");
    } else
        create_threads = 0;

    if (left >= right) /* do nothing if array contains */
        return NULL;        /* fewer than 2 elements */
    swap(v, left, (left + right)/2); /*  move partition elem */
    last_swapped_pos = left;                     /* to v[0] */
    for (i = left + 1; i <= right; i++) /* partition */
        if (v[i] < v[left])
            swap(v, ++last_swapped_pos, i);
    swap(v, left, last_swapped_pos);      /* restore partition elem */

    leftpkg.v = v;
    leftpkg.left = left;
    leftpkg.right = last_swapped_pos-1;

    rightpkg.v = v;
    rightpkg.left = last_swapped_pos+1;
    rightpkg.right = right;

    if (create_threads == 2) {
        pthread_create(&left_thread, NULL, quicksort, &leftpkg);
        pthread_create(&right_thread, NULL, quicksort, &rightpkg);
        pthread_join(left_thread, NULL);
        pthread_join(right_thread, NULL);
    } else if (create_threads == 1) {
        pthread_create(&left_thread, NULL, quicksort, &leftpkg);
        quicksort(&rightpkg);
        pthread_join(left_thread, NULL);
    } else {
        quicksort(&leftpkg);
        quicksort(&rightpkg);
    }

    if (create_threads) {
        while(pthread_mutex_lock(&globals_lock))
            ;
        allowed_threads++;
        while(pthread_mutex_unlock(&globals_lock))
            fprintf(stderr, "Failure giving up lock\n");
    }
    return NULL;
}

int main()
{
    FILE *output;
    long int i;
    int array[ARRAYLENGTH];
    qpackage q;

    for (i = 0; i < ARRAYLENGTH; i++)
    {
        array[i] = rand() % MAXRAND;
    }

    output = fopen("output", "w");
    for (i = 0; i < ARRAYLENGTH-1; i++)
        fprintf(output, "%d, ", array[i]);
    fprintf(output, "%d\n\n", array[i]);

    q.v = array;
    q.left = 0;
    q.right = ARRAYLENGTH-1;
    quicksort(&q);

    for (i = 0; i < ARRAYLENGTH-1; i++)
        fprintf(output, "%d, ", array[i]);
    fprintf(output, "%d\n", array[i]);
}
