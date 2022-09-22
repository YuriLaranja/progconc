
**Verifiquei os arquivos Binários das execução sequencial e da concorrente com o diff e retornou vazio como esperado**
Lei de Amdahl
(T sequencial/T concorrente)
Verificando o tempo agora
**Com 2 threads**
----------------------
**500X500**

**Execução 1**
O programa demorou 0.000018 segundos para criar a matriz

O programa demorou 0.260478 segundos para fazer a multiplicação

O programa demorou 0.000006 segundos para escrever no arquivo

O programa demorou 0.260502 segundos total


**Execução 2**

O programa demorou 0.000014 segundos para criar a matriz

O programa demorou 0.274820 segundos para fazer a multiplicação

O programa demorou 0.000007 segundos para escrever no arquivo

O programa demorou 0.274842 segundos total

**Execução 3**

O programa demorou 0.000013 segundos para criar a matriz

O programa demorou 0.256618 segundos para fazer a multiplicação

O programa demorou 0.000006 segundos para escrever no arquivo

O programa demorou 0.256637 segundos total

média = (0.260502 + 0.274842 + 0.256637)/3

**média = 0,2639936 segundos**
Ganho teórico: 100%
Ganho Real:
Lei de Amdahl >> 0,596375/0,2639936 = 2,25 >> 125%


**1000X1000** 

**Execução 1**

O programa demorou 0.000019 segundos para criar a matriz

O programa demorou 2.096585 segundos para fazer a multiplicação

O programa demorou 0.000007 segundos para escrever no arquivo

O programa demorou 2.096612 segundos total

**Execução 2**

O programa demorou 0.000014 segundos para criar a matriz

O programa demorou 2.113911 segundos para fazer a multiplicação

O programa demorou 0.000010 segundos para escrever no arquivo

O programa demorou 2.113934 segundos total

**Execução 3**

O programa demorou 0.000021 segundos para criar a matriz

O programa demorou 2.077923 segundos para fazer a multiplicação

O programa demorou 0.000008 segundos para escrever no arquivo

O programa demorou 2.077951 segundos total

média = (2.096612+2.113934+2.077951)/3

**média = 2,096165 segundos** 

Ganho teórico: 100%
Ganho Real:
Lei de Amdahl >> 3,972725/2,096165 = 1,89 >> 89% de ganho


**2000X2000**

**Execução 1**

O programa demorou 0.000018 segundos para criar a matriz

O programa demorou 16.809084 segundos para fazer a multiplicação

O programa demorou 0.000048 segundos para escrever no arquivo

O programa demorou 16.809150 segundos total

**Execução 2**
O programa demorou 0.000015 segundos para criar a matriz

O programa demorou 16.726429 segundos para fazer a multiplicação

O programa demorou 0.000048 segundos para escrever no arquivo

O programa demorou 16.726492 segundos total

**Execução 3**

O programa demorou 0.000014 segundos para criar a matriz

O programa demorou 16.954229 segundos para fazer a multiplicação

O programa demorou 0.000056 segundos para escrever no arquivo

O programa demorou 16.954298 segundos total

média = (16.809150+16.726492+16.954298)/3

**média = 16,82998 segundos**

Ganho teórico: 100%
Ganho Real:
Lei de Amdahl >> 29,23041466666667/16,82998 = 1,73 >> 73% de ganho
-----------------

**Com 4 threads**

**500X500** 

**Execução 1**
O programa demorou 0.000017 segundos para criar a matriz

O programa demorou 0.150564 segundos para fazer a multiplicação

O programa demorou 0.000007 segundos para escrever no arquivo

O programa demorou 0.150588 segundos total

**Execução 2**

O programa demorou 0.000013 segundos para criar a matriz

O programa demorou 0.132737 segundos para fazer a multiplicação

O programa demorou 0.000005 segundos para escrever no arquivo

O programa demorou 0.132755 segundos total

**Execução 3**

O programa demorou 0.000013 segundos para criar a matriz

O programa demorou 0.139299 segundos para fazer a multiplicação

O programa demorou 0.000007 segundos para escrever no arquivo

O programa demorou 0.139319 segundos total

média = (0.150588+0.132755+ 0.139319)/3

**média = 0,1408873 segundos**

Ganho teórico: 400%
Ganho Real:
Lei de Amdahl >> 0,596375/0,1408873 = 4,23 >> 423% de ganho


**1000X1000** 

**Execução 1**

O programa demorou 0.000050 segundos para criar a matriz

O programa demorou 1.109305 segundos para fazer a multiplicação

O programa demorou 0.000007 segundos para escrever no arquivo

O programa demorou 1.109362 segundos total

**Execução 2**

O programa demorou 0.000014 segundos para criar a matriz

O programa demorou 1.107495 segundos para fazer a multiplicação

O programa demorou 0.000007 segundos para escrever no arquivo

O programa demorou 1.107516 segundos total

**Execução 3**

O programa demorou 0.000282 segundos para criar a matriz

O programa demorou 1.126362 segundos para fazer a multiplicação

O programa demorou 0.000009 segundos para escrever no arquivo

O programa demorou 1.126653 segundos total

média = (1.109362+1.107516+1.126653)/3

**média = 1,103725 segundos**

Ganho teórico: 400%
Ganho Real:
Lei de Amdahl >> 3,972725/1,103725 = 3,6 >> 360% de ganho

**2000X2000** 

**Execução 1**

O programa demorou 0.000019 segundos para criar a matriz

O programa demorou 8.954469 segundos para fazer a multiplicação

O programa demorou 0.000038 segundos para escrever no arquivo

O programa demorou 8.954526 segundos total

**Execução 2**

O programa demorou 0.000014 segundos para criar a matriz

O programa demorou 8.808237 segundos para fazer a multiplicação

O programa demorou 0.000046 segundos para escrever no arquivo

O programa demorou 8.808297 segundos total

**Execução 3**
O programa demorou 0.000043 segundos para criar a matriz

O programa demorou 8.983490 segundos para fazer a multiplicação

O programa demorou 0.000052 segundos para escrever no arquivo

O programa demorou 8.983585 segundos total

média = (8.954526+8.808297+8.983585)/3

**média = 8,9154693 segundos**

Ganho teórico: 400%
Ganho Real:
Lei de Amdahl >> 29,23041466666667/8,9154693 = 3,278 >> 320% de ganho

---------------------

**Com 6 threads**

**500X500** 

**Execução 1**

O programa demorou 0.000017 segundos para criar a matriz

O programa demorou 0.090180 segundos para fazer a multiplicação

O programa demorou 0.000005 segundos para escrever no arquivo

O programa demorou 0.090203 segundos total

**Execução 2**
O programa demorou 0.000013 segundos para criar a matriz

O programa demorou 0.086917 segundos para fazer a multiplicação

O programa demorou 0.000005 segundos para escrever no arquivo

O programa demorou 0.086936 segundos total

**Execução 3**

O programa demorou 0.000013 segundos para criar a matriz

O programa demorou 0.089927 segundos para fazer a multiplicação

O programa demorou 0.000007 segundos para escrever no arquivo

O programa demorou 0.086936 segundos total

média = (0.090203+0.086936+0.086936)/3

**média = 0,088025 segundos**

Ganho teórico: 600%
Ganho Real:
Lei de Amdahl >> 0,596375/0,088025 = 6,77 >> 677% de ganho

**1000X1000**

**Execução 1**

O programa demorou 0.000018 segundos para criar a matriz

O programa demorou 0.672197 segundos para fazer a multiplicação

O programa demorou 0.000007 segundos para escrever no arquivo

O programa demorou 0.672222 segundos total

**Execução 2**

O programa demorou 0.000016 segundos para criar a matriz

O programa demorou 0.661949 segundos para fazer a multiplicação

O programa demorou 0.000006 segundos para escrever no arquivo

O programa demorou 0.661970 segundos total

**Execução 3**

O programa demorou 0.000014 segundos para criar a matriz

O programa demorou 0.668038 segundos para fazer a multiplicação

O programa demorou 0.000006 segundos para escrever no arquivo

O programa demorou 0.668058 segundos total

média = (0.672222+0.661970+0.668058)/3

**média = 0,667416 segundos**

Ganho teórico: 600%
Ganho Real:
Lei de Amdahl >> 3,972725/0,667416 = 5,95 >> 595% de ganho

**2000X2000**

**Execução 1**

O programa demorou 0.000019 segundos para criar a matriz

O programa demorou 5.546347 segundos para fazer a multiplicação

O programa demorou 0.000048 segundos para escrever no arquivo

O programa demorou 5.546414 segundos total

**Execução 2**

O programa demorou 0.000014 segundos para criar a matriz

O programa demorou 5.612300 segundos para fazer a multiplicação

O programa demorou 0.000053 segundos para escrever no arquivo

O programa demorou 5.612367 segundos total

**Execução 3**
O programa demorou 0.000014 segundos para criar a matriz

O programa demorou 5.548697 segundos para fazer a multiplicação

O programa demorou 0.000047 segundos para escrever no arquivo

O programa demorou 5.548757 segundos total

média = (5.546414+5.612367+5.548757)/3

**média = 5,5691793 segundos**

Ganho teórico: 600%
Ganho Real:
Lei de Amdahl >> 29,23041466666667/5,5691793 = 5,24 >> 524% de ganho
