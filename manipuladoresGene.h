#include <stdio.h> 
#include <stdlib.h> 
#include <time.h> 

#include "abobora.h"

// função para criar genes
void guarda_gene(struct Abobora *abobora, int p1, int p2);

void cruzamento_genes(
	struct Abobora abobora1, 
	struct Abobora abobora2, 
	int setor,
	int eleitos[2]);


