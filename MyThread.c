#include "MyThread.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


/*
compile like 

gcc -c main.c -o main.o
gcc -c MyThread.c -o MyThread.o
gcc main.o MyThread.o -o my_program

*/

DWORD WINAPI threadFunction(LPVOID lpParam);



void my_pthread_join(HANDLE threadHandle) {
    WaitForSingleObject(threadHandle, INFINITE);
    CloseHandle(threadHandle);
}

DWORD WINAPI threadFunction(LPVOID lpParam) {
    ThreadData* data = (ThreadData*)lpParam;
    data->function(data->arg);
    return 0;
}


int my_pthread_create(void (*function)(void*), void* arg, HANDLE* threadHandle) {
    ThreadData* data = malloc(sizeof(ThreadData));

    if (data == NULL) {
        fprintf(stderr, "Error allocating memory for thread data\n");
        return -1;
    }

    data->function = function;
    data->arg = arg;

    *threadHandle = CreateThread(NULL, 0, threadFunction, data, 0, NULL);

    if (*threadHandle == NULL) {
        fprintf(stderr, "Error creating thread\n");
        free(data);
        return -1;
    }

    return 0;
}


int mythread_resume(unsigned long tid) {
    HANDLE threadHandle = OpenThread(THREAD_SUSPEND_RESUME, FALSE, tid);

    if (threadHandle == NULL) {
        fprintf(stderr, "Error opening thread handle for resumption\n");
        return -1;
    }

    if (ResumeThread(threadHandle) == (DWORD)-1) {
        fprintf(stderr, "Error resuming thread\n");
        CloseHandle(threadHandle);
        return -1;
    }

    CloseHandle(threadHandle);

    return 0;
}

unsigned long mythread_self(void) {
    return (unsigned long)GetCurrentThreadId();
}


int mythread_suspend(unsigned long tid) {
    HANDLE threadHandle = OpenThread(THREAD_SUSPEND_RESUME, FALSE, tid);

    if (threadHandle == NULL) {
        fprintf(stderr, "Error opening thread handle for suspension\n");
        return -1;
    }
    DWORD exitCode;
    if (GetExitCodeThread(threadHandle, &exitCode) && exitCode == STILL_ACTIVE) {
        // Suspend the thread
        if (SuspendThread(threadHandle) == (DWORD)-1) {
            fprintf(stderr, "Error suspending thread\n");
            CloseHandle(threadHandle);
            return -1;
        }

        CloseHandle(threadHandle);
        WaitForSingleObject(threadHandle, INFINITE);

        return 0;
    } else {
        fprintf(stderr, "Thread is not running or already terminated\n");
        CloseHandle(threadHandle);
        return -1;
    }
}

int mythread_terminate(unsigned long tid) {
    //Termination of threads is generally discouraged due to potential resource leaks and unpredictable behavior.
    
    HANDLE threadHandle = OpenThread(THREAD_TERMINATE, FALSE, tid);

    if (threadHandle == NULL) {
        fprintf(stderr, "Error opening thread handle for termination\n");
        return -1;
    }

    if (!TerminateThread(threadHandle, 0)) {
        fprintf(stderr, "Error terminating thread\n");
        CloseHandle(threadHandle);
        return -1;
    }

    CloseHandle(threadHandle);

    return 0;
}



