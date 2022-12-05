#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

int lockAllThread = 0;

void lock(){
    int inter =0;
    asm(
        "movl $1, %%eax;"
        "xchgl %%eax %1;"
        "movl %%eax, %0;" 
        :"=r"(inter, lockAllThread)        //Output
        :"r"(lockAllThread)                 //Input
        :"%eax","%ebx"
        );
    printf("%d", inter);
    printf("%d", lockAllThread);
};

void unlock();


int main(int argc, char const *argv[])
{
    int N = atoi(argv[1]);
    lock();
    return 0;
}