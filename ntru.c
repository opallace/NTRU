#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <string.h>

#include "poly.h"

int main(){

	Poly *a = poly_init();
	poly_tern_generating(5, 3, 1, a);
	poly_println(a);

	Poly *b = poly_init();
	poly_tern_generating(4, 2, 1, b);
	poly_println(b);

	Poly *result = poly_init();
	poly_sub(a, b, result);

	poly_println(result);

	return 0;
}