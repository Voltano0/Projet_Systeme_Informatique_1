#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

int lockAllThread = 0;

void lock(){
    int inter =0;
    //implement spinlock with inline assempbly
    __asm__ __volatile__(
        "1: \n"
        "movl $1, %%eax \n"
        "xchgl %%eax, %0 \n"
        "testl %%eax, %%eax \n"
        "jnz 1b \n"
        : "=m" (lockAllThread)
        :
        : "eax"
        
    );
    printf("%d", inter);
    printf("%d", lockAllThread);
};

void unlock(){
    //implement spinlock unlock with inline assempbly
    __asm__ __volatile__(
        "movl $0, %0 \n"
        : "=m" (lockAllThread)
        :
        : "eax"
        
    );
    }

int main(int argc, char const *argv[])
{
    int N = atoi(argv[1]);
    lock();
    unlock();
    lock();
    return 0;
}