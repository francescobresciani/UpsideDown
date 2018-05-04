//
// Created by Roberto Trapletti on 15.03.18.
//


#include <assert.h>
#include "../main/tqueue.h"


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

void tqueue_at_offset_test(){  //TODO finire
    TQueue q = NULL;
    unsigned long int offset = 2;

    for (int i=0;i<3;i++){
        tqueue_enqueue(&q,(void*) i);
    }




}

/* Returns the data on the first node of the given list */
void tqueue_get_data_test(){
//    TQueue q
}

int main(){
    tqueue_size_and_enqueue_test();
    tqueue_pop_test();
}
