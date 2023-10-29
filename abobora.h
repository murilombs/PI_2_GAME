#ifndef __ABOBORA_H__
#define __ABOBORA_H__

#include "semente.h"

struct Abobora
{
	struct Semente semente;
	int caractetisticas[4];
	int estagio[3];
	int jaReproduziu;
};

void gera_abobora_code(struct Abobora *abobora, int anterior);

#endif
