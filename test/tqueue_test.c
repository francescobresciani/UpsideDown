//
// Created by Roberto Trapletti on 15.03.18.
//


#include <assert.h>
#include "../main/tqueue.h"


void tqueue_pop_test(){
    printf("inizio di tqueue_pop_test -> ");
    TQueue q = NULL;
    int data = 12;
    tqueue_enqueue(&q,&data);
    int retreivedData = *(int*)tqueue_pop(&q);
    assert(retreivedData==12);
    printf("inizio di tqueue_pop_test\n");

}

/* Returns the number of elements in the list */
void tqueue_size_and_enqueue_test(){
    printf("inizio  di tqueue_size_and_enqueue_test -> ");
    TQueue q = NULL;
    assert(tqueue_size(q) == 0);

    int data = 5;

    tqueue_enqueue(&q,&data);
    assert(tqueue_size(q) == 1);
    printf("fine di tqueue_size_and_enqueue_test\n");

};

void tqueue_at_offset_and_t_queue_at_offset_test(){

    printf("inizio  di tqueue_at_offset_and_t_queue_at_offset_test -> ");
    TQueue q = NULL;
    unsigned long int offset = 2;

    for (int i=0;i<5;i++){
        tqueue_enqueue(&q,(void*) i);
    }


    for (int i=0;i<5;i++){
        TQueue currentNode = tqueue_at_offset(&q,i);
        assert((int)tqueue_get_data(&currentNode)==i);

    }
    printf("fine di tqueue_at_offset_and_t_queue_at_offset_test\n");
}

void yield_test(){

}


/*int main(){
    tqueue_size_and_enqueue_test();
    tqueue_pop_test();
    tqueue_at_offset_and_t_queue_at_offset_test();
}*/
