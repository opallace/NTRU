#ifndef POLY_H_INCLUDED
#define POLY_H_INCLUDED

typedef struct{
	int *coeff;
	int size;
} Poly;

Poly* poly_init();

void poly_print(Poly *a);
void poly_println(Poly *a);
void poly_copy(Poly *a, Poly *b);

void poly_tern_generating(int n, int d1, int d2, Poly *result);

void poly_sum(Poly *a, Poly *b, Poly *result);
void poly_sub(Poly *a, Poly *b, Poly *result);
void poly_mul(Poly *a, Poly *b, Poly *result);

#endif