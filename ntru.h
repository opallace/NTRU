#ifndef NTRU_H_INCLUDED
#define NTRU_H_INCLUDED

typedef struct{
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
	Poly *b;	
} Ntru;

Ntru* ntru_init();
void ntru_params_set(int p, int q, int n, int df, int dg, Ntru *ntru);
void ntru_gen_ring(int p, Poly *result);
void ntru_gen_random_keys(Ntru *ntru);
void ntru_encrypt(Ntru *ntru, Poly *msg, Poly *result);
void ntru_decrypt(Ntru *ntru, Poly *msg, Poly *result);

#endif