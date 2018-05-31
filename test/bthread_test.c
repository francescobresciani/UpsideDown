#include <assert.h>
#include "../main/bthread.h"

#include "../main/bthread.h"
void* testRoutine1(void* arg);
void* testRoutine2(void* arg);

void* testRoutine1(void* arg)
{

    volatile int i;

    for(i=0;i<10;i++) {

        printf("BThread1, i=%d\n", i);
        //bthread_yield();
        bthread_sleep(2000);
        bthread_printf("");
    }
}

void* testRoutine2(void* arg)
{
    volatile int i;

    for(i=0;i<10;i++) {

        printf("BThread2, i=%d\n", i);
        //bthread_yield();
        bthread_printf("");
    }
}


void main(){
    unsigned long int bid1;
    unsigned long int bid2;
    bthread_create(&bid1,NULL,testRoutine1,NULL);


    bthread_create(&bid2,NULL,testRoutine2,NULL);
    bthread_join(bid1,NULL);
    bthread_join(bid2,NULL);

}
