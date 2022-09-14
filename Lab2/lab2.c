#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "timer.h"


int main(int argc, char *argv[])
{

    float *matA, *matB, *matResul;
    int linhasA, linhasB, colunasA, colunasB;
    long long int tam;
    FILE *descritorArquivoMatA = fopen(argv[1], "rb");
    FILE *descritorArquivoMatB = fopen(argv[2], "rb");
    FILE *descritorArquivoResul = fopen(argv[3], "wb");
    size_t ret; // retorno da funcao de leitura no arquivo de entrada
    double inicioCriamatriz,fimCriaMatriz,deltaMatriz;
    double inicioMultiplicacao,fimMultiplicacao,deltaMultiplicacao;
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
    tam = linhasA * colunasA; // calcula a qtde de elementos da matriz

    // aloca memoria para a matriz
    matA = (float *)malloc(sizeof(float) * tam);
   if (!matA)
   {
      fprintf(stderr, "Erro de alocao da memoria da matrizA\n");
      return 3;
   }

   // carrega a matriz de elementos do tipo float do arquivo
   ret = fread(matA, sizeof(float), tam, descritorArquivoMatA);
   if (ret < tam)
   {
      fprintf(stderr, "Erro de leitura dos elementos da matrizA\n");
      return 4;
   }
    tam = linhasB * colunasB; // calcula a qtde de elementos da matriz

    // aloca memoria para a matriz
    matB = (float *)malloc(sizeof(float) * tam);
   if (!matB)
   {
      fprintf(stderr, "Erro de alocao da memoria da matrizB\n");
      return 3;
   }

   // carrega a matriz de elementos do tipo float do arquivo
   ret = fread(matB, sizeof(float), tam, descritorArquivoMatB);
   if (ret < tam)
   {
      fprintf(stderr, "Erro de leitura dos elementos da matrizB\n");
      return 4;
   }
    matResul = (float *)malloc(sizeof(float) * tam);
    if (!matResul)
    {
        fprintf(stderr, "Erro de alocao da memoria da matriz\n");
        return 3;
    }

    GET_TIME(fimCriaMatriz);
    deltaMatriz = fimCriaMatriz - inicioCriamatriz;
    GET_TIME(inicioMultiplicacao);
    // multiplicação de matriz
    for (int i = 0; i < linhasA; i++)
    {
        for (int j = 0; j < colunasB; j++)
        {
            for (int k = 0; k < linhasA; k++)
            {
                matResul[i * linhasA + j] += matA[i * linhasA + k] * matB[k * linhasA + j];
            }
        }
    }
    for (int i = 0; i < linhasA; i++)
    {
        for (int j = 0; j < colunasB; j++)
        {
            printf("%.1f ", matResul[i * linhasA + j]);
        }
        puts("");
    }
    GET_TIME(fimMultiplicacao);
    deltaMultiplicacao = fimMultiplicacao - inicioMultiplicacao;
    //escreve numero de linhas e de colunas
   ret = fwrite(&linhasA, sizeof(int), 1, descritorArquivoResul);
   //escreve os elementos da matriz
   ret = fwrite(&colunasB, sizeof(int), 1, descritorArquivoResul);
   ret = fwrite(matResul, sizeof(float), tam, descritorArquivoResul);
   if(ret < tam) {
      fprintf(stderr, "Erro de escrita no  arquivo\n");
      return 4;
   }
    printf("O programa demorou %f segundos para criar a matriz \n",deltaMatriz);
    printf("O programa demorou %f segundos para fazer a multiplicação \n",deltaMultiplicacao);
    printf("O programa demorou %f segundos total \n",(deltaMultiplicacao+deltaMatriz));
   //finaliza o uso das variaveis
   fclose(descritorArquivoResul);
   free(matA);
   free(matB);
   free(matResul);
   return 0;


    return 0;
}