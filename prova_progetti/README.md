PROVA PROGETTI

Descrizione del funzionamento dei programmi contenuti in questa cartella: cosa fanno, a cosa servono, cosa usano in input e cosa forniscono in output. Vengono forniti anche i comandi per poter eseguire i codici.

- boxmull_gauss: confrontare box muller e box muller polare per generare dei numeri casuali con una
  distribuzione gaussiana.
  Generiamo una distribuzione di probabilità non uniforme a partire da una
  distribuzione uniforme: Metodo del cambio di variabili. Vogliamo calcolare il tempo di esecuzione di box muller normale con singola
  gaussiana e quello a doppia gaussiana polare.
  Successivamente il programma controlla quanto i dati simulati si avvicinano ad una reale distribuzione gaussiana.
  - Prende in input il numero di campionamenti che vogliamo fare

  ```bash
  cd ~/metodi_numerici/prova_progetti
  make
  ./boxmull_gauss 15
  ```

  - Fornisce in output due file di dati in formato txt; entrambi i file sono composti solo da una colonna:
    - dati_gauss.txt che contine i dati gaussiani campionati
    - dati_rand.txt che contiene i dati campionati con distribuzione uniforme

- gauss_plot.ipynb: prende in input i dati contenuti nei file dati_gauss.txt e dati_rand.txt. Fornisce in output vari grafici. Mostra che i dati di rand sono distribuiti uniformemente nel quadrato [0,1]x[0,1]. Inoltre mostra la dispersione dei dati gaussiani campionati intorno a 0 (valor medio della gaussiana normale) e, tramite un istogramma, mostra che i dati sono distribuiti come una gaussiana.

```bash
  cd ~/metodi_numerici/prova_progetti/analisi
  make
  nbconvert gauss_plot.ipynb
```

- pi_ss.c: calcolare pi greco con il simple sampling. Campionare punti con distribuzione unforme tra 0 e 1 e vedere quanti entrano nel cerchio di raggio uno e quanti no.
  - Prende in input il numero di campionamenti che possono fornirci un risultato sensato per la simulazione

  ```bash
  cd ~/metodi_numerici/prova_progetti
  make
  ./pi_ss 15
  ```

  - Fornisce in output un file di testo punti_pi.txt con due colonne; una contenente la coordinata x e una la coordinata y

- analisi_pi.ipynb: prende in input i dati contenuti nel file con due colonne punti_pi.txt e mostra in output il risultato grafico dell'analisi con la distribuzione dei punti dentro e fuori dal cerchio.

```bash
  cd ~/metodi_numerici/prova_progetti/analisi
  make
  nbconvert analisi_pi.ipynb
```
