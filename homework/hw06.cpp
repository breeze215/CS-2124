/*
  bigUnsigned class;
  Purpose : Model the Unsigned class and implement the operator functions
  Author : Uvindu Salgado
*/
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Put your class and all function definitions here.
class BigUnsigned{
    // the output operator
    friend ostream& operator<<(ostream& os, const BigUnsigned& output){
        // if there's nothing in the vector we just output a 0
        if(output.number.size() == 0) { os << 0; }
        else{
            // loop from the back of the vector which contains the most 
            //significant digit and output each element one at a time.
            for(size_t index = output.number.size() ; index > 0; --index){
                os << output.number[index - 1];
            }
        }
        return os;
    }
    // friend function prototypes for the == and < operators
    friend bool operator==(const BigUnsigned& lhs, const BigUnsigned& rhs);
    friend bool operator<(const BigUnsigned& lhs, const BigUnsigned& rhs);
public:
    // the first constructor which takes an integer value, defaults to 0 if no value is provided
    BigUnsigned(int val = 0){
        if(val < 0){
            // unsigned cannot take negative so if negative is given just push back 0 into the vector
            number.push_back(0);
        }
        else{
            if(val == 0){ // trivial
                number.push_back(0);
            }
            else{
                // we want to push the smallest digit in the number first. Eg: If we have 123, 
                //we want to push back 3 first. The way we do this is by modding the number with
                //10 which gives us the remainder which is equivalent to the digit we are on.
                //Following from the 123 example, 123 % 10 = 3 but this is exactly the same as
                //the last digit we wanted so we push it back into the vector and repeat this
                //process for the other digits.
                while(val > 0){
                    number.push_back(val % 10);
                    // we do this to get rid of the digit we just added. Eg: 123 / 10 = 12 
                    //so we effectively removed the 3 after adding it.
                    val /= 10;
                }
            }
        }
    }
    
    // the second constructor which takes a string
    BigUnsigned(const string& val){
        // checks to see if the first digit in the string is a number,
        //if it is not, then we push back 0
        if(!isdigit(val[0])){
            number.push_back(0);
        }
        else{
            // create a temporary vector and push all elements from the starting number
            //in the string up until the final digit before the string ends or there are
            //no more digits to the right of that final digit (there are only characters)
            size_t checkDigit = 0;
            vector<int> tempDigits;
            while(checkDigit < val.size() && isdigit(val[checkDigit])){
                // - '0' because we want to convert the characters we're pushing into
                //integers before pushing back into the temporary vector
                tempDigits.push_back(val[checkDigit] - '0');
                checkDigit++;
            }
            // this is to eleminate any leading zero's, iterate through the temporary vector
            //until the point where you reach the first non zero element and mark that point.
            //Note that you can do this from front to back in the temporary vector because
            //we haven't stored them in reverse order like we will in the next step.
            size_t firstNonZero = 0;
            while(firstNonZero < val.size() - 1 && tempDigits[firstNonZero] == 0){
                firstNonZero++;
            }
            // add all elements from the temporary vector to the number vector from the end
            //to the point where you found the first non zero element. This way you order
            //the elements from least signficant digit to most significant digit in the
            //number vector and you eliminate any leading 0's.
            for(size_t i = tempDigits.size(); i > firstNonZero; --i){
                number.push_back(tempDigits[i - 1]);
            }
        }
    }
    
    // += operator which we use later in the + operator as well as in main
    BigUnsigned& operator+=(const BigUnsigned& rhs){
        // define a carry incase the sum of two numbers exceeds 9
        int carry = 0;
        // an alternate way of saying assign maxSize to the size whichever vector is bigger
        size_t maxSize = number.size() > rhs.number.size() ? number.size() : rhs.number.size();
        // keep running through the loop while index < maxSize or carry is not 0
        for(size_t index = 0; index < maxSize || carry != 0; ++index){
            // if the index is past the vector of the number we are adding to, make it 
            //larger by pushing a 0 into it, which is technically the first digit of
            //the number now
            if(index >= number.size()){
                number.push_back(0);
            }
            // if the index is past the size of the vector of rhs, then assign 0 to 
            //rhsNumber, else we assign rhs.number[index]
            int rhsNumber = index < rhs.number.size() ? rhs.number[index] : 0;
            // the new value at the index position is whatever was in it plus the 
            //carry plus the number in that same position in rhs
            number[index] += rhsNumber + carry;
            // dividing by 10 gives us by how much the carry needs to be incase the
            //number is 10 or more. Eg: 14 / 10 = 1 so 1 becomes the carry
            carry = number[index] / 10;
            // the index cannot hold a value larger than 9 so mod it with 10 to 
            //guarantee this. Following from our previous example, 14 % 10 = 4
            //so 4 becomes the digit at the index and 1 gets carried over which
            //is exactly what we want
            number[index] %= 10;
        }
        // return the BigUnsigned we're performing += on
        return *this;
    }
    
    // pre increment operator
    BigUnsigned& operator++(){
        *this += 1;
        return *this;
    }
    
    // post increment operator, marked by a dummy variable
    //to differentiate between pre and post
    BigUnsigned operator++(int dummy){
        BigUnsigned result(*this);
        *this += 1;
        return result;
    }
    
    // this explicit operator supports the ? we call in main
    explicit operator bool() const { return !(number[0] == 0); }
private:
    vector<int> number;
};

// == and < are friend functions
bool operator==(const BigUnsigned& lhs, const BigUnsigned& rhs){
    bool equality = false;
    // if the numbers are not the same length, they can 
    //never be equal (because we have no leading zero's)
    if(lhs.number.size() != rhs.number.size()){
        return equality;
    }
    // if they are the same length and one or more of the 
    //elements of their vectors are different,
    // the numbers are not equal
    for(size_t index = 0; index < lhs.number.size(); index++){
        if(lhs.number[index] != rhs.number[index]){
            return equality;
        }
    }
    // if all the checks are passed, we return true
    return !equality;
}

bool operator<(const BigUnsigned& lhs, const BigUnsigned& rhs){
    bool lessThan = true;
    // if the lhs is longer than the rhs, then the lhs 
    //must be a larger value (because we have no
    //leading zero's)
    if(lhs.number.size() > rhs.number.size()){
        return !lessThan;
    }
    // if they are of the same length, then check 
    //whether they are equal and return false if they are
    if(lhs == rhs){
        return !lessThan;
    }
    // if they are not equal check the moment at which the first difference
    //in digits occurs and check whether at this point the digit on the lhs
    //is greater than the digit in the rhs and return false if it is.
    //Loop from back of the vector to the front because the front contains
    //the least significant digit.
    for(size_t index = lhs.number.size(); index > 0; --index){
        if(lhs.number[index - 1] != rhs.number[index - 1]
           && lhs.number[index - 1] > rhs.number[index -1]){
            return !lessThan;
        }
    }
    // return true if it passes all checks
    return lessThan;
}

// all non member and non friend operators have their prototypes here
// the functions themselves are written under main
BigUnsigned operator+(const BigUnsigned& lhs, const BigUnsigned& rhs);
bool operator!=(const BigUnsigned& lhs, const BigUnsigned& rhs);
bool operator<=(const BigUnsigned& lhs, const BigUnsigned& rhs);
bool operator>(const BigUnsigned& lhs, const BigUnsigned& rhs);
bool operator>=(const BigUnsigned& lhs, const BigUnsigned& rhs);

int main()
{
    BigUnsigned zero;
    BigUnsigned one(1);
    cout << "zero: " << zero << endl;
    cout << "one: " << one << endl;
    BigUnsigned val = 1;
    cout << "val: " << val << endl;
    cout << "++val: " << ++val << endl;
    cout << "val: " << val << endl;
    cout << "val++: " << val++ << endl;
    cout << "val: " << val << endl;
    
    cout << "(one + zero): " << (one + zero) << endl;
    cout << "(one + one): " <<  (one + one) << endl;

    cout << boolalpha;
    cout << "one < one: " << (one < one) << endl;
    cout << "zero < one: " << (zero < one) << endl;

    BigUnsigned a = 123;
    BigUnsigned b = 1234;
    BigUnsigned c = 124;
    BigUnsigned d = 12345;

    cout << "a: " << a << ", b: " << b
         << ", c: " << c << ", d: " << d << endl;
    cout << "a + d: " << (a + d) << endl;
    cout << "d + d: " << (d + d) << endl;
    cout << "a < d: " << (a < d) << endl;
    cout << "d < a: " << (d < a) << endl;
    cout << "zero == zero: " << (zero == zero) << endl
         << "zero == one: " << (zero == one) << endl
         << "a == a: " << (a == a) << endl
         << "a == d: " << (a == d) << endl
         << "d == a: " << (d == a) << endl;

    cout << "(zero == 0): " << (zero == 0) << endl
         << "(one == 0): " << (one == 0) << endl
         << "(1 == one): " << (1 == one) << endl;

    // +=
    cout << "b: " << b << ", c: " << c << endl;
    cout << "(c += b): " << (c += b) << endl;
    cout << "b: " << b << ", c: " << c << endl;


    BigUnsigned x = a;
    cout << "x: " << x << ", a: " << a << endl
         << "x == a: " << (x == a) << endl
         << "a == x: " << (a == x) << endl
         << "a < x: " << (a < x) << endl
         << "a > x: " << (a > x) << endl;
    
    cout << "x > a: " << (x > a) << endl
         << "x >= a: " << (x >= a) << endl
         << "x <= a: " << (x <= a) << endl
         << "x != a: " << (x != a) << endl;
         
    
    BigUnsigned big("987654321");
    BigUnsigned big2("  ");
    BigUnsigned big3("felix");
    BigUnsigned big4("00987654321");

    cout << "big: " << big << endl
         << "big2: " << big2 << endl
         << "big3: " << big3 << endl
         << "big4: " << big4 << endl;

    BigUnsigned big5(98765);
    BigUnsigned big6(2457);
    cout << "big5: " << big5  << ", big6: " <<  big6 << endl
         << "(big5 + big6): " << (big5 + big6) << endl
         << "(big6 + big5): " << (big6 + big5) << endl;


    // How does this work?
    // works using our explicit operator bool() function
    cout << zero << " is " << (zero ? "true" : "false") << endl;
    cout << one << " is " << (one ? "true" : "false") << endl;
    cout << big4 << " is " << (big4 ? "true" : "false") << endl;
} // main

// the + operator calls on the += to simplify the work
BigUnsigned operator+(const BigUnsigned& lhs, const BigUnsigned& rhs){
    BigUnsigned result(lhs);
    result += rhs;
    return result;
}

// the != operator calls on the == to simplify the work. If the
//lhs == rhs does not return true, then lhs != rhs will return true
bool operator!=(const BigUnsigned& lhs, const BigUnsigned& rhs){
    return !(lhs == rhs);
}

// the <= operator calls on both the == and the < operators to
//simplify the work, if either operator returns true, <= returns true
bool operator<=(const BigUnsigned& lhs, const BigUnsigned& rhs){
    return (lhs < rhs) || (lhs == rhs);
}

// the > operator calls on the <= operator to simplify the work.
//If the lhs is not <= the rhs, then it must be greater
bool operator>(const BigUnsigned& lhs, const BigUnsigned& rhs){
    return !(lhs <= rhs);
}

// the >= operator calls on the < operator to simplify the work.
//If lhs < rhs returns false then lhs must be >= rhs so lhs >= rhs
//returns true.
bool operator>=(const BigUnsigned& lhs, const BigUnsigned& rhs){
    return !(lhs < rhs);
}
