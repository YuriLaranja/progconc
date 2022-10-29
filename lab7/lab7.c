
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>

#define N 5
#define Prod 1 
#define Cons 4 

// variaveis do problema
int Buffer[N];                  
int count = 0; 
int in = 0, out = 0; 
sem_t condtInserir, condtRetirar; // semaforos para sincronizar a ordem de execucao das threads
pthread_mutex_t mutex;

void ImprimeBuffer(int n)
{
    int i;
    for (i = 0; i < n; i++)
        printf("%d ", Buffer[i]);
    printf("\n");
}

// insere um elemento no Buffer ou bloqueia a thread caso o Buffer esteja cheio
void Insere(int elemento, int id)
{
    printf("Produtor [%d] chegou para inserir\n", id);
    sem_wait(&condtInserir);
    for (int i = 0; i < N; i++)
    {
        Buffer[i] = elemento;
        count++;
    }
    printf("Produtor [%d] inseriu\n", id);
    ImprimeBuffer(N);
    sem_post(&condtRetirar);
}

void Retira(int id)
{
    printf("Consumidor [%d] chegou para consumir\n", id);
    sem_wait(&condtRetirar);
    if (count == 0) 
    {
        sem_wait(&condtRetirar);
        sem_post(&condtInserir);
      
    }
    count--;
    
    printf("Consumidor [%d] consumiu %d\n", id, Buffer[out]);
    Buffer[out] = 0;
    out = (out + 1) % N;
    ImprimeBuffer(N);
    sem_post(&condtRetirar);
    if (count == 0) 
    {
        sem_wait(&condtRetirar);
        sem_post(&condtInserir);
    }

}

void *produtor(void *arg)
{
    int *id = (int *)arg;
    printf("Sou a thread produtora %d\n", *id);
    while (1)
    {
        Insere(*id, *id);
        sleep(1);
        
    }
    free(arg);
    pthread_exit(NULL);
}

void *consumidor(void *arg)
{
    int *id = (int *)arg;
    printf("Sou a thread consumidora %d\n", *id);
    while (1)
    {
        Retira(*id);
        sleep(1);
    }
    free(arg);
    pthread_exit(NULL);
}

int main(void)
{
    int i;

    pthread_t tid[Prod + Cons];
    int *id[Prod + Cons];

    // aloca espaco para os IDs das threads
    for (i = 0; i < Prod + Cons; i++)
    {
        id[i] = malloc(sizeof(int));
        if (id[i] == NULL)
            exit(-1);
        *id[i] = i + 1;
    }

   
    for (int i = 0; i < N; i++)
        Buffer[i] = 0;

    // inicializa as variaveis de sincronizacao
    sem_init(&condtInserir, 0, 1);
    sem_init(&condtRetirar, 0, 0);
    

    // cria as threads produtoras
    for (int i = 0; i < Prod; i++)
    {
        if (pthread_create(&tid[i], NULL, produtor, (void *)id[i]))
            exit(-1);
    }

    // cria as threads consumidoras
    for (int i = 0; i < Cons; i++)
    {
        if (pthread_create(&tid[i + Prod], NULL, consumidor, (void *)id[i + Prod]))
            exit(-1);
    }

    pthread_exit(NULL);
    return 1;
}