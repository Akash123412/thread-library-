// main.c

#include <stdio.h>
#include <windows.h>
#include "MyThread.h"




void g()
{ 
    int i = 0;
    while(i<10)
    {   
        printf("the id for the thread is : %d \n",mythread_self());
        printf("In g(%d) :\n",i++);
        fflush(stdout);
        sleep(1);
    }
    return;
}



void f ()
{
    printf("In f\n");
    int i = 0;
    char a[100];
    strcat(a,"a");
    strcat(a,"a");
    // sleep(1);
    strcat(a,"a");
    strcat(a,"a");
    printf("%s\n",a);
    while(i < 5)
    {
        printf("In f(%d) :\n",i++);
        fflush(stdout);
        sleep(2);
    }
    return;
}





int main() {
    HANDLE threadHandle1, threadHandle2;
    int value = 42;

    if (my_pthread_create(f, &value, &threadHandle1) == 0) {
        printf("Thread created successfully with ID: %lu\n", (unsigned long)threadHandle1);
    } else {
        fprintf(stderr, "Failed to create thread\n");
    }

    if (my_pthread_create(g, &value, &threadHandle2) == 0) {
        printf("Thread created successfully with ID: %lu\n", (unsigned long)threadHandle2);
    } else {
        fprintf(stderr, "Failed to create thread\n");
    }
    mythread_suspend((unsigned long)threadHandle1);
    // my_pthread_join(threadHandle1);

    my_pthread_join(threadHandle2);

    return 0;
}