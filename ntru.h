#ifndef NTRU_H_INCLUDED
#define NTRU_H_INCLUDED

struct ntru{
	int p;
	int q;
	int n;

	int df;
	int dg;
	int db;

	Poly *h;
	Poly *g;
	Poly *f;
	Poly *f_p;
	Poly *f_q;

	Poly *r;
	Poly *b;	
};

struct ntru* ntru_init_ctx(int p, int q, int n, int df, int dg, int db);
void ntru_gen_ring(int p, Poly *result);
void ntru_gen_random_keys(struct ntru *ctx);
void ntru_encrypt(struct ntru *ctx, Poly *msg, Poly *result);
void ntru_decrypt(struct ntru *ctx, Poly *msg, Poly *result);

#endif