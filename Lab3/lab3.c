#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "timer.h"
#include<pthread.h>
int nthreads;
float *matA; ////matriz A de entrada
float *matB; //matriz B de entrada
float *matResul;
pthread_t *tid;


typedef struct {
    int id;
    int dim;
} tArgs;

void * tarefa(void *arg) {
   tArgs *args = (tArgs*) arg;

    for (int i = (args->id); i <args->dim; i+=nthreads)
    {
        for (int j = 0; j < args->dim; j++)
        {
            for (int k = 0; k < args->dim; k++)
            {
                matResul[i * (args->dim) + j] += matA[i * (args->dim) + k] * matB[k * (args->dim) + j];
            }
        }
        
    }
    pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
    int linhasA, linhasB, colunasA, colunasB;
    int dim;
    pthread_t *tid; 
    tArgs *args;
    FILE *descritorArquivoMatA = fopen(argv[1], "rb");
    FILE *descritorArquivoMatB = fopen(argv[2], "rb");
    FILE *descritorArquivoResul = fopen(argv[3], "wb");
    size_t ret;
    double inicioCriamatriz,fimCriaMatriz,deltaMatriz;
    double inicioMultiplicacao,fimMultiplicacao,deltaMultiplicacao;
    double inicioEscreverMatriz,fimEscreverMatriz,deltaEscreverMatriz;
    
    GET_TIME(inicioCriamatriz);
    
    if (argc == 0)
    {
        printf("Informe os argumentos corretamente:\n");
        printf("digite %s <Arquivo matrizA> <Arquivo matrizB> <Arquivo matrizResul>\n", argv[0]);
        return 1;
    }
    else if (argc == 1)
    {
        printf("Informe os argumentos corretamente:\n");
        printf("Faltou o <Arquivo matrizB> e o <Arquivo matrizResul> \n");
        printf("digite %s <Arquivo matrizA> <Arquivo matrizB> <Arquivo matrizResul>\n", argv[0]);
        return 1;
    }
    else if (argc == 2)
    {
        printf("Informe os argumentos corretamente:\n");
        printf("Faltou o <Arquivo matrizResul> \n");
        printf("digite %s <Arquivo matrizA> <Arquivo matrizB> <Arquivo matrizResul>\n", argv[0]);
        return 1;
    }
    if (!descritorArquivoMatA || !descritorArquivoMatB)
    {
        fprintf(stderr, "Erro de abertura do arquivo\n");
        return 2;
    }
    ret = fread(&linhasA, sizeof(int), 1, descritorArquivoMatA);
    if (!ret)
    {
        fprintf(stderr, "Erro de leitura das dimensoes da matriz arquivoA \n");
        return 3;
    }
    ret = fread(&colunasA, sizeof(int), 1, descritorArquivoMatA);
    if (!ret)
    {
        fprintf(stderr, "Erro de leitura das dimensoes da matriz arquivoA \n");
        return 3;
    }
    ret = fread(&linhasB, sizeof(int), 1, descritorArquivoMatB);
    if (!ret)
    {
        fprintf(stderr, "Erro de leitura das dimensoes da matriz arquivoB \n");
        return 3;
    }
    ret = fread(&colunasB, sizeof(int), 1, descritorArquivoMatB);
    if (!ret)
    {
        fprintf(stderr, "Erro de leitura das dimensoes da matriz arquivoB \n");
        return 3;
    }
    dim = linhasA; // calcula a qtde de elementos d
   //alocacao de memoria para as estruturas de dados
    matA = (float *) malloc(sizeof(float) * dim*dim);
   if (matA == NULL){printf("ERRO--malloc\n"); return 2;}

   matB = (float *) malloc(sizeof(float) * dim*dim);
   if (matB == NULL){printf("ERRO--malloc\n"); return 2;}

   matResul = (float *) malloc(sizeof(float) * dim*dim);
   if (matResul == NULL){printf("ERRO--malloc\n"); return 2;} 

    nthreads = atoi(argv[4]);
    GET_TIME(fimCriaMatriz);
    deltaMatriz = fimCriaMatriz - inicioCriamatriz;

    tid = (pthread_t*) malloc(sizeof(pthread_t)*nthreads);
    if(tid==NULL){puts("ERRO--malloc");return 2;}
    args = (tArgs*) malloc(sizeof(tArgs)*nthreads);
     if(args==NULL){puts("ERRO--malloc");return 2;}
    
    GET_TIME(inicioMultiplicacao);
    // multiplicação de matriz
    for (int i = 0; i < nthreads; i++)
    {
        (args+i) ->id =i;
        (args+i) ->dim =dim;
        if(pthread_create(tid+i, NULL,tarefa, (void *) (args+i))){
            puts("ERRO--pthread_create");return 6;
        }
    }
    for(int i=0; i<nthreads; i++) {
      if(pthread_join(*(tid+i), NULL) ) {
          printf("ERRO--pthread_join");
          exit(-1);
      }
   }
    GET_TIME(fimMultiplicacao);

    deltaMultiplicacao = fimMultiplicacao - inicioMultiplicacao;
    GET_TIME(inicioEscreverMatriz);
    //escreve numero de linhas e de colunas
   ret = fwrite(&linhasA, sizeof(int), 1, descritorArquivoResul);
   //escreve os elementos da matriz
   ret = fwrite(&colunasB, sizeof(int), 1, descritorArquivoResul);
   ret = fwrite(matResul, sizeof(float), dim, descritorArquivoResul);
   GET_TIME(fimEscreverMatriz);
    deltaEscreverMatriz = fimEscreverMatriz - inicioEscreverMatriz;
    printf("O programa demorou %f segundos para criar a matriz \n",deltaMatriz);
    printf("O programa demorou %f segundos para fazer a multiplicação \n",deltaMultiplicacao);
     printf("O programa demorou %f segundos para escrever no arquivo \n",deltaEscreverMatriz);
    printf("O programa demorou %f segundos total \n",(deltaMultiplicacao+deltaMatriz+deltaEscreverMatriz));
   //finaliza o uso das variaveis
   fclose(descritorArquivoResul);
   free(matA);
   free(matB);
   free(matResul);
   free(args);
   free(tid);
   return 0;

}