#include <assert.h>
#include <printf.h>
#include "../main/bthread.h"
#include "../main/tbarrier.h"


bthread_barrier_t barrier;


void* routine_with_barrier(void *args) {
    for(int i = 0; i< 2; i++){
        printf("step1\n");
        bthread_barrier_wait(&barrier);
        printf("step2\n");
        bthread_sleep(2000);
    }
}


void main(){
    //seleziono il tipo di scheduler da usare, OPZIONALE (se non impostato = ROUND ROBIN)
    setScheduler(__SCHEDULER_ROUNDROBIN);

    //test con barriera
    bthread_barrier_init(&barrier,NULL, 2);

    unsigned long int bid1;
    unsigned long int bid2;
    unsigned long int bid3;
    unsigned long int bid4;

    bthread_create(&bid1,NULL,routine_with_barrier,NULL, 2);
    bthread_create(&bid2,NULL,routine_with_barrier,NULL, 4);
    bthread_create(&bid3,NULL,routine_with_barrier,NULL, 3);
    bthread_create(&bid4,NULL,routine_with_barrier,NULL, 1);


    bthread_join(bid1,NULL);
    bthread_join(bid2,NULL);
    bthread_join(bid3,NULL);
    bthread_join(bid4,NULL);


    bthread_barrier_destroy(&barrier);

}
