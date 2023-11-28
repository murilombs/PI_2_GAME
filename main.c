#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <stdio.h>
#include <time.h>
#include <locale.h>

#include "abobora.h"
#include "manipuladoresGene.h"


int main() {

	setlocale(LC_ALL, "Portuguese");

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
	int contador = 300; //definido em 5 min
	// > variavel para pular linhas em exibição de lista de genes
	int espacoY = 0;

	//Inicializa o contador criado anteriormente
	al_start_timer(timer);

	time_t segundos;
	//time(&segundos);
	//struct tm* data_hora_atual = localtime(&segundos);

	struct Abobora aboboras[40];

	int *aboborasCriadas = 4;

	for (int i = 0; i < aboborasCriadas; i++) {
		gera_abobora_code(&aboboras[i], i);
		for (int p1 = 0; p1 < 4; p1++) {
			for (int p2 = 0; p2 < 2; p2++) {
				guarda_gene(&aboboras[i], p1, p2);
			}
		}
		guarda_caracteristicas(&aboboras[i]);
		tempoDeCiclo(&aboboras[i], time(&segundos), 10);
	};

	int code1, code2, filhas;

	filhas = 4; // quantas filhas cada cruzamento vai criar

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
				al_draw_textf(font, al_map_rgb(0, 0, 0), 100, 10,
					ALLEGRO_ALIGN_CENTER, "%d", aboboras[i].semente.aboboraCode);
			}

			//Atualiza a tela
			al_flip_display();

			redraw = false;
		}

		displayTodasAboboras(aboborasCriadas, &aboboras);
		code1 = -1;

		code2 = -1;

		while (code1 <= 1 || code1 >= aboborasCriadas && code2 <= 1 || code2 >= aboborasCriadas) {

			printf("Entre com o código da Primeira abobora: ");
			scanf("%d", &code1);

			printf("Entre com o código da Segunda abobora: ");
			scanf("%d", &code2);

			cruzamento(code1, code2, filhas, &aboborasCriadas, aboboras, time(&segundos));

			mudancaDeCiclo(&aboboras, aboborasCriadas, time(&segundos));
			displayTodasAboboras(aboborasCriadas, &aboboras);
			break;
		}
	}

	al_destroy_font(font);
	al_destroy_display(disp);
	al_destroy_timer(timer);

	return 0;
}
