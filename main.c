#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>

#include "aux.h"
#include "poly.h"
#include "ntru.h"

int main(){

	/*-----------------------key generation----------------------*/

	struct ntru *ctx = ntru_init_ctx(3, 2048, 743, 247, 149, 149);

	/*-----------------------key generation----------------------*/
	
	ntru_gen_random_keys(ctx);

	printf("p = %i\n", ctx->p);
	printf("q = %i\n", ctx->q);
	printf("n = %i\n", ctx->n);
	printf("df = %i\n", ctx->df);
	printf("dg = %i\n\n", ctx->dg);

	printf("g(x) = ");
	poly_println(ctx->g);

	printf("f(x) = ");
	poly_println(ctx->f);

	printf("f_p(x) = ");
	poly_println(ctx->f_p);

	printf("f_q(x) = ");
	poly_println(ctx->f_q);

	printf("h(x) = ");
	poly_println(ctx->h);

	printf("r(x) = ");
	poly_println(ctx->r);

	printf("b(x) = ");
	poly_println(ctx->b);

	/*-----------------------encrypt----------------------*/

	Poly *msg = poly_init();
	msg->size = ctx->n;
	msg->coeff = calloc(msg->size, sizeof(int));
	msg->coeff[0] = 0;
	msg->coeff[1] = -1;
	msg->coeff[2] = 1;
	msg->coeff[3] = 1;
	msg->coeff[4] = 0;
	msg->coeff[5] = -1;
	msg->coeff[6] = 1;
	msg->coeff[7] = 1;
	msg->coeff[msg->size - 1] = -1;

	printf("msg(x) = ");
	poly_println(msg);

	Poly *enc = poly_init();
	ntru_encrypt(ctx, msg, enc);

	printf("enc(x) = ");
	poly_println(enc);


	/*-----------------------decrypt----------------------*/

	Poly *dec = poly_init();
	ntru_decrypt(ctx, enc, dec);

	printf("dec(x) = ");
	poly_println(dec);

	return 0;
}