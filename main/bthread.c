#include "bthread.h"
#include "bthread_private.h"
#include <sys/time.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdarg.h>
#include <signal.h>
#include "scheduler.h"

// funzione che richiama lo scheduler per tutte le operazioni basilari
__bthread_scheduler_private *bthread_get_scheduler() {
    static __bthread_scheduler_private * ourScheduler = NULL;
    if(ourScheduler == NULL){
        ourScheduler = malloc(sizeof(__bthread_scheduler_private));
        ((__bthread_scheduler_private*) ourScheduler)->queue = NULL;
        ((__bthread_scheduler_private*) ourScheduler)->scheduling_routine = roundRobinSchedulerRoutine;
    }
    return ourScheduler;
}

// setta la routine dello scheduler: roundrobin(default), random, priority
void setScheduler(scheduler_name selectScheduler){
    volatile __bthread_scheduler_private* scheduler = bthread_get_scheduler();
    switch (selectScheduler){
        case __SCHEDULER_RANDOM:
            scheduler->scheduling_routine = randomSchedulerRoutine;
            break;
        case __SCHEDULER_PRIORITY:
            scheduler->scheduling_routine = prioritySchedulerRoutine;
            break;
        case __SCHEDULER_ROUNDROBIN:
            scheduler->scheduling_routine = roundRobinSchedulerRoutine;
        default:
            scheduler->scheduling_routine = roundRobinSchedulerRoutine;
    }
}

// istanzia il thread, modificato rispetto all'originale per aggiunta priorità
int bthread_create(bthread_t *bthread, const bthread_attr_t *attr, void *(*start_routine) (void *), void *arg, unsigned int priority){
    __bthread_private *  thread = (__bthread_private* )malloc(sizeof(__bthread_private));
    thread->cancel_req = 0; //Cancellation flag set by zero as default
    thread->body = start_routine;
    thread->arg = arg;
    thread->state = __BTHREAD_UNINITIALIZED;
    thread->priority = priority;
    if(attr != NULL){
        thread->attr = *attr;
    }
    volatile __bthread_scheduler_private* scheduler = bthread_get_scheduler();
    thread->tid = tqueue_enqueue(&scheduler->queue, thread);
    *bthread = thread->tid;
    scheduler->current_item = scheduler->queue;
}

// accoda il thread nella queue dello scheduler
int bthread_join(bthread_t bthread, void **retval) {
    bthread_block_timer_signal();
    bthread_setup_timer();
    volatile __bthread_scheduler_private* scheduler = bthread_get_scheduler();
    if (save_context(scheduler->context) == 0) {
        bthread_initialize_next();
        restore_context(scheduler->context);
    } else {
        __bthread_private* tp;
        do {
            if (bthread_reap_if_zombie(bthread, retval)) return 0;

            scheduler->scheduling_routine();



            tp = (__bthread_private*) tqueue_get_data(scheduler->current_item);
            volatile __bthread_private * thread = tqueue_get_data(scheduler->current_item);
            //thread sleep implementation
            if (thread->state == __BTHREAD_SLEEPING) {
                if (thread->wake_up_time <= get_current_time_millis()) {
                    thread->state = __BTHREAD_READY;
                }
            }
        } while (tp->state != __BTHREAD_READY);
        restore_context(tp->context);
    }
}

// Yield del thread corrente, praticamente il thread salva il suo stato e passa il context al prossimo thread in coda.
void bthread_yield() {
    bthread_block_timer_signal();
    volatile __bthread_scheduler_private *scheduler = bthread_get_scheduler();
    volatile __bthread_private * thread = tqueue_get_data(scheduler->current_item);

    if (!save_context(thread->context)) {
        bthread_initialize_next();
        restore_context(scheduler->context);
    }
    bthread_unblock_timer_signal();
}

// elimina il thread, poi passa a yield per passare al prossimo thread in coda
void bthread_exit(void *retval){
    volatile __bthread_scheduler_private* scheduler = bthread_get_scheduler();
    __bthread_private * thread = tqueue_get_data(scheduler->current_item);
    thread->state = __BTHREAD_ZOMBIE;
    thread->retval = retval;
    bthread_yield();
}

// crea o aggiunge un cushion e poi si pone alla fine della
static void bthread_create_cushion(__bthread_private* t_data){
    char cushion[CUSHION_SIZE];
    cushion[CUSHION_SIZE-1] = cushion[0];
    t_data->state = __BTHREAD_READY;
    //bthread_unblock_timer_signal();  commentato perchè nessuno sa come mai era qui
    bthread_exit(t_data->body(t_data->arg));

}

// chiama l'inizializzazione del prossimo processo nella coda, usato dallo yield.
static void bthread_initialize_next(){
    volatile __bthread_scheduler_private* scheduler = bthread_get_scheduler();
    volatile TQueue next = tqueue_at_offset(scheduler->current_item, 1);
    volatile __bthread_private * nextThread = tqueue_get_data(next);

    if(nextThread->state == __BTHREAD_UNINITIALIZED){
        scheduler->current_item = next;
        bthread_create_cushion(nextThread);
    }
}

// se thread è in stato zombie lo setta a exited
static int bthread_reap_if_zombie(bthread_t bthread, void **retval){
    volatile __bthread_scheduler_private* scheduler = bthread_get_scheduler();
    __bthread_private * thread = tqueue_get_data(scheduler->current_item);
    if(thread->state == __BTHREAD_ZOMBIE){
        thread->state = __BTHREAD_EXITED;
        if(retval != NULL){
            *retval = thread->retval;
        }
        return 1;
    }else{
        return 0;
    }

}

// Controlla se il thread attuale può terminare. Check se cancel_req a 1, se si esce
void bthread_testcancel(void){
    volatile __bthread_scheduler_private* scheduler = bthread_get_scheduler();
    __bthread_private * thread = tqueue_get_data(scheduler->current_item);
    if(thread->cancel_req == 1){
        bthread_exit(-1);
    }
}

// speculando che l'offset sia dato dall'id;
// Il thread chiede ad un altro thread di uscire.
int bthread_cancel(bthread_t bthread) {
    volatile __bthread_scheduler_private *scheduler = bthread_get_scheduler();
    volatile TQueue th = tqueue_at_offset(scheduler->queue, bthread);
    volatile __bthread_private *threadToTerminate = tqueue_get_data(th);
    threadToTerminate->cancel_req = 1;
}

void bthread_cleanup(){

}

// Mette il thread in pausa.
void bthread_sleep (double ms) {
    volatile __bthread_scheduler_private* scheduler = bthread_get_scheduler();
    __bthread_private * thread = tqueue_get_data(scheduler->current_item);
    thread->state = __BTHREAD_SLEEPING;
    thread->wake_up_time = ms+get_current_time_millis();
    bthread_yield();
}

// prende il timestamp
double get_current_time_millis() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec) * 1000 + (tv.tv_usec) / 1000;
}

// inizializza il timer per lo scheduler
static void bthread_setup_timer() {
    static bool initialized = false;
    if (!initialized) {
        signal(SIGVTALRM, (void (*)()) bthread_yield);
        struct itimerval time;
        time.it_interval.tv_sec = 0;
        time.it_interval.tv_usec = QUANTUM_USEC;
        time.it_value.tv_sec = 0;
        time.it_value.tv_usec = QUANTUM_USEC;
        initialized = true;
        setitimer(ITIMER_VIRTUAL, &time, NULL);   ///se non funziona usare ITIMER_REAL
    }
}

// Lock atomico bloccando il segnale.
void bthread_block_timer_signal(){
    sigset_t x;
    sigemptyset(&x);
    sigaddset(&x, SIGVTALRM);
    sigprocmask(SIG_BLOCK, &x, NULL);
}

// Unlock del segnale
void bthread_unblock_timer_signal(){
    sigset_t x;
    sigemptyset(&x);
    sigaddset(&x, SIGVTALRM);
    sigprocmask(SIG_UNBLOCK, &x, NULL);
}

// Funzione che sostituisce la macro iniziale per la chimamta dello yield.
void bthread_printf(const char* format, ...){
    bthread_block_timer_signal();
    va_list args;
    va_start (args, format);
    vprintf (format, args);
    va_end (args);
    bthread_unblock_timer_signal();
}
