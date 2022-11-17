
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>
// #include "time.h"


 int bloqueadas = 0, nthreads = 1, n;
 pthread_mutex_t x_mutex;
 pthread_cond_t x_cond;
int maxIndex;
 float A[3][3], b[3], vetorAuxiliar[3], vetorFinal[3], EPSILON = 0.00001, soma;

// Função barreira vista em aula
void barreira(int nthreads)
{
    pthread_mutex_lock(&x_mutex); // inicio secao critica
    if (bloqueadas == (nthreads - 1))
    {
        // ultima thread a chegar na barreira
        pthread_cond_broadcast(&x_cond);
        bloqueadas = 0;
    }
    else
    {
        bloqueadas++;
        pthread_cond_wait(&x_cond, &x_mutex);
    }
    pthread_mutex_unlock(&x_mutex); // fim secao critica
}

void *tarefaGauss(void *arg)
{
    int id = (long int)arg; // Identificação das threads
    int k,i;
    for ( k = 0; k < n - 1; k++) {
    double max = fabs(A[k][k]);
    
    for (i = k + 1 +id; i < n; i++) {
            if (max < fabs(A[i][k])) {
                max = fabs(A[i][k]);
                maxIndex = i;
            }
        }
     }
    barreira(nthreads);
}


//Código de testes
void main(int argc, char **argv){

    int n;
    // double momentoInicializacao, momentoProcessamento, momentoFinalizacao, tempoInicializacao, tempoProcessamento, tempoFinalizacao;
    // GET_TIME(momentoInicializacao);
    // tempoInicializacao = momentoInicializacao;
    pthread_t *tid; // Identificadores das threads no sistema
    if (argc > 1)
    {
        nthreads = atoi(argv[1]); // Argumento que recebe a quantidade de threads que o programa utilizará
    }
     printf("PROGRAMA EXECUTANDO COM %d THREADS \n", nthreads);
    printf("\nQuantas variáveis possui na equação?: ");
    scanf("%d", &n);

        printf("\nEntre com a matriz de equações: ");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            scanf("%f", &A[i][j]);
        }
    }
    printf("\nEntre com o vetor de resultados: ");
    for (int i = 0; i < n; i++)
        scanf("%f", &b[i]);
    for (int i = 0; i < n; i++)
        vetorAuxiliar[i] = 0;
    tid = (pthread_t *)malloc(sizeof(pthread_t) * nthreads);
    if (tid == NULL)
    {
        fprintf(stderr, "ERRO--malloc\n");
        return;
    }
    


    long int i, j, k, l, m;
    //ETAPA DE ESCALONAMENTO
    for ( k = 0; k < n - 1; k++) {
        
        //procura o maior coeficiente em modulo
        for (long int i = 0 ; i < nthreads; i++) {
           if (pthread_create(tid + i, NULL, tarefaGauss, (void *)i))
            {
                fprintf(stderr, "ERRO--pthread_create\n");
                return;
            }
        }
        for (long int i = 0; i < nthreads; i++)
        {
            if (pthread_join(*(tid + i), NULL))
            {
                printf("--ERRO: pthread_join() \n");
                exit(-1);
            }
        }
        if (maxIndex != k) {
            
             //troca a equacao pela equacao com o maior coeficiente em modulo
            for (j = 0; j < n; j++) {
                double temp = A[k][j];
                A[k][j] = A[maxIndex][j];
                A[maxIndex][j] = temp;
            }
            double temp = b[k];
            b[k] = b[maxIndex];
            b[maxIndex] = temp;
        }
        //Se A[k][k] e zero, entao a matriz dos coeficiente e singular
        //det A = 0
        if (A[k][k] == 0) {
            printf("A matriz dos coeficientes é singular\n");
            return;
        } else {
            //realiza o escalonamento
            for (m = k + 1; m < n; m++) {
                double F = -A[m][k] / A[k][k];
                A[m][k] = 0;
                b[m] = b[m] + F * b[k];
                for (l = k + 1; l < n; l++) {
                    A[m][l] = A[m][l] + F * A[k][l];
                }
            }
        }
    }
    //ETAPA DE RESOLUCAO DO SISTEMA
    for (i = n - 1; i >= 0; i--) {
        vetorFinal[i] = b[i];
        for (j = i + 1; j < n; j++) {
            vetorFinal[i] = vetorFinal[i] - vetorFinal[j] * A[i][j];
        }
        vetorFinal[i] = vetorFinal[i] / A[i][i];
    }
    printf("Solução: \n");
    for (int i = 0; i < n; i++)
        printf("x%d: %f \n", i + 1, vetorFinal[i]);

}