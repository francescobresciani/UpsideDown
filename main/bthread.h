#ifndef UPSIDEDOWN_BTHREAD_H
#define UPSIDEDOWN_BTHREAD_H

#include <setjmp.h>
#include "tqueue.h"

typedef struct {
} bthread_attr_t;

typedef void *(*bthread_routine) (void* );

typedef unsigned long int bthread_t;

typedef enum { __BTHREAD_EXITED = 0, __BTHREAD_ZOMBIE, __BTHREAD_UNINITIALIZED,
    __BTHREAD_READY, __BTHREAD_BLOCKED, __BTHREAD_SLEEPING } bthread_state;

typedef struct {
    TQueue queue;
    TQueue current_item;
    jmp_buf context;
} __bthread_scheduler_private;

__bthread_scheduler_private* bthread_get_scheduler(); // Private

int bthread_create(bthread_t *bthread, const bthread_attr_t *attr,
                   void *(*start_routine) (void* ), void *arg);

int bthread_join(bthread_t bthread, void **retval);

void bthread_yield();

void bthread_exit(void *retval);

void bthread_cleanup(); // Private


#endif //UPSIDEDOWN_BTHREAD_H