#include <stdlib.h>
#include "bthread.h"
#include "bthread_private.h"

// Routine round robin
void roundRobinSchedulerRoutine(){
    volatile __bthread_scheduler_private* scheduler = bthread_get_scheduler();
    scheduler->current_item = tqueue_at_offset(scheduler->current_item, 1);
}

// routine random, sceglie a caso dalla coda
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

// Usa il valore id di priorità del thread per scegliere il prossimo da eseguire.
void prioritySchedulerRoutine(){
    volatile __bthread_scheduler_private* scheduler = bthread_get_scheduler();
    volatile __bthread_private * thread;
    TQueue queue;
    unsigned long size = tqueue_size(scheduler->queue);
    volatile unsigned int priorityLevel = 999;
    int i;

    for(i = 0; i < size; i++){
        TQueue tempQueue = tqueue_at_offset(scheduler->queue, i);
        thread = tqueue_get_data(tempQueue);
        if(thread->state != __BTHREAD_EXITED){
            if(thread->priority < priorityLevel){
                priorityLevel = thread->priority;
                queue = tempQueue;
            }
        }

    }

    scheduler->current_item = queue;
}