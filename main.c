#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

#include "tilemap.h"

#include "abobora.h"
#include "manipuladoresGene.h"

#define TILE_SIZE 96

char textoDebug[2000];
char* textoDisplay[10];

void must_init(bool inicializacao_bem_sucedida, const char* description) {

	if (inicializacao_bem_sucedida) return;
	printf("Erro ao inicializar %s.", description);
	exit(1);
}

void exibir_mensagem(ALLEGRO_FONT* font, const char* mensagem) {
	al_draw_textf(font, al_map_rgb(255, 255, 255), 640, 50, ALLEGRO_ALIGN_CENTER, "%s\n", mensagem);
	al_flip_display();
	al_rest(1.0);

}

void tooltip(
	ALLEGRO_FONT* font, 
	const char* texto, 
	int mouse_x, 
	int mouse_y, 
	int aboborasCriadas,
	struct Abobora* aboboras) 
{
	int largura = 220;
	int altura = 100;


	int temAbobora = checaPosicaoNoCampo(400, 120, mouse_x, mouse_y, aboborasCriadas, &aboboras);
	if (temAbobora) {
		int idx = buscadorDeAbobora(temAbobora, aboborasCriadas, &aboboras);
		displayCaracteristica(&textoDisplay,  &aboboras[idx]);

		al_draw_filled_rectangle(mouse_x, mouse_y, 
			mouse_x + largura, 
			mouse_y + altura, 
			al_map_rgb(3, 181, 24));

		al_draw_textf(font, al_map_rgb(0, 0, 0), 
			mouse_x + 15, 
			mouse_y + 10, 
			20, "%s", textoDisplay);
	}
}

int checaPosicaoNoCampo(
	int inicio_x, 
	int fim_y, 
	int mouse_x, 
	int mouse_y, 
	int aboborasCriadas,
	struct Abobora* aboboras) 
{
	for (int linha = 0; linha < 5; linha++) {
		for (int coluna = 0; coluna < 5; coluna++) {

			int x = inicio_x + coluna * TILE_SIZE;
			int y = fim_y + linha * TILE_SIZE;

			if (mouse_x > x &&
				mouse_y > y &&
				mouse_x < x + TILE_SIZE &&
				mouse_y < y + TILE_SIZE) {
				for (int i = 0; i < aboborasCriadas; i++) {
					if (aboboras[i].cordernadas[0] == linha && 
						aboboras[i].cordernadas[1] == coluna) {
						return aboboras[i].semente.aboboraCode;
					}
				}
			}
		}
	}
	return 0;
}


int main() {

	must_init(al_init(), "Allegro"); // Inicialização do Allegro

	must_init(al_init_font_addon(), "addons de fonte"); // Inicializa os addons de fonte

	must_init(al_init_ttf_addon(), "addons do Allegro"); // Inicializa os addons do Allegro

	// Inicializa, carrega a fonte True Type + caminho relativo
	ALLEGRO_FONT* font = al_load_ttf_font("fontes/GoetheBold.ttf", 28, 0);
	must_init(font, "fonte");

	// Inicialização, criação do display e dimensões
	ALLEGRO_DISPLAY* display = al_create_display(1280, 720);
	must_init(display, "display");

	// Inicialização e criação da fila de eventos
	ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
	must_init(queue, "fila de eventos");

	// Inicializalção dos addons de imagem
	must_init(al_init_image_addon(), "addons de imagem");

	ALLEGRO_BITMAP* grama = al_load_bitmap("imagens/tileGrama.png");
	must_init(grama, "imagem de grama");
	ALLEGRO_BITMAP* terra = al_load_bitmap("imagens/tileTerra.png");
	must_init(terra, "imagem de terra");
	ALLEGRO_BITMAP* estagio0 = al_load_bitmap("imagens/tileEstagio0.png");
	must_init(estagio0, "imagem de estagio0");
	ALLEGRO_BITMAP* estagio1 = al_load_bitmap("imagens/tileEstagio1.png");
	must_init(estagio1, "imagem de estagio1");
	ALLEGRO_BITMAP* estagio2 = al_load_bitmap("imagens/tileEstagio2.png");
	must_init(estagio2, "imagem de estagio2");
	ALLEGRO_BITMAP* estagio3 = al_load_bitmap("imagens/tileEstagio3.png");
	must_init(estagio3, "imagem de estagio3");

	must_init(al_init_primitives_addon(), "primitives addon"); // Inicialização dos primitives

	// Inicialização e criação do timer
	ALLEGRO_TIMER* timer = al_create_timer(1.0 / 30.0);
	must_init(timer, "timer");

	must_init(al_install_keyboard(), "teclado"); // Inicializa e recebe comandos do teclado
	must_init(al_install_mouse(), "mouse"); // Inicializa e recebe comandos do mouse

	al_register_event_source(queue, al_get_keyboard_event_source()); // Recebe eventos do teclado
	al_register_event_source(queue, al_get_mouse_event_source()); // Recebe eventos do mouse
	al_register_event_source(queue, al_get_display_event_source(display)); // Recebe eventos do display
	al_register_event_source(queue, al_get_timer_event_source(timer)); // Recebe eventos do timer


	ALLEGRO_EVENT event;

	bool done = false; // done será a variável que fechará o programa.
	bool redraw = true; // Variável para redesenhar a tela a cada x segundos

	int mouse_x = 0; // Coordenada de x (eixo vertical)
	int mouse_y = 0; // Coordenada de y (eixo horizontal)

	int tilemap[7][7] = {
	{4, 4, 4, 4, 4, 4, 4},
	{4, 2, 5, 5, 5, 5, 4},
	{4, 5, 5, 5, 5, 5, 4},
	{4, 5, 5, 5, 5, 5, 4},
	{4, 5, 5, 5, 5, 5, 4},
	{4, 5, 5, 5, 5, 5, 4},
	{4, 4, 4, 4, 4, 4, 4}
	};

	int comeco_tilemap_x = (al_get_display_width(display) - (7 * 96)) / 2;
	int fim_tilemap_y = (al_get_display_height(display) - (7 * 96)) / 2;

	bool mostrar_tooltip = false; // O tooltip será visível quando a variável for true

	bool arrastando = false;

	time_t segundos;

	struct Abobora aboboras[49];

	int* aboborasCriadas = 1;

	for (int i = 0; i < aboborasCriadas; i++) {
		gera_abobora_code(&aboboras[i], i);
		for (int p1 = 0; p1 < 4; p1++) {
			for (int p2 = 0; p2 < 2; p2++) {
				guarda_gene(&aboboras[i], p1, p2);
			}
		}
		guarda_caracteristicas(&aboboras[i]);
		tempoDeCiclo(&aboboras[i], time(&segundos), 10);
		aboboras[i].cordernadas[0] = 0;
		aboboras[i].cordernadas[1] = 0;
	};

	// tilemap da plantação

	while (1) { // Loop principal

		al_wait_for_event(queue, &event);

		al_clear_to_color(al_map_rgb(163, 210, 119));
		desenhartilemap(
			tilemap, 
			comeco_tilemap_x, 
			fim_tilemap_y, 
			mouse_x, 
			mouse_y, 
			grama, 
			terra, 
			estagio0, 
			estagio1, 
			estagio2, 
			estagio3, 
			queue, 
			TILE_SIZE);

		// Caso ocorra um evento x, tal coisa deve acontecer
		switch (event.type) {

		case ALLEGRO_EVENT_KEY_DOWN:
			// Se a tecla pressionada for ESC o programa fecha
			if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) { 
				done = true;
			}
			break;

		case ALLEGRO_EVENT_DISPLAY_CLOSE:
			// Se o display for fechado, o programa acaba
			done = true;
			break;

		case ALLEGRO_EVENT_MOUSE_AXES:
			// Guarda na fila de eventos do mouse as coordenadas do cursor
			mouse_x = event.mouse.x;
			mouse_y = event.mouse.y;

			if ((mouse_x >= 395 && 
				 mouse_x <= 875) && 
				(mouse_y >= 120 && 
				 mouse_y <= 600)) {
				mostrar_tooltip = true;
				al_start_timer(timer);
			}
			else {
				mostrar_tooltip = false;
				al_stop_timer(timer);
			}

			if (arrastando) {
				mouse_x += event.mouse.dx;
				mouse_y += event.mouse.dy;

			}

			break;

		case ALLEGRO_EVENT_TIMER:
			if ((al_get_timer_started(timer)) && 
				(mostrar_tooltip)) { 
				tooltip(font, "Essa \u00e9 uma tooltip!", mouse_x, mouse_y, 
					aboborasCriadas, &aboboras);
			}
			break;

		case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:

			mouse_x = event.mouse.x;
			mouse_y = event.mouse.y;
			printf("x = %d\ny = %d\n\n", mouse_x, mouse_y);

			if (event.mouse.button & 1) {
				if ((event.mouse.x >= 480 && event.mouse.x <= 800) && 
					(event.mouse.y >= 300 && event.mouse.y <= 600)) {
					arrastando = true;

				}
			}

			//checaPosicaoNoCampo(400, 120, mouse_x, mouse_y, aboborasCriadas, &aboboras);
			break;

		case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
			arrastando = false;
			break;
		}

		if (done) {
			// Caso done seja true, o programa fecha.
			break;
		}

		al_draw_text(font, al_map_rgb(0, 0, 0), 10, 10, 0, textoDebug);

		al_flip_display();

		al_clear_to_color(al_map_rgb(255, 255, 255));

		al_set_target_bitmap(al_get_backbuffer(display));

	}

	//free((void*)textoDisplay);
	//displayTodasAboboras(aboborasCriadas, &aboboras);
	al_destroy_font(font);
	al_destroy_display(display);
	al_destroy_event_queue(queue);
	al_destroy_timer(timer);

	return 0;
}
