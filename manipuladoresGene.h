#include <stdio.h> 
#include <stdlib.h> 
#include <time.h> 

#include "abobora.h"

// fun��o para criar genes
void guarda_gene(struct Abobora *abobora, int p1, int p2);

// fun��o para guardar genes
void guarda_caracteristicas(struct Abobora* abobora);

void cruzamento_genes(
	struct Abobora abobora1, 
	struct Abobora abobora2, 
	struct Abobora **aboboras, 
	int *comprimento,
	int novoComprimento);


