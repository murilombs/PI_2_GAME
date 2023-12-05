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
	abobora->jaReproduziu = 0;
};

//vincula ao vetor de caracteristicas
void guarda_caracteristicas(struct Abobora* abobora) {
	for (int idx = 0; idx < 4; idx++) {
		int somaGene = abobora->semente.genes[idx][0] + abobora->semente.genes[idx][1];
		abobora->caractetisticas[idx] = somaGene;
	}
}

void redimensionadorDeArrays(struct Abobora* original, int *comprimento, int novoComprimento) {

	struct Abobora* array_temporario = (struct Abobora*)malloc(novoComprimento * sizeof(struct Abobora));
	int copiarTamanho = (*comprimento < novoComprimento) ? *comprimento : novoComprimento;

	if (array_temporario) {
		for (int i = 0; i < copiarTamanho; i++) {
			array_temporario[i] = original[i];
		}
		free(original); // libera o espaço no array original
		original = array_temporario; // passa para original // O ERRO SEMPRE ACONTECE AQUI
		*comprimento = novoComprimento; // reescreve o tamanho
	}
}

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
		eleitos[p] = res[randon][p];
	}
}

void cruzamento(
	int aboboraCode1, 
	int aboboraCode2, 
	int filhas, 
	int* aboborasCriadas, 
	struct Abobora* aboboras,
	time_t* timestamp)
{
	int eleitos[2];

	int ponteiro1 = buscadorDeAbobora(aboboraCode1, *aboborasCriadas, aboboras);
	int ponteiro2 = buscadorDeAbobora(aboboraCode2, *aboborasCriadas, aboboras);

	if (aboboras[ponteiro1].jaReproduziu || aboboras[ponteiro2].jaReproduziu) {
		printf("Uma ou ambas das aboboras selecionadas ja reproduziram\n");
		return;
	}

	for (int setor = 0; setor < filhas; setor++) {
		gera_abobora_code(&aboboras[*aboborasCriadas], *aboborasCriadas);
		cruzamento_genes(aboboras[ponteiro1], aboboras[ponteiro2], setor, eleitos);
		for (int p1 = 0; p1 < 4; p1++) {
			for (int p2 = 0; p2 < 2; p2++) {
				aboboras[*aboborasCriadas].semente.genes[p1][p2] = eleitos[p2];
			}
		}
		guarda_caracteristicas(&aboboras[*aboborasCriadas]);
		tempoDeCiclo(&aboboras[*aboborasCriadas], time(&timestamp), 10);

		*aboborasCriadas += 1;
	}

	aboboras[ponteiro1].jaReproduziu = 1;
	aboboras[ponteiro2].jaReproduziu = 1;
}
