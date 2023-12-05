#ifndef __ABOBORA_H__
#define __ABOBORA_H__

#include "semente.h"

struct Abobora
{
	struct Semente semente;
	int caractetisticas[4];
	int tempoCiclo;
	int estagio;
	int jaReproduziu;
	int cordernadas[2];
};

void gera_abobora_code(struct Abobora *abobora, int anterior);

int buscadorDeAbobora(int aboboraCode, int aboborasCriadas, struct Abobora* aboboras);

void tempoDeCiclo(struct Abobora* abobora, time_t* timestamp, int acrescimo);

void mudancaDeCiclo(struct Abobora* aboboras, int aboborasCriadas, int timestampAtual);

void displayCaracteristica(char* caracteristicas, struct Abobora* abobora);

//void displayTodasAboboras(int aboborasCriadas, struct Abobora* aboboras);
#endif
