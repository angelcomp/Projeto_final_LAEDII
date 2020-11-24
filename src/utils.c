#include "restaurante.h"

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

void chamar_prox_tela() {
	switch(prox_tela) {
		case TELA_PRINCIPAL:
			tela_principal();
			break;
		case TELA_CARDAPIO:
			tela_cardapio();
			break;
		case TELA_PEDIDOS:
			tela_pedidos();
			break;
		case TELA_VER_CARDAPIO:
			tela_ver_cardapio();
			break;
		case TELA_ADICIONAR_NO_CARDAPIO:
			tela_adicionar_no_cardapio();
			break;
		case TELA_REMOVER_DO_CARDAPIO:
			tela_remover_do_cardapio();
			break;
		case TELA_VER_PEDIDOS:
			tela_ver_pedidos();
			break;
		case TELA_ADICIONAR_NOS_PEDIDOS:
			tela_adicionar_nos_pedidos();
			break;
		case TELA_SERVIR_PEDIDO:
			tela_servir_pedido();
			break;
		case TELA_SAIR:
			fila_esvaziar(&pedidos);
			lista_esvaziar(&cardapio);
			break;
		default:
			break;
	}
}

int obter_indice_combobox(kiss_combobox *combobox) {
	int i;
	int indice_final = -1; // Índice da string na ComboBox. -1 significa inexistente
	char *str_pesquisa = combobox->entry.text; // String que está escrita na Entry da ComboBox
	void ** dado_original = combobox->textbox.array->data; // Ponteiro para lembrar a posição inicial do ponteiro de dados
	char *str_dado_atual; // String que guarda o dado que está na string em um dado índice

	for(i = 0; i < combobox->textbox.array->length; i++) {
		str_dado_atual = (char *) *combobox->textbox.array->data;
		
		// Se o dado for encontrado
		if(!strcmp(str_pesquisa, str_dado_atual)) {
			indice_final = i; // Definir o índice como i
		}
		combobox->textbox.array->data++; // Passar para a próxima versão do ponteiro de dados
	}

	combobox->textbox.array->data = dado_original; // Voltando o ponteiro à posição inicial
	return indice_final;
}