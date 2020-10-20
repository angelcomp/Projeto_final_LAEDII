#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "header.h"

void mostrarCardapio(lista c){
	struct no_lista *aux;
	int i;
    if (c.inicio == NULL)
        printf("Cardapio vazio. . .\n\n");
    else
    {
        printf("\nCardapio Grande Restaurante da Tia Magali:\n");
        aux = c.inicio;
        do
        {
            printf("Item %d: %d ", i, aux->nome);
            aux = aux->prox;
            i++;
        } while (aux != NULL);//enquanto nao chegar no aux->prox == NULL, continuar o programa.
    }
}
void mostrarPedidos(fila p){

}
void adicionarItemCardapio(lista *c){

}
void removerItemCardapio(lista *c){

}
void cadastrarPedido(fila *p){

}
void servirPedido(fila *p){

}
//Erro de compilacao no CodeBlocks(Marcus): c:\program files (x86)\codeblocks\mingw\bin\..\lib\gcc\mingw32\4.4.1\..\..\..\libSDL2main.a(SDL_windows_main.o):SDL_windows_main.c||
//mensagem do erro: undefined reference to `SDL_main'|
