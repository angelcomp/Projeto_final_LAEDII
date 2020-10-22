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
void adicionarItemCardapio(lista *c){
    char *novo_item;
    int tam = 30;

    novo_item = (char *) malloc(sizeof(char) * tam);

    printf("\nDigite o item a ser adicionado no card�pio: ");
    fgets(novo_item,tam,stdin);

    if(lista_inserir(c, novo_item))
    {
        printf("\nItem adicionado com sucesso!!\n");
    }
    else
    {
        printf("\nN�o foi poss�vel adicionar o item � lista\n");
    }
}
void removerItemCardapio(lista *c){
    struct no_lista *aux;
    int indice = 1, tam = 30, escolha, item;
    char nome_prato[tam];
    
    aux = c->inicio;
    
    if (aux == NULL)
    {
        printf("\n Cardápio está vazio!\n");
    } else {
        do {
            printf("\nHá duas maneiras para se retirar um item da lista:\n\t 1 - Por índice\n\t 2 - Por nome\n\n Qual você prefere?");
            scanf("%d", &escolha);
            getchar();
        
            switch (escolha) {
                case 1:
                    while (aux != NULL) {
                        printf("\nItem %d: %s", indice, aux->nome);
                        aux = aux->prox;
                        indice++;
                    }
                    printf("\nQual desses itens você deseja remover da lista do Cardápio?");
                    scanf("%d", &item);
                    getchar();

                    if (lista_retirar_por_posicao(c, item-1))
                    {
                        printf("\n Opção retirada do cardápio com sucesso!");
                    } else {
                        printf("\n * Não foi possível fazer a retirada desse item.. *");
                    }
                    break;

                case 2:
                    if (nome_prato == NULL)
                    {
                        printf("\n * Erro ao tentar alocar uma nova string.. *");
                    } else {
                        printf("\nEscreva o nome do prato que está no cardápio para que possamos removê-lo: ");
                        fgets(nome_prato, tam, stdin);
						nome_prato[strlen(nome_prato)-1] = '\0'; // Removendo o \n do final
						printf("'%s'\n", nome_prato);

                        if (lista_retirar_por_nome(c, nome_prato))
                        {
                            printf("\n Opção retirada do cardápio com sucesso!");
                        } else {
                            printf("\n * Não foi possível fazer a retirada desse item.. *");
                        }
                    }
                    break;

                default:
                    printf("\n * você escolheu uma opção inválida! *");
                    break;
            }
        } while (!(escolha == 1 || escolha == 2));
    }
}
void cadastrarPedido(fila *p){

}
void servirPedido(fila *p){

}
//Erro de compilacao no CodeBlocks(Marcus): c:\program files (x86)\codeblocks\mingw\bin\..\lib\gcc\mingw32\4.4.1\..\..\..\libSDL2main.a(SDL_windows_main.o):SDL_windows_main.c||
//mensagem do erro: undefined reference to `SDL_main'|
