#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "header.h"

void mostrarCardapio(lista c){
	struct no_lista *aux;
	int i = 1;
    if (c.inicio == NULL)
        printf("O cardapio está vazio...\n\n");
    else
    {
        printf("\nCardapio do Grande Restaurante da Tia Magali:\n");
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
        printf("Fila de pedidos vazia....\n");
    } else {
        while (aux != NULL)
        {
            printf("> Pedido %d: %s\n", contagem, aux->nome);
            aux = aux->prox;
        }
    }
}
void adicionarItemCardapio(lista *c){
    char *novo_item;
    int tam = 30;

    novo_item = (char *) malloc(sizeof(char) * tam);

    printf("\nDigite o item a ser adicionado no cardápio: ");
    fgets(novo_item,tam,stdin);
	novo_item[strlen(novo_item)-1] = '\0'; // Removendo o \n do final

    if(lista_inserir(c, novo_item))
    {
        printf("\nItem adicionado com sucesso!!\n");
    }
    else
    {
        printf("\nNão foi possível adicionar o item à lista\n");
    }
}
void removerItemCardapio(lista *c){
    struct no_lista *aux;
    int indice = 1, tam = 30, escolha, item;
    char nome_prato[tam];
    
    aux = c->inicio;
    
    if (aux == NULL)
    {
        printf("Cardápio está vazio!\n");
    } else {
        do {
            printf("Há duas maneiras para se retirar um item da lista:\n\t 1 - Por índice\n\t 2 - Por nome\n\n Qual você prefere?\n");
            scanf("%d", &escolha);
            getchar();
        
            switch (escolha) {
                case 1:
                    while (aux != NULL) {
                        printf("Item %d: %s\n", indice, aux->nome);
                        aux = aux->prox;
                        indice++;
                    }
                    printf("Qual desses itens você deseja remover da lista do Cardápio? ");
                    scanf("%d", &item);
                    getchar();

                    if (lista_retirar_por_posicao(c, item-1))
                    {
                        printf(" Opção retirada do cardápio com sucesso!\n");
                    } else {
                        printf(" * Não foi possível fazer a retirada desse item.. *\n");
                    }
                    break;

                case 2:
                    if (nome_prato == NULL)
                    {
                        printf(" * Erro ao tentar alocar uma nova string.. *\n");
                    } else {
                        printf("Escreva o nome do prato que está no cardápio para que possamos removê-lo: ");
                        fgets(nome_prato, tam, stdin);
						nome_prato[strlen(nome_prato)-1] = '\0'; // Removendo o \n do final

                        if (lista_retirar_por_nome(c, nome_prato))
                        {
                            printf(" Opção retirada do cardápio com sucesso!\n");
                        } else {
                            printf(" * Não foi possível fazer a retirada desse item... *\n");
                        }
                    }
                    break;

                default:
                    printf(" * Você escolheu uma opção inválida! *\n");
                    break;
            }
        } while (!(escolha == 1 || escolha == 2));
    }
}
void cadastrarPedido(fila *p){

}
void servirPedido(fila *p){

}