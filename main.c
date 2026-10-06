#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

typedef struct No{
    char valor;
    int decimal;
    int peso;
    struct No *proximo;
} No;

void dec_para_binario(int numero, int *bin, int *tamanho_bin, int posicao_bin);
void aumentar_tamanho(int *bin, int t);
void dec_hex(int num, int *bin, int *tamanho);
char valor_hex(int num);
void mostrar_hex(int *bin, int tamanho);
int hex_dec(char *num);
int hex_to_int(char c);
No *criar_elemento(char valor);
No *ultimo_elemento(No *lista);
void hex_to_bin(char *numero);
No *split(char *numero);
int hex_dec_individual(char c, int peso);
void atribuir_peso(No *lista);
int listalen(No *lista);
void inserir_novo_elemento(No *lista, int valor);
void mostrar_elementos(No *lista);
void calcular_decimal(No *lista);
int somar_decimais(No *lista);
void mostrar_binario(int *bin, int tamanho_bin);;

int main(int argc, char *argv[]){

	int num;
	char *base;
	char *destino;
	int c;
	while((c = getopt(argc, argv, "c:t:a:o:x:n")) != -1){
		char *valor;
		switch (c){
		case 'c':
			if(optarg[1] == 'x'){
				base = "hex";
				valor = optarg;
				optarg[1] = '0';
				break;
			}
			else if(optarg[1] == 'b'){
				base = "bin";
				optarg[1] = '0';	
			}
			else base = "dec";
			num = atoi(optarg);
			if(num<=0 && strcmp(base, "hex")){
				fprintf(stderr, "[ERRO] -> Você digitou algo errado ou o valor a ser convertido não pode ser menor ou igual a 0!\n");
				exit(-1);
			}
			break;
		case 't':
			int *bin = malloc(1*sizeof(int));
			destino = optarg;
			int tamanho=0;
			if(!strcmp(base, "dec") && !strcmp(destino, "binary")){
				dec_para_binario(num, bin, &tamanho, 0);
				mostrar_binario(bin, tamanho);
	
			} 
			else if(!strcmp(base, "dec") && !strcmp(destino, "hex")){
				dec_hex(num, bin, &tamanho);
				mostrar_hex(bin, tamanho);
			}
			else if(!strcmp(base, "hex") && !strcmp(destino, "dec")){
				*bin = hex_dec(valor);
				printf("%d", *bin);
			}
			else if(!strcmp(base, "hex") && !strcmp(destino, "binary")){
				hex_to_bin(valor);
			}
			else{
				fprintf(stderr, "[ ERRO ] -> Destino não conhecido\n");
				exit(-1);
			}
			break;
        case 'a':
            int num1 = atoi(argv[2]);
            int num2 = atoi(argv[3]);
            printf("%d\n", num1 & num2);
            break;
        case 'o':
            int or1 = atoi(argv[2]);
            int or2 = atoi(argv[3]);
            printf("%d\n", or1 | or2);
            break;
        case 'x':
            int xor1 = atoi(argv[2]);
            int xor2 = atoi(argv[3]);
            printf("%d\n", xor1 ^ xor2);
            break;
        case 'n':
            int not = atoi(argv[2]);
            printf("%d\n", ~not);
            break;
		default:
			printf("Uso: %s -c 10 -t binary\n", argv[0]);
			break;
		}
	}
	return 0;
}

void hex_to_bin(char *numero){
    No *lista = split(numero);
    atribuir_peso(lista);
    calcular_decimal(lista);
    int resultado = somar_decimais(lista);
    int *bin = (int*) malloc(1*sizeof(int));
    int tamanho = 1;
    dec_para_binario(resultado, bin, &tamanho, 0);
    mostrar_binario(bin, tamanho);
}

int somar_decimais(No *lista){
    int resultado = 0;
    while(1){
        if(lista->proximo == NULL){
            resultado += lista->decimal;
            return resultado;
        };
        resultado += lista->decimal;
        lista = lista->proximo;
    }
}

void atribuir_peso(No *lista){
    int tamanho = listalen(lista)-1;
    int x=0;
    while(lista->proximo != NULL){
        lista->peso = tamanho;
        lista = lista->proximo;
        tamanho--;
    };
}

void calcular_decimal(No *lista){
    while(1){
        if(lista->proximo == NULL){
            lista->decimal = hex_dec_individual(lista->valor, lista->peso);
            return;
        };
        lista->decimal = hex_dec_individual(lista->valor, lista->peso);
        lista = lista->proximo;
    }
};

int listalen(No *lista){
    int t=0;
    while(lista->proximo != NULL){
        lista = lista->proximo;
        t++;
    };
    return t+1;
}

int hex_dec_individual(char c, int peso){
    int numero;
    if((c >= 65 && c <= 70) || (c >= 97 && c <= 102)){
        numero = hex_to_int(c);
    }else{
        numero = atoi(&c);
    }
    return (numero * (int)pow(16, peso));
}

void inserir_novo_elemento(No *lista, int valor){
    lista = ultimo_elemento(lista);
    No *novo_elemento = criar_elemento(valor);
    lista->proximo = novo_elemento;
};

No *ultimo_elemento(No *lista){
    while(lista->proximo != NULL) lista = lista->proximo;
    return lista;
}

No *criar_elemento(char valor){
    No *novo = malloc(sizeof(No));
    novo->valor = valor;
    novo->decimal = 0;
    novo->peso = 0;
    novo->proximo = NULL;
    return novo;
}

void mostrar_elementos(No *lista){
    while(1){
        puts("+-------------+");
        printf("| valor = %c  |\n", lista->valor);
        printf("| decimal = %d  |\n", lista->decimal);
        printf("| peso = %d  |\n", lista->peso);
        lista->proximo == NULL ?printf("| próximo=NULL|\n"): printf("| próximo=%p|\n", lista->proximo);
        puts("+-------------+");
        if(lista->proximo == NULL) return;
        lista = lista->proximo;
    }
}

No *split(char *numero){
    size_t tamanho = strlen(numero);
    No *lista = malloc(sizeof(No));
    lista->valor = *(numero + 2);
    lista->decimal = 0;
    lista->peso = 0;
    lista->proximo = NULL;
    // printf("Tamanho -> %zu\n", tamanho);
    // printf("%c\n", lista->valor);
    for(int x = 3;x<tamanho;x++){
        // printf("%c\n", *(numero + x));
        inserir_novo_elemento(lista, *(numero + x));
    }
    return lista;
}

void mostrar_binario(int *bin, int tamanho_bin){
    for(int x = (tamanho_bin-1); x!=0;x--)printf("%d", *(bin+x));
    puts("");
}

void aumentar_tamanho(int *bin, int t){
    bin = (int*)realloc(bin, (t+10) * sizeof(int));
}

void dec_para_binario(int numero, int *bin, int *tamanho_bin, int posicao_bin){
    if(numero==0){
        *tamanho_bin = posicao_bin;
        return;
    };
    int resto = numero % 2;
    if(posicao_bin+1 > *tamanho_bin){
		aumentar_tamanho(bin, *tamanho_bin);
        *tamanho_bin += 10;
    }
    *(bin + posicao_bin) = resto;
    dec_para_binario(numero/2, bin, tamanho_bin, ++posicao_bin);
}

void dec_hex(int num, int *bin, int *tamanho){
    if(num == 0) return;
    *(bin + *tamanho) = num%16;

    ++*tamanho;
    return dec_hex(num/16, bin, tamanho);
}

char valor_hex(int num){
    if(num == 10) return 'A';
    if(num == 11) return 'B';
    if(num == 12) return 'C';
    if(num == 13) return 'D';
    if(num == 14) return 'E';
    if(num == 15) return 'F';
    return num + '0';
}

void mostrar_hex(int *bin, int tamanho){
    for(int x = --tamanho;x>=0;x--){
        printf("%c", valor_hex(*(bin + x)));
    };
}

int hex_to_int(char c){
    c = toupper(c);
    if(c == 'A' || c == 'a') return 10;
    if(c == 'B' || c == 'b') return 11;
    if(c == 'C' || c == 'c') return 12;
    if(c == 'D' || c == 'd') return 13;
    if(c == 'E' || c == 'e') return 14;
    if(c == 'F' || c == 'f') return 15;
    return 0;
}

int hex_dec(char *num){
    int x = 0;
    int numero;
    int peso = (int)strlen(num) - 3;
    int resultado = 0;
    char c;
    while(*(num + x) != '\0'){
        if(x<=1){
            x++;
            continue;
        };
        c = *(num + x);
        if((c >= 65 && c <= 70) || (c >= 97 && c <= 102)){
            numero = hex_to_int(c);
        }else{
            numero = atoi(&c);
        }
        resultado += (numero * (int)pow(16, peso));
        --peso;
        x++;
    }
    return resultado;
}