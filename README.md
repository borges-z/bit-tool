# bit-tool

 O `bit-tool` é uma ferramenta de linha de comando desenvolvida em C para estudar e praticar conceitos relacionados a sistemas numéricos, representação de números e operações com bits.

 O programa permite realizar conversões entre números decimais, binários e hexadecimais, além de executar operações bitwise como AND, OR, XOR, NOT e operações de deslocamento de bits.

 ## Uso

 Após compilar o programa, uma operação bitwise pode ser executada da seguinte forma:

```
./programa -a 5 3
```

 Nesse exemplo, a operação AND (`&`) é realizada entre os valores `5` e `3`.

 ## Objetivo

 O projeto foi desenvolvido com finalidade educacional, principalmente para praticar a linguagem C e compreender melhor o funcionamento de bits, conversões numéricas e operações bitwise.

 Como se trata de um projeto de estudos, algumas partes podem ser melhoradas ou corrigidas futuramente conforme novos conhecimentos forem adquiridos.

 ## Compilação

 Para compilar o programa:

```
gcc main.c -o programa -lm
```

 O nome do arquivo de saída pode ser alterado conforme a preferência. Por exemplo:

```
gcc main.c -o bit-tool -lm
```

 ## Aviso sobre IA

 O código deste projeto foi desenvolvido sem o uso de Inteligência Artificial. O projeto foi criado como uma forma de estudo e aprendizado prático da linguagem C.