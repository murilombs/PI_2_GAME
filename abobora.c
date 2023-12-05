#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "abobora.h"

/*	Aqui vamos gerar o c�digo indentificador de cada abobora
*	vamos precissar armazenar os c�digos gerados anteriormente
*	para saber qual deve ser o proximo.
*/
void gera_abobora_code(struct Abobora *abobora, int anterior) {
	abobora->semente.aboboraCode = anterior + 1;
	abobora->estagio = 0;
}

// Retorna a posi��o da abobora no array dado seu aboboraCode
int buscadorDeAbobora(int aboboraCode, int aboborasCriadas, struct Abobora* aboboras) {
	for (int i = 0; i < aboborasCriadas; i++) {
		if (aboboraCode == aboboras[i].semente.aboboraCode) {
			printf("aboboraCode %d\n", aboboras[i].semente.aboboraCode);
			return i;
		}
	}
}

// Guarda o timestamp de cria��o da abobora + tempo ate o ciclo seguinte
// O TEMPO DE MUDAN�A DO PROXIMO CICLO SERA O TEMPO DE CRIA��O MAIS 60 SEG
void tempoDeCiclo(struct Abobora* abobora, time_t* timestamp, int acrescimo) {
	abobora->tempoCiclo = timestamp + acrescimo;
}

void mudancaDeCiclo(struct Abobora* abobora, int aboborasCriadas, int timestampAtual) {
	for (int idx = 0; idx < aboborasCriadas; idx++) {
		if (timestampAtual > abobora[idx].tempoCiclo && abobora[idx].estagio < 3) {
			abobora[idx].estagio += 1;
			tempoDeCiclo(&abobora[idx], timestampAtual, 10);
			printf("O ciclo de #%d � %d\n", abobora[idx].semente.aboboraCode, abobora[idx].estagio);
		}
	}
}

// FUN��ES PARA TESTE [DEVEM SER APAGADAS]
char* displayCaracteristica(struct Abobora* abobora) {
	char* sabor = "A";
	char* tamanho = "B";
	char* cor = "C";
	char* casca = "D";

	for (int i = 0; i < 4; i++) {
		// SABOR
		if (i == 0 && abobora->caractetisticas[i] == 0) {
			sabor = "Doce";
		}

		if (i == 0 && abobora->caractetisticas[i] == 1) {
			sabor = "Salgada";
		}

		if (i == 0 && abobora->caractetisticas[i] == 2) {
			sabor = "Salgada";
		}
		// SABOR


		// TAMANHO
		if (i == 1 && abobora->caractetisticas[i] == 0) {
			tamanho = "Grande";
		}

		if (i == 1 && abobora->caractetisticas[i] == 1) {
			tamanho = "Pequena";
		}

		if (i == 1 && abobora->caractetisticas[i] == 2) {
			tamanho = "Pequena";
		}
		// TAMANHO
		
		// COR
		if (i == 2 && abobora->caractetisticas[i] == 0) {
			cor = "Verde";
		}

		if (i == 2 && abobora->caractetisticas[i] == 1) {
			cor = "Laranja";
		}

		if (i == 2 && abobora->caractetisticas[i] == 2) {
			cor = "Laranja";
		}
		// COR

		// CASCA
		if (i == 3 && abobora->caractetisticas[i] == 0) {
			casca = "Grossa";
		}

		if (i == 3 && abobora->caractetisticas[i] == 1) {
			casca = "Fina";
		}

		if (i == 3 && abobora->caractetisticas[i] == 2) {
			casca = "Fina";
		}
		// CASCA
	}

	size_t comprimento_total = strlen(sabor) + strlen(tamanho) + strlen(cor) + strlen(casca);

	char* caracteristicas = (char*)malloc(comprimento_total);

	if (caracteristicas == NULL) {
		fprintf(stderr, "Erro ao alocar mem�ria.\n");
		exit(EXIT_FAILURE);
	}

	sprintf(caracteristicas, "%s,\n%s,\n%s,\n%s", sabor, tamanho, cor, casca);

	return caracteristicas;
}

void displayTimestampStagio(struct Abobora abobora) {
	printf("Estagio: %d \nTimestamp: %d\n", abobora.estagio, abobora.tempoCiclo);
};

void displayTodasAboboras(int aboborasCriadas, struct Abobora* aboboras) {
	for (int j = 0; j < aboborasCriadas; j++) {
		printf("#### AboboraCode: %d ####\n", aboboras[j].semente.aboboraCode);
		
		displayTimestampStagio(aboboras[j]);
		printf("Cordenadas:\nX -> %d\nY -> %d\n", aboboras[j].cordernadas[0], aboboras[j].cordernadas[1]);
		printf("********************************\n");
	}
};
// FUN��ES PARA TESTE [DEVEM SER APAGADAS]