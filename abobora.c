#include <stdio.h>
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

// FUNÇÕES PARA TESTE [DEVEM SER APAGADAS]
char* displayCaracteristica(struct Abobora abobora, int qualExibir) {
	switch (qualExibir) {
		case 0:
			switch (abobora.caractetisticas[qualExibir]) {
			case 0:
				return "Sabor: Doce\n";
				break;
			case 1:
				return "Sabor: Salgada\n";
				break;
			case 2:
				return "Sabor: Salgada\n";
				break;
			}
			break;
		case 1:
			switch (abobora.caractetisticas[qualExibir]) {
			case 0:
				return "Tamanho: Grande\n";
				break;
			case 1:
				return "Tamanho: Pequena\n";
				break;
			case 2:
				return "Tamanho: Pequena\n";
				break;
			}
			break;
		case 2:
			switch (abobora.caractetisticas[qualExibir]) {
			case 0:
				return "Cor: Verde\n";
				break;
			case 1:
				return "Cor: Laranja\n";
				break;
			case 2:
				return "Cor: Laranja\n";
				break;
			}
			break;
		case 3:
			switch (abobora.caractetisticas[qualExibir]) {
			case 0:
				return "Casca: Grossa\n";
				break;
			case 1:
				return "Casca: Fina\n";
				break;
			case 2:
				return "Casca: Fina\n";
				break;
			}
			break;
	}
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
// FUNÇÕES PARA TESTE [DEVEM SER APAGADAS]