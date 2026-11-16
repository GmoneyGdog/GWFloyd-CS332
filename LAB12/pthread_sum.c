/* 
  Simple Pthread Program to find the sum of a vector.
  Uses mutex locks to update the global sum. 
  Author: Purushotham Bangalore
  Date: Jan 25, 2009

  To Compile: gcc -O -Wall pthread_sum.c -lpthread
  To Run: ./a.out 1000 4
*/
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

struct ThreadData{
  double *a;
  double *sum;
  int N;
  int size;
  long tid;
};


pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;

//double *a=NULL, sum=0.0;
//int    N, size;

void *compute(void *arg) {
    int myStart, myEnd, myN, i;
    struct ThreadData *data = (struct ThreadData *)arg;

    // determine start and end of computation for the current thread
    myN = data->N/data->size;
    myStart = data->tid*myN;
    myEnd = myStart + myN;
    if (data->tid == (data->size-1)) myEnd = data->N;

    // compute partial sum
    double mysum = 0.0;
    for (i=myStart; i<myEnd; i++)
      mysum += data->a[i];

    // grab the lock, update global sum, and release lock
    pthread_mutex_lock(&mutex);
    *(data->sum) += mysum;
    pthread_mutex_unlock(&mutex);

    return (NULL);
}

int main(int argc, char **argv) {
    long i;
    pthread_t *tid;

    if (argc != 3) {
       printf("Usage: %s <# of elements> <# of threads>\n",argv[0]);
       exit(-1);
    }

    int N = atoi(argv[1]); // no. of elements
    int size = atoi(argv[2]); // no. of threads
    double sum = 0.0;

    // allocate vector and initialize
    clock_t start = clock();
    tid = (pthread_t *)malloc(sizeof(pthread_t)*size);
    struct ThreadData *data = (struct ThreadData *)malloc(sizeof(struct ThreadData) * size);
    double *a = (double *)malloc(sizeof(double)*N); 
    for (i=0; i<N; i++)
      a[i] = (double)(i + 1);

    // create threads
    for ( i = 0; i < size; i++){
      data[i].a = a;
      data[i].sum = &sum;
      data[i].N = N;
      data[i].size = size;
      data[i].tid = i;
      pthread_create(&tid[i], NULL, compute, (void *)&data[i]);
    }
    
    // wait for them to complete
    for ( i = 0; i < size; i++)
      pthread_join(tid[i], NULL);
    clock_t end = clock();
    float seconds = (float)(end - start) / CLOCKS_PER_SEC;
    printf("The time is %f\n", seconds);
    printf("The total is %g, it should be equal to %g\n", sum, ((double)N*(N+1))/2);
    
    return 0;
}

