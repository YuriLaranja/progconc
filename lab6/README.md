Testando com diferentes configurações de threads, percebemos o quão impactante isso é para o sistema.
Pois dependendo das configurações o número de execuções de um certo tipo de Thread domina o outro e se torna grande maioria na execução.
Exemplo com T2 = 4 threads, dessa forma em algumas execuções o numero de threads leitoras leu em média 5 vezes o valor 0 antes de alguma thread escritora conseguir escrever e incrementar o valor
E ao mesmo tempo muitas threads escritoras se bloquearam pois quanto mais threads mais chances delas se bloquearem na exclusão mútua e racícinio do sistema, onde nenhuma thread pode escrever enquanto outra está lendo
