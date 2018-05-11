#ifndef UPSIDEDOWN_BTHREAD_PRIVATE_H
#define UPSIDEDOWN_BTHREAD_PRIVATE_H
#define save_context(CONTEXT) sigsetjmp(CONTEXT,1)
#define restore_context(CONTEXT) siglongjmp(CONTEXT,1)

#include <setjmp.h>
#include "bthread.h"
typedef struct {
} bthread_attr_t;


typedef struct {
} bthread_attr_t;

typedef void *(*bthread_routine) (void* );

typedef unsigned long int bthread_t;

typedef enum { __BTHREAD_EXITED = 0, __BTHREAD_ZOMBIE, __BTHREAD_UNINITIALIZED,
    __BTHREAD_READY, __BTHREAD_BLOCKED, __BTHREAD_SLEEPING } bthread_state;

typedef struct {
    bthread_t tid;
    bthread_routine body;
    void* arg;
    bthread_state state;
    const bthread_attr_t *attr;
    jmp_buf context;
    void* retval;
} __bthread_private;


typedef struct {
    TQueue queue;
    TQueue current_item;
    jmp_buf context;
} __bthread_scheduler_private;

typedef void *(*bthread_routine) (void* );

typedef struct {
    bthread_t tid;
    bthread_routine body;
    void* arg;
    bthread_state state;
    bthread_attr_t attr;
    jmp_buf context;
    void* retval;
} __bthread_private;



__bthread_scheduler_private* bthread_get_scheduler();
static void bthread_initialize_next();
static void bthread_create_cushion(__bthread_private* t_data);
static int bthread_reap_if_zombie(bthread_t, void **);





#endif //UPSIDEDOWN_BTHREAD_PRIVATE_H