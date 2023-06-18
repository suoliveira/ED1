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
void inserirTabela(Lista[], char[]);


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
    //printf("\n****Lista: ");
    printf("TAM: %d ", lista->size);
    while (a != NULL) {
        printf("%s ", a->info);
        a = a->prox;
    }
  	 printf("****\n");
}

//Ler 
void ler(char f[], Lista *t) {
    FILE *file = fopen(f, "r");
    char text[20];

    if (file) {
        printf("\nTexto lido\n");
        while (fgets(text, 20, file)) {
            text[strcspn(text, "\n")] = '\0';  // Remove a nova linha (\n)
            inserirTabela(t, text);
            printf("%s\n", text);
        }
        fclose(file);
    } else {
        printf("\nErro ao abrir o arquivo.\n");
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
    printf("\nIndice gerada: %d\n", i);
    return buscaNo(&t[i], info);
}

void imprimirTabela(Lista t[]){
    int i;
    for(i = 0; i < TAM; i++){
        printf("\tChave %d: ", i);
        ImprimeLista(&t[i]);
        printf("\n");
    }
}




       
int main(){

    int opcao;
    No *retorno;
    char info[20];
    Lista tabela[TAM];

    inicializarTabela(tabela);
    char nome[] = "nomes.txt";
    

    do{
        printf("\n\t0 - Sair\n\t1 - Ler\n\t2 - Buscar\n\t3 -Imprimir\n");
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
        default:
            printf("Opcao invalida!\n");
        }
    }while(opcao != 0);

    return 0;
}





