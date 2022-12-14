#include<pthread.h>
#include<stdio.h>
#include<unistd.h>
#include<stdbool.h>
#include<semaphore.h>

#define N 8 // places dans le buffer

int buffer[N];
pthread_mutex_t mutex;
sem_t empty;
sem_t full;
int head = 0;
int nProd = 0;
int nProd2 = 8192;

/**
 * Insert item in the buffer
 * @param item
 * 
*/
void ins(int item){
    if (head < 8){
        buffer[head] = item;
    }else{
        printf("ERROR: Insert when Buffer was already full");
    }
    head++;
}
/**
 * Remove item from the buffer
 * @return item
*/
int rem(){
    if (head > 0){
        head--;
        return buffer[head];
    }else{
        printf("ERROR: Insert when Buffer was already empty");
    }
}
/**
 * Produce item and insert it in the buffer
 * 
*/
void* producer(){
  int item = 1;
  for (int i=0; i<10000; i++);
  bool run = true;
  while(run){
    sem_wait(&empty); // attente d'une place libre
    pthread_mutex_lock(&mutex);
        if(nProd < 8192){
            ins(item);
            nProd++;
        }else{run = false;}
    pthread_mutex_unlock(&mutex);
    sem_post(&full); // il y a une place remplie en plus
    }
}
/**
 * Remove item from the buffer and consume it
 * 
*/
void* consumer(){   
    int item;
    bool run = true;
    while(run){
        sem_wait(&full); // attente d'une place remplie
        pthread_mutex_lock(&mutex);
        if(nProd2 > 0){
            item = rem();
            nProd2--;
        }else{run = false;}
        pthread_mutex_unlock(&mutex);
        sem_post(&empty); // il y a une place libre en plus
        for (int i=0; i<10000; i++);
    }
}

int main(int argc, char const *argv[])
{
    int nProduct;
    int nConsom;

    pthread_mutex_init(&mutex, NULL);
    sem_init(&empty, 0 , N);
    sem_init(&full, 0 , 0); 
    sscanf(argv[1], "%d", &nProduct);
    sscanf(argv[2], "%d", &nConsom);

    pthread_t ProdThreads[nProduct];
    pthread_t ConsThreads[nConsom];
    for (int i = 0; i < nProduct; i++){
        if(pthread_create(&ProdThreads[i],NULL,&producer,NULL)!=0)return 1;
    }
    for (int i = 0; i < nConsom; i++){
        if(pthread_create(&ConsThreads[i],NULL,&consumer,NULL)!=0)return 1;
    }
    for (int i = 0; i < nProduct; i++){
        if(pthread_join(ProdThreads[i],NULL)!=0)return 1;
    }
    for (int i = 0; i < nConsom; i++){
        if(pthread_join(ConsThreads[i],NULL)!=0)return 1;
    }
    pthread_mutex_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);
    return 0;
}