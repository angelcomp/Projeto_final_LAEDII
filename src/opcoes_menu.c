#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "header.h"

void mostrarCardapio(lista c){
	
}
void mostrarPedidos(fila p){
    struct no_fila *aux;
    aux = p.inicio;

    if (aux == NULL) {
        printf("\nFila de pedidos vazia....\n\n");
    } else {
        while (aux != NULL)
        {
            printf("\n%s", aux->nome);
            aux = aux->prox;
        }
    }
}
void adicionarItemCardapio(lista *c){

}
void removerItemCardapio(lista *c){

}
void cadastrarPedido(fila *p){

}
void servirPedido(fila *p){

}