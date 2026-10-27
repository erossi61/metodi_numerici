/*provare a calcolare pi greco con il simple sampling*/
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../include/random.h"

int main(int insert, char **termini)
{
	long int sample;
	const double real_pi = 3.1415926535897932384626433;
	/*vogliamo che il programma prenda in ingresso il numero di campionamenti
	necessari per avere una simulazione sensata. lo scopo sarebbe
	avere la possibilità di inserire questi valori da terminale
	in fase di compitazione e esecuzione.
	Scrivere un ciclo if che controlli che il programma è stato eseguito
	nel modo giusto. parole è il controllo che verifica che siano state
	scritte solo due cose separate da spazio in fase di esecuzione
	(nome del programma da eseguire e numero di campionamenti).*/
	if (insert != 2)
	{ /*se abbiamo digitato più di due parole o meno ci
	  spiega come far funzionare il programma*/
		printf("Per usare il programma è necessario inserire il numero di\n"
			   "campionamenti che si vuole fare dopo il nome del programma.\n"
			   "La forma da usare è:\n");
		printf("%s campionamenti", termini[0]);
		printf("In uscita viene fornita la stima di pi greco con il simple sampling Monte carlo.");

		return 0;
	}
	else /*se abbiamo messo il giusto numero di termini in ingresso prende
	  il numero di campionamenti ed esegue il codice*/
	{
		sample = atol(termini[1]); // salva il numero di campionamenti richiesti
	}

	if (sample <= 0)
	{
		printf("Il numero di campionamenti deve essere positivo e non nullo.");
		return 1;
	}

	/*inizializzare pare delle variabili necessarie, soprattutto i seed
	di partenza del generatore di numeri casuali. è comodo usare il
	tempo macchina di modo che i seed siano sempre diversi ad ogni esecuzione
	e quindi che i numeri casuali generati siano sempre diversi.*/

	long int contatore, i;
	double x, y, rispi, errpi;
	const unsigned long int seme1 = (unsigned long int)time(NULL);
	/*indica che il valore che gli verrà assegnato e un intero lungo che deve
	rimanere costante durante tutta l'esecuzione*/
	const unsigned long int seme2 = seme1 + 157;
	/*consigliabile che la differenza tra i due semi sia un numero primo di modo da non avere
	strani schemi ripetitivi*/

	/*dobbiamo definire il numero di punti che butteremo nel cerchio: sample. numero
	di campionamenti all'interno del quadrato di lato 1x1.*/
	myrand_init(seme1, seme2);
	contatore = 0;

	FILE *fp = fopen("dati/punti_pi.txt", "w");

	if (fp == NULL)
	{
		printf("Errore nell'apertura del file!\n");
		return 1;
	}

	myrand_init(seme1, seme2);
	contatore = 0;

	for (i = 0; i < sample; i++)
	{ /*per ogni campionamento prendiamo x, y e vediamo se il punto sta nel cerchio*/
		x = myrand();
		y = myrand();
		fprintf(fp, "%f %f\n", x, y);

		if (x * x + y * y < 1)
		{
			contatore += 1;
			/*se il punto viene accettato aumentiamo contatore che ci dice quanti punti accettiamo.
			se la condizione di accettazione non è soddisfatta passa semplicemente ad un successivo campionamento*/
		}
	}

	fclose(fp);

	rispi = (double)contatore / (double)sample;
	errpi = sqrt(rispi - rispi * rispi) / sqrt((double)sample - 1); /*l'errore in questo caso è la deviazione standard/il numero di estrazioni
			 In statistica, per una variabile che può assumere solo i valori 0 o 1 (distribuzione di Bernoulli), la varianza
			 di una singola estrazione è esattamente $p(1 - p)$.*/

	rispi = rispi * 4;
	errpi = errpi * 4;
	printf("Valori trovati:\n");
	printf("Stima_pi = %f \n", rispi);
	printf("Sigma = %f \n", errpi);

	printf("Differenza tra stima e valore reale = %f\n", rispi - real_pi);
	/*Calcolare errore assoluto (stima pi-real pi) e dividere per la deviazione standard
	dalla maedia per vedere se la simulazione è andata bene o meno. se è un numero
	piccolo allora la simulazione è andata bene*/
	printf("(errore assoluto)/sigma = %f\n", (rispi - real_pi) / errpi);
	return 0;
}