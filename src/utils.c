#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "header.h"

char * nova_string(char texto[]) {
	// Alocando uma nova string do tamanho exato do parâmetro texto
	// Isso é necessário para que a string não seja desalocada sem nosso controle
	char * nova_str = (char *) malloc(sizeof(char) * (strlen(texto) + 1));

	// Copiando a string que o usuário passou para essa nova string
	if(nova_str != NULL) {
		strcpy(nova_str, texto);
	}

	return nova_str;
}