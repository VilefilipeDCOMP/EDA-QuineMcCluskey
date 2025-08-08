#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int globalArray[256];
int globalArrayQtd = 0;

typedef struct no {
    char binario[20];
    int numeros1;
    int cobertura[32];
    int coberturaQtd;
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

int comparador (char *bit1, char *bit2, char* result) {
    int tamanho = strlen(bit1);
    int aux = 0;
    
    for(int i=0; i < tamanho; i++){
        if (bit1[i] != bit2[i]) {
            aux++;
        }
    }
    
    if(aux > 1) {
        return -1;
    }
    
    int auxNumeros1 = 0;
    for(int i=0; i < tamanho; i++){
        if(bit1[i] == bit2[i]){
            result[i] = bit1[i];
            if (result[i] == '1') {
                auxNumeros1++;
            }
        } else {
            result[i] = '-';
        }
    }  
    return auxNumeros1;
}

void printar(char *binaro){
    char letra = 'A';

    for(int i =0; i<strlen(binaro); i++){
        if(binaro[i] == '-') continue;

        if(binaro[i] == '0'){
            printf("~");
        }
        printf("%c", letra + i);
    }
}

void escolhaCobertura (tipoLista *lista) {
    tipoNo *aux = lista->inicio;
    int novoArray[32]; 
    int print =0;
    
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
                if(print) printf(" + ");
                printar(aux->binario);
                print = 1;

                for (int i = 0; i < aux->coberturaQtd; i++) {
                    // printf("%i ", aux->cobertura[i]);
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
                    if (aux->cobertura[j] == globalArray[i]) {
                        // printf("%s\n", aux->binario);
                        if(print) printf(" + ");
                        printar(aux->binario);
                        print = 1;
                        achou = 1;
                    }
                }
                if (achou == 1) {
                    break;
                }
                aux = aux->prox;
            }
        }
        if (achou == 1) {
            break;
        }

        // while (aux != NULL) {
        //     for (int j=0; j < aux->coberturaQtd; j++) {
        //         if (globalArray[i] == aux->cobertura[j]) {
        //             if (globalArray[i + 1] != aux->cobertura[j + 1]) {
        //                 achou = 1;
        //             }
        //         } else {
        //             valorFalta = aux->cobertura[j];
        //         }
        //         printf("%d %d %d\n", globalArray[i], aux->cobertura[j], achou);
        //     }
        //     aux = aux->prox;
        // }
        // if (achou == 0) {
        //     printf("Valor: %d\n", valorFalta);
        // }
    }
}

// void escolhaCobertura (tipoLista *lista) {
//     tipoNo *aux = lista->inicio;
//     int novoArray[32]; 
//     int contadorNOVOARRAY;
//     for (int i = 0; i < lista->qtd; i++) {
//         tipoNo* aux2 = lista->inicio;
//         int achou = 0;
//         for (int m = 0; m < aux->coberturaQtd; m++)
//             for (int j = 0; j < lista->qtd; j++) {
//             {
//                 for (int n = 0; n < aux2->coberturaQtd; n++)
//                 {   
//                     if (aux->cobertura != aux2->cobertura) {
//                         if (aux->cobertura[n] == aux2->cobertura[m]) {
//                             achou = 1;
//                         }
//                         printf("%d %d %d\n", aux->cobertura[m], aux2->cobertura[n], achou);
//                     }
//                 }
//             }
//             aux2 = aux2->prox;
//         }
//         if (achou == 1) {
//             printf("%s\n", aux->binario);
//         }
//         aux = aux->prox;
//     }
// }

int mergeArray(int *cobertura1, int *cobertura2, int size1, int size2, int *soma) {
    int k = 0;
    for (int i=0; i < size1; i++) {
        soma[k++] = cobertura1[i];
    }
    for (int j=0; j < size2; j++) {
        soma[k++] = cobertura2[j];
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
                    int somaArray[64];
                    
                    mergeArray(aux->cobertura, aux2->cobertura, aux->coberturaQtd, aux2->coberturaQtd, somaArray);

                    // Print the merged array
                    // printf("Cobertura: ");
                    // printf("{ ");
                    // for (int i = 0; i < (aux->coberturaQtd + aux2->coberturaQtd); i++) {
                    //     printf("%d ", somaArray[i]);
                    // }
                    // printf("}");
                    // printf("\n");

                    mergeArray(globalArray, somaArray, globalArrayQtd, (aux->coberturaQtd + aux2->coberturaQtd), globalArray);
                    globalArrayQtd = globalArrayQtd + 2;

                    // Print the merged array
                    // printf("Cobertura GERAL: ");
                    // printf("{ ");
                    // for (int i = 0; i < globalArrayQtd; i++) {
                    //     printf("%d ", globalArray[i]);
                    // }
                    // printf("}");
                    // printf("\n");


                    adicionarLista(complexodemais,resultado, resultadoComparador, somaArray, (aux->coberturaQtd + aux2->coberturaQtd));
                    pfvfunciona =1;
                    // printf("%s %s %s %i %i\n", aux->binario, aux2->binario, resultado, resultadoComparador);
                }
            }
            aux2 = aux2->prox;
        }
        aux = aux->prox;
    }
    return pfvfunciona;
}



int main (){
    // "./benchmark/tests/ex00_f_da_folha.pla";
    char nome_arquivo[] = "./benchmark/tests/ex04_funcao6var.pla"; // Tem que colocar caso ele n encontre para ler o arquivo
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
    int entrada;
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

        liberaLista(&listamin);
        listamin = nova;

        ordenarNum1(&listamin);
        ciclo++;
    }
    
    // printf("Os mintermos %i:\n", listamin.qtd);
    // tipoNo *aux = listamin.inicio;
    // for (int j=0; j < listamin.qtd; j++) {
    //     printf("%s %i\n", aux->binario, aux->numeros1);
    //     aux = aux->prox;
    // }

    escolhaCobertura(&listamin);

    // 10-1 110- -011 1-11 -> 11-- 

    fclose(file);
    return 0; 
}