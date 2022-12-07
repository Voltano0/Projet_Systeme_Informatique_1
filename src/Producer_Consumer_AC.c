#include<pthread.h>
#include<stdio.h>
#include<unistd.h>
#include<stdbool.h>
#include"../headers/semative.h"
#define N 8 // places dans le buffer
int buffer[N];
int* mutex;
custom_sema_t empty;
custom_sema_t full;
int head = 0;
int nprod = 0;
int nprod2 = 8192;

void ins(int item){
    if (head < 8){
        buffer[head] = item;
    }
    else{
        printf("ERROR: Insert when Buffer was already full");
    }
    head++;
}
int rem(){
    if (head > 0){
        head--;
        return buffer[head];
    }
    else{
        printf("ERROR: Insert when Buffer was already empty");
    }
}

// Producteur
void* producer()
{
  int item = 1;
  for (int i=0; i<10000; i++);
  bool run = true;
  while(run)
  {
    wait(&empty); // attente d'une place libre
    lock(mutex);
        if(nprod < 8192){
        ins(item);
        nprod++;
        }
        else {
            run = false;
        }
    unlock(mutex);
    post(&full); // il y a une place remplie en plus
    }
 }

// Consommateur
void* consumer()
{   
 int item;
 bool run = true;
 while(run)
 {
   wait(&full); // attente d'une place remplie
   lock(mutex);
    if(nprod2 > 0){
        item = rem();
        nprod2--;
        }
        else {
            run = false;
        }
   unlock(mutex);
   post(&empty); // il y a une place libre en plus
   for (int i=0; i<10000; i++);
 }
}

int main(int argc, char const *argv[])
{
    int nproduct;
    int nconsom;
    mutex = malloc(sizeof(int));
    *mutex = 0;
    init(&empty, N);
    init(&full, 0); 
    sscanf(argv[1], "%d", &nproduct);
    sscanf(argv[2], "%d", &nconsom);

    pthread_t ProdThreads[nproduct];
    pthread_t ConsThreads[nconsom];
    for (size_t i = 0; i < nproduct; i++)
    {
        if(0 != pthread_create(&ProdThreads[i],NULL,&producer,NULL)){
            printf("ERROR: Error while creating producter thread n°%ld",i);
        }
        //else printf("Producter Thread %ld created\n",i+1);
    }
    for (size_t i = 0; i < nconsom; i++)
    {
        if(0 != pthread_create(&ConsThreads[i],NULL,&consumer,NULL)){
            printf("ERROR: Error while creating consumer thread n°%ld\n",i);
        }
        //else printf("Consumer Thread %ld created\n",i+1);
    }
    for (size_t i = 0; i < nproduct; i++)
    {
        if(0 != pthread_join(ProdThreads[i],NULL)){
            printf("ERROR: Error while joining producter thread n°%ld\n",i);
        }
    }
    for (size_t i = 0; i < nconsom; i++)
    {
        if(0 != pthread_join(ConsThreads[i],NULL)){
            printf("ERROR: Error while joining consumer thread n°%ld\n",i);
        }
    }
    free(mutex);
    destroy(&empty);
    destroy(&full);
    return 0;
}