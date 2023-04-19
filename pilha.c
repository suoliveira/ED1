#include <stdio.h> 
#include <stdlib.h>

typedef struct no {
    char caracter;
    struct no *prox; 
} No;

typedef struct pilha {
    struct no *head;
    int size;
} Pilha;

No *alocaMemoriaNo();
Pilha *alocaMemoriaPilha();
No *criaNo(char caracter);
Pilha *criaPilha();
void Empilhar(Pilha *pilha, char caracter);
void ImprimePilha(Pilha *pilha);
void Desempilhar(Pilha *pilha);
int par(char fecha, char desemp);
int forma(Pilha *pilha, char caracter[]);

No *alocaMemoriaNo() {
    return (No*) malloc(sizeof(No));
}

Pilha *alocaMemoriaPilha() {
    return (Pilha*) malloc(sizeof(Pilha));
}

No *criaNo(char caracter) {
    No *no = alocaMemoriaNo();

    if (no != NULL) {
        no->caracter = caracter;
        no->prox = NULL;  
    }
    return no;   
}

Pilha *criaPilha() {
    Pilha *pilha = alocaMemoriaPilha();

    if (pilha != NULL) {
        pilha->head = NULL;
        pilha->size = 0;
    }
    return pilha;   
}

void Empilhar(Pilha *pilha, char caracter) {
    No *novo = criaNo(caracter);
    
    if (novo != NULL) {
        if (pilha->head == NULL) {
            pilha->head = novo;
        } else {
            novo->prox = pilha->head;
            pilha->head = novo;
        }
        pilha->size++; 
    }
}

void Desempilhar(Pilha *pilha) {
    No *desempilha = pilha->head;
    
    if (desempilha != NULL) {
        pilha->head = desempilha->prox;
        free(desempilha);
        pilha->size--;  
    } else {
        printf("\nA pilha está vazia");
    }
}

void ImprimePilha(Pilha *pilha) {
    No *aux = pilha->head;
    printf("\nPilha: ");
    while (aux != NULL) {
        printf("%c ", aux->caracter);
        aux = aux->prox;
    }
}

int par(char fecha, char desemp) {
    if ((desemp == '(' && fecha == ')') || (desemp == '{' && fecha == '}') || (desemp == '[' && fecha == ']'))
        return 1;
    else
        return 0;
}
int forma(Pilha *pilha, char caracter[]) {
    int i;
    char desemp;
        for (i = 0; caracter[i] != '\0'; i++) {
            if (caracter[i] == '(' || caracter[i] == '{' || caracter[i] == '[') {
                Empilhar(pilha, caracter[i]);
            }else if (caracter[i] == ')' || caracter[i] == '}' || caracter[i] == ']') {
                if (pilha->head == NULL) {
                    printf("\nExpressão inválida");
                    return 0;
                } else{
                    desemp = pilha->head->caracter;
                if (par(caracter[i], desemp)) {
                    Desempilhar(pilha);
                } else {
                    printf("\nExpressão inválida");
                    return 0;
                }
            }
        }
    }
    if (pilha->head == NULL) {
        printf("\nExpressão válida");
        return 1;
    }else {
        printf("\nExpressão inválida");
        return 0;
    }
}

int main() {
    Pilha *pilha = criaPilha();
    char exp[50];
    printf("Digite a expressão: ");
    scanf("%[^\n]", exp);
    forma(pilha, exp);
    return 0;
}
