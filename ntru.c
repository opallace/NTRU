#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <string.h>

#include "poly.h"

int main(){

	Poly *a = poly_init();
	a->coeff = malloc(3 * sizeof(double));
	a->coeff[0] = -2;
	a->coeff[1] = 4;
	a->coeff[2] = 3;
	a->size = 3;


	Poly *b = poly_init();
	b->coeff = malloc(2 * sizeof(double));
	b->coeff[0] = 1;
	b->coeff[1] = 2;
	b->size = 2;

	
	Poly *result = poly_init();
	poly_mdc(a, b, result);

	poly_println(result);

	return 0;
}