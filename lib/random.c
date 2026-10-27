#include <math.h>
#include <stdint.h>

#include "../include/pcg32min.h"
#include "../include/random.h"

// initialization
void myrand_init(unsigned long int initstate, unsigned long int initseq)
{
	pcg32_srandom_r(&pcg32_random_state, (uint64_t)initstate, (uint64_t)initseq);
}
/*possiamo vedere che questa funzione chiama il generatore di numeri casuali
e lo fa partire fornendogli i valori iniziali che inseriamo noi nella funzione myrand_init()*/
/*il generatore di numeri casuali deve essere iniziallizato una sola volta all'inizio del main altrimenti
ogni volta ripartirebbe da capo e mi darebbe sempre gli stessi numeri (soprattutto se metto sempre gli stessi semi
iniziali)*/
// number in [0,1)
double myrand(void)
{
	return (double)pcg32_random_r(&pcg32_random_state) / (pow(2.0, 32.0));
}
/*questa funzione non prende niente in ingresso, chiama il generatore di numeri casuali che ha effettivamente
generato un numero e lo divide per un numero enorme (probabilemte sicuramente più grande di long int) di modo
da ottenere in unscita un numero con la virgola compreso tra 0 e 1 escluso.
A questo punto, nei nostri programmi dobbiamo usare myrandinit per far partire il generatore
e poi prendere myrand di modo da acere il numero casuale desiderato tra 0 e 1.*/