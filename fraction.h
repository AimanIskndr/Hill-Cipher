#ifndef FRACTION_H
#define FRACTION_H

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

struct Fraction {
    int numerator;
    int denominator;

    Fraction(string num){
        set_frac(num);
    }

    Fraction(int n = 0, int d = 1){
        set_frac(n, d);
    }

    void simplify(){
        int gcd = __gcd(numerator, denominator);
        numerator /= gcd;
        denominator /= gcd;
        if(denominator < 0){
            numerator = -numerator;
            denominator = -denominator;
        }
    }

    Fraction operator+(const Fraction &other) const{
        int common_denom = denominator * other.denominator;
        int num = numerator * other.denominator + other.numerator * denominator;
        return Fraction(num, common_denom);
    }

    Fraction operator-(const Fraction &other) const{
        int common_denom = denominator * other.denominator;
        int num = numerator * other.denominator - other.numerator * denominator;
        return Fraction(num, common_denom);
    }

    Fraction operator*(const Fraction &other) const{
        int num = numerator * other.numerator;
        int denom = denominator * other.denominator;
        return Fraction(num, denom);
    }

    void set_frac(int n, int d){
        numerator = n;
        denominator = d;
        simplify();
    }

    void set_frac(string num){
        size_t pos = num.find('/');
        if(pos != string::npos){
            numerator = stoi(num.substr(0, pos));
            denominator = stoi(num.substr(pos + 1));
        }
        else{
            numerator = stoi(num);
            denominator = 1;
        }
        simplify();
    }

    double get() const{
        return 1.0 * numerator / denominator;
    }

    friend ostream& operator<<(ostream &out, const Fraction &frac){
        out << frac.numerator;
        if(frac.denominator != 1)
            out << "/" << frac.denominator;
        return out;
    }

    friend istream& operator>>(istream& is, Fraction& frac) {
        string input;
        is >> input;
        frac.set_frac(input);
        return is;
    }
};

#endif // FRACTION_H
