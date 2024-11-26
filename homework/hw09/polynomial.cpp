/*
 Author : Uvindu Salgado
 Purpose : hw09.cpp
 Polynomial class
 */


#include "polynomial.hpp"
using namespace std;

namespace Math {
    //all the codes for the Polynomial class

    //recursive function to output the polynomial
    //call this function in the output operator
    void printTerm(Polynomial::Term* termPtr, int degree){
        if(termPtr -> next){
            // recursive call
            printTerm(termPtr -> next, degree + 1);
            if(termPtr -> coefficient) cout << " + ";
        }
        if(termPtr -> coefficient){
            if((termPtr -> coefficient != 1 &&
               termPtr -> coefficient != -1) || degree == 0){
                cout << termPtr -> coefficient;
            }
            if(degree > 0){
                // we don't want to print coefficients if they are 1 or -1
                // as shown in the output example
                if(termPtr -> coefficient == -1){
                    cout << "-x";
                }
                else{
                    cout << "x";
                }
                if(degree > 1) cout << "^" << degree;
            }
        }
        else if(!termPtr -> next) cout << "0";
    }
    
    //friend operators
    // << operator overload, simplify it by calling printTerm within the output operator
    ostream& operator<<(ostream& os, const Polynomial& rhs){
        printTerm(rhs.headptr, 0);
        return os;
    }

    // == operator overload
    bool operator==(const Polynomial& lhs, const Polynomial& rhs){
        if(lhs.degree != rhs.degree) return false;
        Polynomial::Term* currLhs = lhs.headptr;
        Polynomial::Term* currRhs = rhs.headptr;
        while(currLhs){
            if(currLhs -> coefficient != currRhs -> coefficient) return false;
            currLhs = currLhs -> next;
            currRhs = currRhs -> next;
        }
        return true;
    }
    
    // default constructor, when called, it creates a zero polynomial
    Polynomial::Polynomial() : headptr(new Term()), degree(0) {}
    // constructor that takes in a vector of ints representing the coefficients
    Polynomial::Polynomial(const vector<int>& coefficients) : headptr(nullptr), degree(-1) {
        for(int coefficient : coefficients){
            addLowestTerm(coefficient);
        }
        clearLeadingZeroes();
    }

    // copy constructor
    Polynomial::Polynomial(const Polynomial& rhs) : headptr(nullptr), degree(0){
        Term* currPtr = rhs.headptr;
        Term* prior = nullptr;
        while(currPtr){
            prior = addHighestTerm(currPtr -> coefficient, prior);
            currPtr = currPtr -> next;
        }
    }

    // member non friend operators
    // overloading the += operator
    Polynomial& Polynomial::operator+=(const Polynomial& rhs){
        Term* currLhs = headptr;
        Term* currRhs = rhs.headptr;
        Term* prior = headptr;
        while(currLhs){
            if(!currRhs) break;
            currLhs -> coefficient += currRhs -> coefficient;
            if(!currLhs -> next) prior = currLhs;
            currLhs = currLhs -> next;
            currRhs = currRhs -> next;
        }
        while(currRhs){
            prior = addHighestTerm(currRhs -> coefficient, prior);
            currRhs = currRhs -> next;
        }
        clearLeadingZeroes();
        return *this;
    }

    // overloading the assignnment operator
    Polynomial& Polynomial::operator=(const Polynomial& rhs){
        if(this != &rhs){
            clearPolynomial(headptr);
            degree = 0;
            Term* currPtr = rhs.headptr;
            Term* prior = nullptr;
            while(currPtr){
                prior = addHighestTerm(currPtr -> coefficient, prior);
                currPtr = currPtr -> next;
            }
        }
        return *this;
    }

    // destructor
    Polynomial::~Polynomial(){
        clearPolynomial(headptr);
    }

    // function to evaluate the polynomial at a given x value
    int Polynomial::evaluate(int val) const{
        int result = 0;
        int degree = 0;
        Term* currPtr = headptr;
        while(currPtr){
            if(currPtr -> coefficient){
                int termValue = currPtr -> coefficient;
                for(int i = 0; i < degree; ++i){
                    termValue *= val;
                }
                result += termValue;
            }
            currPtr = currPtr -> next;
            ++degree;
        }
        return result;
    }

    // clear the leading 0's in the polynomial, used multiple times throughout the code
    void Polynomial::clearLeadingZeroes(){
        Term* currPtr = headptr;
        Term* prior = nullptr;
        while(currPtr -> next){
            if(!currPtr -> next -> coefficient){
                // we store the adress of the first zero before the
                // consecutive zero's begin
                if(!prior) prior = currPtr;
            }
            else{
                // in case we hit a non zero before the end, reset prior to nullptr
                if(prior) prior = nullptr;
            }
            currPtr = currPtr -> next;
        }
        if(prior){
            // call this function only if leading zero's are found
            clearPolynomial(prior -> next);
            prior -> next = nullptr;
        }
    }

    // clear the rest of the polynomial from a given pointer
    void Polynomial::clearPolynomial(Term* currTerm){
        while(currTerm){
            // store the current term, bump it and then delete it using the variable prior
            Term* prior = currTerm;
            currTerm = currTerm -> next;
            delete prior;
            --degree;
        }
        currTerm = nullptr;
    }

    // add the lowest term to the polynomial, called multiple times throughout the code
    void Polynomial::addLowestTerm(int val){
        headptr = new Term(val, headptr);
        ++degree;
    }

    // add the highest term to the polynomial and return a pointer to this term
    // this is done because we call this function in while loops
    Polynomial::Term* Polynomial::addHighestTerm(int val, Term* highest){
        if(!highest){
            // handle the case where highest is a nullptr
            headptr = new Term(val);
            return headptr;
        }
        highest -> next = new Term(val);
        ++degree;
        return highest -> next;
    }

    // nested struct Term's constructor
    Polynomial::Term::Term(int coefficient, Term* next) : coefficient(coefficient), next(next) {}

    //non member non friend operators
    // overloading the + operator, using the += method
    Polynomial operator+(const Polynomial& lhs, const Polynomial& rhs){
        Polynomial result(lhs);
        return result += rhs;
    }

    // overloading the != operator, using the == operator
    bool operator!=(const Polynomial& lhs, const Polynomial& rhs){
        return !(lhs == rhs);
    }
}

