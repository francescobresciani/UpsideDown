//
// Created by Andrea De Carlo on 04.05.18.
//

#include "bthread.h"

int bthread_create(bthread_t *bthread, const bthread_attr_t *attr, void *(*start_routine) (void* ), void *arg){

    //Crea struttura queue e la inserisce alla fine della coda.
    //il thread id corrisponde alla posizione della coda (bthread_t *bthread è il buffer pointer)





}

int bthread_join(bthread_t bthread, void **retval){

}

void bthread_yield(){

}

void bthread_exit(void *retval){

}

void bthread_cleanup(){

} // Private