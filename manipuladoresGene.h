#include <stdio.h> 
#include <stdlib.h> 
#include <time.h> 

#include "abobora.h"

// função para criar genes
void guarda_gene(struct Abobora *abobora, int p1, int p2);

// função para guardar genes
void guarda_caracteristicas(struct Abobora* abobora);

void cruzamento_genes(
	struct Abobora abobora1, 
	struct Abobora abobora2, 
	struct Abobora **aboboras, 
	int *comprimento,
	int novoComprimento);


