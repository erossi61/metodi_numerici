#ifndef RANDOM_H
#define RANDOM_H

// initialize the random number generator
void myrand_init(unsigned long int initstate, unsigned long int initseq);
// unsigned long int è un intero molto lungo che si stampa con %lu
// unsigned indica che non possono essere negativi
/*la prima parola indica cosa restituisce la funzione. in questo
caso la funzione non restituisce niente ma fa solo delle operazioni.
In input ha due interi (lunghi).*/

//  return a random number in [0,1)
double myrand(void);
/*la funzione my rand restituisce un numero con la virgola dato che ha double come prima parola.
La funzione rand non prende niente in ingresso. Funziona anche senza.*/
/*in questo file vengono definte due funzioni ma non ne viene definito il funzionamento.
Ne definiamo solo in tipo di input e il tipo di output.
La funzione myrand_init inizializza il generatore di numeri casuali.*/
#endif
