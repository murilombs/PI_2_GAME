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
void guarda_gene(struct Abobora *abobora, int p1, int p2) {
	int gene = gerador_de_genes();
	abobora->semente.genes[p1][p2] = gene;
};

void cruzamento_genes(
	struct Abobora abobora1, 
	struct Abobora abobora2,
	int setor,
	int eleitos[2])
{

	int res[4][2]; // Array de resultantes da combinatoria

	// CODIGO PRO CRUZAMENTO EM PARTES
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			res[i * 2 + j][0] = abobora1.semente.genes[setor][i];
			res[i * 2 + j][1] = abobora2.semente.genes[setor][j];
		}
	}
	// CODIGO PRO CRUZAMENTO EM PARTES

	int randon = geradorRandom(0, 3, 1);

	for (int p = 0; p < 2; p++) {
		//aboboras[index].semente.genes[setor][p] = res[randon][p];
		eleitos[p] = res[randon][p];
	}
	/*
	for (int n = 0; n < 4; n++) {
		gera_abobora_code(&aboboras[comprimento], comprimento); // aboboras[4], 4 + 1
		for (int p1 = 0; p1 < 4; p1++) {
			for (int p2 = 0; p2 < 2; p2++) {
				aboboras[comprimento].semente.genes[p1][p2] = eleitos[p2];
			}
		}
		comprimento += 1; // 4 + 1
	}
	*/
}
