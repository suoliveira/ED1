#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#define TAM 53

typedef struct no {
    char *info;
    struct no *prox;
    struct no *ant; 
} No;

typedef struct lista {
    struct no *head;
    struct no *tail;
    int size;
} Lista;

No *alocaMemoriaNo();
Lista *alocaMemoriaLista();
No *criaNo(char info[]);
Lista *criaLista();
void inserirNaLista (Lista *lista, char info[]);
int RemoverDaLista(Lista *lista, No* no);
void ImprimeLista(Lista *lista);
No* buscaNo(Lista *lista , char info[]);
void ler(char f[], Lista *t);
void inicializarTabela(Lista t[]);
int funcaoHash(char info[]);
void inserirTabela(Lista t[], char info[]);
No *buscaTabela(Lista t[], char info[]);
void imprimirTabela(Lista t[]);
void removerTabela(Lista t[], char info[]);
void imprimirIndice (Lista t[], int i);


No *alocaMemoriaNo() {
    return (No*) malloc(sizeof(No));
}

Lista *alocaMemoriaLista() {
    return (Lista*) malloc(sizeof(Lista));
}

No *criaNo(char info[]) {
    No *no = alocaMemoriaNo();

    if (no != NULL) {
        no->info = (char*) malloc((strlen(info) + 1) * sizeof(char));  
        if (no->info != NULL) {
            strcpy(no->info, info);  
            no->prox = NULL;
            no->ant = NULL;
        } else {
            free(no);  
            return NULL;
        }
    }
    return no;
}


Lista *criaLista() {
    Lista *lista = alocaMemoriaLista();

    if (lista != NULL) {
        lista->head = NULL;
        lista->tail = NULL;
        lista->size = 0;
    }
    return lista;   
}

void inserirNaLista(Lista *lista, char info[]) {
    No *novo = criaNo(info);
    No *pivo = lista->tail;
    
    if(lista->size == 0){
        lista->head = novo;
        lista->tail = novo;
    }else{
        novo->prox = pivo->prox;
            novo->ant = pivo;
        if (pivo->prox == NULL) {
                lista->tail = novo;
        }else{
            pivo->prox->ant = novo;
        } 
        pivo->prox = novo;
    }
        lista->size++; 
}


int RemoverDaLista(Lista *lista, No *no){
     if((no!= NULL) && (lista->size!=0)){
	    
        if(no == lista->head){
		  lista->head = no->prox;
		  
          if(lista->head == NULL){
			 lista->tail = NULL;
		  }else{
			  no->prox->ant = NULL;
              }
	  }else{
		  no->ant->prox = no ->prox;
		  if(no->prox == NULL){
			  lista->tail = no->ant;
		  }else{
			  no->prox->ant = no->ant;
		  }
    }
	  free(no);
	  lista->size--;
  }
  return 0;
}

No* buscaNo(Lista *lista, char info[]){
  
  No *busca = lista->head;
  while(busca!=NULL){
    if(strcmp(busca->info, info)==0){
      return busca;
    }
    busca=busca->prox;  
  }
  return NULL;
}
   
  
void ImprimeLista(Lista *lista) {
    No *a = lista->head;
    printf("TAM: %d ", lista->size);
    while (a != NULL) {
        printf("%s ", a->info);
        a = a->prox;
    }
  	 printf("\n\t-----------------------------------------------------------------------------------------------------\t\n");
}

//Ler 
void ler(char f[], Lista *t) {
    FILE *file = fopen(f, "r");
    char text[20];

    if (file) {
        printf("\nTexto lido\n");
        while (fgets(text, 20, file)) {
            text[strcspn(text, "\n")] = '\0';  
            inserirTabela(t, text);
            printf("%s\n", text);
        }
        fclose(file);
    } else {
        printf("\nErro ao abrir o arquivo.\n");
    }
}

//Quicksort

int Igual(No *i,No* f){
    No *busca = i;
    while (busca != NULL){
        if(busca == f){
            return 1;
        }else{
            busca = busca ->prox;
        }
    } 
    return 0; 
}

int Menor(No *i,No* f){
    No *busca = i;
    while (busca != NULL){
        if(busca == f->ant){
            return 1;
        }else{
            busca = busca ->prox;
        }
    } 
    return 0; 
}

No* Meio(Lista *lista, No *inicio, No *fim){
	 if(lista->size != 0){
		int pivo = 0;
		int i;
        No *busca = inicio;
        while (busca != fim){
            pivo++;
            busca = busca -> prox;
        }
        pivo = pivo/2;
        busca = inicio;
        for(i = 0; i < pivo; i++) {
            busca = busca->prox;
        }
        return busca;
	}	
    return NULL;
}

void Trocar(No *i, No *f){
	char *aux = i->info;
	i->info = f->info;
	f->info = aux;	
}

void Quicksort(Lista *lista, No *inicio, No *fim){
	No *i = inicio;
	No *f = fim;
	No *pivo = Meio(lista, inicio, fim);
	char *InfoDoPivo = pivo ->info;
	
    while((i != NULL) && (f != NULL) && (Igual(i,f))){
	    
        while((i != NULL) && (pivo != NULL) && (strcmp(i->info, InfoDoPivo) < 0)){
		    i = i->prox;
	    }
	
	    while((f != NULL) && (pivo != NULL) && (strcmp(f->info, InfoDoPivo) > 0)){
		    f = f->ant;
	    }
	
	    if((i != NULL) && (f != NULL) && (Igual(i,f))){
		    Trocar(i,f);
		    i = i->prox;
		    f = f->ant;
	    }
    }
	
	if((inicio != NULL) && (f != NULL) && (Menor(inicio,f))) {
        Quicksort(lista, inicio, f);
    }
     if((i != NULL) && (fim != NULL) && (Menor(i,fim))){
        Quicksort(lista, i, fim);
    }
}


//Tabela Hash
void inicializarTabela(Lista t[]){
    int i;
    for(i = 0; i < TAM; i++){
        t[i] = *criaLista();
    }      
}

int funcaoHash(char info[]){
    int i, tam = strlen(info);
    int hash = 0;

    for ( i = 0; i < tam; i++){
        hash += info[i] *  (i + 1);
    }
     return hash % TAM;
}

void inserirTabela(Lista t[], char info[]){
    int i = funcaoHash(info);
    inserirNaLista(&t[i], info);
}

No *buscaTabela(Lista t[], char info[]){
    int i = funcaoHash(info);
    printf("\nIndice: %d\n", i);
    return buscaNo(&t[i], info);
}

void imprimirTabela(Lista t[]){
    int i;
    for(i = 0; i < TAM; i++){
        printf("\tIndice %d: ", i);
        ImprimeLista(&t[i]);
        printf("\n");
    }
}

void removerTabela(Lista t[], char info[]){
	No *no = buscaTabela(t, info);
	
	if (no != NULL){
		int i = funcaoHash(info);
		RemoverDaLista(&t[i],no);
		printf("Nome removido: %s\n", info);
	}else{
		printf("Nome n�o encontrado\n");
	}
	
}

void imprimirIndice (Lista t[], int i){
	if(i>=0 && i<TAM){
		printf("\tIndice %d: ", i);
		Quicksort(&t[i], t[i].head, t[i].tail);
		ImprimeLista(&t[i]);
		printf("\n");
	}else{
		printf("N�o foi possivel encontrar esse indice\n");
	}
}


int main(){

    int opcao;
    No *retorno;
    char info[20];
    Lista tabela[TAM];
    int i;

    inicializarTabela(tabela);
    char nome[] = "nomes.txt";
    
    do{
        printf("\n\t0 - Sair\n\t1 - Ler\n\t2 - Buscar\n\t3 - Imprimir\n\t4 - Remover\n\t5 - Ordenar chave\n");
        scanf("%d", &opcao);

        switch(opcao){
        case 1:
            printf("\tLer arquivo");
            ler(nome, tabela);
            break;
        case 2:
            printf("\tQual Nome deseja buscar? ");
            scanf("%s", info);
            retorno = buscaTabela(tabela, info);
            if(retorno != 0)
                printf("\tNome encontrado: %s\n", retorno->info);
            else
                printf("\tNome nao encontrado!\n");
            break;
        case 3:
            imprimirTabela(tabela);
            break;
        case 4:
    		printf("Qual nome deseja remover? ");
   	 		scanf("%s", info);
    		removerTabela(tabela, info);
    		break;
    	case 5:
    		printf("Qual chave deseja ordenar?");
    		scanf("%d", &i);
    		imprimirIndice(tabela, i);
    		break;
        default:
            printf("Opcao invalida!\n");
        }
    }while(opcao != 0);

    return 0;
}


