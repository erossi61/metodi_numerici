COME FUNZIONANO I VARI FILE DELLA LIBRERIA

- **`pgc32min.c`** e **`random.c`**: pgc32min contiene i dettagli del generatore di numeri casuali mentre random lo implementa. Random contiene due funzioni fondamentali che verranno usate sempre:
  - **_`myrand_init(unsigned long int initstate, unsigned long int initseq)`_**: chiama il generatore di numeri casuali e lo fa partire fornendogli i valori iniziali che inseriamo noi. Il generatore di numeri casuali deve essere iniziallizato una sola volta all'inizio del main altrimentiogni volta ripartirebbe da capo e darebbe sempre gli stessi numeri (soprattutto se metto sempre gli stessi semi iniziali). Generalmente si inizializza con il tempo macchina.
    Esempio di implementazione:

    ```bash
    const unsigned long int seme1 = (unsigned long int)time(NULL);
    const unsigned long int seme2 = seme1 + 157;
    #deve essere un numero primo grandicello
    myrand_init(seme1, seme2);
    ```

  - **_`double myrand(void)`_**: questa funzione non prende niente in ingresso, chiama il generatore di numeri casuali (che ha effettivamente generato un numero) e lo divide per un numero enorme (probabilemte sicuramente più grande di long int) di modo da ottenere in unscita un numero con la virgola compreso tra 0 e 1 escluso. A questo punto, nei nostri programmi dobbiamo usare myrandinit per far partire il generatore e poi prendere myrand di modo da acere il numero casuale desiderato tra 0 e 1.
    Esempio di implementazione:
    ```bash
    z = myrand();
    ```

- **`box_muller.c`**: Definisce 3 funzioni corrispondente ai 3 possibili box muller utilizzabili.
  - **_`void bm_base(double *restrict y1, double *restrict y2)`_**: box muller normale. Prende due numeri casuali generati con distribuzione uniforme tra 0 e 1. Con questi due valori costruisce due nuovi numeri distribuiti con una gaussiana. La funzione non produce un vero e proprio output sotto forma di return. La funzione in ingresso prende le posizioni della memoria in cui vivono y1 e y2 e alla fine, una volta calcolati y1 e y2 i valori ottenuti vengono inseriti in tale indirizzo di memoria. Questo metodo è più lento di quello polare dato checalcolare le funzioni trigonometriche è pesante.
  - **_`double bm_1gauss_pol(void)`_**: Il box muller isotropo seleziona con probabilità uniforme dei punti nel cerchio il che equivale a scegliere un angolo con distrib uniforme tra 0 e 2pi e un raggio r^2 tra 0 e 1. La distribuzione uniforme in coordinate polari è dr^2dphi/2pi. L'unica differenza tra bm1 e bm2 è che bm1 seleziona un punto lo restituisce come output dalla funzione mentre bm2 genera due numeri gaussiani e li restituisce come puntatori ovvero li inserisce negli indirizzi di memoria che gli abbiamo dato in input.
  - **_`void bm_2gauss_pol(double *restrict g1, double *restrict g2)`_**: box muller isotropo con due gaussiane. Restituisce sotto forma di puntatori messi nell'input della funzione due numeri gaussiani.
