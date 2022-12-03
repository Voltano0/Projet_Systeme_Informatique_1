#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

int numberOfPhilo;
pthread_mutex_t *baguette; 
pthread_t *phil;

void error(int err, char *msg) {
  fprintf(stderr,"%s a retourné %d message d'erreur : %s\n",msg,err,strerror(errno));
  exit(EXIT_FAILURE);
}

void mange(int id) {//printf("Philosophe [%d] mange\n",id);
}


void* philosophe ( void* arg)
{
  int* i = (int*) arg;
  int id = *i;
  int left = id;
  int right = (left + 1) % numberOfPhilo;
  
  for(int i=0; i<100000; i++){
    // philosophe pense
    if(left<right) {
      pthread_mutex_lock(&baguette[left]);
      pthread_mutex_lock(&baguette[right]);
    }
    else {
      pthread_mutex_lock(&baguette[right]);
      pthread_mutex_lock(&baguette[left]);
    }
    mange(id);
    pthread_mutex_unlock(&baguette[left]);
    pthread_mutex_unlock(&baguette[right]);
  }
  return (NULL);
}


int main ( int argc, char *argv[])
{
  numberOfPhilo = atoi(argv[1]);
  int id[numberOfPhilo];
  //autant de couvert que de chaise, hors avec 1 philosphe, il n'y a qu'un couvert donc pas assez pour manger -> bug
  if(numberOfPhilo ==1){
    baguette = (pthread_mutex_t*) malloc((numberOfPhilo+1)*sizeof(pthread_mutex_t));
   }else{
    baguette = (pthread_mutex_t*) malloc(numberOfPhilo*sizeof(pthread_mutex_t));
  }
  phil = (pthread_t*)malloc(numberOfPhilo*sizeof(pthread_t));

  srand(getpid());

  for (int i = 0; i < numberOfPhilo; i++)
    id[i]=i;

  for (int i = 0; i < numberOfPhilo; i++) {
    int err=pthread_mutex_init(&baguette[i], NULL);
    
    if(err!=0) error(err,"pthread_mutex_init");
  }

  for (int i = 0; i < numberOfPhilo; i++) {
    int err=pthread_create(&phil[i], NULL, philosophe,(void*)&(id[i]));

    if(err!=0) error(err,"pthread_create");
  }

  for (int i = 0; i < numberOfPhilo; i++) {
    int err = pthread_join(phil[i], NULL);

    if(err!=0) error(err,"pthread_join");
  }

  for (int i = 0; i < numberOfPhilo; i++) {
    int err = pthread_mutex_destroy(&baguette[i]);
    if(err!=0) error(err,"pthread_mutex_destroy");
  }
  free(baguette);
  free(phil);

  return (EXIT_SUCCESS);
}
