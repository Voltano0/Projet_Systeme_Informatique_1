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
