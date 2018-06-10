//
// Created by attilio on 01/06/18.
//

#ifndef UPSIDEDOWN_SCHEDULER_H
#define UPSIDEDOWN_SCHEDULER_H

typedef enum { __SCHEDULER_RANDOM, __SCHEDULER_PRIORITY, __SCHEDULER_ROUNDROBIN } scheduler_name;

void randomSchedulerRoutine();
void prioritySchedulerRoutine();
void roundRobinSchedulerRoutine();

#endif //UPSIDEDOWN_SCHEDULER_H
