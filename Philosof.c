#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

int numberOfPhilo;
pthread_t *phil;
pthread_mutex_t *baguette;

void mange(int id) {};

void penser(int id){};

void* philosophe (void* arg)
{
  int * idl = (int*) arg;
  int left = *idl;pthread_t *phil;
  int numberOfPhilo1 = (numberOfPhilo==1) ? numberOfPhilo+1 : numberOfPhilo;
  int right = (left + 1) % numberOfPhilo1;
  for (int j = 0; j < 100000; j++) {
    // philosophe pense
    if(left<right) {
      pthread_mutex_lock(&baguette[left]);
      pthread_mutex_lock(&baguette[right]);
    }
    else {
      pthread_mutex_lock(&baguette[right]);
      pthread_mutex_lock(&baguette[left]);
    }
    mange(*idl);
    pthread_mutex_unlock(&baguette[left]);
    pthread_mutex_unlock(&baguette[right]);
    penser(*idl);
  }
  return (NULL);
}

int main ( int argc, char *argv[])
{
    numberOfPhilo = atoi(argv[1]);
    long i;
    int id[numberOfPhilo];
    int numberOfPhilo1 = (numberOfPhilo==1) ? numberOfPhilo+1 : numberOfPhilo;
    if (numberOfPhilo == 1){
      baguette = (pthread_mutex_t *) malloc((numberOfPhilo+1) * sizeof(pthread_mutex_t));
    }
    else{
      baguette = (pthread_mutex_t *) malloc(numberOfPhilo * sizeof(pthread_mutex_t));
    }
    phil = (pthread_t *) malloc(numberOfPhilo*sizeof(pthread_mutex_t));

    for (i = 0; i < numberOfPhilo; i++){
      id[i]=i;
    }

    for (i = 0; i < numberOfPhilo1; i++){
      pthread_mutex_init( &baguette[i], NULL);
    }

    for (i = 0; i < numberOfPhilo; i++){
      pthread_create(&phil[i], NULL, philosophe, (void*)&(id[i]) );
    }

    for (i = 0; i < numberOfPhilo; i++){
      pthread_join(phil[i], NULL);
    }

    for (int i = 0; i < numberOfPhilo1; i++)
    {
      pthread_mutex_destroy(&baguette[i]);
    }

    free(baguette);
    free(phil);
    return 0;
}