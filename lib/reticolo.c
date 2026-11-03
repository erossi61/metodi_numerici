#include <math.h>
#include <stdint.h>

#include "../include/pcg32min.h"
#include "../include/reticolo.h"

// definizione delle variabili globali dichiarate (extern) in reticolo.h
Spin spin[L][L][L];
int ip[L], im[L];

void vicini_period(void)
{
	int i;
	ip[i] = (i + 1) % L;
	im[i] = (i - 1 + L) % L;
}

void freddo(void)
{
	int i, j, k;

	for (i = 0; i < L; i++)
	{
		for (j = 0; j < L; j++)
		{
			for (k = 0; k < L; k++)
			{
				spin[i][j][k].x = 1.0;
				spin[i][j][k].y = 0.0;
			}
		}
	}
}

void caldo(void)
{
	double theta;
	int i, j, k;

	for (i = 0; i < L; i++)
	{
		for (j = 0; j < L; j++)
		{
			for (k = 0; k < L; k++)
			{
				theta = DUEPI * myrand();
				spin[i][j][k].x = sin(theta);
				spin[i][j][k].y = cos(theta);
			}
		}
	}
}

void rinormalizza(void)
{
	int i, j, k;
	double norma;

	for (i = 0; i < L; i++)
	{
		for (j = 0; j < L; j++)
		{
			for (k = 0; k < L; k++)
			{
				norma = sqrt(spin[i][j][k].x * spin[i][j][k].x + spin[i][j][k].y * spin[i][j][k].y);
				spin[i][j][k].x /= (double)norma;
				spin[i][j][k].y /= (double)norma;
			}
		}
	}
}
