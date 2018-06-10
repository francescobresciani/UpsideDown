#include <assert.h>
#include "tbarrier.h"
#include "bthread_private.h"
#include "bthread.h"


//attr is ignored
int bthread_barrier_init(bthread_barrier_t* b, const bthread_barrierattr_t* attr, unsigned count){
    assert(b!=NULL);
    b->waiting_list = malloc(sizeof(TQueue));
    b->count=0;
    b->barrier_size=count;
    return 0;
}

int bthread_barrier_wait(bthread_barrier_t* b){
    TQueue q = bthread_get_scheduler()->current_item;
    __bthread_private* thread = tqueue_get_data(q);
    thread->state=__BTHREAD_BLOCKED;
    tqueue_enqueue(b->waiting_list,thread);
    b->count++;
    if(b->count==b->barrier_size){
        for(int i = 0; i<tqueue_size(b->waiting_list); i++){
            __bthread_private* tempThread = tqueue_pop(b->waiting_list);
//            __bthread_private* tempThread = tqueue_get_data(tqueue_at_offset(b->waiting_list,i));
            tempThread->state==__BTHREAD_READY;

        }
    }

    //if sometring bad happens return -1

    return 0;
}




int bthread_barrier_destroy(bthread_barrier_t* b);
