#include <assert.h>
#include "../main/bthread.h"

#include "../main/bthread.h"
void* testRoutine1(void* arg);
void* testRoutine2(void* arg);

void* testRoutine1(void* arg)
{

    volatile int i;

    for(i=0;i<200;i++) {


        printf("BThread1, i=%d\n", i);
        //bthread_yield();
        bthread_sleep(2000.0);
            printf("BThread1, i=%d\n", i);
            //bthread_yield();
            bthread_printf("");

        if( i == 100){
            printf("CANCELLAZIONE DEL THREAD 1");
            bthread_cancel(1);
        }
        bthread_yield();
        bthread_printf("");
    }
}

void* testRoutine2(void* arg) {
    volatile int i;

    for (i = 0; i < 200; i++) {



            printf("BThread1, i=%d\n", i);
            //bthread_yield();
            bthread_printf("");

            if (i == 160) {
                printf("CANCELLAZIONE DEL THREAD 1");
                bthread_testcancel();
            }
            bthread_yield();
            bthread_printf("");
        }

}

void* testRoutine3(void* arg) {
    volatile int i;

    for (i = 0; i < 10; i++) {



        printf("BThread3, i=%d\n", i);

        bthread_printf("");
    }

}

void* testRoutine4(void* arg) {
    volatile int i;

    for (i = 0; i < 10; i++) {
        printf("BThread4, i=%d\n", i);
        //bthread_yield();
        bthread_printf("");
    }

}




void testCancellation(){

    unsigned long int bid1;
    unsigned long int bid2;

    bthread_create(&bid1,NULL,testRoutine1(&bid1),NULL);
    bthread_create(&bid2,NULL,testRoutine2(&bid2),NULL);

    bthread_join(bid1,NULL);
    bthread_join(bid2,NULL);


}

void main(){

    unsigned long int bid1;
    unsigned long int bid2;

    bthread_create(&bid1,NULL,testRoutine3,NULL);
    bthread_create(&bid2,NULL,testRoutine4,NULL);

    bthread_join(bid1,NULL);
    bthread_join(bid2,NULL);



    //testCancellation();

}
