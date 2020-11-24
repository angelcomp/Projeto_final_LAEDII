#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kiss_sdl/kiss_sdl.h"

// Estruturas
struct no_lista { // Ocupa 10 bytes na simulação do João
	struct no_lista * ant;
	char * nome;
	struct no_lista * prox;
};

typedef struct {
	struct no_lista * inicio;
	struct no_lista * fim;
} lista;

struct no_fila {
	char * nome;
	struct no_fila *prox;
};

typedef struct {
	struct no_fila *inicio;
	struct no_fila *fim;
} fila;

// Enumerador que representa o identificador de cada tela
enum telas {
	TELA_SAIR,
	TELA_PRINCIPAL,

	TELA_CARDAPIO,
	TELA_PEDIDOS,

	TELA_VER_CARDAPIO,
	TELA_ADICIONAR_NO_CARDAPIO,
	TELA_REMOVER_DO_CARDAPIO,

	TELA_VER_PEDIDOS,
	TELA_ADICIONAR_NOS_PEDIDOS,
	TELA_SERVIR_PEDIDO
};

// Funções para a manipulação de listas
void lista_criar(lista *q);
int lista_inserir(lista *q, char novo_item[]);
void lista_mostrar(lista q);
int lista_estaVazia(lista q);
int lista_retirar_por_nome(lista *q, char *ptr_novo_nome);
int lista_retirar_por_posicao(lista *q, int indice);
void lista_esvaziar(lista *q);

// Funções para a manipulação de filas
void fila_criar(fila *q);
int fila_inserir(fila *q, char *ptr_nome);
int fila_retirar(fila *q, char receptor_nome[], int tamanho_buffer_receptor);
int lista_retirar_fila_por_posicao(fila *q, int indice);
int fila_estaVazia(fila q);
void fila_mostrar(fila q);
char * fila_inicio(fila q);
int fila_procurar(fila q, char busca[]);
void fila_esvaziar(fila *q);

// Funções do menu
void mostrarCardapio(lista c);
void mostrarPedidos(fila p);
void adicionarItemCardapio(lista *c);
void removerItemCardapio(lista *c);
void cadastrarPedido(fila *p, lista c);
void servirPedido(fila *p);

// Funções da tela
void tela_principal();
void tela_cardapio();
void tela_ver_cardapio();
void tela_adicionar_no_cardapio();
void tela_remover_do_cardapio();
void tela_pedidos();
void tela_ver_pedidos();
void tela_adicionar_nos_pedidos();
void tela_servir_pedido();

// Funções utilitárias
char * nova_string(char texto[]);
int obter_indice_combobox(kiss_combobox *combobox);
void chamar_prox_tela();

// Variáveis globais para o projeto todo, chamadas com 'extern'
int prox_tela;
lista cardapio;
fila pedidos;