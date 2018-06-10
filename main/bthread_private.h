#ifndef UPSIDEDOWN_BTHREAD_PRIVATE_H
#define UPSIDEDOWN_BTHREAD_PRIVATE_H
#define save_context(CONTEXT) sigsetjmp(CONTEXT,1)
#define restore_context(CONTEXT) siglongjmp(CONTEXT,1)

#include <setjmp.h>
#define CUSHION_SIZE 10000
#define QUANTUM_USEC 20000

typedef enum { __BTHREAD_EXITED = 0, __BTHREAD_ZOMBIE, __BTHREAD_UNINITIALIZED,
    __BTHREAD_READY, __BTHREAD_BLOCKED, __BTHREAD_SLEEPING } bthread_state;

typedef unsigned long int bthread_t;

typedef struct {} bthread_attr_t;
typedef void *(*bthread_routine) (void *);
typedef void (*bthread_scheduling_routine)();

typedef struct {
    TQueue queue;
    TQueue current_item;
    jmp_buf context;
    bthread_scheduling_routine scheduling_routine;
} __bthread_scheduler_private;

typedef struct {
    bthread_t tid;
    bthread_routine body;
    void* arg;
    bthread_state state;
    bthread_attr_t attr;
    jmp_buf context;
    void* retval;
    int cancel_req;
    double wake_up_time;
    unsigned int priority;
} __bthread_private;

__bthread_scheduler_private* bthread_get_scheduler();
void bthread_cleanup();
static void bthread_create_cushion(__bthread_private* t_data);
static void bthread_initialize_next();
static int bthread_reap_if_zombie(bthread_t bthread, void **retval);

double get_current_time_millis();
void bthread_block_timer_signal();
void bthread_unblock_timer_signal();

static void bthread_setup_timer();

#endif //SUPSI_SO_18_BTHREAD_PRIVATE_H
