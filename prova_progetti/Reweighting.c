#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../include/random.h"
#include "../include/box_muller.h"

/*box muller isotropo condue gaussiane*/

/*Vogliamo vedere come il reweighting puo' creare problemi (importance sampling).
Calcoliamo il valor medio di una variabile rispoetto ad una gaussiana
con valor medio mu e varianza 1: N(mu,1) ma campionando dati da una
gaussiana standard com media 0 e varianza 1 (quella ottenuta con il box muller).
*/

int main(int insert, char **termini)
{
	long int sample;
	double mu;
	if (insert != 3)
	{ /*se abbiamo digitato più di due parole o meno ci
	  spiega come far funzionare il programma*/
		printf("Per usare il programma è necessario inserire il numero di\n"
			   "campionamenti che si vuole fare dopo il nome del programma.\n"
			   "Inoltre bisogna inserire il valore di mu = mesia della gaussiana di riferimento.\n"
			   "La forma da usare è:\n");
		printf("%s con accanto il numero campionamenti desiderati e dopo il valore di mu desiderato\n", termini[0]);
		printf("In uscita viene fornita una distribuzione gaussiana di punti\n"
			   "campionata da una distrizione uniforme.\n");

		return 1;
	}
	else
	{
		sample = atol(termini[1]); // salva il numero di campionamenti richiesti
		mu = atof(termini[2]);	   // salva il valor medio scelto per la gaussiana
	}

	if (sample <= 0)
	{
		printf("Il numero di campionamenti deve essere positivo e non nullo.");
		return 1;
	}

	(void)mu;
}