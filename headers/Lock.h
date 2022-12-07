/**
 * Switch the value of locker with 1
 * @param locker variable set to 0 or 1
 *  
*/
void lock(int* locker){
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
/**
 * Switch the value of locker with 0
 * @param locker variable set to 0 or 1
 *  
*/
void unlock(int* locker){
    __asm(
        "movl $0, %0 ;"
        : "=m" (*locker)
        :: "eax"
        );
};