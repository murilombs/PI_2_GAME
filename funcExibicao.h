#ifndef __FUNC_EXIB__
#define __FUNC_EXIB__

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include "abobora.h"

void tooltip(
	ALLEGRO_FONT* font,
	char* texto,
	int mouse_x,
	int mouse_y,
	int aboborasCriadas,
	struct Abobora* aboboras);

int checaPosicaoNoCampo(
	int inicio_x,
	int fim_y,
	int mouse_x,
	int mouse_y,
	int aboborasCriadas,
	struct Abobora* aboboras);
#endif