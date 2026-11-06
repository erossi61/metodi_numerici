# Cosa abbiamo creato

## simulazioni.c

Programma che implementa tutto ciò che è necessario per realizzare simulazioni numeriche e fare raccolta dati su un modello XY (O(N) con N = 2) in 3D. Il reticolo per questa simulazione è definito in **`reticolo.c`** e la dimensione del reticolo è definita come variabile globale in **`reticolo.h`**.
La dimensione del reticolo si cambia durante l'esecuzione con:

```c
// lato del reticolo (si cambia con -DL=...)
```

Cosa prende in input, cosa restituisce in output e cosa scrive su file:

```c
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


fprintf(fpdata, "# L = %d\n# beta = %.10f\n# seed = %lu\n# alpha = %f\n# epsilon = %f\n", L, beta, seed, alpha, epsilon);
fprintf(fpdata, "# sample = %ld\n# inizializzazione = %d\n", sample, inizializzazione);
fprintf(fpdata, "# ripetizioni_max = %d\n# misura_ogni = %d\n", ripetizioni_max, misura_ogni);
fprintf(fpdata, "# colonne: densita_energia mx my\n");

fprintf(fpdata, "# tempo CPU = %f s\n", tempo_totale);

fprintf(fpdata, "# accettanza = %f\n", accettanza_metr); //metropolis accettati/metropolis fatti*volume

```
