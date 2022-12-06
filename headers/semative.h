#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <malloc.h>
#include <unistd.h>
#include "custom_sema_t.h"
#include "Lock2.h"


void init(custom_sema_t *custom_sem, int value){
    custom_sem -> locker = (int *) malloc(sizeof(int));
    *(custom_sem -> locker) = 0;
    custom_sem -> value = value;
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