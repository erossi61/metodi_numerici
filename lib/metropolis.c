#include <math.h>

#include "../include/random.h"
#include "../include/reticolo.h"
#include "../include/metropolis.h"

int metropolis(int i, int j, int k, double alpha, double beta)
{
	double theta, Sx, Sy, nuovo_x, nuovo_y;
	double delta_E, coseno, seno;
	theta = alpha * (1 - 2 * myrand());

	somma_vicini(i, j, k, &Sx, &Sy);
	coseno = cos(theta);
	seno = sin(theta);
	nuovo_x = spin[i][j][k].x * coseno + spin[i][j][k].y * seno;
	nuovo_y = -spin[i][j][k].x * seno + spin[i][j][k].y * coseno;

	delta_E = -((nuovo_x - spin[i][j][k].x) * Sx + (nuovo_y - spin[i][j][k].y) * Sy);

	if (delta_E <= 0)
	{
		spin[i][j][k].x = nuovo_x;
		spin[i][j][k].y = nuovo_y;
		return 1;
	}
	else
	{
		if (myrand() < exp(-beta * delta_E))
		{
			spin[i][j][k].x = nuovo_x;
			spin[i][j][k].y = nuovo_y;
			return 1;
		}
	}
	return 0;
}