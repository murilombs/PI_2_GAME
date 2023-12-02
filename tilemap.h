#ifndef TILEMAP_H
#define TILEMAP_H

#include <allegro5/allegro.h>

void desenharMatriz(int matriz[3][14], int inicio_x, int fim_y, int mouse_x, int mouse_y, ALLEGRO_BITMAP* abob, ALLEGRO_EVENT_QUEUE* queue, int tamanho_tile);

#endif