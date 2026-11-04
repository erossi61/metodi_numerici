// test.c: controlla inizializzazione, misure, microcanonico e rinormalizzazione
// prima di lanciare qualsiasi simulazione.
//
// Compilazione (dentro modulo1):
//   gcc -O2 -Wall -Wextra -std=c99 -DL=8 -I../include test.c ../lib/random.c ../lib/pcg32min.c ../lib/reticolo.c ../lib/microcanonico.c -o test -lm
// Esecuzione:
//   ./test

#include <stdio.h>
#include <math.h>

#include "../include/random.h"
#include "../include/reticolo.h"
#include "../include/microcanonico.h"

// stampa energia e magnetizzazione della configurazione attuale
void stampa_misure(const char *nome)
{
	double mx, my;
	magnetizzazione(&mx, &my);
	printf("%-28s energia = %+.12f   |m| = %.12f\n", nome, densita_energia(), sqrt(mx * mx + my * my));
}

int main(void)
{
	double e_prima, e_dopo, x0, y0, norma, max_err;
	int i, j, k;

	myrand_init(12345, 678);
	vicini_period();

	printf("L = %d\n\n", L);

	// TEST 1: partenza fredda -> energia = -3 e |m| = 1 esatti
	printf("TEST 1: partenza fredda (atteso: energia = -3, |m| = 1)\n");
	freddo();
	stampa_misure("freddo");

	// TEST 2: partenza calda -> energia ~ 0 e |m| ~ 0
	// (fluttuazioni dell'ordine di 1/sqrt(L^3))
	printf("\nTEST 2: partenza calda (atteso: energia ~ 0, |m| ~ %.3f)\n", 1.0 / sqrt(VOLUME));
	caldo();
	stampa_misure("caldo");

	// TEST 3: gli spin della partenza calda hanno lunghezza 1
	max_err = 0.0;
	for (i = 0; i < L; i++)
		for (j = 0; j < L; j++)
			for (k = 0; k < L; k++)
			{
				norma = sqrt(spin[i][j][k].x * spin[i][j][k].x + spin[i][j][k].y * spin[i][j][k].y);
				if (fabs(norma - 1.0) > max_err)
					max_err = fabs(norma - 1.0);
			}
	printf("\nTEST 3: lunghezza degli spin (atteso: errore ~ 1e-16)\n");
	printf("max | |s| - 1 | = %.2e\n", max_err);

	// TEST 4: uno sweep microcanonico conserva l'energia
	printf("\nTEST 4: sweep microcanonici (atteso: differenza ~ 1e-13 o meno)\n");
	e_prima = densita_energia();
	for (i = 0; i < 100; i++)
		sweep_micro_can();
	e_dopo = densita_energia();
	printf("energia prima = %+.15f\nenergia dopo  = %+.15f\ndifferenza    = %.2e\n", e_prima, e_dopo, fabs(e_dopo - e_prima));

	// TEST 5: due riflessioni sullo stesso sito riportano allo spin iniziale
	printf("\nTEST 5: doppia riflessione sul sito (0,0,0) (atteso: differenza ~ 1e-16)\n");
	x0 = spin[0][0][0].x;
	y0 = spin[0][0][0].y;
	micro_can(0, 0, 0);
	printf("dopo 1 riflessione: (%+.6f, %+.6f)  (diverso dall'iniziale)\n", spin[0][0][0].x, spin[0][0][0].y);
	micro_can(0, 0, 0);
	printf("dopo 2 riflessioni: differenza = %.2e\n", fabs(spin[0][0][0].x - x0) + fabs(spin[0][0][0].y - y0));

	// TEST 6: rinormalizza() riporta tutti gli spin a lunghezza 1
	printf("\nTEST 6: rinormalizzazione (atteso: errore ~ 1e-16)\n");
	spin[1][2][3].x *= 1.5; // rovino apposta uno spin
	rinormalizza();
	norma = sqrt(spin[1][2][3].x * spin[1][2][3].x + spin[1][2][3].y * spin[1][2][3].y);
	printf("|s| dopo rinormalizza() = %.15f\n", norma);

	return 0;
}