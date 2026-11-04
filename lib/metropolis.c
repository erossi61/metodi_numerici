#include <math.h>

#include "../include/random.h"
#include "../include/reticolo.h"
#include "../include/metropolis.h"

int metropolis(int i, int j, int k, int ripetizione_max, double alpha, double beta)
{
	double theta, Sx, Sy, nuovo_x, nuovo_y;
	double delta_E, coseno, seno;
	int ripetizione;
	int accettanza_interna_metr = 0;

	somma_vicini(i, j, k, &Sx, &Sy);

	for (ripetizione = 0; ripetizione < ripetizione_max; ripetizione++)
	{
		theta = alpha * (1 - 2 * myrand());
		coseno = cos(theta);
		seno = sin(theta);
		nuovo_x = spin[i][j][k].x * coseno + spin[i][j][k].y * seno;
		nuovo_y = -spin[i][j][k].x * seno + spin[i][j][k].y * coseno;

		delta_E = -((nuovo_x - spin[i][j][k].x) * Sx + (nuovo_y - spin[i][j][k].y) * Sy);

		if (delta_E <= 0)
		{
			spin[i][j][k].x = nuovo_x;
			spin[i][j][k].y = nuovo_y;
			accettanza_interna_metr += 1;
		}
		else
		{
			if (myrand() < exp(-beta * delta_E))
			{
				spin[i][j][k].x = nuovo_x;
				spin[i][j][k].y = nuovo_y;
				accettanza_interna_metr += 1;
			}
		}
	}
	return accettanza_interna_metr;
}

long sweep_metropolis(int ripetizione_max, double alpha, double beta)
{
	int i, j, k;
	long accettanza = 0;

	for (i = 0; i < L; i++)
	{
		for (j = 0; j < L; j++)
		{
			for (k = 0; k < L; k++)
			{
				accettanza += metropolis(i, j, k, ripetizione_max, alpha, beta);
			}
		}
	}
	return accettanza;
}