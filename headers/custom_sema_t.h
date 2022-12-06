typedef struct custom_sema_t {
    int value;
    int *locker;
} custom_sema_t;