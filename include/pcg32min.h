#ifndef PCG32MIN_H
#define PCG32MIN_H

#include <math.h>
#include <stdint.h>

// *Really* minimal PCG32 code / (c) 2014 M.E. O'Neill / pcg-random.org
// Licensed under Apache License 2.0 (NO WARRANTY, etc. see website)

typedef struct
{
	uint64_t state;
	uint64_t inc;
} pcg32_random_t;

extern pcg32_random_t pcg32_random_state;

uint32_t pcg32_random_r(pcg32_random_t *rng);
void pcg32_srandom_r(pcg32_random_t *rng, uint64_t initstate, uint64_t initseq);
/*Questo file è incompresnibile ma contiene solo i dettagli di come funziona il
generatore di numeri casuali. Non penso sia necessario capirlo ma basta sapere che questo
file.h contiene la "libreria" o meglio le funzioni che definiscono il funzionamento del generatore di numeri casuali.
La funzione pcg32_srandom_r inizializza il generatore di numeri casuali.
Non restituisce niente e prende in ingresso gli stati inseriti in myrand_init(). */

#endif
