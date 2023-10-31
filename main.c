#include <stdio.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>

#include "abobora.h"
#include "manipuladoresGene.h"

int main() {

	//Inicializa o programa
	al_init();

	if (!al_init()) {
		printf("Erro ao inicializar o Allegro\n");
		return 1;
	}

	//Habilita receber dado do teclado
	al_install_keyboard();

	if (!al_install_keyboard()) {
		printf("Erro ao inicializar o teclado\n");
		return 1;
	}

	//Cria um timer
	//O timer atualiza a cada 1s
	ALLEGRO_TIMER* timer = al_create_timer(1.0);

	if (!timer) {
		printf("Erro ao inicializar o timer\n");
		return 1;
	}

	//Cria uma filha de eventos
	ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();

	if (!queue) {
		printf("Erro ao inicializar a fila de eventos\n");
		return 1;
	}

	//Cria uma janela
	ALLEGRO_DISPLAY* disp = al_create_display(900, 700);

	if (!disp) {
		printf("Erro ao inicializar a janela\n");
		return 1;
	}

	//Inicializa a fonte padrao
	ALLEGRO_FONT* font = al_create_builtin_font();

	if (!font) {
		printf("Erro ao inicializar a fonte\n");
		return 1;
	}

	//al_register_event é usado para registrar eventos de uma fonte especifica (display, teclado etc) 
	al_register_event_source(queue, al_get_keyboard_event_source());
	al_register_event_source(queue, al_get_display_event_source(disp));
	al_register_event_source(queue, al_get_timer_event_source(timer));

	/*
	> A variavel done é usada para controlar quando o programa deve ser encerrado
	Ao ser definida como "false", o programa entende que não deve ser encerrado
	> A variável "redraw" é usada para controlar quando a tela deve ser redesenhada
	Ao ser definida como "true", o programa entende que no início ela deve ser reinicializada
	> A variável "event" em ALLEGRO_EVENT é usada para armazenar eventos. É nele que os eventos
	pendentes ficam armazenados e eventualmente processados
	*/

	bool done = false;
	bool redraw = true;
	ALLEGRO_EVENT event;

	// > Variável do contador regressivo
	int contador = 60;
	// > variavel para pular linhas em exibição de lista de genes
	int espacoY = 0;

	//Inicializa o contador criado anteriormente
	al_start_timer(timer);

	struct Abobora *aboboras;

	aboboras = (struct Abobora*)malloc(4 * sizeof(struct Abobora));

	for (int i = 0; i < 4; i++) {
		gera_abobora_code(&aboboras[i], i);
		for (int p1 = 0; p1 < 4; p1++) {
			for (int p2 = 0; p2 < 2; p2++) {
				guarda_gene(&aboboras[i], p1, p2);
			}
		}
	};

	int aboborasCriadas = sizeof(aboboras) / sizeof(aboboras[0]);

	int novoComprimento = aboborasCriadas + 4;

	cruzamento_genes(aboboras[0], aboboras[2], &aboboras, &aboborasCriadas, novoComprimento);

	for (int j = 0; j < 4; j++) {
		printf("AboboraCode: %d \n", aboboras[j].semente.aboboraCode);
		for (int x = 0; x < 4; x++) {
			for (int y = 0; y < 2; y++) {
				printf("Genes[%d][%d]: %d\n", x, y, aboboras[j].semente.genes[x][y]);
			}
		}
		printf("********************************\n");
	}
	printf("Comprimento: %d \n", aboborasCriadas);

	while (1) {
		al_wait_for_event(queue, &event);

		//Caso ocorra um evento x, tal coisa deverá ocorrer
		switch (event.type) {

			case ALLEGRO_EVENT_TIMER:

				//Passo do contador
				contador--;

				if (contador <= 0) {
					//Desativa o temporizador e encerra o programa quando o contador chega a 0s
					al_stop_timer(timer);
					done = true;
				}
				redraw = true;
				break;

			case ALLEGRO_EVENT_KEY_DOWN:

				//Encerra o programa quando ESC é pressionado
				if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
					done = true;
				}

				break;

			case ALLEGRO_EVENT_DISPLAY_CLOSE:

				done = true;
				break;
		}


		if (done)
			break;

		if (redraw && al_is_event_queue_empty(queue)) {
			//Define a cor de fundo
			al_clear_to_color(al_map_rgb(255, 219, 245));

			// al_draw_textf -> fonte , cor da fonte, posição em X, posição em Y, alinhamento, tipo
			for (int i = 0; i < aboborasCriadas; i++) {
				al_draw_textf(font, al_map_rgb(0, 0, 0), 100, espacoY += 10,
					ALLEGRO_ALIGN_CENTER, "%d", aboboras[i].semente.aboboraCode);
			}

			//Atualiza a tela
			al_flip_display();

			redraw = false;
		}
	}

	al_destroy_font(font);
	al_destroy_display(disp);
	al_destroy_timer(timer);
	free(aboboras);

	return 0;
}
