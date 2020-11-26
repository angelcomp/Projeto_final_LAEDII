/*

*                        Ciencia da Computacao - PUC Pocos de Caldas

* Laboratório de Algoritmos e Estruturas de Dados II
* Professor: Claudio Correa
* 2º periodo

* Alunos: Angelica dos Santos
* 		  Lucas de Godoi Moraes
*		  Marcus Vinicius Ribeiro
*		  Rhian Luis Garcia Moraes

* Trabalho Final LAED II - Implementação de Estruturas de Dados Dinâmicas e Interface Gráfica
* Data entrega projeto: 01/12/2020
*/

#include "restaurante.h"

extern int prox_tela;
extern fila pedidos;
extern lista cardapio;

void button_cardapio_event(kiss_button *button, SDL_Event *e, int *quit, int *draw);
void button_pedidos_event(kiss_button *button, SDL_Event *e, int *quit, int *draw);
void chamar_prox_tela();

int main(void) {
	lista_criar(&cardapio);
	fila_criar(&pedidos);
	
	prox_tela = TELA_PRINCIPAL;

	chamar_prox_tela();

	return 0;
}

void tela_principal(void) {
	/* Declaração de variáveis */
	SDL_Renderer *renderer;
	SDL_Event e;
	kiss_array objects;
	kiss_window window;

	kiss_label label_titulo = {0};
	kiss_label label_nomes_autores = {0};
	kiss_button button_cardapio = {0};
	kiss_button button_pedidos = {0};

	char txt_titulo[KISS_MAX_LENGTH];
	char txt_autores[KISS_MAX_LENGTH];
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
	strcpy(txt_titulo, "Seja bem-vindo ao restaurante da tia Magali!");
	kiss_label_new(&label_titulo, &window, txt_titulo,
		window.rect.w / 2 - strlen(txt_titulo) * kiss_textfont.advance / 2,
		window.rect.h / 4 - (kiss_textfont.fontheight + 2 * kiss_normal.h / 2)
	);
	label_titulo.textcolor.r = 255;

	/* Nomes autores */
	strcpy(txt_autores, "Autores: Angelica, Lucas Godoi, Marcus, Rhian");
	kiss_label_new(&label_nomes_autores, &window, txt_autores,
		window.rect.w / 2 - strlen(txt_autores) * kiss_textfont.advance / 2,
		49 * window.rect.h /50 - (kiss_textfont.fontheight + 2 * kiss_normal.h / 2)
	);
	label_nomes_autores.textcolor.b = 255;

	/* Criando o botão do Cardápio */
	kiss_button_new(&button_cardapio, &window, "Cardápio",
		1*window.rect.w / 3 - kiss_normal.w / 2,
		window.rect.h / 2
	);
	/* Criando o botão dos Pedidos */
	kiss_button_new(&button_pedidos, &window, "Pedidos",
		2*window.rect.w / 3 - kiss_normal.w / 2,
		window.rect.h / 2
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
			button_cardapio_event(&button_cardapio, &e, &quit, &draw);
			button_pedidos_event(&button_pedidos, &e, &quit, &draw);
		}

		if(!draw)
			continue;
		
		SDL_RenderClear(renderer); /* Limpando a tela */

		/* Desenhando os outros componentes */
		kiss_window_draw(&window, renderer);
		kiss_label_draw(&label_titulo, renderer);
		kiss_label_draw(&label_nomes_autores, renderer);
		kiss_button_draw(&button_cardapio, renderer);
		kiss_button_draw(&button_pedidos, renderer);

		/* Renderizando as alterações */
		SDL_RenderPresent(renderer);

		draw = 0;
	}

	kiss_clean(&objects);
	
	chamar_prox_tela();
}

void button_cardapio_event(kiss_button *button, SDL_Event *e, int *quit, int *draw) {
	if(kiss_button_event(button, e, draw)) {
		prox_tela = TELA_CARDAPIO;
		*quit = 1;
	}
}
void button_pedidos_event(kiss_button *button, SDL_Event *e, int *quit, int *draw) {
	if(kiss_button_event(button, e, draw)) {
		prox_tela = TELA_PEDIDOS;
		*quit = 1;
	}
}