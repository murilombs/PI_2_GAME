#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "abobora.h"

/*	Aqui vamos gerar o código indentificador de cada abobora
*	vamos precissar armazenar os códigos gerados anteriormente
*	para saber qual deve ser o proximo.
*/
void gera_abobora_code(struct Abobora *abobora, int anterior) {
	abobora->semente.aboboraCode = anterior + 1;
	abobora->estagio = 0;
}

// Retorna a posição da abobora no array dado seu aboboraCode
int buscadorDeAbobora(int aboboraCode, int aboborasCriadas, struct Abobora* aboboras) {
	for (int i = 0; i < aboborasCriadas; i++) {
		if (aboboraCode == aboboras[i].semente.aboboraCode) {
			return i;
		}
	}
}

// Guarda o timestamp de criação da abobora + tempo ate o ciclo seguinte
// O TEMPO DE MUDANÇA DO PROXIMO CICLO SERA O TEMPO DE CRIAÇÃO MAIS 60 SEG
void tempoDeCiclo(struct Abobora* abobora, time_t* timestamp, int acrescimo) {
	abobora->tempoCiclo = timestamp + acrescimo;
}

void mudancaDeCiclo(struct Abobora* abobora, int aboborasCriadas, int timestampAtual) {
	for (int idx = 0; idx < aboborasCriadas; idx++) {
		if (timestampAtual > abobora[idx].tempoCiclo && abobora[idx].estagio < 3) {
			abobora[idx].estagio += 1;
			tempoDeCiclo(&abobora[idx], timestampAtual, 10);
			printf("O ciclo de #%d é %d\n", abobora[idx].semente.aboboraCode, abobora[idx].estagio);
		}
	}
}


void displayCaracteristica(char** caracteristicas, struct Abobora* abobora) {
	char* sabor;
	char* tamanho;
	char* cor;
	char* casca;

	char* concatenados[60];

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

	sprintf(concatenados, "%s,\n%s,\n%s,\n%s\n", sabor, tamanho, cor, casca);
	*caracteristicas = concatenados;
}