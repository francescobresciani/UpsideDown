//
// Created by Roberto Trapletti on 15.03.18.
//

#ifndef UPSIDEDOWN_BTHREAD_PRIVATE_H
#define UPSIDEDOWN_BTHREAD_PRIVATE_H

#include <setjmp.h>
#include "bthread.h"

typedef struct {
    bthread_t tid;
    bthread_routine body;
    void* arg;
    bthread_state state;
    bthread_attr_t attr;
    jmp_buf context;
    void* retval;
} __bthread_private;

#endif //UPSIDEDOWN_BTHREAD_PRIVATE_H
