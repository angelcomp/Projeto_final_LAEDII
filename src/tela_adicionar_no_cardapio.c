#include "restaurante.h"

#define VOLTAR_AO_ADICIONAR_ITEM 0

extern int prox_tela;
extern fila pedidos;
extern lista cardapio;

int itens_adicionados = 0;

void t07_button_confirmar_event(kiss_button *button, SDL_Event *e, kiss_entry *entry, kiss_label *label_contador, int *quit, int *draw);
void t07_button_voltar_event(kiss_button *button, SDL_Event *e, int *quit, int *draw);
void atualizar_label_itens_adicionados(kiss_label *label_contador);

void tela_adicionar_no_cardapio(void) {
	/* Declaração de variáveis */
	SDL_Renderer *renderer;
	SDL_Event e;
	kiss_array objects;
	kiss_window window;

	kiss_label label_header = {0};
	kiss_label label_contador = {0};
	kiss_entry entry_novo_item = {0};
	kiss_button t07_button_confirmar = {0};
	kiss_button t07_button_voltar = {0};

	char txt_header[KISS_MAX_LENGTH];
	int entrada_novo_item_width;
	
	int draw, quit;


	quit = 0;
	draw = 1;

	/* Inicializando o KISS e o vetor de objetos */
	kiss_array_new(&objects);
	renderer = kiss_init("Restaurante da Tia Magali", &objects, 480, 360);

	if(!renderer) {
		return;
	}

	/* Inicializando a janela */
	kiss_window_new(&window, NULL, 0, 0, 0, kiss_screen_width, kiss_screen_height);

	/* Criando a label centralizada com a janela */
	strcpy(txt_header, "Digite o nome do item que deseja adicionar:");
	kiss_label_new(&label_header, &window, txt_header,
		window.rect.w / 2 - strlen(txt_header) * kiss_textfont.advance / 2,
		window.rect.h / 4 - (kiss_textfont.fontheight + 2 * kiss_normal.h / 2)
	);
	label_header.textcolor.r = 255;
	
	/* Criando a label que mostra quantas entradas o usuário adicionou */
	kiss_label_new(&label_contador, &window, "",
		0,
		3*window.rect.h / 8 - (kiss_textfont.fontheight + 2 * kiss_normal.h / 2)
	);
	label_contador.textcolor.b = 128;

	/* Criando o widget de entrada */
	entrada_novo_item_width = window.rect.w/3;
	kiss_entry_new(&entry_novo_item, &window, 1, "",
		1*window.rect.w / 2 - entrada_novo_item_width / 2,
		1*window.rect.h / 2,
		entrada_novo_item_width
	);
	entry_novo_item.visible = 1;

	/* Criando o botão do Cardápio */
	kiss_button_new(&t07_button_confirmar, &window, "Confirmar",
		1*window.rect.w / 2 - kiss_normal.w / 2,
		15*window.rect.h / 20
	);
	/* Criando o botão dos Pedidos */
	kiss_button_new(&t07_button_voltar, &window, "Voltar",
		1*window.rect.w / 2 - kiss_normal.w / 2,
		17*window.rect.h / 20
	);

	/* Fazendo com que a janela seja visível */
	window.visible = 1;
	/* Loop principal */
	while(!quit) {
		SDL_Delay(10);
		/* Passando pela lista de eventos */
		while(SDL_PollEvent(&e)) {
			if(e.type == SDL_QUIT) { // Usuário clicou no X da janela
				quit = 1;
				prox_tela = TELA_SAIR;
			}

			/* Processando eventos da janela e do botão */
			kiss_window_event(&window, &e, &draw);
			t07_button_confirmar_event(&t07_button_confirmar, &e, &entry_novo_item, &label_contador, &quit, &draw);
			t07_button_voltar_event(&t07_button_voltar, &e, &quit, &draw);
			kiss_entry_event(&entry_novo_item, &e, &draw);
		}

		if(!draw)
			continue;
		
		SDL_RenderClear(renderer); /* Limpando a tela */

		/* Desenhando os outros componentes */
		kiss_window_draw(&window, renderer);
		kiss_label_draw(&label_header, renderer);
		kiss_label_draw(&label_contador, renderer);
		kiss_button_draw(&t07_button_confirmar, renderer);
		kiss_button_draw(&t07_button_voltar, renderer);
		kiss_entry_draw(&entry_novo_item, renderer);

		/* Renderizando as alterações */
		SDL_RenderPresent(renderer);

		draw = 0;
	}

	kiss_clean(&objects);
	
	chamar_prox_tela();
}

// Função que efetiva a inserção
void t07_button_confirmar_event(kiss_button *button, SDL_Event *e, kiss_entry *entry, kiss_label *label_contador, int *quit, int *draw) {
	char *novo_item;

	if(kiss_button_event(button, e, draw) && (strcmp(entry->text, ""))) {
		novo_item = nova_string(entry->text); // Alocando uma nova string com base no que o usuário escreveu

		lista_inserir(&cardapio, novo_item); // Inserindo na lista

		// Definindo o comportamento após a inserção
		if(VOLTAR_AO_ADICIONAR_ITEM) {
			prox_tela = TELA_CARDAPIO;
			*quit = 1;
		} else {
			strcpy(entry->text, ""); // Apagando o texto da entrada
		}

		itens_adicionados++;
		atualizar_label_itens_adicionados(label_contador);
	}
}

// Evento do botão que volta para a tela do cardápio
void t07_button_voltar_event(kiss_button *button, SDL_Event *e, int *quit, int *draw) {
	if(kiss_button_event(button, e, draw)) {
		prox_tela = TELA_CARDAPIO;
		*quit = 1;
	}
}
void atualizar_label_itens_adicionados(kiss_label *label_contador) {
	// Atualizando o texto da label
	if(itens_adicionados == 1) {
		strcpy(label_contador->text, "1 item foi adicionado até agora!");
	} else {
		sprintf(label_contador->text, "%d itens foram adicionados até agora!", itens_adicionados);
	}

	// Atualizando sua posição horiziontal para refletir o tamanho da nova string
	label_contador->rect.x = (label_contador->wdw->rect.w) / 2 - strlen(label_contador->text) * kiss_textfont.advance / 2;
}