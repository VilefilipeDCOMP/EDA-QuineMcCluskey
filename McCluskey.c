#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int globalArray[256];
int globalArrayQtd = 0;
int entrada;
int DEBUG_Contador = 0;

typedef struct no {
    char binario[20];
    int numeros1;
    int cobertura[32];
    int coberturaQtd;
    int foiUtilizado;
    int foiPrintado;
    struct no *prox;
} tipoNo;

typedef struct cabeca {
    int qtd;
    tipoNo *inicio;
    tipoNo *fim;
} tipoLista;

void inicializa (tipoLista* lista) {
    lista->qtd = 0;
    lista->inicio = NULL;
    lista->fim = NULL;
    int coberturaQtd = 0;
    int foiUtilizado = 0;
}

void adicionarLista (tipoLista* lista, char binarioP[10], int numerosP, int cobertura[32], int coberturaQtd) {
    tipoNo *aux = (tipoNo*) malloc(sizeof(tipoNo));
    strcpy(aux->binario, binarioP);
    aux->prox = NULL;
    aux->numeros1 = numerosP;
    aux->coberturaQtd = coberturaQtd;
    for (int i = 0; i < coberturaQtd; i++) {
        aux->cobertura[i] = cobertura[i];
    }
    if (lista->qtd == 0) {
        lista->inicio = aux;
        lista->fim = aux;
    } else {
        lista->fim->prox = aux;
        lista->fim = aux;
    }
    lista->qtd++;
}

void ordenarNum1 (tipoLista *lista){

    if(lista->inicio == NULL) return;
    
    int troca;
    tipoNo *aux, *aux2;
    
    do{
        troca = 0;
        aux = lista->inicio;
        while(aux->prox != NULL){
            aux2 = aux->prox;
            if(aux->numeros1 > aux2->numeros1){
                
                char binlixo[20];
                strcpy(binlixo, aux->binario);
                strcpy(aux->binario, aux2->binario);
                strcpy(aux2->binario, binlixo);
                
                int temp = aux->numeros1;
                aux->numeros1 = aux2->numeros1;
                aux2->numeros1 = temp;
                
                troca =1;
            }
            aux = aux->prox;
        }
    }while(troca);
}

int buscaArray(int *soma, int size, int elemento) {
    for (int i=0; i < size; i++) {
        if (soma[i] == elemento){
            return 1;
        }
    }
    return 0;
}

int buscaLista(tipoLista *lista, char binario[20]) {
    tipoNo* aux = lista->inicio;
    for (int i=0; i < lista->qtd; i++) {
        if (strcmp(aux->binario, binario) == 0){ 
            return 1;
        }
        aux = aux->prox;
    }
    return 0;
}

int comparador (char *bit1, char *bit2, char* result) {
    int tamanho = strlen(bit1);
    int aux = 0;
    int numBarras = 0;
    
    for(int i=0; i < tamanho; i++){
        if (bit1[i] != bit2[i]) {
            if (bit1[i] == '-') {
                numBarras++;
            }
            aux++;
        }
    }
    
    if(aux > 1) {
        return -1;
    }
    
    int auxNumeros1 = 0;
    for(int i=0; i < tamanho; i++){
        if(bit1[i] == bit2[i] && bit1[i] != '-'){
            result[i] = bit1[i];
            if (result[i] == '1') {
                auxNumeros1++;
            }
        } 
        // else if((bit1[i] == '-' || bit2[i] == '-') || (entrada/2 <= numBarras)){
        //     return -1;
        //     // bit1[i] = bit1[i+1];
        //     // bit2[i] = bit2[i+1];
        // }
        else {
            result[i] = '-';
        }
    }  
    return auxNumeros1;
}

int printar(char *binaro, tipoLista *lista){
    char letra = 'A';
    if (buscaLista(lista, binaro) == 0) {
        for(int i =0; i<strlen(binaro); i++){
            if(binaro[i] == '-') continue;
    
            if(binaro[i] == '0'){
                printf("~");
            }
            printf("%c", letra + i);
            adicionarLista(lista, binaro, -1, NULL, -1);
            return 1;
        }
    }
    return 0;
}

void escolhaCobertura (tipoLista *lista) {
    tipoNo *aux = lista->inicio;
    int novoArray[32]; 
    int print = 0;
    tipoLista listaJaPrintada;
    inicializa(&listaJaPrintada);
    
    int contadorNOVOARRAY;
    for (int i = 0; i < lista->qtd; i++) {
        for (int m = 0; m < aux->coberturaQtd; m++) {
            tipoNo* aux2 = lista->inicio;
            int achou = 0;
            for (int j = 0; j < lista->qtd; j++) {
                for (int n = 0; n < aux2->coberturaQtd; n++) {
                    if (aux != aux2) {
                        if (aux->cobertura[m] == aux2->cobertura[n]) {
                            achou = 1;
                        }
                        // printf("%d %d %d\n", aux->cobertura[m], aux2->cobertura[n], achou);
                    }
                }
                aux2 = aux2->prox;
            }
            if (achou == 0) {
                // printf("únicos");
                if(print) printf(" + ");
                print = printar(aux->binario, &listaJaPrintada);
                // print = 1;

                for (int i = 0; i < aux->coberturaQtd; i++) {
                    for (int j=0; j < globalArrayQtd; j++) {
                        if (aux->cobertura[i] == globalArray[j]) {
                            globalArray[j] = -1;
                        }
                    }
                }
                // printf("}");
                // printf("\n", aux->binario);
               
            }
        }
        aux = aux->prox;
    }

    for (int i=0; i < globalArrayQtd; i++) {
        aux = lista->inicio;
        int achou = 0;
        int valorFalta;
        if (globalArray[i] != -1) {
            while (aux != NULL) {
                for (int j=0; j < aux->coberturaQtd; j++) {
                    if (globalArray[i] != 0) {
                        // printf("%i %i\n", aux->cobertura[j], globalArray[i]);
                        if (aux->cobertura[j] == globalArray[i]) {
                            if(print) printf(" + ");
                            print = printar(aux->binario, &listaJaPrintada);
                            globalArray[i] = 0;
                            // print = 1;
                            achou = 1;
                            break;
                        }
                    }
                }
                if (achou == 1) {
                    break;
                }
                aux = aux->prox;
            }
        }
        // if (achou == 1) {
        //     break;
        // }
    }
}



int mergeArray(int *cobertura1, int *cobertura2, int size1, int size2, int *soma) {
    int k = 0;
    for (int i=0; i < size1; i++) {
        if (buscaArray(soma, size1, cobertura1[i]) == 0) {
            soma[k++] = cobertura1[i];
        }
        // soma[k++] = cobertura1[i];
    }
    for (int j=0; j < size2; j++) {
        if (buscaArray(soma, size2, cobertura2[j]) == 0) {
            soma[k++] = cobertura2[j];
        }
        // soma[k++] = cobertura2[j];
    }
    return k;
}

void liberaLista(tipoLista *lista) {
    tipoNo *aux = lista->inicio;
    while (aux != NULL) {
        tipoNo *tmp = aux;
        aux = aux->prox;
        free(tmp);
    }
    lista->inicio = lista->fim = NULL;
    lista->qtd = 0;
}

int algoritmoComparar (tipoLista *lista, tipoLista *complexodemais) {
    tipoNo* aux = lista->inicio;
    int pfvfunciona = 0;
    if(aux == NULL) return 0;
    for (int i = 0; i < lista->qtd; i++) {
        tipoNo* aux2 = lista->inicio;
        for (int j = 0; j < lista->qtd; j++) {
            if (aux->numeros1 + 1 == aux2->numeros1) {
                char resultado[strlen(aux->binario)];
                int resultadoComparador = comparador(aux->binario, aux2->binario, resultado);
                if(resultadoComparador != -1){
                    if (buscaLista(complexodemais, resultado) == 0) {
                        // printf("res: %s, resU: %i\n", resultado, buscaLista(complexodemais, resultado));
                        int somaArray[64];
                        
                        aux->foiUtilizado = 1;
                        aux2->foiUtilizado = 1;
                        mergeArray(aux->cobertura, aux2->cobertura, aux->coberturaQtd, aux2->coberturaQtd, somaArray);
    
                        mergeArray(globalArray, somaArray, globalArrayQtd, (aux->coberturaQtd + aux2->coberturaQtd), globalArray);
                        globalArrayQtd = globalArrayQtd + 2;
    
                        adicionarLista(complexodemais, resultado, resultadoComparador, somaArray, (aux->coberturaQtd + aux2->coberturaQtd));
                        pfvfunciona = 1;
                        if (DEBUG_Contador == 2) {
                            printf("%s %s %s %i [%i]\n", aux->binario, aux2->binario, resultado, resultadoComparador, DEBUG_Contador);
                        }
                    }
                }
            }
            aux2 = aux2->prox;
        }
        aux = aux->prox;
    }
    return pfvfunciona;
}

int buscarNaoUtilziado (tipoLista *lista) {
    tipoNo* aux = lista->inicio;
    for (int i = 0; i < lista->qtd; i++) {
        if (aux->foiUtilizado != 1) {
            printf("Elemento não utilizado: %s\n", aux->binario);
        }
        aux = aux->prox;
    }
}

int main (){
    // "./benchmark/tests/ex00_f_da_folha.pla";
    char nome_arquivo[] = "./benchmark/tests/ex03_funcao5var.pla"; // Tem que colocar caso ele n encontre para ler o arquivo
    // char nome_arquivo[256];
    // printf("Insira o nome do arquivo (com a extensao .pla no fim): \n");
    // fgets(nome_arquivo,sizeof(nome_arquivo),stdin);
    // nome_arquivo[strcspn(nome_arquivo, "\n")] = 0;
    // getchar();

    FILE *file = fopen (nome_arquivo, "r");
    char a[500];

    tipoLista listamin; 
    inicializa(&listamin);

    int i = 0;
    while (fgets(a, sizeof(a), file) != NULL) {
        if (a[0] == '.' && a[1] == 'i') {
            entrada = a[3] - '0';
        }
        if (a[0] != '.' && a[0] != '\n') {
            if (a[entrada+1] == '1') {
                int numerosP = 0;
                char valor[10];
                int j = 0;
                while (a[j] != 32) {
                    if (a[j] == '1') {
                        numerosP++;
                        }
                    valor[j] = a[j];
                    j++;
                }
                valor[j] = '\0';
                int cobertura[32];
                cobertura[0] = i;
                adicionarLista(&listamin, valor, numerosP, cobertura, 1);
            }
            i++;
        }
        
    }
    
    ordenarNum1(&listamin);

    int ciclo = 1;
    while(1){
        tipoLista nova;
        inicializa(&nova);

        int foi = algoritmoComparar(&listamin, &nova);

        if(!foi){
            break;
        }

        buscarNaoUtilziado(&listamin);
        liberaLista(&listamin);
        listamin = nova;
        
        ordenarNum1(&listamin);
        ciclo++;
        DEBUG_Contador++;
        // break;
    }

    tipoNo* aux = listamin.inicio;
    for (int i=0; i < listamin.qtd; i++) {
        printf("%s\n", aux->binario);
        aux = aux->prox;
    }

    // printf("[");
    // for (int i = 0; i < globalArrayQtd; i++) {
    //     printf("%i ", globalArray[i]);
    // }
    // printf("]\n");

    escolhaCobertura(&listamin);


    fclose(file);
    return 0; 
}