#include "restaurante.h"

#define VOLTAR_AO_ADICIONAR_ITEM 0

extern int prox_tela;
extern fila pedidos;
extern lista cardapio;

//int indice_item_remover = -1;

void t05_button_confirmar_event(kiss_button *button, SDL_Event *e, kiss_combobox *cb, kiss_array *a, int *quit, int *draw);
void t05_button_voltar_event(kiss_button *button, SDL_Event *e, int *quit, int *draw);
static void t05_combobox_event(kiss_combobox *combobox, SDL_Event *e, int *draw);

void t05_preencher_cardapio(kiss_array *a);

void tela_adicionar_nos_pedidos(void) {
	/* Declaração de variáveis */
	SDL_Renderer *renderer;
	SDL_Event e;
	kiss_array objects;
	kiss_window window;

	kiss_label label_header = {0};
	kiss_combobox cb_seletor = {0};
	kiss_array seletor_itens = {0};
	kiss_button t05_button_confirmar = {0};
	kiss_button t05_button_voltar = {0};

	char txt_header[KISS_MAX_LENGTH];
	int cb_seletor_width;
	int cb_seletor_height;
	
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

	/* Criando o widget de entrada */
	kiss_array_new(&seletor_itens);
	kiss_array_append(&objects, ARRAY_TYPE, &seletor_itens);
	t05_preencher_cardapio(&seletor_itens);
	cb_seletor_width = window.rect.w/3;
	cb_seletor_height = window.rect.h/3;
	kiss_combobox_new(&cb_seletor, &window, "", &seletor_itens,
		1*window.rect.w / 2 - cb_seletor_width / 2,
		1*window.rect.h / 2,
		cb_seletor_width, cb_seletor_height);

	/* Criando o botão do Cardápio */
	kiss_button_new(&t05_button_confirmar, &window, "Confirmar",
		1*window.rect.w / 2 - kiss_normal.w / 2,
		15*window.rect.h / 20
	);
	/* Criando o botão dos Pedidos */
	kiss_button_new(&t05_button_voltar, &window, "Voltar",
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
			t05_button_confirmar_event(&t05_button_confirmar, &e, &cb_seletor, &seletor_itens, &quit, &draw);
			t05_button_voltar_event(&t05_button_voltar, &e, &quit, &draw);
			t05_combobox_event(&cb_seletor, &e, &draw);
		}

		kiss_combobox_event(&cb_seletor, NULL, &draw);

		if(!draw)
			continue;
		
		SDL_RenderClear(renderer); /* Limpando a tela */

		/* Desenhando os outros componentes */
		kiss_window_draw(&window, renderer);
		kiss_label_draw(&label_header, renderer);
		kiss_button_draw(&t05_button_confirmar, renderer);
		kiss_button_draw(&t05_button_voltar, renderer);
		kiss_combobox_draw(&cb_seletor, renderer);

		/* Renderizando as alterações */
		SDL_RenderPresent(renderer);

		draw = 0;
	}

	kiss_clean(&objects);
	
	chamar_prox_tela();
}

// Função que controla a combobox seletora
static void t05_combobox_event(kiss_combobox *combobox, SDL_Event *e, int *draw) {
	if (kiss_combobox_event(combobox, e, draw)) { // Se a ComboBox foi selecionada
		*draw = 1;
	}
}

// Função que efetiva a inserção
void t05_button_confirmar_event(kiss_button *button, SDL_Event *e, kiss_combobox *cb, kiss_array *a, int *quit, int *draw) {
	if(kiss_button_event(button, e, draw)) {
		if(obter_indice_combobox(cb) >= 0) {
			fila_inserir(&pedidos, nova_string(cb->entry.text));
			strcpy(cb->entry.text, "");
		}
	}
}

// Evento do botão que volta para a tela do cardápio
void t05_button_voltar_event(kiss_button *button, SDL_Event *e, int *quit, int *draw) {
	if(kiss_button_event(button, e, draw)) {
		prox_tela = TELA_PEDIDOS;
		*quit = 1;
	}
}

void t05_preencher_cardapio(kiss_array *a) {
	struct no_lista *aux;
	int i = 0;

	aux = cardapio.inicio;
	// Desalocando e recriando o vetor
	kiss_array_free(a);
	kiss_array_new(a);

	// Para cada posição na lista
	while(aux != NULL) {
		// Adicionar o valor ao kiss_array
		kiss_array_appendstring(a, i, aux->nome, NULL);
		aux = aux->prox;
		i++;
	}
}