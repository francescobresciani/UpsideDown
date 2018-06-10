#ifndef UPSIDEDOWN_BTHREAD_H
#define UPSIDEDOWN_BTHREAD_H

#include <setjmp.h>
#include "tqueue.h"
#include "bthread_private.h"
#include "scheduler.h"
#include "tqueue.h"
#include "bthread_private.h"

/* Vecchia Macro sostituita dalla Preemption (cap 4.6)
#define bthread_printf(...)\
printf(__VA_ARGS__);\
bthread_yield();
 */

int bthread_create(bthread_t *bthread, const bthread_attr_t *attr, void *(*start_routine) (void *), void *arg, unsigned int priority);
int bthread_join(bthread_t bthread, void **retval);
void bthread_yield();
void bthread_exit(void *retval);
int bthread_cancel(bthread_t bthread);
void bthread_testcancel(void);
void bthread_sleep(double ms);
void bthread_printf(const char* format, ...);
void bthread_testcancel(void);
int bthread_cancel(bthread_t bthread);
void setScheduler(scheduler_name selectScheduler);


#endif //SUPSI_SO_18_BTHREAD_H
