#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <string.h>

#include "poly.h"

int main(){

	Poly *a = poly_init();
	a->coeff = malloc(4 * sizeof(int));
	a->coeff[0] = 4;
	a->coeff[1] = -6;
	a->coeff[2] = 3;
	a->coeff[3] = 2;
	a->size = 4;

	// poly_println(a);

	Poly *b = poly_init();
	b->coeff = malloc(3 * sizeof(int));
	b->coeff[0] = -2;
	b->coeff[1] = 3;
	b->coeff[2] = 1;
	b->size = 3;
	
	// poly_println(b);

	Poly *quotient = poly_init();
	Poly *remainder = poly_init();
	poly_div(a, b, quotient);
	poly_mod(a, b, remainder);

	printf("\n");
	poly_println(quotient);
	poly_println(remainder);

	return 0;
}