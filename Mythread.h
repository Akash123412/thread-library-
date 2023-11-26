// MyThread.h

#ifndef THREADS_H
#define THREADS_H

#include <windows.h>

typedef struct {
    void (*function)(void*);
    void* arg;
} ThreadData;


int my_pthread_create(void (*function)(void*), void* arg, HANDLE* threadHandle);


void my_pthread_join(HANDLE threadHandle);


int mythread_terminate(unsigned long tid);


int mythread_suspend(unsigned long tid);


int mythread_resume(unsigned long tid);


unsigned long mythread_self(void);

#endif  // THREADS_H