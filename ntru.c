#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <string.h>

#include "poly.h"

int main(){

	Poly *a = poly_init();
	a->coeff = malloc(7 * sizeof(double));
	a->coeff[0] = 1;
	a->coeff[1] = 1;
	a->coeff[2] = 0;
	a->coeff[3] = 0;
	a->coeff[4] = 1;
	a->coeff[5] = 1;
	a->coeff[6] = 1;
	a->size = 7;

	Poly *b = poly_init();
	b->coeff = malloc(8 * sizeof(double));
	b->coeff[0] = 1;
	b->coeff[1] = 0;
	b->coeff[2] = 0;
	b->coeff[3] = 0;
	b->coeff[4] = 0;
	b->coeff[5] = 0;
	b->coeff[6] = 0;
	b->coeff[7] = 1;
	b->size = 8;

	
	Poly *result = poly_init();
	poly_gdce(a, b, result);

	return 0;
}