#include "restaurante.h"

extern int prox_tela;
extern fila pedidos;
extern lista cardapio;

void t04_button_voltar_event(kiss_button *button, SDL_Event *e, int *quit, int *draw);
static void vscrollbar1_event(kiss_vscrollbar *vscrollbar, SDL_Event *e, kiss_textbox *textbox1, int *draw);

void tela_ver_pedidos(void){
	SDL_Renderer *renderer;
	SDL_Event e;
	kiss_array objects, a;
	kiss_window window;
	kiss_label label_titulo = {0};
	kiss_button button_voltar = {0};
	kiss_vscrollbar scroll = {0};
	kiss_textbox caixa_texto = {0};

	char stext[KISS_MAX_LENGTH];
	char txt_titulo[KISS_MAX_LENGTH];
	int draw, quit;
	
	quit = 0;
	draw = 1;

	strcpy(stext,"");

	/* Inicializando o KISS e o vetor de objetos */
	kiss_array_new(&objects);
	renderer = kiss_init("Restaurante da Tia Magali", &objects, 480, 360);

	if(!renderer) {
		return;
	}

	kiss_array_new(&a);

	struct no_fila *aux;
	if(pedidos.inicio == NULL) {
		kiss_array_appendstring(&a, 0, "Sem pedidos!", NULL);
	} else {
		aux = pedidos.inicio;
		while(aux != NULL) {

			kiss_array_appendstring(&a, 0, aux->nome, NULL);
			aux = aux->prox;			
		}
	}
	
	/* Inicializando a janela */
	kiss_window_new(&window, NULL, 0, 0, 0, kiss_screen_width, kiss_screen_height);

	/* Criando a label centralizada com a janela */
	strcpy(txt_titulo, "Pedidos na fila");
	kiss_label_new(&label_titulo, &window, txt_titulo,
		1*window.rect.w / 2 - strlen(txt_titulo) * kiss_textfont.advance / 2,
		window.rect.h / 4 - (kiss_textfont.fontheight + 2 * kiss_normal.h / 2)
	);
	label_titulo.textcolor.r = 255;

	/* Criando o botão de voltar */
	kiss_button_new(&button_voltar, &window, "Voltar",
		window.rect.w / 2 - kiss_normal.w / 2,
		window.rect.h / 1.2
	);

	/* Criando a scrollbar */
	kiss_vscrollbar_new(&scroll, &window, 400, 100, 180);

	/* Criando a textbox */
	kiss_textbox_new(&caixa_texto, &window, 1, &a, 100, 100, 300, 180);

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
			/* Processando eventos da janela, botão, scroll e a caixa de texto */
			kiss_window_event(&window, &e, &draw);
			t04_button_voltar_event(&button_voltar, &e, &quit, &draw);
			kiss_vscrollbar_event(&scroll, &e, &draw);
			kiss_textbox_event(&caixa_texto, &e, &draw);
			vscrollbar1_event(&scroll, &e, &caixa_texto, &draw);		
		}

		if(!draw)
			continue;
		
		SDL_RenderClear(renderer); /* Limpando a tela */

		/* Desenhando os outros componentes */
		kiss_window_draw(&window, renderer);
		kiss_label_draw(&label_titulo, renderer);
		kiss_button_draw(&button_voltar, renderer);
		kiss_vscrollbar_draw(&scroll, renderer);
		kiss_textbox_draw(&caixa_texto, renderer);
		vscrollbar1_event(&scroll, NULL, &caixa_texto, &draw);

		/* Renderizando as alterações */
		SDL_RenderPresent(renderer);

		draw = 0;
	}

	kiss_clean(&objects);

	chamar_prox_tela();
}

static void vscrollbar1_event(kiss_vscrollbar *vscrollbar, SDL_Event *e,
	kiss_textbox *textbox1, int *draw)
{
	int firstline;

	if (kiss_vscrollbar_event(vscrollbar, e, draw) &&
		textbox1->array->length - textbox1->maxlines > 0) {
		firstline = (int) ((textbox1->array->length - 
			textbox1->maxlines) * vscrollbar->fraction + 0.5);
		if (firstline >= 0) textbox1->firstline = firstline;
		*draw = 1;
	}
}

void t04_button_voltar_event(kiss_button *button, SDL_Event *e, int *quit, int *draw) {
	if(kiss_button_event(button, e, draw)) {
		prox_tela = TELA_PEDIDOS;
		*quit = 1;
	}
}