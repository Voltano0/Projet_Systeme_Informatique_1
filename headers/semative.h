#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <malloc.h>
#include <unistd.h>
#include "custom_sema_t.h"
#include "../src/test_and_test_and_set.c"


void init(custom_sema_t *custom_sem){
    *(custom_sem -> locker) = 0;
    custom_sem -> locker = (int *) malloc(sizeof(int));
    custom_sem -> value = 0;
}

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

void post(custom_sema_t *custom_sem){
    lock(custom_sem -> locker);
    (custom_sem -> value)++;
    unlock(custom_sem -> locker);
}

void destroy(custom_sema_t *custom_sem){
    free(custom_sem -> locker);
}