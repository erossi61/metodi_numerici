# Come funzionano i diversi file della libreria

## pgc32min.c e random.c

pgc32min contiene i dettagli del generatore di numeri casuali mentre random lo implementa. Random contiene due funzioni fondamentali che verranno usate sempre:

- **`myrand_init(unsigned long int initstate, unsigned long int initseq)`**: chiama il generatore di numeri casuali e lo fa partire fornendogli i valori iniziali che inseriamo noi. Il generatore di numeri casuali deve essere iniziallizato una sola volta all'inizio del main altrimentiogni volta ripartirebbe da capo e darebbe sempre gli stessi numeri (soprattutto se metto sempre gli stessi semi iniziali). Generalmente si inizializza con il tempo macchina.
  Esempio di implementazione:

  ```c
  const unsigned long int seme1 = (unsigned long int)time(NULL);
  const unsigned long int seme2 = seme1 + 157;
  #deve essere un numero primo grandicello
  myrand_init(seme1, seme2);
  ```

- **`double myrand(void)`**: questa funzione non prende niente in ingresso, chiama il generatore di numeri casuali (che ha effettivamente generato un numero) e lo divide per un numero enorme (probabilemte sicuramente più grande di long int) di modo da ottenere in unscita un numero con la virgola compreso tra 0 e 1 escluso. A questo punto, nei nostri programmi dobbiamo usare myrandinit per far partire il generatore e poi prendere myrand di modo da acere il numero casuale desiderato tra 0 e 1.
  Esempio di implementazione:
  ```c
  z = myrand();
  ```

## box_muller.c

Definisce 3 funzioni corrispondente ai 3 possibili box muller utilizzabili.

- **`void bm_base(double *restrict y1, double *restrict y2)`**: box muller normale. Prende due numeri casuali generati con distribuzione uniforme tra 0 e 1. Con questi due valori costruisce due nuovi numeri distribuiti con una gaussiana. La funzione non produce un vero e proprio output sotto forma di return. La funzione in ingresso prende le posizioni della memoria in cui vivono y1 e y2 e alla fine, una volta calcolati y1 e y2 i valori ottenuti vengono inseriti in tale indirizzo di memoria. Questo metodo è più lento di quello polare dato checalcolare le funzioni trigonometriche è pesante.
- **`double bm_1gauss_pol(void)`**: Il box muller isotropo seleziona con probabilità uniforme dei punti nel cerchio il che equivale a scegliere un angolo con distrib uniforme tra 0 e 2pi e un raggio r^2 tra 0 e 1. La distribuzione uniforme in coordinate polari è dr^2dphi/2pi. L'unica differenza tra bm1 e bm2 è che bm1 seleziona un punto lo restituisce come output dalla funzione mentre bm2 genera due numeri gaussiani e li restituisce come puntatori ovvero li inserisce negli indirizzi di memoria che gli abbiamo dato in input.
- **`void bm_2gauss_pol(double *restrict g1, double *restrict g2)`**: box muller isotropo con due gaussiane. Restituisce sotto forma di puntatori messi nell'input della funzione due numeri gaussiani.

## reticolo.c

Contiene tutte le funzioni asociate ai dettagli del reticolo.

- **`void somma_vicini(int i, int j, int k, double *Sx, double *Sy)`** : funzione contenuta nel file reticolo.h. Fa la somma di tutti i primi vicini di un sito sia lungo x che lungo y e sia avanti che indietro. Restituisce questa somma come indirizzi nella definizione della funzione.

```c
*Sx = spin[ip[i]][j][k].x + spin[i][ip[j]][k].x + spin[i][j][ip[k]].x + spin[im[i]][j][k].x + spin[i][im[j]][k].x + spin[i][j][im[k]].x;
*Sy = spin[ip[i]][j][k].y + spin[i][ip[j]][k].y + spin[i][j][ip[k]].y + spin[im[i]][j][k].y + spin[i][im[j]][k].y + spin[i][j][im[k]].y;
```

- **`void vicini_period(void)`** inizializza le condizioni periodiche al contorno. Quando ci troviamo in L-1 e avanziamo andiamo in 0 e vicevera (se ci troviamo in 0 e indietreggiamo ci troviamo in L-1).
- **`void freddo(void)`**: inizializza il reticolo con configurazione fredda. Tutti gli spin lungo x vengono inizializzati con 1.0 e quello lungo y con 0.0.
  - Valori attesi: energia = -3, |m| = sqrt(mx^2 + my^2) = 1.
- **`void caldo(void)`**: inizializza il reticolo con configurazione calda. Viene generato un numero casuale dal quale di ricava un angolo, poi tutti gli spin lungo x vengono inizializzati con sin(theta) e quello lungo y con cos(theta).
  - Valori attesi: energia ~ 0, |m| ~ 0.
- **`void rinormalizza(void)`**: Rinormalizza i vettori di sito lungo x e lungo y. Controllo necessario dato che i vettori nel modello O(N) devono essere normalizzati ad uno (operativamente il computer non li mantiene sempre normalizzati ad uno).
- **`double densita_energia(void)`**: Calcola l'energia del reticolo come:

```c
energia -= spin[i][j][k].x * (spin[ip[i]][j][k].x + spin[i][ip[j]][k].x + spin[i][j][ip[k]].x) + spin[i][j][k].y * (spin[ip[i]][j][k].y + spin[i][ip[j]][k].y + spin[i][j][ip[k]].y);
```

(spin del sito \* somma sui primi vicini) e successivamente calcola la densità d'energia.
Restituisce il valore della densità d'energia.

- **`void magnetizzazione(double *mx, double *my)`**: Calcola la magnetizzazione lungo x e lungo y come la somma di tutti gli spin lungo x e lungo y del reticolo. Restituisce questi valori/volume come indirizzi di puntatori nella definizione della magnetizzazione. Viene usato come:

```c
double mx, my;
magnetizzazione(&mx, &my);
fprintf(fpdata, "%.12f %.12f\n",mx, my);
```

## metropolis.c

Funzioni necessarie per applicare il metropolis.

- **`int metropolis(int i, int j, int k, int ripetizione_max, double alpha, double beta)`**: Prende in input la temperatura, l'angolo dell'ampiezza del metropolis e il numero di volte in cui si fa il metropolis sullo stesso stesso sito per evitare di calcolare più volte la somma sui primi vicini. Somma sui vicini del sito preso in considerazione, poi definisce un angolo theta che sia simmetrico rispetto a 0 per poter applicare il metropolis come:

```c
theta = alpha*(1 - 2*myrand());
```

definisce i nuovi spin lungo x e y come:

```c
nuovo_x = spin[i][j][k].x * coseno + spin[i][j][k].y * seno;
nuovo_y = -spin[i][j][k].x * seno + spin[i][j][k].y * coseno;
```

Calcola la differenza di energia tra la configurazione di partenza e quella nuova come

```c
delta_E = -((nuovo_x - spin[i][j][k].x) * Sx + (nuovo_y - spin[i][j][k].y) * Sy);
```

Poi decide se accettare o meno lo stato di prova; lo accetta se una di queste due condizioni viene soddisfatta

```c
delta_E <= 0;
myrand() < exp(-beta * delta_E);
```

Ogni volta che lo stato viene accettato contiamo +1. La funzione ritorna il numero di stati di prova accettati.

- **`long sweep_metropolis(int ripetizione_max, double alpha, double beta)`**: Fa uno sweep metropolis dell'intero reticolo e ritorna il numero di volte che il passo metropolis viene accettato.

## microcanonico.c

Funzioni necessarie per realizzare un update microcanonico.

**`void micro_can(int i, int j, int k)`**: Prende in ingresso il sito seul quale fare il microcanonico. Controlla che il modulo quadro della somma dei primi vicini sia sopra soglia altrimenti le operazioni del microcanonico vanno all'infinito. Se soddisfa questa condizione si procede con il microcanonico ovvero con la proiezione degli spin:

```c
srSr = spin[i][j][k].x * Sx + spin[i][j][k].y * Sy;
coeff = 2 * srSr / Sr_quadro;
spin[i][j][k].x = coeff * Sx - spin[i][j][k].x;
spin[i][j][k].y = coeff * Sy - spin[i][j][k].y;
```

**`void sweep_micro_can(void)`**: fa uno sweep microcanonico dell'intero reticolo.
