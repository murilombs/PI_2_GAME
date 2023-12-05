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

void desenharSementeInv(struct Semente sementeInv[9], int tamanho, int comecoTilemap_x, ALLEGRO_BITMAP* semente, ALLEGRO_BITMAP* grid) {
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
		}
		else {
			al_draw_bitmap(semente, x, y, 0);
		}
	}
}
void desenharAboboraInv(struct Abobora aboboraInv[9], int tamanho, int comecoTilemap_x, ALLEGRO_BITMAP* abobora, ALLEGRO_BITMAP* grid) {
	int total_largura = 3 * tamanho;
	int total_altura = 3 * tamanho;

	int offset_x = (comecoTilemap_x - total_largura) / 2 + (comecoTilemap_x + (7 * 80));
	int offset_y = (720 - total_altura) / 2;

	al_draw_bitmap(abobora, (offset_x + tamanho), 100, 0);

	for (int i = 0; i < 9; i++) {
		int x = offset_x + (i % 3) * tamanho;
		int y = offset_y + (i / 3) * tamanho;

		if (aboboraInv[i].semente.aboboraCode == 0) {
			al_draw_bitmap(grid, x, y, 0);
		}
		else {
			al_draw_bitmap(abobora, x, y, 0);
		}
	}
}