#include <stdlib.h>

#include "aux.h"
#include "poly.h"
#include "ntru.h"

Ntru* ntru_init(){
	Ntru *ntru = malloc(sizeof(Ntru));

	ntru->h = poly_init();
	ntru->g = poly_init();
	ntru->f = poly_init();
	ntru->f_p = poly_init();
	ntru->f_q = poly_init();

	ntru->r = poly_init();
	ntru->b = poly_init();

	return ntru;
}

void ntru_params_set(int p, int q, int n, int df, int dg, Ntru *ntru){
	ntru->p = p;
	ntru->q = q;
	ntru->n = n;
	ntru->df = df;
	ntru->dg = dg;

	ntru_gen_ring(ntru->n, ntru->r);
	poly_gen_tern(ntru->n - 1, ntru->df, ntru->df, ntru->b);
}

void ntru_gen_ring(int p, Poly *result){
	Poly *ring = poly_init();

	ring->coeff = calloc((p + 1), sizeof(int));
	ring->size = p + 1;

	ring->coeff[0] = -1;
	ring->coeff[p] = 1;

	poly_copy(result, ring);
	poly_free(ring);
}

void ntru_gen_random_keys(Ntru *ntru){
	poly_gen_tern(ntru->n - 1, ntru->dg, ntru->dg, ntru->g);

	int f_valid = 0;
	do{

		poly_gen_tern(ntru->n - 1, ntru->df + 1, ntru->df, ntru->f);

		int f_p_inverse;
		int f_q_inverse;

		f_p_inverse = poly_invert(ntru->f, ntru->r, ntru->p, ntru->f_p);
		f_q_inverse = poly_invert(ntru->f, ntru->r, ntru->q, ntru->f_q);

		f_valid = f_p_inverse && f_q_inverse;

	}while(!f_valid);
	

	poly_mul(ntru->f_q, ntru->g, ntru->q, ntru->h);
	poly_int_mul(ntru->h, ntru->p, ntru->q, ntru->h);
	poly_mod(ntru->h, ntru->r, ntru->q, ntru->h);
}

void ntru_encrypt(Ntru *ntru, Poly *msg, Poly *result){
	Poly *enc = poly_init();

	poly_mul(ntru->b, ntru->h, ntru->q, enc);
	poly_sum(enc, msg, ntru->q, enc);
	poly_mod(enc, ntru->r, ntru->q, enc);

	poly_copy(result, enc);
	poly_free(enc);
}

void ntru_decrypt(Ntru *ntru, Poly *msg, Poly *result){
	Poly *dec = poly_init();

	poly_mul(ntru->f, msg, ntru->q, dec);
	poly_mod(dec, ntru->r, ntru->q, dec);
	poly_mod_center(dec, ntru->q, dec);

	poly_mul(ntru->f_p, dec, ntru->p, dec);
	poly_mod(dec, ntru->r, ntru->p, dec);
	poly_mod_center(dec, ntru->p, dec);

	poly_copy(result, dec);
	poly_free(dec);
}


