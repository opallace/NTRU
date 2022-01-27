# NTRUEncrypt
The NTRUEncrypt public key cryptosystem, also known as the NTRU encryption algorithm, is an NTRU lattice-based alternative to RSA and elliptic curve cryptography (ECC) and is based on the shortest vector problem in a lattice (which is not known to be breakable using quantum computers).

It relies on the presumed difficulty of factoring certain polynomials in a truncated polynomial ring into a quotient of two polynomials having very small coefficients. Breaking the cryptosystem is strongly related, though not equivalent, to the algorithmic problem of lattice reduction in certain lattices. Careful choice of parameters is necessary to thwart some published attacks.

Since both encryption and decryption use only simple polynomial multiplication, these operations are very fast compared to other asymmetric encryption schemes, such as RSA, ElGamal and elliptic curve cryptography. However, NTRUEncrypt has not yet undergone a comparable amount of cryptographic analysis in deployed form. 

NTRU operations are based on objects in a truncated polynomial ring   R = Z [ X ] / ( X N − 1 ) {\displaystyle \ R=\mathbb {Z} [X]/(X^{N}-1)} \ R={\mathbb {Z}}[X]/(X^{N}-1) with convolution multiplication and all polynomials in the ring have integer coefficients and degree at most N-1: 

![alt text](https://wikimedia.org/api/rest_v1/media/math/render/svg/209831fd2f9300396594dd7b71c88b52e53f7a6e)
