#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

int numberOfOccur; 
int lockAllThread = 0;

void lock(){
    //implement spinlock with inline assembly
    while(lockAllThread == 1){};
    __asm(
        "1:"
        "movl $1, %%eax;"  
        "xchgl %%eax, %0;"
        "testl %%eax, %%eax;"
        "jnz 1b;"
        : "=m" (lockAllThread)
        :
        : "eax", "ebx"
        );
};

void unlock(){
    //implement spinlock unlock wit#include "spinLock.c"h inline assembly
    __asm(
        "movl $0, %0 ;"
        : "=m" (lockAllThread)
        :: "eax"
        );
};

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