#include <math.h>

#include "../include/random.h"
#include "../include/box_muller.h"

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
void bm_base(double *restrict y1, double *restrict y2)
{
	double x, z;
	x = -2 * log(myrand());
	z = 2 * M_PI * myrand();

	*y1 = sqrt(x) * cos(z);
	*y2 = sqrt(x) * sin(z);
}
/*box muller isotropo con gaussiana.
 */
double bm_1gauss_pol(void)
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
void bm_2gauss_pol(double *restrict g1, double *restrict g2)
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
