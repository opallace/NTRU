#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>

#include "aux.h"
#include "poly.h"
#include "ntru.h"

int main(){

	/*-----------------------init----------------------*/

	Ntru *ntru = ntru_init();

	ntru_params_set(3, 2048, 1171, 106, 390, ntru);
	ntru_gen_random_keys(ntru);

	printf("p = %i\n", ntru->p);
	printf("q = %i\n", ntru->q);
	printf("n = %i\n", ntru->n);
	printf("df = %i\n", ntru->df);
	printf("dg = %i\n\n", ntru->dg);

	printf("g(x) = ");
	poly_println(ntru->g);

	printf("f(x) = ");
	poly_println(ntru->f);

	printf("f_p(x) = ");
	poly_println(ntru->f_p);

	printf("f_q(x) = ");
	poly_println(ntru->f_q);

	printf("h(x) = ");
	poly_println(ntru->h);

	printf("r(x) = ");
	poly_println(ntru->r);

	printf("b(x) = ");
	poly_println(ntru->b);

	/*-----------------------encrypt----------------------*/

	Poly *msg = poly_init();
	msg->size = ntru->n;
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
	ntru_encrypt(ntru, msg, enc);

	printf("enc(x) = ");
	poly_println(enc);


	/*-----------------------decrypt----------------------*/

	Poly *dec = poly_init();
	ntru_decrypt(ntru, enc, dec);

	printf("dec(x) = ");
	poly_println(dec);

	return 0;
}