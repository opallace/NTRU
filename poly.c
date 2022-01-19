#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <string.h>
#include <math.h>

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

	printf("\n\n");
}

void poly_copy(Poly *a, Poly *b){

	a->coeff = malloc(b->size * sizeof(int));
	a->size  = b->size;

	memcpy(a->coeff, b->coeff, b->size * sizeof(int));
}

/* se a > b  = 1
 * se a == b = 0
 * se a < b  = -1
 */
int poly_cmp(Poly *a, Poly *b){
	if(a->size == b->size){

		if(a->coeff[a->size - 1] == b->coeff[b->size - 1]){
			return 0;

		}else {
			if(a->coeff[a->size - 1] > b->coeff[b->size - 1]){
				return 1;

			}else {
				return -1;

			}
		}

	}else {
		if(a->size > b->size){
			return 1;
		}else {
			return -1;
		}
	}
}

void poly_rem_null_terms(Poly *a){
	for (int i = a->size - 1; a->coeff[i] == 0 && i > 0; i--){
		a->coeff = realloc(a->coeff, --a->size * sizeof(int));
	}
}

void poly_free(Poly *a){
	free(a->coeff);
	free(a);
}

int max(int a, int b){
	if(a >= b){
		return a;
	
	}else {
		return b;
	}
}

int mod(int a, int m){
	int resto = a % m;
	
	if(resto < 0){
		return resto + m;
	
	}else {
		return resto;
	} 
}

void poly_to_Zq(Poly *a, int q){
	for (int i = 0; i < a->size; ++i){
		a->coeff[i] = mod(a->coeff[i], q);
	}

	poly_rem_null_terms(a);
}

void poly_fill(Poly *a, int new_size, int value){

	a->coeff = realloc(a->coeff, new_size * sizeof(int));
	
	for (int i = a->size; i < new_size; i++){
		a->coeff[i] = value;	
	}

	a->size = new_size;
}

void poly_tern_generating(int n, int d1, int d2, Poly *result){
	srand(time(NULL));

	result->coeff = calloc(n + 1, sizeof(int));
	result->size = n + 1;

	for(int i = 0; i < d1;){
		int degree = rand() % (n + 1);

		if(result->coeff[degree] == 0){
			result->coeff[degree] = 1;
			i++;
		}
	}

	for(int i = 0; i < d2;){
		int degree = rand() % (n + 1);

		if(result->coeff[degree] == 0){
			result->coeff[degree] = -1;
			i++;
		}
	}

	poly_rem_null_terms(result);
}

void poly_sum(Poly *aa, Poly *bb, int modulus, Poly *result){
	
	Poly *temp_result = poly_init();
	Poly *a = poly_init();
	Poly *b = poly_init();

	poly_copy(a, aa);
	poly_copy(b, bb);

	poly_to_Zq(a, modulus);
	poly_to_Zq(b, modulus);

	temp_result->size = max(a->size, b->size);
	temp_result->coeff = calloc(temp_result->size, sizeof(int));

	poly_fill(a, temp_result->size, 0);
	poly_fill(b, temp_result->size, 0);

	for (int i = 0; i < temp_result->size; i++){
		temp_result->coeff[i] = a->coeff[i] + b->coeff[i];
	}

	poly_to_Zq(temp_result, modulus);
	poly_rem_null_terms(temp_result);
	poly_copy(result, temp_result);

	poly_free(a);
	poly_free(b);
}

void poly_sub(Poly *aa, Poly *bb, int modulus, Poly *result){
	Poly *a = poly_init();
	Poly *b = poly_init();

	poly_copy(a, aa);
	poly_copy(b, bb);

	poly_to_Zq(a, modulus);
	poly_to_Zq(b, modulus);

	result->size = max(a->size, b->size);
	result->coeff = calloc(result->size, sizeof(int));

	poly_fill(a, result->size, 0);
	poly_fill(b, result->size, 0);

	for (int i = 0; i < result->size; i++){
		result->coeff[i] = a->coeff[i] - b->coeff[i];
	}

	poly_to_Zq(result, modulus);
	poly_rem_null_terms(result);

	poly_free(a);
	poly_free(b);
}

void poly_int_mul(Poly *aa, int num, int modulus, Poly *result){
	Poly *a = poly_init();

	poly_copy(a, aa);
	poly_to_Zq(a, modulus);

	for (int i = 0; i < a->size; i++){
		a->coeff[i] *= num;
	}

	poly_to_Zq(a, modulus);
	poly_rem_null_terms(a);

	poly_copy(result, a);

	poly_free(a);
}

void poly_mul(Poly *aa, Poly *bb, int modulus, Poly *result){
	Poly *a = poly_init();
	Poly *b = poly_init();

	poly_copy(a, aa);
	poly_copy(b, bb);

	poly_to_Zq(a, modulus);
	poly_to_Zq(b, modulus);

	result->coeff = calloc(a->size + b->size - 1, sizeof(int));
	result->size  = a->size + b->size - 1;


	for (int i = 0; i < a->size; i++){
		for (int j = 0; j < b->size; j++){
			result->coeff[i+j] += a->coeff[i] * b->coeff[j];
		}
	}

	poly_to_Zq(result, modulus);
	poly_rem_null_terms(result);

	poly_free(a);
	poly_free(b);

}

int poly_is_zero(Poly *aa){
	Poly *a = poly_init();
	poly_copy(a, aa);
	
	poly_rem_null_terms(a);

	if(a->size == 1 && a->coeff[0] == 0){
		return 1;
	}else {
		return 0;
	}

	poly_free(a);
}

int poly_degree(Poly *aa){
	Poly *a = poly_init();
	poly_copy(a, aa);
	
	poly_rem_null_terms(a);

	int degree = a->size - 1;

	poly_free(a);
	return degree;
}

uint16_t ntruprime_inv_int(uint16_t a, uint16_t modulus) {
    int16_t x = 0;
    int16_t lastx = 1;
    int16_t y = 1;
    int16_t lasty = 0;
    int16_t b = modulus;
    while (b != 0) {
        int16_t quotient = a / b;

        int16_t temp = a;
        a = b;
        b = temp % b;

        temp = x;
        x = lastx - quotient*x;
        lastx = temp;

        temp = y;
        y = lasty - quotient*y;
        lasty = temp;
    }
    if (lastx < 0)
        lastx += modulus;
    return lastx;
}

void poly_div(Poly *aa, Poly *bb, int modulus, Poly *quotient){
	if(!poly_is_zero(bb)){
		quotient->coeff = malloc(sizeof(int));
		quotient->coeff[0] = 0;
		quotient->size = 1;

		Poly *remainder = poly_init();
		Poly *b = poly_init();

		poly_copy(remainder, aa);
		poly_copy(b, bb);

		poly_to_Zq(remainder, modulus);
		poly_to_Zq(b, modulus);

		while(!poly_is_zero(remainder) && poly_degree(remainder) >= poly_degree(b)){
			Poly *temp = poly_init();
			temp->coeff = calloc(((remainder->size - b->size) + 1), sizeof(int));
			temp->coeff[remainder->size - b->size] = remainder->coeff[remainder->size - 1] * ntruprime_inv_int(b->coeff[b->size - 1], modulus);
			temp->size = (remainder->size - b->size) + 1;

			poly_sum(quotient, temp, modulus, quotient);

			Poly *mul = poly_init();
			Poly *sub = poly_init();

			poly_mul(temp, b, modulus, mul);
			poly_sub(remainder, mul, modulus, remainder);

			poly_to_Zq(remainder, modulus);
			poly_to_Zq(quotient, modulus);
		}

		poly_rem_null_terms(quotient);

	}else {
		printf("Error: division by zero.\n");

	}
}

void poly_mod(Poly *aa, Poly *bb, int modulus, Poly *result){
	if(!poly_is_zero(bb)){
		Poly *quotient = poly_init();
		quotient->coeff = malloc(sizeof(int));
		quotient->coeff[0] = 0;
		quotient->size = 1;

		Poly *remainder = poly_init();
		Poly *divisor = poly_init();

		poly_copy(remainder, aa);
		poly_copy(divisor, bb);

		poly_to_Zq(remainder, modulus);
		poly_to_Zq(divisor, modulus);

		while(!poly_is_zero(remainder) && poly_degree(remainder) >= poly_degree(divisor)){
			Poly *temp = poly_init();
			temp->coeff = calloc(((remainder->size - divisor->size) + 1), sizeof(int));
			temp->coeff[remainder->size - divisor->size] = remainder->coeff[remainder->size - 1] * ntruprime_inv_int(divisor->coeff[divisor->size - 1], modulus);
			temp->size = (remainder->size - divisor->size) + 1;

			poly_sum(quotient, temp, modulus, quotient);

			Poly *mul = poly_init();
			Poly *sub = poly_init();

			poly_mul(temp, divisor, modulus, mul);
			poly_sub(remainder, mul, modulus, remainder);

			poly_to_Zq(remainder, modulus);
			poly_to_Zq(quotient, modulus);
		}

		poly_rem_null_terms(remainder);
		poly_copy(result, remainder);

	}else {
		printf("Error: division by zero.\n");

	}
}

/*  calculates the greatest common divisor between two big numbers 
 *	with the euclidean algorithm
 *
 *  Input: two big number pointers to calculate the mdc between 
 *         them, a big number pointer
 *  Output:
 *
 *	Pseudocode:  
 * 				while (y != 0)
 *	       			r = x % y
 *	       			x = y
 *	       			y = r
 *				return x;
 * 
 */
void poly_gdc(Poly *aa, Poly *bb, int modulus, Poly *result){
	Poly *a = poly_init();
	Poly *b = poly_init();

	poly_copy(a, aa);
	poly_copy(b, bb);

	poly_to_Zq(a, modulus);
	poly_to_Zq(b, modulus);
	
	while(!poly_is_zero(b)){
		Poly *r = poly_init();

		poly_mod(a, b, modulus, r);

		poly_copy(a, b);
		poly_copy(b, r);

		poly_free(r);
	}

	poly_copy(result, a);

	poly_free(a);
	poly_free(b);
}

void poly_gdce(Poly *a, Poly *b, int modulus, Poly *result){

    Poly *r     = poly_init();
    Poly *new_r = poly_init();

    Poly *t     = poly_init();
    Poly *new_t = poly_init();
   
    poly_copy(new_r, a);
    poly_copy(r, b);

    poly_to_Zq(new_r, modulus);
    poly_to_Zq(r, modulus);
   
    t->coeff = malloc(sizeof(double));
    t->size  = 1;
    t->coeff[0] = 0;

    new_t->coeff = malloc(sizeof(double));
    new_t->size  = 1;
    new_t->coeff[0] = 1;
   
    while(!poly_is_zero(new_r)){
        Poly *quo = poly_init();
        poly_div(r, new_r, modulus, quo);
        
        Poly *mul = poly_init();
        Poly *sub = poly_init();

        Poly *temp_new_r = poly_init();
        poly_copy(temp_new_r, new_r);

        poly_mul(quo, new_r, modulus, mul);

        poly_sub(r, mul, modulus, new_r);
        poly_copy(r, temp_new_r);

        Poly *temp_new_t = poly_init();
        poly_copy(temp_new_t, new_t);

        poly_mul(quo, new_t, modulus, mul);
        poly_sub(t, mul, modulus, new_t);
        poly_copy(t, temp_new_t);
    }

    poly_div(t, r, modulus, result);
}

int is_prime(int n){
	for (int i = 2; i < n; i++){
		if(n % i == 0){
			return 0;
		}
	}

	return 1;
}

int is_2_power(int n){
	if(n == 0){
		return 0;
	}else {
		while(n != 1){
			if(n % 2 != 0){
				return 0;
			}

			n /= 2;
		}

		return 1;
	}
}

int poly_invert(Poly *aa, Poly *ring, int modulus, Poly *result){
	Poly *gcd = poly_init();
	Poly *a = poly_init();

	poly_copy(a, aa);
	poly_to_Zq(a, modulus);

	if(is_prime(modulus)){

		poly_gdc(a, ring, modulus, gcd);

		if(poly_degree(gcd) != 0){
			return 0;
		}

		poly_gdce(a, ring, modulus, result);
		return 1;
	
	}else if(is_2_power(modulus)){

		poly_gdc(a, ring, 2, gcd);

		if(poly_degree(gcd) != 0){
			return 0;
		}

		poly_gdce(a, ring, 2, result);

		for (int i = 1; i < (int)log2(modulus); i++){
			
			Poly *mul1 = poly_init();
			poly_int_mul(result, 2, modulus, mul1);//(2 * result)

			Poly *pow = poly_init();
			poly_mul(result, result, modulus, pow);//(result * result)

			Poly *mul2 = poly_init();
			poly_mul(a, pow, modulus, mul2);

			Poly *sub = poly_init();
			poly_sub(mul1, mul2, modulus, sub);

			Poly *mod = poly_init();
			poly_mod(sub, ring, modulus, result);
		}

	}
}