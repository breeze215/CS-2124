/*
 Author : Uvindu Salgado
 Purpose : Inheritance
 */

#include <iostream>
using namespace std;

class Base{
public:
private:
};

class Derived : public Base{
public:
private:
};

int main(){
    Base base;
    Derived derived;
    Base* base2 = new Base;
    base2 = nullptr;
    Derived* derived2 = new Derived;
    derived2 = nullptr;
    base = derived;
    //derived = base; //ILLEGAL : BASE TO DERIVED
    base2 = derived2;
    //derived2 = base2; //ILLEGAL : BASE TO DERIVED
    base2 = &base;
    base2 = &derived;
    derived2 = &derived;
    //derived2 = &base; //ILLEGAL : BASE TO DERIVED
}
