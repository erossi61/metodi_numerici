#ifndef BOX_MULLER_H
#define BOX_MULLER_H

void bm_base(double *restrict y1, double *restrict y2);
double bm_1gauss_pol(void);
void bm_2gauss_pol(double *restrict g1, double *restrict g2);

#endif