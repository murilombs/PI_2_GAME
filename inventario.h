#ifndef INVENTARIO_H
#define INVENTARIO_H

#include <allegro5/allegro.h>
#include "abobora.h"



void initInv(struct Semente sementeInv[9], struct Abobora aboboraInv[9]);
void desenharSementeInv(struct Semente sementeInv[9], int tamanho, int comecoTilemap_x, ALLEGRO_BITMAP* semente, ALLEGRO_BITMAP* grid);
void desenharAboboraInv(struct Abobora aboboraInv[9], int tamanho, int finalTilemap_x, ALLEGRO_BITMAP* abobora, ALLEGRO_BITMAP* grid);
void desenharToolbar(int inicio_x, int inicio_y, int tamanho, ALLEGRO_BITMAP* grid);


#endif