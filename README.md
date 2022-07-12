# Rabin-Public-Key-Cryptosystem
This repository includes 
- big number arithmetic
- Miller-Rabin primality test
- 256-bit prime number generation
- Rabin public key cryptosystem

# Usage
```bash
g++ main.cpp bignumber.cpp
```

# Sample IO:
## Rabin Encryption
  
p = daaefe65 2cad1614 f17e87f2 cd80973f
  
q = f9998862 6723eef2 a54ed484 dfa735c7
  
n = pq = d5375c87 792a4ac9 135966b6 d1689939 c249ed22 452f77d6 3fa82d67 e95e9cf9

Plaintext: be000bad bebadbad bad00deb deadface deafbeef add00add bed00bed
  
Ciphertext = 205651dd a3fced3e 74e9c50a 61342e29 b6b8e14e 85ce5666 7b341c78 cc2965cb

## Rabin Decryption
Ciphertext = 5452361a db4c34be 04a5903a e00793bc 1086e887 ebed06e2 3ffba0b4 a4348cc0
  
### Private Key:

p = d5e68b2b 5855059a d1a80dd6 c5dc03eb

q = c96c6afc 57ce0f53 396d3b32 049fe2d3

Plaintext = 00000000 12345678 87654321 12345678 87654321 12345678 87654321
