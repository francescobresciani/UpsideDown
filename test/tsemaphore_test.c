//
// Created by Francesco on 17/06/2018.
//

#include "../main/tsemaphore.h"
#include "../main/bthread.h"

bthread_sem_t semaphore;



void* routine_with_semaphore1(void *args) {
    for(int i = 0; i< 5; i++){
        bthread_sem_wait(&semaphore);
        printf("1: in\n");
        bthread_sleep(2000);
        bthread_sem_post(&semaphore);
        //dfggdf
        printf("1: out again\n");
//        bthread_sleep(2000);
    }
}

void* routine_with_semaphore2(void *args) {
    for(int i = 0; i< 5; i++){
        bthread_sem_wait(&semaphore);
        printf("2: in\n");
        bthread_sleep(2000);
        bthread_sem_post(&semaphore);
        printf("2: out again\n");
//        bthread_sleep(2000);
    }
}

void* routine_with_semaphore3(void *args) {
    for(int i = 0; i< 5; i++){
        bthread_sem_wait(&semaphore);
        printf("3: in\n");
        bthread_sleep(2000);
        bthread_sem_post(&semaphore);
        printf("3: out again\n");
//        bthread_sleep(2000);
    }
}


int main(){
    bthread_sem_init(&semaphore,0,1);

    unsigned long int bid1;
    unsigned long int bid2;
    unsigned long int bid3;

    bthread_create(&bid1,NULL,routine_with_semaphore1,NULL, 2);
    bthread_create(&bid2,NULL,routine_with_semaphore2,NULL, 4);
    bthread_create(&bid3,NULL,routine_with_semaphore3,NULL, 4);

    bthread_join(bid1,NULL);
    bthread_join(bid2,NULL);
    bthread_join(bid3,NULL);

    bthread_sem_destroy(&semaphore);

}