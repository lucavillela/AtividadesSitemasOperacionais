#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

int g = 0; //inicialização da variavel global
sem_t mutex; //criação do semaforo

void *threadInc(void *vargp){
    sem_wait(&mutex); //equivalente ao down (verifica se a regiao critica pode ser acessada)
    int a = g;
    a = a + 1;
    sleep(0.1); 
    g = a; // incrementa a variavel global
    sem_post(&mutex); //equivalente ao up (libera acesso a regiao critica)
}

void *threadDec(void *vargp){
    sem_wait(&mutex);
    int a = g;
    a = a - 1;
    sleep(0.1); //mesma coisa da funcao de cima so que decrementando a variavel global
    g = a;
    sem_post(&mutex);
}
  
int main(){
    int i;
    sem_init(&mutex, 0, 1); //inicializa o semaforo
    pthread_t idInc[100]; //cria um vetor de threads que vão incrementar a variavel global
    pthread_t idDec[100]; //cria um vetor de threads que vão decrementar a variavel global

    for (i = 0; i < 100; i++){
        pthread_create(&(idInc[i]), NULL, threadInc, (void *)&(idInc[i])); //cria de fato as 100 threads
        pthread_create(&(idDec[i]), NULL, threadDec, (void *)&(idDec[i])); //cria de fato as outras 100 threads
    }
    for (i = 0; i < 100; i++){
        pthread_join(idInc[i], NULL); //função que espera a thread terminar (pra finalizar o processo das threads)
        pthread_join(idDec[i], NULL);
    }
    printf("%d\n", g); //printa a variavel global (se os semaforos funcionaram é pra ser 0)
    return 0;
}