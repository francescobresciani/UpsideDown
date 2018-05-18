#include <assert.h>
#include "../main/bthread.h"

void bthread_create_test(){

    printf("inizio  di bthread_create_test -> ");
    bthread_t bthread;
    unsigned long tid = bthread_create(&bthread, NULL, printf("bthread creation"), NULL);
    bthread_get_scheduler()->queue;
    printf("fine di bthread_create_test\n");
}


int main(){
    bthread_create_test();
}