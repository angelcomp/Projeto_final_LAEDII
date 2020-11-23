#include "restaurante.h"

void lista_criar(lista *q) {
	q->inicio = NULL;
	q->fim = NULL;
}

// Inserção natural (sempre no final)
int lista_inserir(lista *q, char *ptr_novo_nome) {
	struct no_lista *aux;

	if(ptr_novo_nome == NULL) {
		// String inválida, erro de alocação
		return 0;
	}

	aux = (struct no_lista *) malloc(sizeof(struct no_lista));
	if(aux == NULL) {
		// Erro de alocação
		return 0;
	}

	// Guardando o nome, que é um ponteiro para uma string já alocada no heap.
	// Usamos 'igual' apenas para transferir de um ponteiro para o outro
	aux->nome = ptr_novo_nome;

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

void lista_mostrar(lista q) {
	struct no_lista *aux;
	int contador = 1;

	if(q.inicio == NULL) {
		printf("Lista vazia. Nada pode ser mostrado.\n");
	} else {
		aux = q.inicio;
		while(aux != NULL) {
			// printf("DEBUG: i%d: %s. aux = %ld, ant = %ld, prox = %ld\n", contador-1, aux->nome, (long int) (aux) %25, (long int) (aux->ant) %25, (long int) (aux->prox) %25);

			printf("%d: %s\n", contador, aux->nome);
			aux = aux->prox;
			contador++;
		}
	}
}

int lista_estaVazia(lista q) {
	return q.inicio == NULL;
}

int lista_retirar_por_nome(lista *q, char busca[]) {
	struct no_lista *aux;
	struct no_lista *anterior;
	struct no_lista *atual;

	if(q->inicio == NULL) {
		// Não é possível remover nada de uma lista vazia
		return 0;
	}

	// Remover o primeiro nó de uma lista unitária, mas cujo nome buscado estiver presente
	if(q->inicio == q->fim && strcmp(busca, q->inicio->nome) == 0) {
		aux = q->inicio; // Guardar o nó para desalocá-lo depois

		q->inicio = NULL;
		q->fim = NULL;

		free(aux->nome); // Desalocando a string nome
		free(aux);
	}
	// Remover o primeiro nó de uma lista não unitária
	else if(q->inicio != q->fim && strcmp(busca, q->inicio->nome) == 0) {
		aux = q->inicio;

		// Atualizando o início
		q->inicio = q->inicio->prox;
		q->inicio->ant = NULL;

		free(aux->nome); // Desalocando a string nome
		free(aux);
	}
	// Remover o último nó da lista
	else if(strcmp(busca, q->fim->nome) == 0) {
		aux = q->fim;

		// Redefinindo o fim
		q->fim = q->fim->ant;
		q->fim->prox = NULL;

		free(aux->nome); // Desalocando a string nome
		free(aux);
	} else {
		// Remover um nó que está no meio da lista
		anterior = q->inicio;
		atual = anterior->prox;

		// Procurar nó a remover, começando do nó que está após o início
		while(strcmp(busca, atual->nome) != 0) {
			// Avançando as posições
			anterior = atual;
			atual = atual->prox;

			// Chegamos ao fim da lista sem encontrar o nó
			if(atual == NULL) {
				return 0;
			}
		}
		// Laço encerrado, dado encontrado

		// Refazendo as ligações
		anterior->prox = atual->prox;
		atual->prox->ant = anterior;

		free(atual->nome); // Desalocando a string nome
		free(atual);
	}
	return 1;
}

int lista_retirar_por_posicao(lista *q, int indice) {
	struct no_lista *aux;
	int i;
	aux = q->inicio;

	if(q->inicio == NULL || indice < 0) {
		// Lista vazia, nada pode ser removido
		// ou o índice é automaticamente inválido
		return 0;
	}
	
	// Obtendo o nó a ser removido e retirando
	for(i = 0; i < indice; i++) {
		aux = aux->prox;

		// Se o indice for maior do que o número de itens na lista
		if(aux == NULL) {
			// Erro
			return 0;
		}
	}

	// Caso a lista seja unitária
	if(q->inicio == q->fim) {
		q->inicio = NULL;
		q->fim = NULL;

	// Lista não unitária, mas removendo do início
	} else if(aux == q->inicio) {
		q->inicio = aux->prox;
		q->inicio->ant = NULL;

	// Lista não unitária, mas removendo do final
	} else if(aux == q->fim) {
		q->fim = aux->ant;
		q->fim->prox = NULL;
	
	// Remover do meio da lista
	} else {
		// Ligando os nó anterior e posterior a este
		aux->ant->prox = aux->prox;
		aux->prox->ant = aux->ant;
	}

	// Desalocando, por fim, o nó
	free(aux->nome); // Desalocando a string nome
	free(aux);
	return 1;
}

void lista_esvaziar(lista *q) {
	while(!lista_estaVazia(*q)) {
		lista_retirar_por_posicao(q, 0);
	}
}