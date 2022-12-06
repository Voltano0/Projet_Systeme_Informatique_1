#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <malloc.h>
#include <unistd.h>
#include "../headers/custom_sema_t.h"
#include "test_and_test_and_set.c"


void init(custom_sema_t *custom_sem, int initial_value){

    custom_sem -> lock = (int *) calloc(1, sizeof(int));
    *(custom_sem -> lock) = 0;
    custom_sem -> value = initial_value;
}

void wait(custom_sema_t *custom_sem){
    while (true) {
        //permet au post de qm accéder au verrou
        lock(custom_sem -> lock);
        if (custom_sem->value > 0){
            (custom_sem -> value)--;
            break;
        }
        unlock(custom_sem -> lock);
    }
    unlock(custom_sem -> lock);
}

void post(custom_sema_t *custom_sem){
    lock(custom_sem -> lock);
    (custom_sem -> value)++;
    unlock(custom_sem -> lock);
}

void destroy(custom_sema_t *custom_sem){
    free(custom_sem -> lock);
}