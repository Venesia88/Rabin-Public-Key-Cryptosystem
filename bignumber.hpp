#ifndef _BIG_H
#define _BIG_H
#include <iostream>
#include <string>

using namespace std;

class BigNumber {
    private:
        bool sign;
        string data;
    public:
        BigNumber();
        BigNumber(int x);
        BigNumber(string s);
        bool operator<(const BigNumber& x);
        bool operator>(const BigNumber& x);
        BigNumber operator+(BigNumber x);
        BigNumber operator-(BigNumber x);
        BigNumber operator*(BigNumber x);
        BigNumber operator/(BigNumber x);
        BigNumber operator%(BigNumber x);
        BigNumber operator=(BigNumber x);
        bool operator==(const BigNumber& x);
        bool operator!=(const BigNumber& x);
        string remove(string number);
        void toHex();
        void Print();
        void toInt();
        void appendData(char a);
        BigNumber getLen();
        string getData();
        void setData(string data);

};
#endif 