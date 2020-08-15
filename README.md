# TRABALHO DE ESTRUTURA DE DADOS - *SIMULADOR DE ELVADOR*


## 1. Descrição sucinta sobre o desenvolvimento do trabalho. 
Este é o meu primeiro projeto de programação pela Universidade de Brasília em 1/2018. O objetivo do programa é criar um simulador de elevador em que duas estratégias pudessem ser escolhidas: First to Come Firts Served (FCFS) e Shortest Job First (SJF).

O programa possui uma função que gera o ambiente do elevador e a lista de eventos. A partir dela, o programa principal recebe a escolha da estratégia pelo usuário, o arquivo .txt do ambiente do elevador e o arquivo .txt dos eventos. Em seguida, dada a estratégia escolhida, o programa principal vai chamar a função da FCFS ou SJF. Cada uma dessas funções chama outras quatro funções que executam os principais procedimentos do elevador: receber um novo pedido da lista de eventos (Adiciona Eventos), verificar se têm alguém para descer (SaidaElevador), verificar se têm alguém para entrar (EntraElevador) e decide em qual sentido ir (Sentido). Cada uma dessas 4 funções chama um conjunto de Tipos Abstratos de Dados (TAD’s). O diagrama a seguir mostra essa cadeia de funções:

![](/CadeiaFuncoes.png)
Format: ![Alt Text](url)

## 2. Módulos e conteúdo

O programa conta com 4 módulos:
1.	Módulo da função principal (main);
2.	Módulo das estratégias;
3.	Módulo das funções que cada estratégia chama dos TAD’s;
4.	Módulo do gerador de eventos e ambiente do elevador.

O módulo que gera o ambiente do elevador e a lista de eventos é independente. O da função principal puxa a biblioteca do módulo das estratégias, que por sua vez puxa a biblioteca do módulo das funções.
Descrição dos TADs e as estruturas de dados utilizadas. 

Nesse programa foi utilizado as estruturas por listas dinamicamente encadeadas e filas.  Existem:
1.	Uma lista dinamicamente encadeada que representa a lista de pessoas dentro do elevador. Cada elemento da lista é uma struct com os três dados de cada evento mais dois campos para o tempo de espera dentro e fora do elevador.
2.	Uma lista dinamicamente encadeada que representa os andares. Cada elemento dessa lista é uma fila.
3.	Uma fila que representa a fila de pessoas esperando em cada andar. Cada Elemento da fila possui uma struct com os três dados de cada evento mais dois campos para o tempo de espera dentro e fora do elevador.
Foram utilizadas as funções de: 
1.	Inserção (cada lista teve um específico);
2.	Desinflarar fila;
3.	Enfileira fila;
4.	Esvaziar Lista (cada lista teve um específico);
5.	Esvaziar Fila.

Além dessas funções, o programa realiza determinados comandos para retirar determinados elementos em cada uma das listas. Por questões de facilidade na programação, optou-se por não criar uma função separada para essa operação.

Da forma como os dados estão organizados, acredita-se que a busca por eventos entre os andares é mais eficiente, uma vez que eles estariam organizados por andar e momento. Quando se diz organizado por andar, quer dizer que todos os eventos que são de determinado andar estarão juntos. Não necessariamente a lista de andares vai estar com os elementos organizados por ordem, os elementos dessa lista aparecem conforme a necessidade, ou seja, quando existe a demanda por uma fila naquele andar, quando existe uma pessoa esperando no andar. Quando a fila/elemento do andar se esvazia, esse elemento sai da lista de andares e o espaço na memória alocado para ele é liberado. 

Dessa forma, essa estrutura pode ser utilizada nas duas estratégias. Na FCFS, o programa vai escolher o sentido do elevador procurando o evento com menor momento no primeiro elemento de cada fila presente na lisa de andares (uma vez o primeiro item de cada fila é o primeiro a pedir dessa fila). Não se considera o pedido da pessoa dentro do elevador.
Elevador

## 3. Descrição do formato de entrada dos dados.

O arquivo .txt com a lista de eventos possui uma matriz nX3 em que cada linha é um evento, ou uma pessoa, com um momento em que esta pediu o elevador, o andar de origem e para qual andar ela deseja ir, respectivamente. Esse programa considera que nem sempre no momento seguinte aparecerá uma pessoa nova pedindo o elevador, ou seja, um momento de determinado evento é x e não necessariamente o momento do próximo evento é x+1. 
O segundo arquivo de entrada é do ambiente do elevador, contendo apenas dois valores: o número de andares do prédio e a capacidade do elevador, respectivamente. 

## 4. Descrição do formato de saída dos dados. 
O programa vai gerar uma sequência de “prints” no console que falaram de qual andar para qual andar o elevador foi, se alguém entrou ou saiu do elevador, informando para onde a pessoa queria/quer ir, qual é a sua origem, o momento que pediu o elevador, tempo de espera fora e dentro do elevador.

## 5. Explicação sobre como utilizar o programa. 
Para executar o programa, escreva: “./Simulador -i Ambiente_Elevador.txt -e Lista_Eventos.txt -s <estratégia>”. A opção “–i” vai pegar o arquivo com as informações do ambiente do elevador, “-e” vai pegar a lista com os eventos e “–s” escolherá a estratégia que só podem ser “fcfs” ou “sjf”. 
Se você quiser utilizar outros arquivos do ambiente e da lista de eventos, certifique-se de que os seus arquivos estão como especificados no item “Descrição do formato de entrada dos dados” e que você coloque o nome com .txt na linha do comando.

## 6. Resultados
Em relação aos resultados do programa, foram testadas quantidades de eventos de 10 mil, 100 mil, 1 milhão e 10 milhões; para prédios de 20 e 40 andares e elevadores de capacidade de 10 e 20 pessoas. De maneira geral, se o número de andares ou a capacidade aumentar, o programa acaba levando aproximadamente, 1,5 e 1 vezes, respectivamente, mais tempo para executar o programa. Entretanto, o tempo continua crescendo na mesma proporção da entrada. 
Além disso, percebeu-se que a estratégia SJF é mais eficiente do que a FCFS. Ainda mais, para um número de andares e capacidade maior, a estratégia SJF fica ainda mais eficiente em relação a FCFS.

No caso da SJF, o programa ao invés de procurar pelo menor momento no primeiro elemento da fila de cada andar, ele verificaria o andar de cada primeira pessoa nas fila de andares existente e procuraria a que tem a menor distancia. Ou seja, o menor módulo de (andar atual – andar do passageiro). 
Para ambos os casos, o programa sempre vai dar preferência na lista de pessoas dentro do elevador. Nessa lista, o primeiro elemento sempre é o que têm preferência. 
