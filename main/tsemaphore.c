//
// Created by attilio on 10/06/18.
//
#include <assert.h>
#include "tsemaphore.h"
#include "bthread.h"


int bthread_sem_init(bthread_sem_t* m, int pshared, int value){

    if (m == NULL){
        m= (bthread_sem_t *) malloc(sizeof(bthread_sem_t));
    }
    m->value= value;
    m->waiting_list=NULL;
    return 0;
}

int bthread_sem_destroy(bthread_sem_t* m){
    assert(tqueue_size(m->waiting_list)==0);
    free(m);
    return 0;
}
int bthread_sem_wait(bthread_sem_t* m){
    bthread_block_timer_signal();
    m->value--;
    bthread_unblock_timer_signal();
}
int bthread_sem_post(bthread_sem_t* m){
    bthread_block_timer_signal();
    m->value++;
    bthread_unblock_timer_signal();
}

