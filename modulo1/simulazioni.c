#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../include/random.h"
#include "../include/reticolo.h"
#include "../include/microcanonico.h"
#include "../include/metropolis.h"

#define ripetizioni_max 3
#define misura_ogni 5

int main(int insert, char **termini)
{
	long int sample;
	int inizializzazione;
	unsigned long seed;
	double beta, alpha, epsilon;
	char nome_file[260];
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
			   "file di dati = nome del file dati va scritto come: dati/prova.txt (se ci troviamo in modulo 1)\n"
			   "altrimenti come ../dati/prova.txt (se ci troviamo metodi numerici e deve cercare la cartella dati)\n"
			   "La forma da usare è:\n");
		printf("%s con accanto il numero campionamenti, beta, seed, alpha, epsilon, inizializzazione, file dati.\n", termini[0]);
		printf("File compilato con L = %d\n", L);
		printf("In uscita viene fornito un file che ha come prime righe i dati di input.\n"
			   "Poi fornisce 3 colonne E, mx, my con una riga per misurazione\n");

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

	if (sample <= 0 || epsilon <= 0.0 || epsilon > 1.0 || alpha <= 0.0)
	{
		printf("I parametri inseriti sono sbagliati: serve sample > 0, epsilon > 0.0,  epsilon <= 1.0, alpha > 0.0\n");
		return 1;
	}

	// controlla che il nome del file entri in nome_file prima di copiarlo
	if (strlen(termini[7]) >= sizeof(nome_file))
	{
		printf("Il nome del file e' troppo lungo\n");
		return 1;
	}
	strcpy(nome_file, termini[7]);

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

	FILE *fpdata = fopen(nome_file, "w");

	if (fpdata == NULL)
	{
		printf("Errore nell'apertura del file!\n");
		return 1;
	}

	fprintf(fpdata, "# L = %d\n# beta = %.10f\n# seed = %lu\n# alpha = %f\n# epsilon = %f\n", L, beta, seed, alpha, epsilon);
	fprintf(fpdata, "# sample = %ld\n# inizializzazione = %d\n", sample, inizializzazione);
	fprintf(fpdata, "# ripetizioni_max = %d\n# misura_ogni = %d\n", ripetizioni_max, misura_ogni);
	fprintf(fpdata, "# colonne: densita_energia mx my\n");

	long int acc = 0;
	double r = 0.0;
	long int i, metropolis_totali = 0;
	double mx, my;
	clock_t tempo_iniziale = clock();
	for (i = 0; i < sample; i++)
	{
		r = myrand();
		if (r < epsilon)
		{
			acc += sweep_metropolis(ripetizioni_max, alpha, beta);
			metropolis_totali += ripetizioni_max;
		}
		else
		{
			sweep_micro_can();
		}
		if ((i + 1) % misura_ogni == 0) // misuro solo ogni misura_ogni passi
		{
			rinormalizza();
			magnetizzazione(&mx, &my);
			fprintf(fpdata, "%.12f %.12f %.12f\n", densita_energia(), mx, my);
		}
		/*
		rinormalizza();
		magnetizzazione(&mx, &my);
		fprintf(fpdata, "%.12f %.12f %.12f\n", densita_energia(), mx, my);
		*/
	}

	double tempo_totale = (double)(clock() - tempo_iniziale) / CLOCKS_PER_SEC;
	fprintf(fpdata, "# tempo CPU = %f s\n", tempo_totale);

	if (metropolis_totali > 0)
	{
		double accettanza_metr = (double)acc / ((double)metropolis_totali * VOLUME);
		fprintf(fpdata, "# accettanza = %f\n", accettanza_metr); // NUOVO: nel file
	}

	fclose(fpdata);
	return 0;
}