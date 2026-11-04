#include "../include/reticolo.h"
#include "../include/microcanonico.h"

void micro_can(int i, int j, int k)
{
	double Sx, Sy;
	double srSr, Sr_quadro, coeff;

	somma_vicini(i, j, k, &Sx, &Sy);
	srSr = spin[i][j][k].x * Sx + spin[i][j][k].y * Sy;
	Sr_quadro = (Sx * Sx + Sy * Sy);

	if (Sr_quadro > 1.0e-26)
	{
		coeff = 2 * srSr / Sr_quadro;
		spin[i][j][k].x = coeff * Sx - spin[i][j][k].x;
		spin[i][j][k].y = coeff * Sy - spin[i][j][k].y;
	}
}

void sweep_micro_can(void)
{
	int i, j, k;

	for (i = 0; i < L; i++)
	{
		for (j = 0; j < L; j++)
		{
			for (k = 0; k < L; k++)
			{
				micro_can(i, j, k);
			}
		}
	}
}