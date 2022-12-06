typedef struct custom_sema_t {
    int value;
    int *lock;
} custom_sema_t;