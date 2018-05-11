#ifndef UPSIDEDOWN_BTHREAD_H
#define UPSIDEDOWN_BTHREAD_H

#include <setjmp.h>
#include "tqueue.h"
#include "bthread_private.h"

int bthread_create(bthread_t *bthread, const bthread_attr_t *attr,
                   void *(*start_routine) (void* ), void *arg);

int bthread_join(bthread_t bthread, void **retval);

void bthread_yield();

void bthread_exit(void *retval);

void bthread_cleanup();

#endif //UPSIDEDOWN_BTHREAD_H