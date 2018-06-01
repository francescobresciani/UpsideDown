//
// Created by attilio on 01/06/18.
//
#include <stdlib.h>
#include "bthread.h"
#include "bthread_private.h"


void randomSchedulerRoutine(){
    volatile __bthread_scheduler_private* scheduler = bthread_get_scheduler();
    volatile __bthread_private * thread;
    TQueue queue;

    do{
        int randID=rand()%tqueue_size(scheduler->queue);
        queue=tqueue_at_offset(scheduler->queue,randID);
        thread = tqueue_get_data(queue);
    }while(!thread->state == __BTHREAD_READY);

    scheduler->current_item = queue;

}

void prioritySchedulerRoutine(){

}