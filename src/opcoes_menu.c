#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "header.h"

void mostrarCardapio(lista c)
{
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
        }
        while (aux != NULL);  //enquanto nao chegar no aux->prox == NULL, continuar o programa.
    }
}
void mostrarPedidos(fila p)
{
    struct no_fila *aux;
    int contagem = 0;
    aux = p.inicio;

    if (aux == NULL)
    {
        printf("\nFila de pedidos vazia....\n\n");
    }
    else
    {
        while (aux != NULL)
        {
            printf("\n > Pedido %d: %s", contagem, aux->nome);
            aux = aux->prox;
            contagem++;
        }
    }
}
void adicionarItemCardapio(lista *c)
{

}
void removerItemCardapio(lista *c)
{

}
void cadastrarPedido(fila *p, lista c)
{
    char *nome_pedido;
    int item, i;
    struct no_lista *aux;

    mostrarCardapio(c);
    printf("\nEscolha o numero do que deseja: ");
    scanf("%d", &item);

    if(item<=0)
    {
        printf("\nCodigo invalido!\n");
        return;
    }
    aux = c.inicio;
    /*i=0;
    while(aux!=NULL && i<item-1)
    {
        printf("\n%d\n",i);
        aux = aux->prox;
        i++;
    }
    if(i==0 && aux == NULL)
    {
        printf("\nNao e possivel servir nada de um cardapio vazio!\n");
        return;
    }
    if(i!=item-1)
    {
        printf("\nERRO! Este valor e muito grande!\n");\
        return;
    }*/
    i=1;
    while(aux!=NULL && i<item)
    {
        printf("\n%d\n",i);
        if(aux->prox == NULL){
            printf("\nERRO! Este valor e muito grande!\n");
            return;
        }
        aux = aux->prox;
        i++;
    }
    if(i==1 && aux == NULL)
    {
        printf("\nNao e possivel servir nada de um cardapio vazio!\n");
        return;
    }
    if(i!=item)
    {
        printf("\nERRO! Este valor e muito grande!\n");
        return;
    }
    nome_pedido = nova_string(aux->nome);
    printf("%s\n",nome_pedido);

    fila_inserir(p,nome_pedido);
}
void servirPedido(fila *p)
{

}
//Erro de compilacao no CodeBlocks(Marcus): c:\program files (x86)\codeblocks\mingw\bin\..\lib\gcc\mingw32\4.4.1\..\..\..\libSDL2main.a(SDL_windows_main.o):SDL_windows_main.c||
//mensagem do erro: undefined reference to `SDL_main'|
