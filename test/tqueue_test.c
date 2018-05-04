//
// Created by Roberto Trapletti on 15.03.18.
//


#include <assert.h>
#include "../main/tqueue.h"

main(){

    TQueue queue = NULL;

    printf("inizio test");
    assert(tqueue_size(queue) == 0);

    int* data = (int*) malloc(sizeof(int));
    *data = 5;

    tqueue_enqueue(&queue,data);
    assert(tqueue_size(queue) == 1);
    exit(1);

}