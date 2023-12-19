#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int sharedArray[6] = {0, 0, 0, 0, 0, 0};

void *writer(void *data)
{
    char *name = (char*)data;
    for (int i = 0; i < 6; i++)
    {
        sharedArray[i] = i;
        printf("Writing %d to sharedArray[%d] from thread %s\n", sharedArray[i], i, name);
        usleep(50000);
    }
    printf("Thread %s done writing!\n", name);
    return NULL;
}

void *reader(void *data)
{
    char *name = (char*)data;
    for (int i = 0; i < 6; i++)
    {
        printf("Reading %d from sharedArray[%d] from thread %s\n", sharedArray[i], i, name);
        usleep(50000);
    }
    printf("Thread %s done reading!\n", name);
    return NULL;
}

// void *worker(void *data)
// {
//     char *name = (char*)data;
//     long id = pthread_self();

//     for (int i = 0; i < 120; i++)
//     {
//     usleep(50000);
//         printf("Hi from thread name = %s\n", name);
//     }

//     printf("Thread %s done!\n", name);
//     return NULL;
// }


int main(void)
{
    
    pthread_t th1, th2;
    pthread_create(&th1, NULL, writer, "X");
    pthread_create(&th2, NULL, reader, "Y");
    sleep(1);
    printf("====> Cancelling Thread Y with ID: %lu\n",(unsigned long)th2);
    pthread_cancel(th2);
    usleep(100000);
    printf("====> Cancelling Thread X with ID: %lu\n",(unsigned long)th1);
    pthread_cancel(th1);
    printf("exiting from main program\n");
    return 0;
}

// ANSWER to The 4th part
//Observations from thread behavior above we can say that there is inconsistency// Yes I expect it to be inconsistent. The phenomenon we are seeing in above is //the race condition. Race condition is when two or more threads try to access  // the same data at the same time. In this scenario we will not know in which order the two threads will access the shared data.
// Therefore there is inconsistency in the behavior of the treads. 
//To resolve this problem we need a mechanism where only thread is able to access the data 
//and modify it at a time and the other thread is not allowed to access it until the first thread is 
//done. This mechanism is also know as lock mechanism where the thread get the lock to 
//access the global array and the other thread is blocked until first thread is done with the lock. 
//This lock mechanism is performed using mutex.
//Another solution can be atomic operations which will allow an operations on the shared data 
//to be performed in a single step.







    
