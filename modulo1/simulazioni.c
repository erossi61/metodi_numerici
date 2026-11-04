#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../include/random.h"
#include "../include/reticolo.h"
#include "../include/microcanonico.h"
#include "../include/metropolis.h"

int main(int insert, char **termini)
{
	long int sample;
	double beta, alpha, epsilon;
	int inizializzazione;
	unsigned long seed;
	char nome_file[50];
	if (insert != 8)
	{ /*se abbiamo digitato più di due parole o meno ci
	  spiega come far funzionare il programma*/
		printf("Per usare il programma è necessario inserire, dopo il nome del programma:\n"
			   "sample = il numero dicampionamenti che si vuole fare\n"
			   "beta = temperatura simulazione\n"
			   "seed = seme del generatore di numeri casuali\n"
			   "alpha = angolo del metropolis\n"
			   "epsilon = probabilità di utilizzo di metropolis o microcanonico (= 1 solo metropolis)\n"
			   "inizializzazione = tipo di inizializzazione (caldo = 0 / freddo = 1)\n"
			   "file di dati = nome del file nel quale vengono scritti i dati\n"
			   "La forma da usare è:\n");
		printf("%s con accanto il numero campionamenti, beta, seed, alpha, epsilon, inizializzazione, file dati.\n", termini[0]);
		printf("File compilato con L = %d\n", L);
		printf("In uscita viene fornito BOOOO.\n");

		return 1;
	}
	else
	{
		sample = atol(termini[1]); // salva il numero di campionamenti richiesti
		beta = atof(termini[2]);
		seed = strtoul(termini[3], NULL, 10);
		alpha = atof(termini[4]);
		epsilon = atof(termini[5]);
		inizializzazione = atoi(termini[6]);
	}

	if (sample <= 0 || epsilon < 0.0 || epsilon > 1.0 || alpha <= 0.0)
	{
		printf("I parametri inseriti sono sbagliati: sample <= 0, epsilon < 0.0,  epsilon > 1.0, alpha <= 0.0\n");
		return 1;
	}

	strcpy(nome_file, termini[7]); // BISOGNA CONTROLLARE NOME FILE

	myrand_init(seed, seed + 127);
	vicini_period();
	// inizializzare il reticolo a seconda di come abbiamo scritto in fase di compilazione
	if (inizializzazione == 0)
	{
		caldo();
	}
	else if (inizializzazione == 1)
	{
		freddo();
	}
	else
	{
		printf("Hai sbagliato a scrivere cretino!\n"
			   "E' necessario scrivere o 1 = freddo o 0 = caldo\n");
		return 1;
	}

	FILE *fpgauss = fopen("dati/dati_gauss.txt", "w");

	if (fpgauss == NULL)
	{
		printf("Errore nell'apertura del file!\n");
		return 1;
	}
	long int acc = 0;
	double r;
	int i;
	for (i = 0; i < sample; i++)
	{
		r = myrand();
		if (r < epsilon)
		{
			acc += sweep_metropolis(alpha, beta);
		}
		else
		{
			sweep_micro_can();
		}
	}
	printf("accetanza %ld\n", acc);
	fclose(fpgauss);
	return 0;
}