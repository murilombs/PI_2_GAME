#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>


void desenhartilemap(
	int tilemap[7][7], 
	int inicio_x, 
	int inicio_y, 
	int mouse_x, 
	int mouse_y, 
	ALLEGRO_BITMAP* grama, 
	ALLEGRO_BITMAP* terra, 
	ALLEGRO_BITMAP* estagio0, 
	ALLEGRO_BITMAP* estagio1, 
	ALLEGRO_BITMAP* estagio2, 
	ALLEGRO_BITMAP* estagio3, 
	ALLEGRO_EVENT_QUEUE* queue, 
	int tamanho_tile) 
{
	for (int linha = 0; linha < 7; linha++) {
		for (int coluna = 0; coluna < 7; coluna++) {

			int x = inicio_x + coluna * tamanho_tile;
			int y = inicio_y + linha * tamanho_tile;

			if (tilemap[linha][coluna] == 4) {
		
				al_draw_bitmap(grama, x, y, 0);
			}
			else if (tilemap[linha][coluna] == 5) {
				al_draw_bitmap(terra, x, y, 0);
				if ((mouse_x >= x && mouse_x <= x + tamanho_tile) && 
					(mouse_y >= y && mouse_y <= y + tamanho_tile)) {
					al_draw_tinted_bitmap(terra, al_map_rgba_f(1, 0, 0, 0.5), x, y, 0);
				}
			}
			else if (tilemap[linha][coluna] == 0) {
				al_draw_bitmap(estagio0, x, y, 0);
				if ((mouse_x >= x && mouse_x <= x + tamanho_tile) && 
					(mouse_y >= y && mouse_y <= y + tamanho_tile)) {
					al_draw_tinted_bitmap(estagio0, al_map_rgba_f(1, 0, 0, 0.5), x, y, 0);
				}
			}
			else if (tilemap[linha][coluna] == 1) {
				al_draw_bitmap(estagio1, x, y, 0);
				if ((mouse_x >= x && mouse_x <= x + tamanho_tile) && 
					(mouse_y >= y && mouse_y <= y + tamanho_tile)) {
					al_draw_tinted_bitmap(estagio1, al_map_rgba_f(1, 0, 0, 0.5), x, y, 0);
				}
			}
			else if (tilemap[linha][coluna] == 2) {
				al_draw_bitmap(estagio2, x, y, 0);
				if ((mouse_x >= x && mouse_x <= x + tamanho_tile) && 
					(mouse_y >= y && mouse_y <= y + tamanho_tile)) {
					al_draw_tinted_bitmap(estagio2, al_map_rgba_f(1, 0, 0, 0.5), x, y, 0);
				}
			}
			else if (tilemap[linha][coluna] == 3) {
				al_draw_bitmap(estagio3, x, y, 0);
				if ((mouse_x >= x && mouse_x <= x + tamanho_tile) && 
					(mouse_y >= y && mouse_y <= y + tamanho_tile)) {
					al_draw_tinted_bitmap(estagio3, al_map_rgba_f(1, 0, 0, 0.5), x, y, 0);
				}
			}
		}
	}

}