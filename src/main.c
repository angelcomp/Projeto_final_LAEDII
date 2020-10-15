/* Compilado com:
gcc -Wall lista.c utils.c main.c -o restaurante; ./restaurante
*/

#include <stdio.h>
#include "header.h"

int main(void) {
	lista_sde lista;

	criar(&lista);

	inserir(&lista, "Teste");
	inserir(&lista, "123");
	inserir(&lista, "456");
	inserir(&lista, "Bob esponja");

	// retirar(&lista, 10);

	if(!estaVazia(lista)) {
		mostrar(lista);
	}	 else {
		printf("A lista está vazia.\n");
	}

	return 0;

	return 0;
}