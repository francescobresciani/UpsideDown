#include <assert.h>
#include "../main/bthread.h"

#include "../main/bthread.h"
void* testRoutine1(void* arg);
void* testRoutine2(void* arg);

void* testRoutine1(void* arg)
{

    printf("bid1 = %d",arg);
    volatile int i;

    for(i=0;i<200;i++) {
        printf("BThread0, i=%d\n", i);

        if( i == 7){
            printf("CANCELLAZIONE DEL THREAD 1\n");

            bthread_cancel(1);
        }
        bthread_sleep(1);
        bthread_printf("");

    }
}

void* testRoutine2(void* arg) {
    volatile int i;

    for (i = 0; i < 200; i++) {

            printf("BThread1, i=%d\n", i);

            if (i == 20) {
                printf("TEST CANCELLAZIONE DEL THREAD 1\n");
                bthread_testcancel();
            }
            bthread_sleep(1);
            bthread_printf("");
        }

}

void* testRoutine3(void* arg) {
    volatile int i;

    for (i = 0; i < 10; i++) {



        printf("BThread3, i=%d\n", i);
        bthread_sleep(1);
        bthread_printf("");
    }

}

void* testRoutine4(void* arg) {
    volatile int i;

    for (i = 0; i < 10; i++) {
        printf("BThread4, i=%d\n", i);
        bthread_sleep(1);
        bthread_printf("");
    }

}



void main(){

    unsigned long int bid1;
    unsigned long int bid2;
printf("bid1 = %d",&bid2);
    bthread_create(&bid1,NULL,testRoutine1,&bid2);
    bthread_create(&bid2,NULL,testRoutine2,NULL);

    bthread_join(bid1,NULL);
    bthread_join(bid2,NULL);




    //testCancellation();

}
