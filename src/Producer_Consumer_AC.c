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
int nProd = 0;
int nProd2 = 8192;

void ins(int item){
    if (head < 8){
        buffer[head] = item;
    }else{
        printf("ERROR: Insert when Buffer was already full");
    }
    head++;
}
int rem(){
    if (head > 0){
        head--;
        return buffer[head];
    }else{
        printf("ERROR: Insert when Buffer was already empty");
    }
}

// Producteur
void* producer(){
    int item = 1;
    for (int i=0; i<10000; i++);
    bool run = true;
    while(run){
        wait(&empty); // attente d'une place libre
        lock(mutex);
        if(nProd < 8192){
            ins(item);
            nProd++;
        }else {run = false;}
        unlock(mutex);
        post(&full); // il y a une place remplie en plus
    }
}

// Consommateur
void* consumer(){   
    int item;
    bool run = true;
    while(run){
        wait(&full); // attente d'une place remplie
        lock(mutex);
        if(nProd2 > 0){
            item = rem();
            nProd2--;
        }else {run = false;}
        unlock(mutex);
        post(&empty); // il y a une place libre en plus
        for (int i=0; i<10000; i++);
    }
}

int main(int argc, char const *argv[])
{
    int nProduct;
    int nConsom;

    mutex = malloc(sizeof(int));
    *mutex = 0;
    
    init(&empty, N);
    init(&full, 0); 
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
    free(mutex);
    destroy(&empty);
    destroy(&full);
    return 0;
}