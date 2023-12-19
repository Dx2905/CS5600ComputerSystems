#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

pthread_mutex_t m;
pthread_cond_t C;
int count = 0;

void *meetup(void *arg) {
char *thread_name = (char *)arg;
pthread_mutex_lock(&m);
printf("Thread %s acquired lock\n", thread_name);
count++;
printf("count is : %d\n", count);
if (count < 2) {
printf("Thread %s waiting on condition\n", thread_name);
pthread_cond_wait(&C, &m);
printf("Thread %s resumed\n", thread_name);
} else {
printf("Thread %s signaling on condition\n", thread_name);
pthread_cond_signal(&C);
}
count = 0;
printf("count is zero and thread is: %d-- %s\n ", count, thread_name);
pthread_mutex_unlock(&m);
printf("Thread %s released lock\n", thread_name);
return NULL;
}

int main(int argc, char *argv[]) {
pthread_t t1, t2, t3;
char *thread1_name = "A";
char *thread2_name = "B";
char *thread3_name = "C";

pthread_mutex_init(&m, NULL);
pthread_cond_init(&C, NULL);

pthread_create(&t1, NULL, meetup, (void *)thread1_name);
// sleep(1);
pthread_create(&t2, NULL, meetup, (void *)thread2_name);
pthread_create(&t3, NULL, meetup, (void *)thread3_name);

pthread_join(t1, NULL);
pthread_join(t2, NULL);
pthread_join(t3, NULL);

pthread_mutex_destroy(&m);
pthread_cond_destroy(&C);
return 0;
}


// #include <pthread.h>
// #include <stdio.h>
// #include <unistd.h>

// pthread_mutex_t m;
// pthread_cond_t C;
// int count = 0;

// void* meetup(void* arg) {
//   pthread_mutex_lock(&m);
//   printf("Thread %ld locked the mutex\n", (long)pthread_self());
//   count = count + 1;
//   if (count < 2) {
//     printf("Thread %ld waiting on condition variable\n", (long)pthread_self());
//     pthread_cond_wait(&C, &m);
//   } else {
//     printf("Thread %ld signaling condition variable\n", (long)pthread_self());
//     pthread_cond_signal(&C);
//   }
//   count = 0;
//   pthread_mutex_unlock(&m);
//   printf("Thread %ld unlocked the mutex\n", (long)pthread_self());
//   return NULL;
// }

// int main() {
//   pthread_t a, b, c;
//   pthread_mutex_init(&m, NULL);
//   pthread_cond_init(&C, NULL);

//   pthread_create(&a, NULL, meetup, NULL);
//   sleep(1);
//   pthread_create(&b, NULL, meetup, NULL);
//   pthread_create(&c, NULL, meetup, NULL);

//   pthread_join(a, NULL);
//   pthread_join(b, NULL);
//   pthread_join(c, NULL);

//   pthread_mutex_destroy(&m);
//   pthread_cond_destroy(&C);
//   return 0;
// }

// #include <pthread.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>
// int count = 0;
// pthread_mutex_t m;
// pthread_cond_t C;
// void meetup(void) {
// pthread_mutex_lock(&m);
// printf("Acquired lock currrent thread %lu\n", pthread_self());
// count = count + 1;
// if (count < 2) {
// pthread_cond_wait(&C, &m);
// } else {
// pthread_cond_signal(&C);
// }
// count = 0;
// pthread_mutex_unlock(&m);
// }
// int main(int argc, char *argv[]) {
// pthread_t threadA, threadB, threadC;
// pthread_mutex_init(&m, NULL);
// pthread_cond_init(&C, NULL);

// pthread_create(&threadA, NULL, (void *) meetup, NULL);
// pthread_create(&threadB, NULL, (void *) meetup, NULL);
// pthread_create(&threadC, NULL, (void *) meetup, NULL);

// pthread_join(threadA, NULL);
// pthread_join(threadB, NULL);
// pthread_join(threadC, NULL);

// pthread_cond_destroy(&C);
// pthread_mutex_destroy(&m);

// return 0;
// }
