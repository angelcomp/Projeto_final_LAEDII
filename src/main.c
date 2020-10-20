/*

*                        Ciencia da Computacao - PUC Pocos de Caldas

* Laboratório de Algoritmos e Estruturas de Dados II
* Professor: Claudio Correa
* 2º periodo

* Alunos: Angelica dos Santos
* 		  Lucas de Godoi Moraes
*		  Marcus Vinicius Ribeiro
*		  Rhian Luis Garcia Moraes

* Trabalho Final LAED II - Implementação de Estruturas de Dados Dinâmicas e Interface Gráfica
* Data entrega projeto: 01/12/2020

*       |~~~~~~~~~~~~~~~~~~~~~~~~~~~ E RECOMENDADO COMPILAR NO TERMINAL ~~~~~~~~~~~~~~~~~~~~~~~~~~~|

*       |  >>>>>>>> gcc -Wall lista.c fila.c utils.c opcoes_menu.c main.c -o restaurante <<<<<<<<  |

*       |~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|

*/

#include <stdio.h>

#include "header.h"

void funcao_teste() {
	lista lista;
	fila f;
	char nome_retirada[30];

	lista_criar(&lista);

	lista_inserir(&lista, nova_string("Teste"));
	lista_inserir(&lista, nova_string("123"));
	lista_inserir(&lista, nova_string("456"));
	lista_inserir(&lista, nova_string("Bob esponja"));

	lista_retirar_por_posicao(&lista, 2);


	if(!lista_estaVazia(lista)) {
		lista_mostrar(lista);
	}	 else {
		printf("A lista está vazia.\n");
	}

	lista_esvaziar(&lista);

	printf("\n");

	fila_criar(&f);

	fila_inserir(&f, nova_string("Hello, world!"));
	fila_inserir(&f, nova_string("Hello there!"));
	fila_inserir(&f, nova_string("General Kenobi!"));

	if(fila_retirar(&f, nome_retirada, 30))
		printf("Dado retirado = %s\n", nome_retirada);
	fila_mostrar(f);

	fila_esvaziar(&f);
}

int main(void) {
	lista cardapio;
	fila pedidos;
	int opcao;

	lista_criar(&cardapio);
	fila_criar(&pedidos);
	
	funcao_teste();

	printf("Bem-vindo ao restaurante da tia Magali!\n");
	do {
		printf("Opções:\n");
		printf("1. Mostrar cardápio\n");
		printf("2. Mostrar pedidos pendentes\n");
		printf("3. Adicionar item no cardápio\n");
		printf("4. Remover item do cardápio\n");
		printf("5. Cadastrar pedido\n");
		printf("6. Servir pedido\n");
		printf("0. Sair\n");
		printf("Digite: ");
		scanf("%d", &opcao);
		getchar();

		switch(opcao) {
			case 0:
				printf("Tchauzinho e até mais!\n");
				break;
			case 1:
				mostrarCardapio(cardapio);
				break;
			case 2:
				mostrarPedidos(pedidos);
				break;
			case 3:
				adicionarItemCardapio(&cardapio);
				break;
			case 4:
				removerItemCardapio(&cardapio);
				break;
			case 5:
				cadastrarPedido(&pedidos);
				break;
			case 6:
				servirPedido(&pedidos);
				break;
			case 7:
			default:
				printf("Opção inválida.\n");
		}
		if(opcao) {
			printf("Digite enter para continuar.");
			getchar();
		}
	} while(opcao);

	return 0;
}