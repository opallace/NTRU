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

int main(){

	struct ntru *ctx = init_ctx();
	ctx->p = 3;
	ctx->q = 2048;
	ctx->n = 743;
	ctx->df = 247;
	ctx->dg = 149;

	ctx->h = poly_init();
	ctx->g = poly_init();
	ctx->f = poly_init();
	ctx->f_p = poly_init();
	ctx->f_q = poly_init();

	ctx->r = create_ring(ctx->n);

	poly_tern_generating(ctx->n - 1, ctx->dg, ctx->dg, ctx->g);
	poly_tern_generating(ctx->n - 1, ctx->df + 1, ctx->df, ctx->f);

	poly_invert(ctx->f, ctx->r, ctx->p, ctx->f_p);
	poly_invert(ctx->f, ctx->r, ctx->q, ctx->f_q);

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

	return 0;
}