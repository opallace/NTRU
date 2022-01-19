#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <string.h>
#include <math.h>

#include "poly.c"

struct ntru{
	int p;
	int q;
	int n;

	int df;
	int dg;

	Poly *b;
	Poly *h;
	Poly *g;
	Poly *f;
	Poly *f_p;
	Poly *f_q;

	Poly *r;
	
};

struct ntru* init_ctx(){
	return malloc(sizeof(struct ntru));
}

Poly* create_ring(int p){
	Poly *ring = poly_init();

	ring->coeff = calloc((p + 1), sizeof(int));
	ring->size = p + 1;

	ring->coeff[0] = -1;
	ring->coeff[p] = 1;

	return ring;
}

void poly_sim_transp(Poly *aa, int q, Poly *result){
	Poly *a = poly_init();
	poly_copy(a, aa);

	for (int i = 0; i < a->size; i++){
		if(a->coeff[i] > (int)(q / 2)){
			a->coeff[i] -= q;
		}
	}

	poly_copy(result, a);
}

int main(){

	struct ntru *ctx = init_ctx();
	ctx->p = 3;
	ctx->q = 2048;
	ctx->n = 743;
	ctx->df = 247;
	ctx->dg = 149;

	ctx->b = poly_init();
	ctx->h = poly_init();
	ctx->g = poly_init();
	ctx->f = poly_init();
	ctx->f_p = poly_init();
	ctx->f_q = poly_init();

	ctx->r = create_ring(ctx->n);

	poly_tern_generating(ctx->n - 1, ctx->dg, ctx->dg, ctx->b);
	poly_tern_generating(ctx->n - 1, ctx->dg, ctx->dg, ctx->g);

	int f_valid = 0;
	do{

		poly_tern_generating(ctx->n - 1, ctx->df + 1, ctx->df, ctx->f);

		int f_p_inverse;
		int f_q_inverse;

		f_p_inverse = poly_invert(ctx->f, ctx->r, ctx->p, ctx->f_p);
		f_q_inverse = poly_invert(ctx->f, ctx->r, ctx->q, ctx->f_q);

		f_valid = f_p_inverse && f_q_inverse;

	}while(!f_valid);
	

	poly_mul(ctx->f_q, ctx->g, ctx->q, ctx->h);
	poly_int_mul(ctx->h, ctx->p, ctx->q, ctx->h);
	poly_mod(ctx->h, ctx->r, ctx->q, ctx->h);

	printf("p = %i\n", ctx->p);
	printf("q = %i\n", ctx->q);
	printf("n = %i\n", ctx->n);
	printf("df = %i\n", ctx->df);
	printf("dg = %i\n", ctx->dg);

	printf("f(x) = ");
	poly_println(ctx->f);

	printf("f_p(x) = ");
	poly_println(ctx->f_p);

	printf("f_q(x) = ");
	poly_println(ctx->f_q);

	printf("g(x) = ");
	poly_println(ctx->g);

	printf("h(x) = ");
	poly_println(ctx->h);

	printf("r(x) = ");
	poly_println(ctx->r);

	/*-----------------------encrypt----------------------*/

	Poly *m = poly_init();
	m->size = ctx->n;
	m->coeff = calloc(m->size, sizeof(int));
	m->coeff[0] = 0;
	m->coeff[1] = -1;
	m->coeff[2] = 1;
	m->coeff[3] = 1;
	m->coeff[4] = 0;
	m->coeff[5] = -1;
	m->coeff[6] = 1;
	m->coeff[7] = 1;
	m->coeff[m->size - 1] = -1;

	printf("m(x) = ");
	poly_println(m);

	Poly *e = poly_init();

	poly_mul(ctx->b, ctx->h, ctx->q, e);
	poly_sum(e, m, ctx->q, e);
	poly_mod(e, ctx->r, ctx->q, e);

	printf("e(x) = ");
	poly_println(e);


	/*-----------------------decrypt----------------------*/

	Poly *a = poly_init();
	poly_mul(ctx->f, e, ctx->q, a);
	poly_mod(a, ctx->r, ctx->q, a);
	poly_sim_transp(a, ctx->q, a);

	poly_mul(ctx->f_p, a, ctx->p, a);
	poly_mod(a, ctx->r, ctx->p, a);
	poly_sim_transp(a, ctx->p, a);

	printf("a(x) = ");
	poly_println(a);

	return 0;
}