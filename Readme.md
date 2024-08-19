# Sistema de Escalonador de processos

## Sobre o sistema

Este software consiste em simular um escalonador de processo com base no tempo de chegada e duração do processo. Foram implementados 3 tipos de escalonadores **FCFS(Primeiro a Entrar, Primeiro a ser Atendido),SJF(Menor Job Primeiro), RR(Round Robin)**.

## Padrão de estilo

Neste sistema, alguns padrões de qualidade de código devem ser seguidos:

<ul>
    <li> Todas as palavras utilizadas devem ser em inglês (exceto nos textos de comentários);</li>
    <li> Classes devem ser substantivos em <i>camelCase</i> e com a primeira letra maiúscula. Abreviações e acrônimos devem ser evitados a fim de tornar os nomes mais claros;</li>
    <li> Interfaces devem seguir o mesmo padrão das classes;</li>
    <li> Métodos devem ser verbos e devem estar em <i>camelCase</i>;</li>
    <li> Variáveis devem estar em <i>camelCase</i> e não devem começar com <i>underscore</i> nem com sinais de dólar ($);</li>
    <li> Os nomes das variáveis devem ser significativos e curtos;</li>
    <li> Constantes devem ter todas as letras maiúsculas e as palavras devem estar separadas por <i>underscore</i>;</li>
</ul>

## Para teste

O que sera usado como processo esta no **aquivo.txt**, para teste rode os seguintes comandos

```c++
g++ -o main main.cpp
./main
```
