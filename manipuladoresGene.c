#include <stdio.h> 
#include <windows.h>
#include <time.h> 

#include "manipuladoresGene.h"
#include "semente.h"


// GERA UM NUMERO ALEATORIO 0 OU 1
int gerador_de_genes() {
	Sleep(500);
	srand((unsigned)time(NULL));
	return rand() % 2;
}

// GERA UM INT DENTRO DE UM RANGE DADO A FUNÇÃO
int geradorRandom(int baixo, int alto, int contador) {
	srand(time(0));
	for (int i = 0; i < contador; i++) {
		int num = (rand() % (alto - baixo + 1)) + baixo;
		return num;
	}
}

// vinculados ao vetor de genes de cada semente
void gerar_genes(struct Semente *semente, int p1, int p2) {
	int gene = gerador_de_genes();
	semente->genes[p1][p2] = gene;
};

void cruzamento_genes(
	struct Abobora *abobora1, 
	struct Abobora *abobora2, 
	struct Abobora *aboboras, 
	int aboborasCriadas) 
{
	int res[4][2]; // Array de resultantes da combinatoria

	for (int i = 0; i < 4; i++) {

		int novoCod = aboboras[aboborasCriadas - 1].semente.aboboraCode + 1;

		aboborasCriadas += 1;

		aboboras = (struct Abobora*)realloc(aboboras, aboborasCriadas * sizeof(struct Abobora));

		aboboras[aboborasCriadas - 1].semente.aboboraCode = novoCod;

		for (int parte = 0; parte < 4; parte++) {
			// CODIGO PRO CRUZAMENTO EM PARES
			for (int i = 0; i < 2; i++) {
				for (int j = 0; j < 2; j++) {
					res[i * 2 + j][0] = abobora1->semente.genes[parte][i];
					res[i * 2 + j][1] = abobora2->semente.genes[parte][j];
				}
			}

			/* gera um numero aleatorio entre 0 e 3 
			e usa para escolher um par no array de resultantes 
			para ser incorporado na abobora filha */
			int randon = geradorRandom(0, 3, 1);
			int eleitos[2];
			for (int p = 0; p < 2; p++) {
				aboboras[aboborasCriadas - 1].semente.genes[parte][p] = res[randon][p];
			}
		}

	}
}
