#include "restaurante.h"

extern int prox_tela;
extern fila pedidos;
extern lista cardapio;

void t06_button_confirmar_event(kiss_button *button, SDL_Event *e, int *quit, int *draw);
void t06_button_voltar_event(kiss_button *button, SDL_Event *e, int *quit, int *draw);

void tela_servir_pedido(void)
{
	/* Declaração de variáveis */
	SDL_Renderer *renderer;
	SDL_Event e;
	kiss_array objects;
	kiss_window window;
	kiss_label label_titulo = {0}, label_nome = {0};
	kiss_button t06_button_voltar = {0}, t06_button_confirmar = {0};

	char txt_titulo[KISS_MAX_LENGTH];
	char txt_nome_pedido[KISS_MAX_LENGTH];

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
	strcpy(txt_titulo, "O Pedido a ser servido é:");
	kiss_label_new(&label_titulo, &window, txt_titulo,
				   1 * window.rect.w / 2 - strlen(txt_titulo) * kiss_textfont.advance / 2,
				   window.rect.h / 4 - (kiss_textfont.fontheight + 2 * kiss_normal.h / 2));
	label_titulo.textcolor.r = 255;

	/* Criando a label com o nome do pedido */
	strcpy(txt_nome_pedido, pedidos.inicio->nome);
	kiss_label_new(&label_nome, &window, txt_nome_pedido,
				   1 * window.rect.w / 2 - strlen(txt_nome_pedido) * kiss_textfont.advance / 2,
				   2 * window.rect.h / 4 - (kiss_textfont.fontheight + 2 * kiss_normal.h / 2));

	label_nome.textcolor.b = 255;

	/* Criando o botão de Confirmar */
	kiss_button_new(&t06_button_confirmar, &window, "Confirmar",
					1 * window.rect.w / 2 - kiss_normal.w / 2,
					15 * window.rect.h / 20);

	/* Criando o botão de Voltar */
	kiss_button_new(&t06_button_voltar, &window, "Voltar",
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
			t06_button_voltar_event(&t06_button_voltar, &e, &quit, &draw);
			t06_button_confirmar_event(&t06_button_confirmar, &e, &quit, &draw);
		}

		if (!draw)
		{
			continue;
		}
		SDL_RenderClear(renderer); /* Limpando a tela */

		/* Desenhando os outros componentes */
		kiss_window_draw(&window, renderer);
		kiss_label_draw(&label_titulo, renderer);
		kiss_label_draw(&label_nome, renderer);
		kiss_button_draw(&t06_button_voltar, renderer);
		kiss_button_draw(&t06_button_confirmar, renderer);

		/* Renderizando as alterações */
		SDL_RenderPresent(renderer);

		draw = 0;
	}

	kiss_clean(&objects);
	chamar_prox_tela();
}

void t06_button_confirmar_event(kiss_button *button, SDL_Event *e, int *quit, int *draw)
{
	if (kiss_button_event(button, e, draw))
	{
		fila_retirar(&pedidos, NULL, 0);
		*quit = 1;
		prox_tela = TELA_PEDIDOS;
	}
}

void t06_button_voltar_event(kiss_button *button, SDL_Event *e, int *quit, int *draw)
{
	if (kiss_button_event(button, e, draw))
	{
		prox_tela = TELA_PEDIDOS;
		*quit = 1;
	}
}