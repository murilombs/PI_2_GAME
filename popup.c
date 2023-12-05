#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>

void popup(ALLEGRO_FONT* font, const char* txt, float rect_x, float rect_y) {

	// Pega o tamanho do texto a ser exibido
	float txt_lar = al_get_text_width(font, txt);
	float txt_alt = al_get_font_line_height(font);

	// Define as coordenadas do popup com base no tamanho do texto
	float rect_lar = txt_lar + 30; // Adicione uma margem de 20 pixels
	float rect_alt = txt_alt + 30;

	// Retângulo dinâmico
	al_draw_filled_rounded_rectangle(rect_x, rect_y, rect_x + rect_lar, rect_y + rect_alt, 20, 20, al_map_rgb(249, 231, 115));
	al_draw_filled_rounded_rectangle(rect_x, rect_y, rect_x + rect_lar - 7, rect_y + rect_alt - 7, 20, 20, al_map_rgb(255, 243, 158));

	al_draw_textf(font, al_map_rgb(0, 0, 0), rect_x + 10, rect_y + 10, 0, "%s", txt);

}


