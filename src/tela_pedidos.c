#include "restaurante.h"

extern int prox_tela;
extern fila pedidos;
extern lista cardapio;

void t02_button_ver_pedidos_event(kiss_button *button, SDL_Event *e, int *quit, int *draw);
void t02_button_add_pedido_event(kiss_button *buton, SDL_Event *e, int *quit, int *draw);
void t02_button_servir_pedido_event(kiss_button *button, SDL_Event *e, int *quit, int *draw);
void t02_button_voltar_event(kiss_button *button, SDL_Event *e, int *quit, int *draw);

void tela_pedidos(void)
{
	/* Declaração de variáveis */
	SDL_Renderer *renderer;
	SDL_Event e;
	kiss_array objects;
	kiss_window window;
	kiss_label label_titulo = {0};
	kiss_button t02_button_ver_pedidos = {0},
				t02_button_add_pedido = {0},
				t02_button_servir_pedido = {0},
				t02_button_voltar = {0};
	char txt_titulo[KISS_MAX_LENGTH];
	int draw, quit;

	quit = 0;
	draw = 1;

	/* Inicializando o KISS e o vetor de objetos */
	kiss_array_new(&objects);
	renderer = kiss_init("Restaurante da Tia Magali", &objects, 480, 360);

	if (!renderer)
	{
		return;
	}

	/* Inicializando a janela */
	kiss_window_new(&window, NULL, 0, 0, 0, kiss_screen_width, kiss_screen_height);

	/* Criando a label centralizada com a janela */
	strcpy(txt_titulo, "Pedidos");
	kiss_label_new(&label_titulo, &window, txt_titulo,
				   1 * window.rect.w / 2 - strlen(txt_titulo) * kiss_textfont.advance / 2,
				   window.rect.h / 4 - (kiss_textfont.fontheight + 2 * kiss_normal.h / 2));

	label_titulo.textcolor.r = 255;

	/*Criando o botão de Ver Pedidos*/
	kiss_button_new(&t02_button_ver_pedidos, &window, "Ver",
					window.rect.w / 2 - kiss_normal.w / 2,
					window.rect.h / 3);

	/* Criando o botão de Adicionar um Pedido */
	kiss_button_new(&t02_button_add_pedido, &window, "Adicionar",
					window.rect.w / 2 - kiss_normal.w / 2,
					window.rect.h / 2.4);

	/*  Criando o botão de SERVIR um Pedido  */
	kiss_button_new(&t02_button_servir_pedido, &window, "Servir",
					window.rect.w / 2 - kiss_normal.w / 2,
					window.rect.h / 2);

	/* Criando o botão de Voltar */
	kiss_button_new(&t02_button_voltar, &window, "Voltar",
					window.rect.w / 2 - kiss_normal.w / 2,
					window.rect.h / 1.2);

	/* Fazendo com que a janela seja visível */
	window.visible = 1;
	/* Loop principal */
	while (!quit)
	{
		SDL_Delay(10);
		/* Passando pela lista de eventos */
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
			{ // Usuário clicou no X da janela
				quit = 1;
				prox_tela = TELA_SAIR;
			}

			/*Processando eventos da janela e do botão */
			kiss_window_event(&window, &e, &draw);
			t02_button_ver_pedidos_event(&t02_button_ver_pedidos, &e, &quit, &draw);
			t02_button_add_pedido_event(&t02_button_add_pedido, &e, &quit, &draw);
			t02_button_servir_pedido_event(&t02_button_servir_pedido, &e, &quit, &draw);
			t02_button_voltar_event(&t02_button_voltar, &e, &quit, &draw);
		}

		if (!draw)
		{
			continue;
		}
		SDL_RenderClear(renderer); /* Limpando a tela */

		/* Desenhando os outros componentes */
		kiss_window_draw(&window, renderer);
		kiss_label_draw(&label_titulo, renderer);
		kiss_button_draw(&t02_button_ver_pedidos, renderer);
		kiss_button_draw(&t02_button_add_pedido, renderer);
		kiss_button_draw(&t02_button_servir_pedido, renderer);
		kiss_button_draw(&t02_button_voltar, renderer);

		/* Renderizando as alterações */
		SDL_RenderPresent(renderer);

		draw = 0;
	}

	kiss_clean(&objects);
	chamar_prox_tela();
}

void t02_button_ver_pedidos_event(kiss_button *button, SDL_Event *e, int *quit, int *draw) {
	if(kiss_button_event(button, e, draw)) {
		prox_tela = TELA_VER_PEDIDOS;
		*quit = 1;
	}
}

void t02_button_add_pedido_event(kiss_button *button, SDL_Event *e, int *quit, int *draw) {
	if(kiss_button_event(button, e, draw)) {
		prox_tela = TELA_ADICIONAR_NOS_PEDIDOS;
		*quit = 1;
	}
}

void t02_button_servir_pedido_event(kiss_button *button, SDL_Event *e, int *quit, int *draw) {
	if(kiss_button_event(button, e, draw)) {
		
		if (pedidos.inicio != NULL)
		{
			prox_tela = TELA_SERVIR_PEDIDO;
			*quit = 1;
		}
	}
}

void t02_button_voltar_event(kiss_button *button, SDL_Event *e, int *quit, int *draw) {
	if(kiss_button_event(button, e, draw)) {
		prox_tela = TELA_PRINCIPAL;
		*quit = 1;
	}
}