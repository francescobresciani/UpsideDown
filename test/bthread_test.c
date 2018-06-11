#include <assert.h>
#include <printf.h>
#include "../main/bthread.h"
#include "../main/tbarrier.h"

void* testRoutine1(void* arg);
void* testRoutine2(void* arg);
bthread_barrier_t barrier;







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
        bthread_sleep(2);
        bthread_printf("");
    }

}

void* testRoutine4(void* arg) {
    volatile int i;

    for (i = 0; i < 10; i++) {
        printf("BThread4, i=%d\n", i);
        bthread_sleep(2);
        bthread_printf("");
    }

}

void* testRoutine5(void* arg) {
    volatile int i;

    for (i = 0; i < 10; i++) {
        printf("BThread5, i=%d\n", i);
        bthread_sleep(2);
        bthread_printf("");
    }

}

void* testRoutine6(void* arg) {
    volatile int i;

    for (i = 0; i < 10; i++) {
        printf("BThread6, i=%d\n", i);
        bthread_sleep(2);
        bthread_printf("");
    }

}

void* thread_barrier (void* args) {
    for(int i = 0; i< 2; i++){
        printf("step1\n");
        bthread_barrier_wait(&barrier);
        printf("step2\n");
        bthread_sleep(2000);
    }

}




void mainb(){
    //seleziono il tipo di scheduler da usare, OPZIONALE (se non impostato = ROUND ROBIN)
    setScheduler(__SCHEDULER_ROUNDROBIN);

    //test con barriera
    bthread_barrier_init(&barrier,NULL, 2);

    unsigned long int bid1;
    unsigned long int bid2;
    unsigned long int bid3;
    unsigned long int bid4;


    /*
    bthread_create(&bid1,NULL,testRoutine3,NULL, 7);
    bthread_create(&bid2,NULL,testRoutine4,NULL, 4);
    bthread_create(&bid3,NULL,testRoutine5,NULL, 3);
    bthread_create(&bid4,NULL,testRoutine6,NULL, 1);

    printf("THREAD 1 con PIDa: %s", bid1);
    printf("THREAD 2 con PIDa: %s", bid2);
    printf("THREAD 3 con PIDa: %s", bid3);
    printf("THREAD 4 con PIDa: %s", bid4);
    */

    bthread_create(&bid1,NULL,thread_barrier,NULL, 2);
    bthread_create(&bid2,NULL,thread_barrier,NULL, 4);
    bthread_create(&bid3,NULL,thread_barrier,NULL, 3);
    bthread_create(&bid4,NULL,thread_barrier,NULL, 1);



    bthread_join(bid1,NULL);
    bthread_join(bid2,NULL);
    bthread_join(bid3,NULL);
    bthread_join(bid4,NULL);


    bthread_barrier_destroy(&barrier);

}
