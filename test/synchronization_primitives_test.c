//
// Created by Francesco on 10/06/2018.
//


#include "../main/tbarrier.h"
#include "../main/bthread.h"

void tbarrier_test();

void* thread_doSomething (void* args, bthread_barrier_t* barrier) {

    printf("step1");
    int result = bthread_barrier_wait(&barrier);

    if (result != 0) {
        perror("Error!\n");
        exit(-1);
    }


    printf("step2");



}

int main(){
    tbarrier_test();

}

void tbarrier_test() {
//    inizializza

    bthread_barrier_t barrier;
    bthread_barrier_init(&barrier,NULL,2);

    unsigned long int bid1;
    unsigned long int bid2;
    bthread_create(&bid1, NULL, thread_doSomething(NULL,&barrier), NULL, 1);
    bthread_create(&bid2, NULL, thread_doSomething, NULL, 2);

    bthread_join(&bid1, NULL);
    bthread_join(&bid2, NULL);

    printf("tutto ok");

//    bthread_barrier_destroy(&barrier);



}