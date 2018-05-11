//
// Created by Andrea De Carlo on 04.05.18.
//

#include "bthread.h"

int bthread_create(bthread_t *bthread, const bthread_attr_t *attr, void *(*start_routine) (void* ), void *arg){

    //Crea struttura queue e la inserisce alla fine della coda.
    //il thread id corrisponde alla posizione della coda (bthread_t *bthread è il buffer pointer)

    __bthread_private* newBthread = ( __bthread_private*) malloc(sizeof( __bthread_private));

    __bthread_scheduler_private* scheduler = bthread_get_scheduler();
    newBthread->body = start_routine;
    newBthread->arg = arg;
    newBthread->state = __BTHREAD_UNINITIALIZED;
    if(attr != NULL){
        newBthread->attr =  attr;
    }

    newBthread->tid = tqueue_enqueue(scheduler->queue, newBthread);
    *bthread = newBthread->tid;

    return newBthread->tid;

}

int bthread_join(bthread_t bthread, void **retval){

}

__bthread_scheduler_private* bthread_get_scheduler(){

    static __bthread_scheduler_private * ourScheduler = NULL;
    if(ourScheduler == NULL){
        ourScheduler = malloc(sizeof(__bthread_scheduler_private));
    }
    return ourScheduler;
};

void bthread_yield(){

}

void bthread_exit(void *retval){

}

void bthread_cleanup(){

} // Private

