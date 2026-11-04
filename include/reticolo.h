#ifndef RETICOLO_H
#define RETICOLO_H

#ifndef L
#define L 16 // lato del reticolo (si cambia con -DL=...)
#endif

#define VOLUME ((double)L * L * L) // numero di siti (come double, per le medie)
#define DUEPI 6.28318530717958647692
typedef struct
{
	double x;
	double y;
} Spin;

extern Spin spin[L][L][L]; // spin[x][y][z] = spin nel sito (x,y,z)
extern int ip[L], im[L];

void vicini_period(void);
void freddo(void);
void caldo(void);
void rinormalizza(void);
double densita_energia(void);
void magnetizzazione(double *mx, double *my);

static inline void somma_vicini(int i, int j, int k, double *Sx, double *Sy)
{
	*Sx = spin[ip[i]][j][k].x + spin[i][ip[j]][k].x + spin[i][j][ip[k]].x + spin[im[i]][j][k].x + spin[i][im[j]][k].x + spin[i][j][im[k]].x;
	*Sy = spin[ip[i]][j][k].y + spin[i][ip[j]][k].y + spin[i][j][ip[k]].y + spin[im[i]][j][k].y + spin[i][im[j]][k].y + spin[i][j][im[k]].y;
}

#endif