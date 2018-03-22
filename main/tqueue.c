//
// Created by Roberto Trapletti on 15.03.18.
//

#include <stddef.h>
#include <stdlib.h>
#include "tqueue.h";

/* Adds a new element at the end of the list, returns its position */
unsigned long int tqueue_enqueue(TQueue* q, void* data){

    if(q==NULL){
        (*q)->data = data;
        (*q)->next = q;
        return 0;
    }else{
        int pos = 0;
        TQueueNode* newNode = (TQueueNode*) malloc(sizeof(TQueueNode));
        newNode->next = q;

        while((*q)->next != q){
            q = (*q)->next;
            pos++;
        }

        (*q)->next = newNode;
        return pos++;
    }
}

void* tqueue_pop(TQueue* q){
    if(q = NULL){
        return NULL;
    }else{
        void* data = malloc(sizeof(void*));
        data = (*q)->data;
        if((*q)->next != q){
            q = (*q)->next;
            return data;
        }else{
            q = NULL;
            return data;
        }
    }
}

/* Returns the number of elements in the list */
unsigned long int tqueue_size(TQueue q){
    int pos =0;
    if(q = NULL){
        return 0;
    }else{
        while(q->next != q){
            q = q->next;
            pos++;
        }
        return pos;
    }
}

TQueue tqueue_at_offset(TQueue q, unsigned long int offset){
    /* Returns a 'view' on the list starting at (a positive) offset distance,
* NULL if the queue is empty */
    if(q = NULL){
        return NULL;
    }else{
        for(int i = 0; i<offset; i++){
            q = q->next;
        }
        return q;
    }
}

/* Returns the data on the first node of the given list */
void* tqueue_get_data(TQueue q){
    return q->data;
}