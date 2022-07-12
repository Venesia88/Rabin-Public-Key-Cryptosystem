#include "bignumber.hpp"
#include <cstdlib>

using namespace std;

int smallPrime[167] = {
    3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67,
    71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139,
    149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223,
    227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281, 283, 293, 
    307, 311, 313, 317, 331, 337, 347, 349, 353, 359, 367, 373, 379, 383, 
    389, 397, 401, 409, 419, 421, 431, 433, 439, 443, 449, 457, 461, 463, 
    467, 479, 487, 491, 499, 501, 509, 521, 523, 541, 547, 557, 563, 569, 
    571, 577, 587, 593, 599, 601, 607, 613, 617, 619, 631, 641, 643, 647, 
    653, 659, 661, 673, 677, 683, 691, 701, 709, 719, 727, 733, 739, 743, 
    751, 757, 761, 769, 773, 787, 797, 809, 811, 821, 823, 827, 829, 839, 
    853, 857, 859, 863, 877, 881, 883, 887, 907, 911, 919, 929, 937, 941, 
    947, 953, 967, 971, 977, 983, 991, 997 };


BigNumber randHex(){
    BigNumber result;
    string text = "0123456789abcdef";
    for(int i = 0; i < 64; i++){
        result.appendData(text[rand() % 16]);
    }
    return result;
}

BigNumber modpow(BigNumber a, BigNumber d, BigNumber n){
    BigNumber result("1"), zero("0"), two("2"), one("1");
    a = a % n;

    while(d > zero){
        if(d % two == one) result = (result * a) % n;
        d = d / two;
        a = (a*a) % n;
    }

    return result;
}
bool isprime(BigNumber n, int k){
    BigNumber two("2"), zero("0"), one("1"), three("3");
    if(n == two)
        return true;
    else if(n == one || n == zero || n % two == zero) 
        return false;
    
    //check small prime trial division
    for(int i = 0; i < 167; i++){
        if(n == BigNumber(smallPrime[i])) return true;
        else if(n % BigNumber(smallPrime[i]) == zero) return false;
    }
    
    //miller rabin
    BigNumber r("0"), d;
    d = n - 1;
    while(d % two == zero){
        d = d / 2;
        r = r + one;
    }

    while(k--){
        bool flag = false;
        BigNumber tmp = randHex();
        tmp.toInt();
        BigNumber a = two + (tmp % (n - three));
        BigNumber x = modpow(a, d, n);

        if(x == one || x == n - one) continue;

        while(r > zero){
            x = (x*x) % n;
            if(x == n - one){
                flag = true;
                break;
            }
            r = r - one;
        }
        if(flag) continue;
        else return false;
    }

    return true;
}

BigNumber generatePrime(){
    BigNumber result;

    result = randHex();
    result.toInt();
    while(!isprime(result, 5)){
        result = randHex();
        result.toInt();
    }
    return result;
}

BigNumber encryption(BigNumber plaintext, BigNumber n){
    BigNumber ciphertext = modpow(plaintext, BigNumber("2"), n);
    ciphertext.toHex();

    return ciphertext;
}

std::pair<BigNumber, BigNumber> egcd(BigNumber a, BigNumber b){
    BigNumber zero("0"), one("1");
    BigNumber q, u, v, r, s1, s2, t1, t2, s, t;
    u = a;
    v = b;
    s1 = one;
    t2 = one;
    s2 = zero;
    t1 = zero;
    while(v != zero){
        q = u / v;
        r = u % v;
        s = s1 - (s2 * q);
        t = t1 - (t2 * q);
        s1 = s2;
        s2 = s;
        t1 = t2;
        t2 = t;
        u = v;
        v = r;

    }
    return std::make_pair(s1, t1);
}

BigNumber decryption(BigNumber ciphertext, BigNumber p, BigNumber q){
    BigNumber mp, mq, r1, r2, r3, r4, n;
    BigNumber four("4"), one("1");
    mp = modpow(ciphertext, (p + one) / four, p);
    mq = modpow(ciphertext, (q + one) / four, q);
    n = p * q;

    std::pair<BigNumber, BigNumber> y;
    y = egcd(p, q);

    

    r1 = ((y.first * p * mq) + (y.second * q * mp)) % n;
    r2 = n - r1;
    r3 = ((y.first * p * mq) - (y.second * q * mp)) % n;
    r4 = n - r3;

    r1.toHex();
    r2.toHex();
    r3.toHex();
    r4.toHex();

    if(r1.getData().substr(0, 4) == r1.getData().substr(4, 4)){
        r1.setData(r1.getData().substr(4, r1.getData().size()));
        return r1;
    }
        
    if(r2.getData().substr(0,4) == r2.getData().substr(4,4)){
        r2.setData(r2.getData().substr(4, r2.getData().size()));
        return r2;
    }
    if(r3.getData().substr(0,4) == r3.getData().substr(4,4)){
        r3.setData(r3.getData().substr(4, r3.getData().size()));
        return r3;
    }
    if(r4.getData().substr(0,4) == r4.getData().substr(4,4)){
        r4.setData(r4.getData().substr(4, r4.getData().size()));
        return r4;
    }

    return one;
}

int main(){
    srand(time(nullptr));

    cout << "<Miller-Rabin>" << endl;
    BigNumber prime = generatePrime();
    prime.toHex();
    prime.Print();

    cout << "<Rabin Encryption>" << endl;
    string p1, q1;
    cout << "p = ";
    cin >> p1;
    cout << "q = ";
    cin >> q1;


    BigNumber p(p1), q(q1);
    p.toInt();
    q.toInt();

    BigNumber n;
    n = p * q;
    cout << "n = pq = ";
    n.toHex();
    n.Print();

    string plaintext1;
    cout << "Plaintext: ";
    cin >> plaintext1;
    BigNumber ciphertext_enc, plaintext_enc(plaintext1 + plaintext1.substr(plaintext1.size()-4));
    n.toInt();
    plaintext_enc.toInt();
    ciphertext_enc = encryption(plaintext_enc, n);
    cout << "Ciphertext = ";
    ciphertext_enc.Print();

    //decryption
    cout << "<Rabin Decryption>" << endl;
    string ciphertext1;
    cout << "Ciphertext = ";
    cin >> ciphertext1;
    cout << "Private Key: " << endl;
    cout << "p = ";
    cin >> p1;
    cout << "q = ";
    cin >> q1;

    BigNumber ciphertext_dec(ciphertext1), plaintext_dec, p_dec(p1), q_dec(q1);
    ciphertext_dec.toInt();
    p_dec.toInt();
    q_dec.toInt();
    plaintext_dec = decryption(ciphertext_dec, p_dec, q_dec); 

    string s("");
    for(int i = 0; i < 56 - plaintext_dec.getData().size(); i++)
        s += '0';
    
    cout << "Plaintext = ";
    cout << s;
    plaintext_dec.Print();
    

}
