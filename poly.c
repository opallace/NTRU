#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <string.h>

#include "poly.h"

Poly* poly_init(){
	Poly* result = malloc(sizeof(Poly));
	result->size = 0;
	return result;
}

void poly_print(Poly *a){
	for (int i = 0; i < a->size; ++i){
		if(a->coeff[i] != 0){
			printf("%ix^%i ", a->coeff[i], i);
		}
	}
}

void poly_println(Poly *a){
	for (int i = 0; i < a->size; ++i){
		if(a->coeff[i] != 0){
			printf("%ix^%i ", a->coeff[i], i);
		}
	}

	printf("\n");
}

void poly_copy(Poly *a, Poly *b){

	a->coeff = malloc(b->size * sizeof(int));
	a->size  = b->size;

	memcpy(a->coeff, b->coeff, b->size * sizeof(int));
}

void poly_tern_generating(int n, int d1, int d2, Poly *result){
	srand(time(NULL));

	result->coeff = calloc(n, sizeof(int));
	result->size = n;

	for(int i = 0; i < d1;){
		int degree = rand() % n;

		if(result->coeff[degree] == 0){
			result->coeff[degree] = 1;
			i++;
		}
	}

	for(int i = 0; i < d2;){
		int degree = rand() % n;

		if(result->coeff[degree] == 0){
			result->coeff[degree] = -1;
			i++;
		}
	}
}

void poly_sum(Poly *a, Poly *b, Poly *result){
	if(a->size >= b->size){
		poly_copy(result, a);

		for (int i = 0; i < b->size; ++i){
			result->coeff[i] += b->coeff[i];
		}

	}else {
		poly_copy(result, b);

		for (int i = 0; i < a->size; ++i){
			result->coeff[i] += a->coeff[i];
		}
	}
}

void poly_sub(Poly *a, Poly *b, Poly *result){
	if(a->size >= b->size){
		poly_copy(result, a);

		for (int i = 0; i < b->size; ++i){
			result->coeff[i] -= b->coeff[i];
		}

	}else {
		poly_copy(result, b);

		for (int i = 0; i < a->size; ++i){
			result->coeff[i] = a->coeff[i] - b->coeff[i];
		}
	}
}

void poly_mul(Poly *a, Poly *b, Poly *result){

	result->coeff = calloc(a->size + b->size, sizeof(int));
	result->size  = a->size + b->size;

	for (int i = 0; i < a->size; i++){
		for (int j = 0; j < b->size; j++){
			result->coeff[i+j] += a->coeff[i] * b->coeff[j];
		}
	}

}