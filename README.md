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
  
p = `daaefe652cad1614f17e87f2cd80973f`
  
q = `f99988626723eef2a54ed484dfa735c7`
  
n = pq = d5375c87792a4ac9135966b6d1689939c249ed22452f77d63fa82d67e95e9cf9

Plaintext: `be000badbebadbadbad00debdeadfacedeafbeefadd00addbed00bed`
  
Ciphertext = 205651dda3fced3e74e9c50a61342e29b6b8e14e85ce56667b341c78cc2965cb

## Rabin Decryption
Ciphertext = `5452361adb4c34be04a5903ae00793bc1086e887ebed06e23ffba0b4a4348cc0`
  
### Private Key:

p = `d5e68b2b5855059ad1a80dd6c5dc03eb`

q = `c96c6afc57ce0f53396d3b32049fe2d3`

Plaintext = 00000000123456788765432112345678876543211234567887654321
