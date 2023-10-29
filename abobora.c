#include "abobora.h"

/*	Aqui vamos gerar o código indentificador de cada abobora
*	vamos precissar armazenar os códigos gerados anteriormente
*	para saber qual deve ser o proximo.
*/
void gera_abobora_code(struct Abobora *abobora, int anterior) {
	abobora->semente.aboboraCode = anterior + 1;
}
