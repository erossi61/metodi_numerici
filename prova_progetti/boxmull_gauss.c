/*confrontare box muller e box muller polare per generare dei numeri casuali con una
distribuzione gaussiana.
Generiamo una distribuzione di probabilità non uniforme a partire da una
distribuzione uniforme: Metodo del cambio di variabili.*/
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../generatore/random.h"

// Definiamo M_PI se il compilatore non lo fa in automatico
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

/*box muller normale: prende due numeri casuali generati con distribuzione
uniforme tra 0 e 1. costruisce poi, con questi due valori, due nuovi numeri distribuiti
con una gaussiana. La funzione non produce un vero e proprio output sotto forma di return.
La funzione in ingresso prende le posizioni della memoria in cui vivono y1 e y2 e
alla fine, una volta calcolati y1 e y2 i valori ottenuti vengono inseriti in tale indirizzo di memoria.
Questo metodo è più lento di quello polare dato checalcolare le funzioni trigonometriche è pesante. */
void boxm_base(double *restrict y1, double *restrict y2)
{
	double x, z;
	x = -2 * log(myrand());
	z = 2 * M_PI * myrand();

	*y1 = sqrt(x) * cos(z);
	*y2 = sqrt(x) * sin(z);
}
/*box muller isotropo con gaussiana.
 */
double bm1_polar(void)
{
	double x, y, s, z1;
	/*Schema do while:
	Il programma esegue le istruzioni racchiuse dentro le parentesi graffe del do.
	Alla fine del blocco, viene valutata l'espressione logica (la condizione) nel while.
	Se la condizione è vera (true), il programma torna all'inizio e ripete il blocco.
	Se la condizione è falsa (false), il ciclo termina e il programma prosegue con le
	istruzioni successive.
	Essenzialmente continua ad estrarre x e y finchè non riesce ad estrarre un punto dentro il cerchio
	unitario. A quel punto accetta x e y e genera il numero con distribuzione gaussiana.
	Il box muller isotropo seleziona con probabilità uniforme punti nel cerchio il che
	equivale a scegliere un angolo con distrib uniforme tra 0 e 2pi e un raggio r^2 tra 0 e 1.
	la distribuzione uniforme in coordinate polari è dr^2dphi/2pi. L'unica differenza tra bm1 e bm2
	è che bm1 seleziona un punto lo restituisce come output dalla funzione mentre bm2
	genera due numeri gaussiani e li restituisce come puntatori ovvero li inserisce negli indirizzi
	di memoria che gli abbiamo dato in input*/
	do
	{
		x = 1 - 2 * myrand();
		y = 1 - 2 * myrand();
		s = x * x + y * y;
	} while (s > 1);

	z1 = x * sqrt(-2 * log(s) / s);

	return z1;
}

/*box muller isotropo condue gaussiane*/
void bm2_polar(double *restrict g1, double *restrict g2)
{
	double x, y, s;
	do
	{
		x = 1 - 2 * myrand();
		y = 1 - 2 * myrand();
		s = x * x + y * y;
	} while (s > 1);

	*g1 = x * sqrt(-2 * log(s) / s);
	*g2 = y * sqrt(-2 * log(s) / s);
}

int main(int insert, char **termini)
{
	long int sample;
	if (insert != 2)
	{ /*se abbiamo digitato più di due parole o meno ci
	  spiega come far funzionare il programma*/
		fprintf(stdout, "Per usare il programma è necessario inserire il numero di\n"
						"campionamenti che si vuole fare dopo il nome del programma.\n"
						"La forma da usare è:\n");
		fprintf(stdout, "%s con accanto il numero campionamenti desideari\n", termini[0]);
		fprintf(stdout, "In uscita viene fornita la stima di pi greco con il simple sampling Monte carlo.\n");

		return 1;
	}
	else
	{
		sample = atol(termini[1]); // salva il numero di campionamenti richiesti
	}

	if (sample <= 0)
	{
		fprintf(stdout, "Il numero di campionamenti deve essere positivo e non nullo.");
		return 1;
	}

	int i;
	const unsigned long int seme1 = (unsigned long int)time(NULL);
	const unsigned long int seme2 = seme1 + 157;

	myrand_init(seme1, seme2);

	FILE *fpgauss = fopen("dati_gauss.txt", "w");

	if (fpgauss == NULL)
	{
		printf("Errore nell'apertura del file!\n");
		return 1;
	}

	FILE *fprand = fopen("dati_rand.txt", "w");

	if (fprand == NULL)
	{
		printf("Errore nell'apertura del file!\n");
		return 1;
	}

	double tm1, tm2, x, x2, x4;
	/*Vogliamo calcolare <x>, <x^2> e <x^4> usando tutti i diversi box muller.
	calcoliamo <x> con i sample pari e <x^2> con i sample dispari.
	La dicitura sample % 2==1 indica il numero del campionamento diviso due che fornisce
	1 come resto ovvero seleziona i campionamenti dispari*/
	/*Media di x: somma valori x/numero di x trovati.
	Media di x^2: somma valori x^2/numero di x.
	Media di x^4: somma valori x^4/numero di x.
	Calcoliamo queste cose solo con quello gaussiano polare.
	Inoltre si fa una valutazione su quale dei due algoritmi (isotropo e non) è più veloce.*/

	// BOX MULLER NORMALE VS BOX MULLER DOPPIA GAUSSIANA
	/*Decidiamo il nuemro di campionametni che vogliamo fare. Dato che il box muller
	fornisce due punti ad ogni campionamento si ha che se facessimo effettivamente
	il numero di campionamenti richiesti avremmo una sovranumerazione di valori ottenuti infatti
	per ogni campionamento estraiamo due numeri (otterremo il doppio dei numeri richiesti in sample).
	Dobbiamo mettere un controllo: se sample è dispari allora dobbiamo aggiungere un'estrazione
	in più per poter avere il corretto numero di sample desiderati.*/
	x = 0.0;
	x2 = 0.0;
	x4 = 0.0;
	double z;
	for (i = 0; i < sample; i++)
	{
		z = myrand();
		fprintf(fprand, "%f\n", z);
	}
	fclose(fprand);

	for (i = 0; i < sample / 2; i++)
	{
		bm2_polar(&tm1, &tm2);
		fprintf(fpgauss, "%f\n%f\n", tm1, tm2);

		x += (tm1 + tm2);
		x2 += (pow(tm1, 2) + pow(tm2, 2));
		x4 += (pow(tm1, 4) + pow(tm2, 4));
	}
	if (sample % 2 == 1)
	{
		tm1 += bm1_polar();
		fprintf(fpgauss, "%f\n", tm1);

		x += (tm1);
		x2 += (pow(tm1, 2));
		x4 += (pow(tm1, 4));
	}
	fclose(fpgauss);

	x /= (double)sample;
	x2 /= (double)sample;
	x4 /= (double)sample;

	double sigmax, sigmax2, sigmax4;
	/*errore di una stima calcolata è, per il teorema del limite centrale,
	errore standard=sqrt(varianza/campionamenti).
	varianza=(valore atteso y^2)-(valore atteso y)^2 con y=x,x^2,x^4.
	Order	|	Non-central moment E[X^p]	|	Central moment E[(X−μ)^p]
	0	|	 1	|	1
	1	|	μ	|	0
	2	|	μ^2 + σ^2	|	σ^2
	3	|	μ^3 + 3μσ^2	|	 0
	4	|	μ^4 + 6μ^2σ^2 + 3σ^4	|	3σ^4
	5	|	μ^5 + 10μ^3σ^2 + 15μσ 4	|	0
	6	|	μ^6 + 15μ^4σ^2 + 45μ^2σ^4 + 15 σ^6	|	15σ^6
	7	|	μ^7 + 21μ^5σ^2 + 105μ^3σ^4 + 105μσ^6	|	0
	8	|	μ^8 + 28μ^6σ^2 + 210μ^4σ^4 + 420μ^2σ^6 + 105σ^8	|	105σ^8*/

	sigmax = sqrt((1 - 0 - 0.0) / (double)sample);
	printf("<x>-esatto = %f \n", x - 0.0);
	printf("sigma_teorico = %f \n", sigmax);
	printf("Distanza del generatore costruito da una gaussiana ideale:\n"
		   "(<x>-esatto)/sigma_teorico= %f \n\n",
		   x / sigmax);

	sigmax2 = sqrt((3.0 - 1.0) / (double)sample);
	printf("<x^2>-esatto = %f \n", x2 - 1.0);
	printf("sigma_teorico = %f \n", sigmax2);
	printf("Distanza del generatore costruito da una gaussiana ideale:\n"
		   "(<x^2>-esatto)/sigma_teorico= %f \n\n",
		   (x2 - 1) / sigmax2);

	sigmax4 = sqrt((105.0 - 9.0) / (double)sample);
	printf("<x^4>-esatto = %f \n", x4 - 3.0);
	printf("sigma_teorico = %f \n", sigmax4);
	printf("Distanza del generatore costruito da una gaussiana ideale:\n"
		   "(<x^4>-esatto)/sigma_teorico= %f \n\n",
		   (x4 - 3) / sigmax4);

	/*Le distanze tra i valori trovati e quelli attesi in una simulazione monte carlo deve
	essere compresa tra -2 e 2 generalmente.*/
	return 0;
}