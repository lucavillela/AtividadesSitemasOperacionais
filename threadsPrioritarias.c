#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

#define NUM_THREADS 15
pthread_mutex_t mutex;

void *exampleFunction(void *arg) {

    int thread_id = *((int *)arg);

    struct sched_param param;
    int policy;
    pthread_getschedparam(pthread_self(), &policy, &param);

    switch (thread_id){
        case 0:
            param.sched_priority = 40;
            break;
        case 1:
            param.sched_priority = 12;
            break;
        case 2:
            param.sched_priority = 9;
            break;
        case 3:
            param.sched_priority = 58;
            break;
        case 4:
            param.sched_priority = 91;
            break;
        case 5:
            param.sched_priority = 47;
            break;
        case 6:
            param.sched_priority = 19;
            break;
        case 7:
            param.sched_priority = 29;
            break;
        case 8:
            param.sched_priority = 51;
            break;
        case 9:
            param.sched_priority = 81;
            break;
        case 10:
            param.sched_priority = 32;
            break;
        case 11:
            param.sched_priority = 18;
            break;
        case 12:
            param.sched_priority = 95;
            break;
        case 13:
            param.sched_priority = 71;
            break;
        case 14:
            param.sched_priority = 63;
            break;
        default:
            break;
    }

    pthread_setschedparam(pthread_self(), SCHED_RR, &param);

    pthread_mutex_lock(&mutex);

        int i, count; 
        for(i = 0; i < 10000000; i++){
            count++;
        }
        printf("Thread number %d with priority %d\n", thread_id, param.sched_priority);

    pthread_mutex_unlock(&mutex);

    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];

    pthread_mutex_init(&mutex, NULL);

    for (int i = 0; i < NUM_THREADS; i++) {
        thread_ids[i] = i;
        pthread_create(&threads[i], NULL, exampleFunction, &thread_ids[i]);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&mutex);

    return 0;
}
