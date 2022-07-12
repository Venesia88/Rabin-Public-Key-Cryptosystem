#include "bignumber.hpp"
#include <iostream>
#include <string>

using namespace std;

BigNumber::BigNumber(){
    sign = false;
    data = "";
}

BigNumber::BigNumber(int x){
    data = to_string(x);
    // cout << data.at(0) << endl;
    
    if (data.at(0) == '-'){
        sign = true;
        this->data.erase(0,1);
    }
    else sign = false;

    reverse(data.begin(), data.end());
    
}

BigNumber::BigNumber(string s){
    data = s;
    if (data.at(0) == '-'){
        sign = true;
        this->data.erase(0,1);
    }
    else sign = false;
    reverse(data.begin(), data.end());
}

bool BigNumber::operator<(const BigNumber& x){
    if(this->data.size() != x.data.size())
        return this->data.size() < x.data.size();
    
    for(int i = this->data.size()-1; i >= 0; i--){
        if(this->data[i] != x.data[i]) return this->data[i] < x.data[i];
    }
    
    return false;
}



bool BigNumber::operator>(const BigNumber& x){
    return !(*this < x) && !(this->data == x.data && this->sign == x.sign);
}

bool BigNumber::operator==(const BigNumber& x){
    if(this->data.size() != x.data.size()) return false;
    if(this->sign != x.sign) return false;

    for(int i = 0; i < this->data.size(); i++){
        if(this->data[i] != x.data[i]) return false;
    }

    return true;
}

bool BigNumber::operator!=(const BigNumber& x){
    return !(*this == x);
}

BigNumber BigNumber::operator+(BigNumber x){
    int carry = 0;
    BigNumber result, temp;
    // - + -
    if(this->sign && x.sign) result.sign = true;
    // + + -
    else if(x.sign){
        temp = x;
        temp.sign = false;
        return(*this - temp);
    }
    else if(this->sign) {
        temp = *this;
        temp.sign = false;
        return(x - temp);
    }


    for(int i = 0; i < this->data.size() || i < x.data.size() || carry; i++){
        carry += ((i < this->data.size()) ? this->data[i] - '0' : 0) + ((i < x.data.size()) ? x.data[i] - '0' : 0);

        result.data += to_string(carry % 10);
        carry /= 10;
    }
    result.data = remove(result.data);
    return result;
}

void BigNumber::appendData(char a){
    this->data += a;
}

BigNumber BigNumber::getLen(){
    return BigNumber(this->data.length());
}

BigNumber BigNumber::operator-(BigNumber x){
    BigNumber result, temp;

    if(this->sign && x.sign){
        temp = x;
        temp.sign = false;
        return (*this + temp);
    }
    else if(x.sign){
        temp = x;
        temp.sign = false;
        return (*this + temp);
    }
    else if(this->sign){
        temp = x;
        temp.sign = true;
        return(*this + temp);
    }


    if(*this < x){
        result = (x - *this);
        result.sign = true;
    }
    else{
        int borrow = 0;
        for(int i = 0; i < this->data.size(); i++){
            borrow = this->data[i] - '0' - borrow - (i < x.data.size() ? x.data[i] - '0' : 0);

            if(borrow < 0){
                result.data += to_string(borrow + 10);
                borrow = 1;
            }
            else {
                result.data += to_string(borrow);
                borrow = 0;
            }
        }
    }
    result.data = remove(result.data);
    return result;
}

BigNumber BigNumber::operator*(BigNumber x){
    BigNumber result;
    string number(this->data.size() + x.data.size(), 0);
    int carry = 0;

    if(this->sign != x.sign) result.sign = true;

    for(int i = 0; i < x.data.size(); i++){
        for(int j = 0; j < this->data.size(); j++){
            carry = (this->data[j] - '0') * (x.data[i] - '0') + number[i+j];
            // cout << i << " " << j << " " << this->data[j] << " " << x.data[i] << " " << carry << endl;
            number[i + j + 1] += carry / 10;
            number[i + j] = carry % 10; 
        }
    }

    for(int i = 0; i < number.size(); i++){
        number[i] += '0';
    }
    result.data = remove(number);
    return result;
}

BigNumber BigNumber::operator/(BigNumber x){
    BigNumber result("0"), temp("0");
    if(this->sign != x.sign) result.sign = true;
    if(x == temp){
        throw std::runtime_error("division by zero!");
    }

    if(*this < x){
        return result;
    }

    string s(data.size(), '0');

    for(int i = data.size() - 1; i >= 0; i--){
        temp = temp + data.substr(i, 1);
        
        while(!(temp < x)){
            temp = temp - x;
            int j;
            for(j = temp.data.size()-1; j >= 0 && temp.data[j] == '0'; j--);
            temp.data = temp.data.substr(0, j+1);
            // cout << j << temp.data.size() << endl;
            s[i]++;
            
        }
        // if(out) break;
        temp.data.insert(temp.data.begin(), '0');
    }
    result.data = remove(s);
    return result;

}

BigNumber BigNumber::operator%(BigNumber x){
    if(x == BigNumber("0")) throw std::runtime_error("modulo by zero!");
    BigNumber result, one("1");
    if(this->sign) {
        BigNumber temp = (*this / x);
        // temp.Print();
        temp.sign = false;
        temp = temp + one;
        result = (*this) + (temp*x);
    }
    else result = (*this) - ((*this / x) * x);
    return result;
}

BigNumber BigNumber::operator=(BigNumber x){
    this->data = x.data;
    this->sign = x.sign;
    return *this;
}

string BigNumber::remove(string number){

    int j;
    for(j = number.size()-1; j > 0 && number[j] == '0'; j--);
    number = number.substr(0, j+1);

    return number;
}

void BigNumber::toHex(){
    BigNumber result, temp;
    string zero("0");

    string text = "0123456789abcdef";
    temp = *this;

    if(temp == zero){
        *this = zero;
        return;
    }

    while(temp.data != zero){
        BigNumber mod = temp % BigNumber("16");
        reverse(mod.data.begin(), mod.data.end());
        result.data += text[stoi(mod.data)];
        temp = temp / BigNumber("16");
    }

    this->data = remove(result.data);
}

void BigNumber::Print(){
    string s(data);
    
    reverse(s.begin(), s.end());
    s = ((sign) ? "-" : "") + s;
    
    cout << s << endl;
}

void BigNumber::toInt(){
    BigNumber a(1), result(0);
    for(int i = 0; i < this->data.size(); i++){
        int hex = (this->data[i] < '0' || this->data[i] > '9') ? toupper(this->data[i]) - 'A' + 10 : this->data[i] - '0';
        result = result + (a * BigNumber(hex));
        a = a * 16;
    }

    // reverse(result.data.begin(), result.data.end());
    this->data = remove(result.data);
    // cout << result.data << endl;

    // return result;
}

string BigNumber::getData(){
    return this->data;
}

void BigNumber::setData(string data){
    this->data = data;
}


// int main(){
//     // BigNumber a("f1245ab3341ff3461818881767676819ee");
//     // BigNumber b("ffa24387539639853800bbecbcb494990");
//     // BigNumber a("616512316543123165465636565231654065565654065405640645");
//     // BigNumber b("616512316543123165465416545405640645");
//     // BigNumber b("0");

//     string a1("0"), b1("0");

//     cout << "a= ";
//     cin >> a1;

//     cout << "b= ";
//     cin >> b1;

//     BigNumber a(a1); 
//     BigNumber b(b1);
//     BigNumber add, mul, sub, mod, div;
//     a.toInt();
//     b.toInt();

//     add = a+b;
//     add.toHex();
//     // assert (add == BigNumber("1011e7eeba95956de6b9893d63332b1637e"));

    
//     sub = a-b;
//     sub.toHex();
//     // assert (sub == BigNumber("e12a367abee68fadc4987c589b9c1ed05e"));
    
//     mul = a*b;
//     mul.toHex();
//     // assert (mul == BigNumber("f0cc0ef5e2f7d593719ce283c6efb373d86a14d50f9f5c5ba42a6bae39ff8d173e0"));

//     div = a/b;
//     div.toHex();
//     // assert (div == BigNumber("f"));

//     mod = a%b;
//     mod.toHex();
//     // assert (mod == BigNumber("17c3b6455c31d593397d7e9767e1cca7e"));

//     cout << "a+b = ";
//     add.Print();

//     cout << "a-b = ";
//     sub.Print();

//     cout << "a*b = ";
//     mul.Print();

//     cout << "a/b = ";
//     div.Print();

//     cout << "a%b = ";
//     mod.Print();
// }