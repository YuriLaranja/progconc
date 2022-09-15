**Respostas**


**500X500** =  (0.596002 +  0.596474 + 0.596649)/3 >> O tempo médio foi de **0,596375** segundos

**1000X1000** = (3.976048 + 3.981883 + 3.960244)/3 >> o tempo médio foi de **3,972725** segundos

**2000X2000** = (29.111981 + 29.436010 + 29.143253)/3  >> o tempo médio foi de **29,23041466666667** segundos


Utilizando a lei de Amdahl vista em sala, vemos que podemos desconsiderar o tempo da criação das matrizes nesses exemplos pois, em todos os casos o valor foi menor que 0,0003 segundos.

Utilizando duas threads na matriz teremos

**500X500** >> 0,596375/2 == 0,2981875 segundos estimado

**1000X1000** >> 3,972725/2 == 1,9863625 segundos estimado

**2000X2000** >> 29,23041466666667/2 == 14,61520733333334 segundos estimado
