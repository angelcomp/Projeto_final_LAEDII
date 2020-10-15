#include <stdio.h>
#include <stdlib.h>
#include "header.h"

void criar(lista_sde *q) {
	q->inicio = NULL;
	q->fim = NULL;
}

// Inserção natural (sempre no final)
int inserir(lista_sde *q, char novo_item[]) {
	struct no *aux;
	char * alocacao_novo_item;

	alocacao_novo_item = alocar_nova_string(novo_item);
	if(alocacao_novo_item == NULL) {
		// Erro de alocação
		return 0;
	}

	aux = (struct no *) malloc(sizeof(struct no));
	if(aux == NULL) {
		// Erro de alocação
		return 0;
	}

	// Guardando o dado
	// Usamos igual apenas para transferir de um ponteiro para o outro
	aux->nome = alocacao_novo_item;

	// Lista vazia
	if(q->inicio == NULL) {

		// Adicionando na lista
		q->inicio = aux;
		q->fim = aux;

		// Fechando as pontas
		aux->prox = NULL;
		aux->ant = NULL;
	} else {
		// Ligando o último nó com o novo
		aux->ant = q->fim;
		q->fim->prox = aux;

		// Fechando as pontas
		aux->prox = NULL;

		// Atualizando o fim da lista
		q->fim = aux;

	}
	return 1;
}


// TODO: Corrigir esta função para funcionar com strings e 
// lista singularmente encandeada
void mostrar(lista_sde q) {
	struct no *aux;
	int contador = 1;

	if(q.inicio == NULL) {
		printf("Lista vazia. Nada pode ser mostrado.\n");
	} else {
		aux = q.inicio;
		while(aux != NULL) {
			printf("%d: %s\n", contador, aux->nome);				
			aux = aux->prox;
			contador++;
		}
	}
}

int estaVazia(lista_sde q) {
	return q.inicio == NULL;
}

// TODO: Corrigir esta função para funcionar com strings e 
// lista singularmente encandeada
/*int retirar_por_nome(lista_sde *q, int d) {
	struct no *aux;
	struct no *anterior;
	struct no *atual;

	if(q->inicio == NULL) {
		// Não é possível remover nada de uma lista vazia
		return 0;
	}

	// Remover o primeiro nó de uma lista unitária, mas cujo dado estiver presente
	else if(q->inicio == q->fim && d == q->inicio->dado) {
		aux = q->inicio; // Guardar o nó para desalocá-lo depois

		q->inicio = NULL;
		q->fim = NULL;

		free(aux);
	}
	// Remover o primeiro de uma lista não unitária
	else if(q->inicio != q->fim && d == q->inicio->dado) {
		aux = q->inicio;

		// Atualizando o início
		q->inicio = q->inicio->prox;

		// Ligando os nós de volta
		q->inicio->ant = q->fim;
		q->fim->prox = q->inicio;

		free(aux);
	}
	// Remover o último nó da lista
	else if(q->fim->dado == d) {
		aux = q->fim;

		// Redefinindo o fim
		q->fim = q->fim->ant;

		// Ligando os nós de volta
		q->fim->prox = q->inicio;
		q->inicio->ant = q->fim;

		free(aux);
	} else {
		// Remover um nó que está no meio da lista
		anterior = q->inicio;
		atual = anterior->prox;

		// Procurar nó a remover
		while(atual->dado != d) {
			if(atual == q->inicio) {
				// Voltamos ao início, o dado não foi encontrado
				return 0;
			}

			// Avançando as posições
			anterior = atual;
			atual = atual->prox;
		}
		// Laço encerrado, dado encontrado

		// Refazendo as ligações
		anterior->prox = atual->prox;
		atual->prox->ant = anterior;

		free(atual);
	}
	return 1;
}*/