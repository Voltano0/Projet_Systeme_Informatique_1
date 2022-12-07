#include"../headers/Lock2.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <pthread.h>

int numberOfPhilo;
int *baguette;

/**
 * philosophe that eat and think for 100000 times
 * @param arg number of the philosophe
 * 
*/
void* philosophe (void* arg){
  int * idl = (int*) arg;
  int left = *idl;
  int numberOfPhilo1 = (numberOfPhilo==1) ? numberOfPhilo+1 : numberOfPhilo;
  int right = (left + 1) % numberOfPhilo1;
  for (int j = 0; j < 100000; j++) {
    if(left<right) {
      lock(&baguette[left]);
      lock(&baguette[right]);
    }
    else {
      lock(&baguette[right]);
      lock(&baguette[left]);
    }
    unlock(&baguette[left]);
    unlock(&baguette[right]);
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
    baguette = (int *) malloc((numberOfPhilo+1) * sizeof(int));
  }else{
    baguette = (int *) malloc(numberOfPhilo * sizeof(int));
  }

  for (int i = 0; i < numberOfPhilo; i++){
    id[i]=i;
    baguette[i] =0;
  }
  for (int i = 0; i < numberOfPhilo; i++){
    if(pthread_create(&phil[i], NULL, philosophe, (void*)&(id[i]) )!=0)return 1;
  }
  for (int i = 0; i < numberOfPhilo; i++){
    if(pthread_join(phil[i], NULL)!=0)return 1;
  }
  free(baguette);
  return 0;
}