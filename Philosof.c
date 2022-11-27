#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

const int N =  8;
pthread_mutex_t baguette[N];


void error(int err, char *msg) {
  fprintf(stderr,"%s a retourné %d message d'erreur : %s\n",msg,err,strerror(errno));
  exit(EXIT_FAILURE);
}

void mange(int id) {printf("Philosophe [%d] mange\n",id);}


void* philosophe ( void* arg )
{
  int *id=(int *) arg;
  int left = *id;
  int right = (left + 1) % N;
  for (int i = 0; i < 100000; i++)
   {
    // philosophe pense
    if(left<right) {
      pthread_mutex_lock(&baguette[left]);
      pthread_mutex_lock(&baguette[right]);
    }
    else {
      pthread_mutex_lock(&baguette[right]);
      pthread_mutex_lock(&baguette[left]);
    }
    mange(*id);
    pthread_mutex_unlock(&baguette[left]);
    pthread_mutex_unlock(&baguette[right]);
  }
  return (NULL);
}


int main ( int argc, char *argv[])
{
    //int N = atoi(argv[1]);
    int i;
    int id[N];
    int err;
    pthread_t phil[N];

    for (i = 0; i < N; i++)
        id[i]=i;

    for (i = 0; i < N; i++) {
        err=pthread_mutex_init( &baguette[i], NULL);
        if(err!=0) error(err,"pthread_mutex_init");
    }

    for (i = 0; i < N; i++) {
        err=pthread_create(&phil[i], NULL, philosophe, (void*)&(id[i]) );
        if(err!=0) error(err,"pthread_create");
    }

    for (i = 0; i < N; i++) {
        pthread_join(phil[i], NULL);
        if(err!=0) error(err,"pthread_join");
    }

    for (i = 0; i < N; i++) {
        pthread_mutex_destroy(&baguette[i]);
        if(err!=0) error(err,"pthread_mutex_destroy");
    }

    return (EXIT_SUCCESS);
}