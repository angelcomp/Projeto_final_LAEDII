#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "header.h"

void mostrarCardapio(lista c){
	struct no_lista *aux;
	int i = 1;
    if (c.inicio == NULL)
        printf("Cardapio vazio. . .\n\n");
    else
    {
        printf("\nCardapio Grande Restaurante da Tia Magali:\n");
        aux = c.inicio;
        do
        {
            printf("Item %d: %s\n", i, aux->nome);
            aux = aux->prox;
            i++;
        } while (aux != NULL);//enquanto nao chegar no aux->prox == NULL, continuar o programa.
    }
}
void mostrarPedidos(fila p){
    struct no_fila *aux;
    int contagem = 0;
    aux = p.inicio;

    if (aux == NULL) {
        printf("\nFila de pedidos vazia....\n\n");
    } else {
        while (aux != NULL)
        {
            printf("\n > Pedido %d: %s", contagem, aux->nome);
            aux = aux->prox;
        }
    }
}
int adicionarItemCardapio(lista *c){
    char *var;
    int tam = 30;

    struct no_lista *aux;

    var = (char *) malloc(sizeof(char) * tam);
    aux = (struct no_lista *) malloc(sizeof(struct no_lista *));

    if(var == NULL)
    {
        return 0;
    }
    if(aux == NULL)
    {
        return 0;
    }

    printf("\nDigite o item a ser adicionado ao cardapio: ");
    fgets(var,tam,stdin);

    aux->nome = var;

    if(c->inicio == NULL)
    {
        c->inicio = aux;
        c->fim = aux;
        aux->prox = NULL;
        aux->ant = NULL;
    }
    else
    {
        aux->ant = c->fim;
		c->fim->prox = aux;
		aux->prox = c->inicio;
		c->inicio->ant = aux;
		c->fim = aux;
		aux->prox=NULL;
    }
    return 1;

}
void removerItemCardapio(lista *c){

}
void cadastrarPedido(fila *p){

}
void servirPedido(fila *p){

}
//Erro de compilacao no CodeBlocks(Marcus): c:\program files (x86)\codeblocks\mingw\bin\..\lib\gcc\mingw32\4.4.1\..\..\..\libSDL2main.a(SDL_windows_main.o):SDL_windows_main.c||
//mensagem do erro: undefined reference to `SDL_main'|
