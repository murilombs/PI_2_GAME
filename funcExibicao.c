#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

#include "abobora.h"
#define TILE_SIZE 80

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

void tooltip(
	ALLEGRO_FONT* font,
	char* texto,
	int mouse_x,
	int mouse_y,
	int aboborasCriadas,
	struct Abobora* aboboras)
{
	int largura = 220;
	int altura = 100;

	int temAbobora = checaPosicaoNoCampo(400, 120, mouse_x, mouse_y, aboborasCriadas, aboboras);
	if (temAbobora) {
		int idx = buscadorDeAbobora(temAbobora, aboborasCriadas, aboboras);
		displayCaracteristica(&texto, &aboboras[idx]);
		printf("texto -> %s", texto);

		al_draw_filled_rectangle(mouse_x, mouse_y,
			mouse_x + largura,
			mouse_y + altura,
			al_map_rgb(3, 181, 24));

		al_draw_textf(font, al_map_rgb(0, 0, 0),
			mouse_x + 15,
			mouse_y + 10,
			20, "%s", texto);
	}
}