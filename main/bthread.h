//
// Created by Roberto Trapletti on 15.03.18.
//

#ifndef UPSIDEDOWN_BTHREAD_H
#define UPSIDEDOWN_BTHREAD_H

typedef struct {
} bthread_attr_t;

typedef void *(*bthread_routine) (void *);

typedef unsigned long int bthread_t;

typedef enum { __BTHREAD_EXITED = 0, __BTHREAD_ZOMBIE, __BTHREAD_UNINITIALIZED,
    __BTHREAD_READY, __BTHREAD_BLOCKED, __BTHREAD_SLEEPING } bthread_state;

#endif //UPSIDEDOWN_BTHREAD_H
