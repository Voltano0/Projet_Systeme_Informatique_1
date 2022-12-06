#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include "spinLock.c"

int numberOfOccur; 

void* sectionCrit(){
    for(int i = 0; i < numberOfOccur; i++)
    {
        lock();
        for (int i=0; i<10000; i++);
        unlock();
    }
    
};
int main(int argc, char const *argv[])
{
    int N = atoi(argv[1]);
    numberOfOccur = 6400/N;

    pthread_t threads[N];
    for (int i = 0; i < N; i++){
        if(pthread_create(&threads[i], NULL, sectionCrit, NULL) !=0)return 1;
    }
    for (int i = 0; i < N; i++){
        if(pthread_join(threads[i], NULL)!=0)return 1;
    }
    return 0;
}   