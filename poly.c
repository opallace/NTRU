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
			printf("%lfx^%i ", a->coeff[i], i);
		}
	}
}

void poly_println(Poly *a){
	for (int i = 0; i < a->size; ++i){
		if(a->coeff[i] != 0){
			printf("%lfx^%i ", a->coeff[i], i);
		}
	}

	printf("\n");
}

void poly_copy(Poly *a, Poly *b){

	a->coeff = malloc(b->size * sizeof(double));
	a->size  = b->size;

	memcpy(a->coeff, b->coeff, b->size * sizeof(double));
}

void poly_tern_generating(int n, int d1, int d2, Poly *result){
	srand(time(NULL));

	result->coeff = calloc(n, sizeof(double));
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

	poly_rem_null_terms(result);
}

void poly_sum(Poly *aa, Poly *bb, Poly *result){
	Poly *a = poly_init();
	Poly *b = poly_init();

	poly_copy(a, aa);
	poly_copy(b, bb);

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

	poly_rem_null_terms(result);
}

void poly_sub(Poly *aa, Poly *bb, Poly *result){
	Poly *a = poly_init();
	Poly *b = poly_init();

	poly_copy(a, aa);
	poly_copy(b, bb);

	poly_mul_int(b, -1, b);
	poly_sum(a, b, result);
}

void poly_mul(Poly *aa, Poly *bb, Poly *result){
	Poly *a = poly_init();
	Poly *b = poly_init();

	poly_copy(a, aa);
	poly_copy(b, bb);

	result->coeff = calloc(a->size + b->size, sizeof(double));
	result->size  = a->size + b->size;

	for (int i = 0; i < a->size; i++){
		for (int j = 0; j < b->size; j++){
			result->coeff[i+j] += a->coeff[i] * b->coeff[j];
		}
	}

	poly_rem_null_terms(result);
}

void poly_mul_int(Poly *aa, double multiplier, Poly *result){

	Poly *a = poly_init();
	poly_copy(a, aa);

	if(multiplier != 0.0 && a->size != 0){
		for (int i = 0; i < a->size; i++){
			a->coeff[i] *= multiplier;
		}
	}

	poly_copy(result, a);
}

void poly_rem_null_terms(Poly *a){
	for (int i = a->size - 1; i >= 0; i--){
		if(a->coeff[i] == 0){
			a->coeff = realloc(a->coeff, --a->size * sizeof(double));
		}else {
			break;
		}
	}
}

void poly_div(Poly *aa, Poly *bb, Poly *quotient){
	if(bb->size > 0){
		Poly *remainder = poly_init();

		Poly *a = poly_init();
		Poly *b = poly_init();

		poly_copy(remainder, aa);
		poly_copy(b, bb);

		while(remainder->size >= b->size){
			
			Poly *temp = poly_init();
			temp->coeff = calloc(((remainder->size - b->size) + 1), sizeof(double));
			temp->coeff[remainder->size - b->size] = (double)remainder->coeff[remainder->size - 1] / (double)b->coeff[b->size - 1];
			temp->size = (remainder->size - b->size) + 1;
			
			poly_sum(quotient, temp, quotient);

			Poly *mul = poly_init();
			Poly *sub = poly_init();

			poly_mul(temp, b, mul);
			poly_sub(remainder, mul, remainder);

		}

		poly_rem_null_terms(quotient);

	}else {
		printf("Error: division by zero.\n");

	}
}

void poly_mod(Poly *aa, Poly *bb, Poly *remainder){
	
	if(bb->size > 0){
		Poly *quotient = poly_init();

		Poly *a = poly_init();
		Poly *b = poly_init();

		poly_copy(remainder, aa);
		poly_copy(b, bb);

		while(remainder->size != 0 && remainder->size >= b->size){
			
			Poly *temp = poly_init();
			temp->coeff = calloc(((remainder->size - b->size) + 1), sizeof(double));
			temp->coeff[remainder->size - b->size] = remainder->coeff[remainder->size - 1] / b->coeff[b->size - 1];
			temp->size = (remainder->size - b->size) + 1;
			
			poly_sum(quotient, temp, quotient);

			Poly *mul = poly_init();
			Poly *sub = poly_init();

			poly_mul(temp, b, mul);
			poly_sub(remainder, mul, remainder);

		}

		poly_rem_null_terms(remainder);

	}else {
		printf("Error: division by zero.\n");

	}
}

void poly_gdc(Poly *aa, Poly *bb, Poly *result){

	Poly *a = poly_init();
	Poly *b = poly_init();

	poly_copy(a, aa);
	poly_copy(b, bb);
	
	if(b->size == 0){
		Poly *temp = poly_init();
		temp->coeff = malloc(sizeof(double));
		temp->coeff[0] = a->coeff[a->size - 1];
		temp->size = 1;

		poly_div(a, temp, result);

	}else {

		Poly *rem = poly_init();
		poly_mod(a, b, rem);

		poly_gdc(b, rem, result);
		
	}
}

void poly_gdce(Poly *a, Poly *b, Poly *result){

    Poly *r     = poly_init();
    Poly *new_r = poly_init();

    Poly *t     = poly_init();
    Poly *new_t = poly_init();
   
    poly_copy(new_r, a);
    poly_copy(r, b);
   
    t->coeff = malloc(sizeof(double));
    t->size  = 1;
    t->coeff[0] = 0;

    new_t->coeff = malloc(sizeof(double));
    new_t->size  = 1;
    new_t->coeff[0] = 1;
   
    while(new_r->size != 0){
        Poly *quo = poly_init();
        poly_div(r, new_r, quo);
       
        Poly *mul = poly_init();
        Poly *sub = poly_init();

        Poly *temp_new_r = poly_init();
        poly_copy(temp_new_r, new_r);

        poly_mul(quo, new_r, mul);
        poly_sub(r, mul, new_r);
        poly_copy(r, temp_new_r);

        Poly *temp_new_t = poly_init();
        poly_copy(temp_new_t, new_t);

        poly_mul(quo, new_t, mul);
        poly_sub(t, mul, new_t);
        poly_copy(t, temp_new_t);
    }
   
    poly_println(r);
    poly_println(t);
}
