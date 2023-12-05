#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>

#include "abobora.h"

void initInv(struct Semente sementeInv[9], struct Abobora aboboraInv[9]) {
	for (int i = 0; i < 9; i++) {
		sementeInv[i].aboboraCode = 0;
		aboboraInv[i].semente.aboboraCode = 0;
	}
}

void desenharSementeInv(struct Semente sementeInv[9], int tamanho, int comecoTilemap_x, ALLEGRO_BITMAP* semente, ALLEGRO_BITMAP* grid, int mouse_x, int mouse_y) {
	int total_largura = 3 * tamanho;
	int total_altura = 3 * tamanho;

	int offset_x = (comecoTilemap_x - total_largura) / 2;
	int offset_y = (720 - total_altura) / 2;


	
	al_draw_bitmap(semente, (offset_x + tamanho), 100, 0);

	for (int i = 0; i < 9; i++) {
		int x = offset_x + (i % 3) * tamanho;
		int y = offset_y + (i / 3) * tamanho;

		if (sementeInv[i].aboboraCode == 0) {
			al_draw_bitmap(grid, x, y, 0);
			if ((mouse_x >= x && mouse_x <= x + tamanho) &&
				(mouse_y >= y && mouse_y <= y + tamanho)) {
				al_draw_tinted_bitmap(grid, al_map_rgba_f(1, 0, 0, 0.5), x, y, 0);
			}

		}
		else {
			al_draw_bitmap(semente, x, y, 0);
			if ((mouse_x >= x && mouse_x <= x + tamanho) &&
				(mouse_y >= y && mouse_y <= y + tamanho)) {
				al_draw_tinted_bitmap(semente, al_map_rgba_f(1, 0, 0, 0.5), x, y, 0);
			}
		}
	}
}
void desenharAboboraInv(struct Abobora aboboraInv[9], int tamanho, int finalTilemap_x, ALLEGRO_BITMAP* abobora, ALLEGRO_BITMAP* grid, int mouse_x, int mouse_y) {
	int total_largura = 3 * tamanho;
	int total_altura = 3 * tamanho;

	int offset_x = (finalTilemap_x - total_largura) / 2 + (finalTilemap_x + (7 * 80));
	int offset_y = (720 - total_altura) / 2;

	al_draw_bitmap(abobora, (offset_x + tamanho), 100, 0);

	for (int i = 0; i < 9; i++) {
		int x = offset_x + (i % 3) * tamanho;
		int y = offset_y + (i / 3) * tamanho;

		if (aboboraInv[i].semente.aboboraCode == 0) {
			al_draw_bitmap(grid, x, y, 0);
			if ((mouse_x >= x && mouse_x <= x + tamanho) &&
				(mouse_y >= y && mouse_y <= y + tamanho)) {
				al_draw_tinted_bitmap(grid, al_map_rgba_f(1, 0, 0, 0.5), x, y, 0);
			}
		}
		else {
			al_draw_bitmap(abobora, x, y, 0);
			if ((mouse_x >= x && mouse_x <= x + tamanho) &&
				(mouse_y >= y && mouse_y <= y + tamanho)) {
				al_draw_tinted_bitmap(abobora, al_map_rgba_f(1, 0, 0, 0.5), x, y, 0);
			}
		}
	}
}

void desenharToolbar(int inicio_x, int inicio_y, int tamanho, ALLEGRO_BITMAP* grid, int mouse_x, int mouse_y) {

	for (int i = 0; i < 4; i++) {
		int x = inicio_x + i * tamanho;
		int y = inicio_y;

		al_draw_bitmap(grid, x, y, 0);
		if ((mouse_x >= x && mouse_x <= x + tamanho) &&
			(mouse_y >= y && mouse_y <= y + tamanho)) {
			al_draw_tinted_bitmap(grid, al_map_rgba_f(1, 0, 0, 0.5), x, y, 0);
		}
	}

	
}

int checarGridSemente(int tamanho, int comecoTilemap_x, int mouse_x, int mouse_y) {
	int total_largura = 3 * tamanho;
	int total_altura = 3 * tamanho;

	int offset_x = (comecoTilemap_x - total_largura) / 2;
	int offset_y = (720 - total_altura) / 2;

	for (int i = 0; i < 9; i++) {
		int x = offset_x + (i % 3) * tamanho;
		int y = offset_y + (i / 3) * tamanho;

		if ((mouse_x >= x && mouse_x <= x + tamanho) &&
			(mouse_y >= y && mouse_y <= y + tamanho)) {
			return i;
		}
	}
	return -1;
}

int checarGridAbobora(int tamanho, int finalTilemap_x, int mouse_x, int mouse_y) {
	int total_largura = 3 * tamanho;
	int total_altura = 3 * tamanho;

	int offset_x = (finalTilemap_x - total_largura) / 2 + (finalTilemap_x + (7 * 80));
	int offset_y = (720 - total_altura) / 2;

	for (int i = 0; i < 9; i++) {
		int x = offset_x + (i % 3) * tamanho;
		int y = offset_y + (i / 3) * tamanho;

		if ((mouse_x >= x && mouse_x <= x + tamanho) &&
			(mouse_y >= y && mouse_y <= y + tamanho)) {
			return i;
		}
	}
	return -1;
}
