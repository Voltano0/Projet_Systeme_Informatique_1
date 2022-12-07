#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

int numberOfPhilo;
pthread_mutex_t *baguette;

void* philosophe (void* arg){
  int * idl = (int*) arg;
  int left = *idl;
  int numberOfPhilo1 = (numberOfPhilo==1) ? numberOfPhilo+1 : numberOfPhilo;
  int right = (left + 1) % numberOfPhilo1;
  for (int j = 0; j < 100000; j++) {
    if(left<right) {
      pthread_mutex_lock(&baguette[left]);
      pthread_mutex_lock(&baguette[right]);
    }
    else {
      pthread_mutex_lock(&baguette[right]);
      pthread_mutex_lock(&baguette[left]);
    }
    pthread_mutex_unlock(&baguette[left]);
    pthread_mutex_unlock(&baguette[right]);
  }
  return (NULL);
}

int main ( int argc, char *argv[]){

  numberOfPhilo = atoi(argv[1]);
  int id[numberOfPhilo];
  int numberOfPhilo1 = (numberOfPhilo==1) ? numberOfPhilo+1 : numberOfPhilo;
  pthread_t phil[numberOfPhilo];

  //create 2 baguettes if there is only one philo
  if (numberOfPhilo == 1){
    baguette = (pthread_mutex_t *) malloc((numberOfPhilo+1) * sizeof(pthread_mutex_t));
  }else{
    baguette = (pthread_mutex_t *) malloc(numberOfPhilo * sizeof(pthread_mutex_t));
  }

  for (int i = 0; i < numberOfPhilo; i++){
    id[i]=i;
  }
  for (int i = 0; i < numberOfPhilo1; i++){
    if(pthread_mutex_init( &baguette[i], NULL)!=0) return 1;
  }
  for (int i = 0; i < numberOfPhilo; i++){
    if(pthread_create(&phil[i], NULL, philosophe, (void*)&(id[i]) )!=0)return 1;
  }
  for (int i = 0; i < numberOfPhilo; i++){
    if(pthread_join(phil[i], NULL)!=0)return 1;
  }
  for (int i = 0; i < numberOfPhilo1; i++){
    if(pthread_mutex_destroy(&baguette[i])!=0)return 1;
  }

  free(baguette);
  return 0;
}