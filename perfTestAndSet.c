#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

int lockAllThread = 0;

void lock(){
    //implement spinlock with inline assempbly
    __asm(
        "1:"
        "movl $1, %%eax;"
        "xchgl %%eax, %0;"
        "testl %%eax, %%eax;"
        "jnz 1b; "
        : "=m" (lockAllThread)
        :
        : "eax"
        );
};

void unlock(){
    //implement spinlock unlock with inline assempbly
    __asm(
        "movl $0, %0 ;"
        : "=m" (lockAllThread)
        :: "eax"
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