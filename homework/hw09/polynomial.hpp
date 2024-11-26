#ifndef POLYNOMIAL_HPP
#define POLYNOMIAL_HPP

#include <iostream>
#include <vector>

namespace Math {

    class Polynomial {
        struct Term;
        
        // non member friend functions
        friend void printTerm(Polynomial::Term* termPtr, int degree);
        friend std::ostream& operator<<(std::ostream& os, const Polynomial& rhs);
        friend bool operator==(const Polynomial& lhs, const Polynomial& rhs);
    public:
        // default constructor, constructor that takes in a vector of ints
        // and the copy constructor
        Polynomial();
        Polynomial(const std::vector<int>& coefficients);
        Polynomial(const Polynomial& rhs);
        
        // non friend member operators
        Polynomial& operator+=(const Polynomial& rhs);
        Polynomial& operator=(const Polynomial& rhs);
        
        // destructor
        ~Polynomial();
        
        // function to evaluate the polynomial at a given x value
        int evaluate(int val) const;
        
        // useful functions to add and delete terms that we will need throughout the code
        void clearLeadingZeroes();
        void clearPolynomial(Term* currTerm);
        void addLowestTerm(int val);
        Polynomial::Term* addHighestTerm(int val, Term* highest);
    private:
        // nested struct Term
        struct Term {
            Term(int coefficient = 0, Term* next = nullptr);
            
            int coefficient;
            Term* next;
        };
        
        Term* headptr;
        int degree;
    };
    
    // non member non friend operators
    Polynomial operator+(const Polynomial& lhs, const Polynomial& rhs);
    bool operator!=(const Polynomial& lhs, const Polynomial& rhs);
}
#endif
