#include "restaurante.h"

void fila_criar(fila *q) {
	q->inicio = NULL;
	q->fim = NULL;
}

int fila_inserir(fila *q, char *ptr_nome) {
	struct no_fila *aux;

	aux = (struct no_fila *) malloc(sizeof(struct no_fila *));

	// Erro de alocação
	if (aux == NULL) {
		return 0;
	}

	aux->nome = ptr_nome; // Aqui atribuímos como uma simples passagem de ponteiros
	aux->prox = NULL; // O nó ainda não foi adicionado à fila

	if(q->inicio == NULL) {
		q->inicio = aux;
		q->fim = aux;
	} else {
		q->fim->prox = aux; // Efetuando a ligação
		q->fim = aux; // Atualizando o ponteiro de fim da fila
	}

	return 1;
}

int fila_retirar(fila *q, char receptor_nome[], int tamanho_buffer_receptor) {
	struct no_fila *aux;

	if(q->inicio == NULL) {
		// A fila está vazia. Nada pode ser retirado
		return 0;
	}

	aux = q->inicio;

	// Checando se foi passado NULL. se for o caso, não será
	// possível atribuir o nome
	if(tamanho_buffer_receptor > 0) {

		// Se o buffer for muito pequeno, gere um erro
		if((strlen(aux->nome) + 1) > tamanho_buffer_receptor) {
			return 0;
		}
		// Se o valor cabe na variável, atribua ele
		strcpy(receptor_nome, aux->nome);
	}

	// Passando para o próximo da fila
	q->inicio = aux->prox;

	// Desalocando o nó
	free(aux->nome);
	free(aux);

	// Se a fila acabar ficando vazia, é importante deixar
	// ambos ponteiros observadores como NULL
	if(q->inicio == NULL) {
		q->fim = NULL;
	}

	return 1;
}

int fila_estaVazia(fila q) {
	if(q.inicio == NULL) {
		return 1;
	}
	return 0;
}

void fila_mostrar(fila q) {
	struct no_fila *aux;
	int contador = 1;

	if(q.inicio == NULL) {
		printf("A fila está vazia.\n");
	} else {
		printf("Mostrando os dados da fila:\n");
		aux = q.inicio;
		while(aux != NULL) {
			printf("%d: %s\n", contador, aux->nome);
			aux = aux->prox;
			contador++;
		}
	}
}

char * fila_inicio(fila q) {
	if(q.inicio != NULL) {
		return q.inicio->nome;
	}
	return NULL;
}

int fila_procurar(fila q, char busca[]) {
	struct no_fila *aux;
	aux = q.inicio;

	if(q.inicio == NULL) {
		return 0;
	}

	while(aux != NULL) {
		if(strcmp(aux->nome, busca) == 0) {
			return 1;
		}

		aux = aux->prox;
	}

	return 0;
}

void fila_esvaziar(fila *q) {
	while(!fila_estaVazia(*q)) {
		fila_retirar(q, NULL, 0);
	}
}