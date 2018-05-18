//
// Created by Andrea De Carlo on 04.05.18.
//

#include "bthread.h"

int bthread_reap_if_zombie(bthread_t bthread, void **retval);

void bthread_initialize_next();

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


int bthread_join(bthread_t bthread, void **retval) { //TODO create test

    volatile __bthread_scheduler_private *scheduler = bthread_get_scheduler();
    if (save_context(scheduler->context) == 0) {
        bthread_initialize_next();
        restore_context(scheduler->context);
    } else {
        __bthread_private *tp;
        do {
            if (bthread_reap_if_zombie(bthread, retval)) return 0;
            scheduler->current_item = tqueue_at_offset(scheduler->current_item, 1);
            tp = (__bthread_private *) tqueue_get_data(scheduler->current_item);
        } while (tp->state != __BTHREAD_READY);

        restore_context(tp->context);
    }
}

static void bthread_initialize_next() {

}

static void bthread_create_cushion(__bthread_private* t_data){

}

static int bthread_reap_if_zombie(bthread_t bthread, void **retval) {
    return 0;
}

__bthread_scheduler_private* bthread_get_scheduler(){

    static __bthread_scheduler_private * ourScheduler = NULL;
    if(ourScheduler != NULL){
        ourScheduler = malloc(sizeof(__bthread_scheduler_private));
    }
    return ourScheduler;
};

void bthread_yield(){
//    Saves the thread context and then
//      checks whether the thread that follows in the queue is in the
//    __BTHREAD_UNINITIALIZED state: if so, a cushion frame is created and the corresponding thread routine is called,
//    otherwise bthread_yield restores (long-jumps to) the scheduler context. Saving the thread context is achieved using sigsetjmp,
//    which is similar to setjmp but can also save the signal mask if the provided additional parameter is not zero (to restore both
//    the context and the signal mask the corresponding call is siglongjmp). Saving and restoring the signal mask is required for implementing preemption.

    save_context()



}

void bthread_exit(void *retval){

}

void bthread_cleanup(){

} // Private

