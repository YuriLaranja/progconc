#include <stdio.h>
#include <stdlib.h> 
#include <pthread.h>

#define TAMVETOR 10000   
#define NTHREADS 2   

float vetor[TAMVETOR];

void * tarefas (void * arg) {
  int tid_sistema, i;
    
  tid_sistema =  * (int *) arg;
  i = ((TAMVETOR - 1)/(tid_sistema));  
    
  for (int j = 0; j < 5000 ;j++) {
    vetor[i-1] *= 1.1 ;
    i--;
  }
  pthread_exit(NULL);
}
int main() {
  pthread_t tid_sistema[NTHREADS];   
  int thread [NTHREADS];   

  // alocando os elementos no vetor
  for (int i = 0; i < TAMVETOR; i++) {
    vetor[i] = i;
  }

  // cria as threads
  for (int i = 1; i <= NTHREADS; i++) { 
    thread[i-1] = i; 

    if (pthread_create (&tid_sistema[i-1], NULL, tarefas, (void *) &thread[i-1])) 
      printf ("--ERRO: pthread_create()\n");
  }
  for (int i = 0; i < NTHREADS; i++) {
    if (pthread_join (tid_sistema[i], NULL)) 
      printf ("--ERRO: pthread_join()\n"); 
  }
  for (int i = 0; i < 10; i++) {
        printf("Posição %d >> %.1f\n",i+1,vetor[i]);
  }  
printf("Programa correto\n");
  return 0;
}
