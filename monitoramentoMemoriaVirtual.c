#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define PAGESIZE 4096

//integrantes: Arthur Sant'Anna, Bernardo Serravalle, Luca Villela e Gabriel Claudino

void pegaDadosMemoria(int pid, int* virtMemRss, int* virtMemSize) {
    char path[1024];
    FILE* file;

    // Constroi o caminho para o arquivo status do processo baseado no input do usuário
    snprintf(path, sizeof(path), "/proc/%d/status", pid);

    // Abre o arquivo status do processo
    file = fopen(path, "r");
    if (file == NULL) {
        perror("Erro ao abrir arquivo");
        exit(EXIT_FAILURE);
    }

    //Lê o arquivo e obtém as informações necessárias
    char buffer[1024];
    while (fscanf(file, " %1023s", buffer) == 1) {
        if (strcmp(buffer, "VmRSS:") == 0) {
            fscanf(file, " %d", virtMemRss);
        }
        if (strcmp(buffer, "VmSize:") == 0) {
            fscanf(file, " %d", virtMemSize);
        }
    }
    fclose(file);
}

int main(void) {

    // PID inserido pelo usuário
    int pid;
    printf("Insira ID do processo: ");
    scanf("%d", &pid);

    // Informações de memória
    int virtMemRss, virtMemSize;

    //loop que chama a função e printa as informações a cada 1 segundo
    while(1){

        // Chamando a função
        pegaDadosMemoria(pid, &virtMemRss, &virtMemSize);
        // Imprimindo as informações
        printf("\n\n\n\n\n\n\nRSS em kilobytes: %d kB\n", virtMemRss);
        printf("O número de páginas na memória real (RAM) utilizadas pelo processo: %d páginas\n", (virtMemRss/(PAGESIZE/1000)));
        printf("O tamanho total da memória virtual do processo: %d kB\n", virtMemSize);
        //considerando o tamanho de cada página como 4kB
        printf("O tamanho das páginas virtuais usadas pelo sistema: %d B\n", PAGESIZE);

        sleep(1);
    }

    return 0;
}
