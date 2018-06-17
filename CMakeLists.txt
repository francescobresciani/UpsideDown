cmake_minimum_required(VERSION 3.9)
project(upsideDown)

set(CMAKE_CXX_STANDARD 11)


add_executable(bthread_test.c test/bthread_test.c main/bthread.c main/bthread.h main/bthread_private.h main/scheduler.h main/scheduler.c main/tbarrier.h main/tbarrier.c main/tcondition.h main/tcondition.c main/tmutex.h main/tmutex.c main/tqueue.h main/tqueue.c main/tsemaphore.h main/tsemaphore.c)