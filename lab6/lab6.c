#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define T1 3 // numero de threads com comportamento T1
#define T2 4  // numero de threads com comportamento T2
#define T3 1 // numero de threads com comportamento T3

// variaveis do problema
int leit = 0; // contador de threads lendo
int escr = 0; // contador de threads escrevendo

// variaveis para sincronizacao
pthread_mutex_t mutex;
pthread_cond_t cond_leit, cond_escr;

// valor global observado pela atividade
int valor = 0;

//entrada leitura
void InicLeit (int id) {
   pthread_mutex_lock(&mutex);
   printf("L[%d] quer ler\n", id);
   while(escr > 0) {
     printf("L[%d] bloqueou\n", id);
     pthread_cond_wait(&cond_leit, &mutex);
     printf("L[%d] desbloqueou\n", id);
   }
   leit++;
   pthread_mutex_unlock(&mutex);
}

//saida leitura
void FimLeit (int id) {
   pthread_mutex_lock(&mutex);
   printf("L[%d] terminou de ler\n", id);
   leit--;
   if(leit==0) pthread_cond_signal(&cond_escr);
   pthread_mutex_unlock(&mutex);
}

//entrada escrita
void InicEscr (int id) {
   pthread_mutex_lock(&mutex);
   printf("E[%d] quer escrever\n", id);
   while((leit>0) || (escr>0)) {
     printf("E[%d] bloqueou\n", id);
     pthread_cond_wait(&cond_escr, &mutex);
     printf("E[%d] desbloqueou\n", id);
   }
   escr++;
   pthread_mutex_unlock(&mutex);
}

//saida escrita
void FimEscr (int id) {
   pthread_mutex_lock(&mutex);
   printf("E[%d] terminou de escrever\n", id);
   escr--;
   pthread_cond_signal(&cond_escr);
   pthread_cond_broadcast(&cond_leit);
   pthread_mutex_unlock(&mutex);
}

// thread leitora
void *leitor(void *arg)
{
    int *id = (int *)arg;
    while (1)
    {
        InicLeit(*id);
        if(valor % 2 == 0){
           printf("leitor %d leu o número: %d que é par\n", *id, valor); 
        }
       else{
            printf("leitor %d leu o número: %d que é ímpar\n", *id, valor); 
       }
        FimLeit(*id);
        sleep(1);
    }
    free(arg);
    pthread_exit(NULL);
}

// thread escritora
void *escritor(void *arg)
{
    int *id = (int *)arg;
    while (1)
    {
        InicEscr(*id);
        valor += 1;
        printf("Escritor %d escreveu o valor: %d\n", *id,valor);
        FimEscr(*id);
        sleep(1);
    }
    free(arg);
    pthread_exit(NULL);
}

void *leitorAndEscritorBobo(void *arg)
{
    int *id = (int *)arg;
    while (1)
    {
        InicLeit(*id);
        printf("Leitor ""bobo"" %d leu o valor %d\n", *id, valor);
        FimLeit(*id);
        InicEscr(*id);
        valor = valor * 3 + 1;
        printf("Escritor ""bobo"" %d escreveu o valor %d\n", *id, valor);
        FimEscr(*id);
        sleep(1);
    }
    free(arg);
    pthread_exit(NULL);
}
// funcao principal
int main(void)
{
    // identificadores das threads
    int nthreads = T1 + T2 + T3;
    pthread_t tid[nthreads];
    int id[nthreads];

    // inicializa as variaveis de sincronizacao
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond_leit, NULL);
    pthread_cond_init(&cond_escr, NULL);

    // cria as threads T2
    for (int i = 0; i < T2; i++)
    {
        id[i] = i + 1;
        if (pthread_create(&tid[i], NULL, leitor, (void *)&id[i]))
            exit(-1);
    }

    // cria as threads T1
    for (int i = 0; i < T1; i++)
    {
        id[i + T2] = i + 1;
        if (pthread_create(&tid[i + T2], NULL, escritor, (void *)&id[i + T2]))
            exit(-1);
    }

    // cria as threads T3
    for (int i = 0; i < T3; i++)
    {
        id[i + T1 + T2] = i + 1;
        if (pthread_create(&tid[i +  T1 + T2], NULL, leitorAndEscritorBobo, (void *)&id[i +  T1 + T2]))
            exit(-1);
    }

    pthread_exit(NULL);
    return 0;
}