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
	struct Abobora *aboboras,
	int *comprimento,
	int novoComprimento) 
{

	struct Abobora novasAboboras[4];
	//novasAboboras = (struct Abobora*)malloc(4 * sizeof(struct Abobora));

	int res[4][2]; // Array de resultantes da combinatoria

	int diferenca = novoComprimento - *comprimento;

	for (int cont = 0; cont < 4; cont++) {
		gera_abobora_code(&novasAboboras[cont], diferenca - 1);
		for (int parte = 0; parte < 4; parte++) {
			// CODIGO PRO CRUZAMENTO EM PARES
			for (int i = 0; i < 2; i++) {
				for (int j = 0; j < 2; j++) {
					res[i * 2 + j][0] = abobora1.semente.genes[parte][i];
					res[i * 2 + j][1] = abobora2.semente.genes[parte][j];
				}
			}

			/* gera um numero aleatorio entre 0 e 3
			e usa para escolher um par no array de resultantes
			para ser incorporado na abobora filha */
			int randon = geradorRandom(0, 3, 1);
			for (int p = 0; p < 2; p++) {
				novasAboboras[cont].semente.genes[parte][p] = res[randon][p];
			}
		}
	}

	redimensionadorDeArrays(&aboboras, &comprimento, novoComprimento);
	int acesso = diferenca;

	for (int n = diferenca; n < novoComprimento; n++) {
		acesso -= 1;
		aboboras[n] = novasAboboras[acesso];
	}
}
