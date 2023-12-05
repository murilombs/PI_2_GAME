#ifndef TILEMAP_H
#define TILEMAP_H

#include <allegro5/allegro.h>

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
	int tamanho_tile);

#endif