# NTRUEncrypt
The NTRUEncrypt public key cryptosystem, also known as the NTRU encryption algorithm, is an NTRU lattice-based alternative to RSA and elliptic curve cryptography (ECC) and is based on the shortest vector problem in a lattice (which is not known to be breakable using quantum computers).

It relies on the presumed difficulty of factoring certain polynomials in a truncated polynomial ring into a quotient of two polynomials having very small coefficients. Breaking the cryptosystem is strongly related, though not equivalent, to the algorithmic problem of lattice reduction in certain lattices. Careful choice of parameters is necessary to thwart some published attacks.

Since both encryption and decryption use only simple polynomial multiplication, these operations are very fast compared to other asymmetric encryption schemes, such as RSA, ElGamal and elliptic curve cryptography. However, NTRUEncrypt has not yet undergone a comparable amount of cryptographic analysis in deployed form. 
