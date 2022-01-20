#include <stdlib.h>

#include "aux.h"
#include "poly.h"
#include "ntru.h"

struct ntru* ntru_init_ctx(int p, int q, int n, int df, int dg, int db){

	struct ntru *ctx = malloc(sizeof(struct ntru));

	ctx->p = p;
	ctx->q = q;
	ctx->n = n;
	ctx->df = df;
	ctx->dg = dg;
	ctx->db = db;

	ctx->h = poly_init();
	ctx->g = poly_init();
	ctx->f = poly_init();
	ctx->f_p = poly_init();
	ctx->f_q = poly_init();

	ctx->r = poly_init();
	ctx->b = poly_init();

	ntru_gen_ring(ctx->n, ctx->r);
	poly_gen_tern(ctx->n - 1, ctx->db, ctx->db, ctx->b);

	return ctx;
}

void ntru_gen_ring(int p, Poly *result){
	Poly *ring = poly_init();

	ring->coeff = calloc((p + 1), sizeof(int));
	ring->size = p + 1;

	ring->coeff[0] = -1;
	ring->coeff[p] = 1;

	poly_copy(result, ring);
}

void ntru_gen_random_keys(struct ntru *ctx){
	poly_gen_tern(ctx->n - 1, ctx->dg, ctx->dg, ctx->g);

	int f_valid = 0;
	do{

		poly_gen_tern(ctx->n - 1, ctx->df + 1, ctx->df, ctx->f);

		int f_p_inverse;
		int f_q_inverse;

		f_p_inverse = poly_invert(ctx->f, ctx->r, ctx->p, ctx->f_p);
		f_q_inverse = poly_invert(ctx->f, ctx->r, ctx->q, ctx->f_q);

		f_valid = f_p_inverse && f_q_inverse;

	}while(!f_valid);
	

	poly_mul(ctx->f_q, ctx->g, ctx->q, ctx->h);
	poly_int_mul(ctx->h, ctx->p, ctx->q, ctx->h);
	poly_mod(ctx->h, ctx->r, ctx->q, ctx->h);
}

void ntru_encrypt(struct ntru *ctx, Poly *msg, Poly *result){
	Poly *e = poly_init();

	poly_mul(ctx->b, ctx->h, ctx->q, e);
	poly_sum(e, msg, ctx->q, e);
	poly_mod(e, ctx->r, ctx->q, e);

	poly_copy(result, e);
}

void ntru_decrypt(struct ntru *ctx, Poly *msg, Poly *result){
	Poly *a = poly_init();

	poly_mul(ctx->f, msg, ctx->q, a);
	poly_mod(a, ctx->r, ctx->q, a);
	poly_mod_center(a, ctx->q, a);

	poly_mul(ctx->f_p, a, ctx->p, a);
	poly_mod(a, ctx->r, ctx->p, a);
	poly_mod_center(a, ctx->p, a);

	poly_copy(result, a);
}


