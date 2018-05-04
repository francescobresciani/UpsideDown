//
// Created by Roberto Trapletti on 15.03.18.
//

#include <assert.h>
#include "../main/tqueue.h"

/* Adds a new element at the end of the list, returns its position */
void tqueue_enqueue_test(){
//    TQueue* q, void* data
}

void tqueue_pop_test(){
//    TQueue* q
}

/* Returns the number of elements in the list */
void tqueue_size_test(){
    TQueue q;
    assert(tqueue_size(q)==0);
    int data = 1;
    tqueue_enqueue(q,&data);
    assert(tqueue_size(q)==1);

    for (int i = 0; i<5;i++){
        int data = i;
        tqueue_enqueue(q,&data);
    }
    assert(tqueue_size(q)==6); // 1 was added before, 5 was added whit the for-cycle
};

void tqueue_at_offset_test(){
//    TQueue q, unsigned long int offset
}

/* Returns the data on the first node of the given list */
void tqueue_get_data_test(){
//    TQueue q
}