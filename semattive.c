#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <malloc.h>
#include <unistd.h>
#include "custom_sema_t.h"
#include "test_and_test_and_set.c"


void initA(custom_sema_t *custom_sem, int initial_value){
    custom_sem -> value = initial_value;
}

void waitA(custom_sema_t *custom_sem){
    while (true) {
        //permet au post de qm accéder au verrou
        lock();
        if (custom_sem->value > 0){
            (custom_sem -> value)--;
            break;
        }
        unlock();
    }
    unlock();
}

void postA(custom_sema_t *custom_sem){
    lock();
    (custom_sem -> value)++;
    unlock();
}

void destroyA(custom_sema_t *custom_sem){
}