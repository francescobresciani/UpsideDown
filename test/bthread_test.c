#include <assert.h>
#include "../main/bthread.h"

void bthread_create_test(){

    printf("inizio  di bthread_create_test -> ");
    bthread_t bthread;
    unsigned long tid = bthread_create(&bthread, NULL, printf("bthread creation"), NULL);
    bthread_get_scheduler()->queue;
    printf("fine di bthread_create_test\n");
}


void bthread_exit_test(){
/*
    printf("inizio di bthread_exit_test -> ");
    bthread_t bthread;
    unsigned long tid = bthread_create(&bthread, NULL, printf("bthread creation"), NULL);
    bthread_get_scheduler()->queue;
    printf("exit di bthread");
    bthread_exit();
*/
}

int main(){
    bthread_create_test();
    bthread_exit_test();
}