#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <malloc.h>
#include <unistd.h>
#include "custom_sema_t.h"
#include "Lock2.h"

/**
 * initialize the value of the semaphore
 * @param custom_sem custom semaphore with our spinlock
 * @param value number of instances of the semaphore
 *  
*/
void init(custom_sema_t *custom_sem, int value){
    custom_sem -> locker = (int *) malloc(sizeof(int));
    *(custom_sem -> locker) = 0;
    custom_sem -> value = value;
}
/**
 * wait until the value of the semaphore is greater than 0
 * @param custom_sem custom semaphore with our spinlock
 *  
*/
void wait(custom_sema_t *custom_sem){
    bool run = true;
    while (run) {
        lock(custom_sem -> locker);
        if (custom_sem->value > 0){
            (custom_sem -> value)--;
            run = false;
        }
        unlock(custom_sem -> locker);
    }
}
/**
 * Increment the value of the semaphore
 * @param custom_sem custom semaphore with our spinlock
 *  
*/
void post(custom_sema_t *custom_sem){
    lock(custom_sem -> locker);
    (custom_sem -> value)++;
    unlock(custom_sem -> locker);
}
/**
 * destroy the semaphore
 * @param custom_sem custom semaphore with our spinlock
 *  
*/
void destroy(custom_sema_t *custom_sem){
    free(custom_sem -> locker);
}