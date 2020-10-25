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

int main(void) {
	lista cardapio;
	fila pedidos;
	int opcao;

	lista_criar(&cardapio);
	fila_criar(&pedidos);


	/*lista_inserir(&cardapio, nova_string("Banana"));
	lista_inserir(&cardapio, nova_string("Uva"));
	lista_inserir(&cardapio, nova_string("Goiaba"));*/
	//Este trecho serve para testar na hora de enviar um pedido para a fila, mostrar cardapio, etc...

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
				cadastrarPedido(&pedidos, cardapio);
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

