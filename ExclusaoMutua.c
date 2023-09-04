#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
  
int g = 0;
    
void *threadInc(void *vargp)
{
    int a = g;
    a = a + 1;
    sleep(0.1);
    g = a;
    //printf("Thread Inc ID: %d, Static: %d, Global: %d\n", *myid, a, g);
    printf("INC - local: %d, global: %d\n", a, g);

}

void *threadDec(void *vargp)
{
    int a = g;
    a = a - 1;
    sleep(0.1);
    //int *myid = (int *)vargp;
    g = a;
    //printf("Thread Inc ID: %d, Static: %d, Global: %d\n", *myid, a, g);
    printf("DEC - local: %d, global: %d\n", a, g);
}
  
int main()
{
    int i;
    pthread_t tid;

    for (i = 0; i < 100; i++){
        pthread_create(&tid, NULL, threadInc, (void *)&tid);
        pthread_create(&tid, NULL, threadDec, (void *)&tid);
    }
    printf("\n\n\n\n\n\n%d\n", g);
    pthread_exit(NULL);
    
    return 0;
}