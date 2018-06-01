cmake_minimum_required(VERSION 3.9)
project(upsideDown)

set(CMAKE_CXX_STANDARD 11)

add_executable(threader main/bthread_private.h main/bthread.h main/tqueue.c main/tqueue.h test/tqueue_test.c main/bthread.c test/bthread_test.c main/scheduler.c main/scheduler.h)