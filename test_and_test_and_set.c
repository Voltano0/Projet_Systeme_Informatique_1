#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

int numberOfOccur; 
int lockAllThread = 0;

void lock(int* locker){
    while(*locker == 1){};
    __asm(
        "1:"
        "movl $1, %%eax;"  
        "xchgl %%eax, %0;"
        "testl %%eax, %%eax;"
        "jnz 1b;"
        : "=m" (*locker)
        :
        : "eax"
        );
};
void unlock(int* locker){
    __asm(
        "movl $0, %0 ;"
        : "=m" (*locker)
        :: "eax"
        );
};

void* sectionCrit(void* arg){
    int * locker = (int*)arg;
    for(int i = 0; i < numberOfOccur; i++)
    {
        lock(locker);
        for (int i=0; i<10000; i++);
        unlock(locker);
    }
    
};

int main(int argc, char const *argv[])
{
    int N = atoi(argv[1]);
    numberOfOccur = 6400/N;
    int *locker = malloc(sizeof(int));
    *locker = 0;
    pthread_t threads[N];
    for (int i = 0; i < N; i++){
        if(pthread_create(&threads[i], NULL, sectionCrit, (void*)locker) !=0)return 1;
    }
    for (int i = 0; i < N; i++){
        if(pthread_join(threads[i], NULL)!=0)return 1;
    }
    return 0;
}   