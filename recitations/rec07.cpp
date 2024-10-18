/*
  rec07_begin.cpp
  CS2124
  Author : Uvindu Salgado
  Implement the class Rational, so that the following program works.
 */

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

int greatestCommonDivisor(int x, int y);

// Put your Rational class here.
class Rational{
    friend ostream& operator<<(ostream& os, const Rational& rationalC){
        os << rationalC.numerator << "/" << rationalC.denominator;
        return os;
    }
    friend istream& operator>>(istream& ifs, Rational& rationalC){
        char skip;
        ifs >> rationalC.numerator >> skip >> rationalC.denominator;
        rationalC.normalize();
        return ifs;
    }
    friend bool operator==(const Rational& lhs, const Rational& rhs);
    friend bool operator<(const Rational& lhs, const Rational& rhs);
public:
    Rational(int num = 0, int denom = 1) : numerator(num), denominator(denom) {}
    void normalize(){
        int gcd = greatestCommonDivisor(numerator, denominator);
        numerator /= gcd;
        denominator /= gcd;
        if(denominator < 0){
            numerator *= -1;
            denominator *= -1;
        }
    }
    Rational& operator+=(const Rational& rhs){
        denominator *= rhs.denominator;
        numerator = rhs.denominator * numerator + rhs.numerator * denominator;
        normalize();
        return *this;
    }
    Rational& operator++(){
        numerator += denominator;
        return *this;
    }
    Rational operator++(int dummy){
        Rational curr(*this);
        numerator += denominator;
        return curr;
    }
    explicit operator bool() const { return numerator != 0; }
private:
    int numerator;
    int denominator;
};

// Any functions that are not members and not friends should have
// prototypes here and their definitions after main.
Rational operator+(const Rational& lhs, const Rational& rhs);
Rational& operator--(Rational& rhs);
Rational operator--(Rational& rhs, int temp);
bool operator!=(const Rational& lhs, const Rational& rhs);
bool operator<=(const Rational& lhs, const Rational& rhs);
bool operator<=(const Rational& lhs, int rhs);
bool operator>(const Rational& lhs, const Rational& rhs);
bool operator>=(const Rational& lhs, const Rational& rhs);

int main()
{
    Rational a, b;
    cout << "Input a rational number, e.g. 6/9.\n";
    cout << "a: ";
    cin >> a;
    cout << "Input a rational number, e.g. 6/9.\n";
    cout << "b: ";
    cin >> b;
    const Rational one = 1;

    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
    cout << "one = " << one << endl;
    cout << "a += b: " << (a += b) << endl;    // Implement as member
    cout << "a = " << a << endl;
    
    // Implement + as non-member, but not a friend
    cout << "a + one: " << (a + one) << endl;
    cout << "a == one: " << boolalpha << (a == one) << endl;
    
    // How does this manage to work?
    // It does NOT require writing another == operator.
    cout << "1 == one: " << boolalpha << (1 == one) << endl;
    
    // Do not implement as friend.
    cout << "a != one: " << boolalpha << (a != one) << endl;

    cout << "a = " << a << endl;
    cout << "++a = " << (++a) << endl;
    cout << "a = " << a << endl;
    cout << "a++ = " << (a++) << endl;
    cout << "a = " << a << endl;
    cout << "--a = " << (--a) << endl;
    cout << "a = " << a << endl;
    cout << "a-- = " << (a--) << endl;
    cout << "a = " << a << endl;

    cout << "++ ++a = " << (++ ++a) << endl;
    cout << "a = " << a << endl;
    cout << "-- --a = " << (-- --a) << endl;
    cout << "a = " << a << endl;

    cout << "a++ ++ = " << (a++ ++) << endl;
    cout << "a = " << a << endl;

    // Even though the above example, (a++ ++), compiled, the
    // following shouldn't.
    // But some compiler vendors might let it...  Is your compiler
    // doing the right thing? Why shouldn't it compile?
    //cout << "a-- -- = " << (a-- --) << endl;
    cout << "a = " << a << endl;


    // Should report that 1 is true
    if (Rational(1)) {
        cout << "1 is true" << endl;
    } else {
        cout << "1 is false" << endl;
    }

    // Should report that 0 is false
    if (Rational(0)) {
        cout << "0 is true" << endl;
    } else {
        cout << "0 is false" << endl;
    }

    cout << "Comparisons\n";
    Rational twoFifths(2, 5);
    Rational threeHalves(3, 2);
    Rational minusFive(-5);
    cout << twoFifths << " < " << threeHalves << " : "
         << (twoFifths < threeHalves) << endl;
    cout << twoFifths << " <= " << 1 << " : " << (twoFifths <= 1) << endl;
    cout << threeHalves << " < " << twoFifths << " : "
         << (threeHalves < twoFifths) << endl;
    cout << threeHalves << " > " << threeHalves << " : "
         << (threeHalves > threeHalves) << endl;
    cout << threeHalves << " >= " << threeHalves << " : "
         << (threeHalves >= threeHalves) << endl;
    cout << minusFive << " >= " << threeHalves << " : "
         << (minusFive >= threeHalves) << endl;
}

int greatestCommonDivisor(int x, int y)
{
    while (y != 0) {
        int temp = x % y;
        x = y;
        y = temp;
    }
    return x;
}

// Any functions that are not members and not friends should have
// their definitions here...

Rational operator+(const Rational& lhs, const Rational& rhs){
    Rational result(lhs);
    result += rhs;
    return result;
}

bool operator==(const Rational& lhs, const Rational& rhs){
    return (lhs.numerator * rhs.denominator) == (rhs.numerator * lhs.denominator);
}

bool operator<(const Rational& lhs, const Rational& rhs){
    return (lhs.numerator * rhs.denominator) < (rhs.numerator * lhs.denominator);
}

Rational& operator--(Rational& rhs){
    rhs += -1;
    return rhs;
}

Rational operator--(Rational& rhs, int var){
    Rational curr(rhs);
    rhs += -1;
    return curr;
}

bool operator!=(const Rational& lhs, const Rational& rhs){
    return !(lhs == rhs);
}

bool operator<=(const Rational& lhs, const Rational& rhs){
    return (lhs < rhs) || (lhs == rhs);
}


bool operator<=(const Rational& lhs, int rhs) {
    return lhs <= Rational(rhs);
}

bool operator<=(int lhs, const Rational& rhs) {
    return Rational(lhs) <= rhs;
}


bool operator>(const Rational& lhs, const Rational& rhs){
    return !(lhs <= rhs);
}

bool operator>=(const Rational& lhs, const Rational& rhs){
    return !(lhs < rhs);
}
