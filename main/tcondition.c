//
// Created by user on 10.06.18.
//
#include "tcondition.h"
#include "bthread.h"

int bthread_cond_init(bthread_cond_t* c, const bthread_condattr_t *attr){
    //attr è ignorato

    if(c==NULL)
    c = (bthread_cond_t*) malloc(sizeof(bthread_cond_t));

    return 0;

    // c->waiting_list = null; è necessario ?

}

int bthread_cond_destroy(bthread_cond_t* c){

    if(tqueue_size(c->waiting_list) > 0)
        free(c);

    return 0;

}

int bthread_cond_wait(bthread_cond_t* c, bthread_mutex_t* mutex){
    bthread_block_timer_signal();

  /*  __bthread_scheduler_private* scheduler = bthread_get_scheduler();

    __bthread_private* current_item = tqueue_get_data(scheduler->current_item);

    if(mutex != NULL && mutex->owner == current_item){
        __bthread_private* unlock = tqueue_pop(&mutex->waiting_list);

        if (unlock != NULL){
            mutex->owner = unlock;
            unlock->state = __BTHREAD_READY;
        }
        else
            mutex->owner = NULL;
    }

    current_item->state = __BTHREAD_BLOCKED;
    tqueue_enqueue(&c->waiting_list, current_item);
    while(current_item->state != __BTHREAD_READY)
        bthread_yield();

    bthread_mutex_lock(mutex);
    bthread_unblock_timer_signal();*/

  __bthread_scheduler_private* scheduler = bthread_get_scheduler();
  __bthread_private* current_item = tqueue_get_data(scheduler->current_item);




}

int bthread_cond_signal(bthread_cond_t* c){
    bthread_block_timer_signal();

    __bthread_private* thread_top;

    if(tqueue_size(c->waiting_list) > 0){
        thread_top = tqueue_pop(&c->waiting_list);
        thread_top->state = __BTHREAD_READY;
    }

    bthread_unblock_timer_signal();

}

int bthread_cond_broadcast(bthread_cond_t* c){
    bthread_block_timer_signal();
    __bthread_private* thread_top;

    for(int i = 0; i < tqueue_size(c->waiting_list); i++){
        thread_top = tqueue_pop(&c->waiting_list);
        thread_top->state = __BTHREAD_READY;
    }

    bthread_unblock_timer_signal();

}