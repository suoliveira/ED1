#include <stdio.h> 
#include <stdlib.h>

typedef struct no {
    int info;
    struct no *prox;
    struct no *ant; 
} No;

typedef struct fila {
    struct no *head;
    struct no *tail;
    int size;
} Fila;

No *alocaMemoriaNo();
Fila *alocaMemoriaFila();
No *criaNo(int info);
Fila *criaFila();
void inserirNaFila (Fila *fila, int info);
int RemoverFila(Fila *fila);
void ImprimeFila(Fila *fila);


No *alocaMemoriaNo() {
    return (No*) malloc(sizeof(No));
}

Fila *alocaMemoriaFila() {
    return (Fila*) malloc(sizeof(Fila));
}

No *criaNo(int info) {
    No *no = alocaMemoriaNo();

    if (no != NULL) {
        no->info = info;
        no->prox = NULL;  
        no->ant = NULL;
    }
    return no;   
}

Fila *criaFila() {
    Fila *fila = alocaMemoriaFila();

    if (fila != NULL) {
        fila->head = NULL;
        fila->tail = NULL;
        fila->size = 0;
    }
    return fila;   
}
void inserirNaFila(Fila *fila, int info) {
    No *novo = criaNo(info);
    No *pivo = fila->tail;
    
    if(fila->size == 0){
        fila->head = novo;
        fila->tail = novo;
    }else{
        novo->prox = pivo->prox;
        novo->ant = pivo;
        if (pivo->prox == NULL) {
                fila->tail = novo;
        }else{
            pivo->prox->ant = novo;
        } 
        pivo->prox = novo;
    }
        fila->size++; 
}


int RemoverFila(Fila *fila) {
    No *remover = fila->head;
    int num = 50;
    No *r = NULL;
    while(remover != NULL){
        if (remover->info < num){
            num = remover->info;
            r = remover;
        }
        remover = remover->prox;
    }
    r->ant->prox = r->prox;
    fila->tail= r->ant;
    printf("removeu:%d\n", r->info);
    free(r);
    fila->size--;  
}

void ImprimeFila(Fila *fila) {
    No *a = fila->head;
    printf("\nFila: ");
    while (a != NULL) {
        printf("%d ", a->info);
        a = a->prox;
    }
    printf("\n");
}

No *buscarInfo(Fila *fila, int info){
  No *no = fila->tail;
  int achou = 0;
    
     while(no != NULL){
        if (no->info == info)
            achou = 1;
            return no;
     }
        no = no->prox;
    
}

int main() {
	Fila* fi;
	fi = criaFila();
	inserirNaFila(fi, 20);
    inserirNaFila(fi, 13);
 	inserirNaFila(fi, 4);
	inserirNaFila(fi, 2);
	inserirNaFila(fi, 18);
	inserirNaFila(fi, 40);
	inserirNaFila(fi, 2);
	inserirNaFila(fi, 19);
	inserirNaFila(fi, 1);
    RemoverFila(fi);
    RemoverFila(fi);
    RemoverFila(fi);
    ImprimeFila(fi);

 
}




