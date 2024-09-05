/*
  rec01_start.cpp
  spring 2024
*/
//Uvindu Salgado
//uis202
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
using namespace std;

//
// Function definitions for tasks 15-17
//

// Task 15. Function to display a vector of ints
void display_vec(const vector<int>& vec){
    for(int val: vec){
        cout << val << ",";
    }
    cout << endl;
}


// Task 16. Function to modify the vector, using indices

void mod_vec_indices(vector<int>& vec){
    for(size_t i = 0; i < vec.size(); ++i){
        vec[i] *= 2;
    }
}

// Task 17. Function to modify the vector, using a ranged for

void mod_vec_for(vector<int>& vec){
    for(int& val : vec){
        val *= 2;
    }
}
//
// main
//
int main() { // Yes, it has to have an int for the return type
    //
    // Output
    //

    // Task 1. Printing hello ...  No use of "using namespace"
    std::cout << "Hello world without namespace" << std::endl;

    // Task 2  Printing hello ...  Using "using namespace"
    cout << "Hello world with namespace, this is much simpler" << endl;


    //
    // Types and variables
    //

    // Task 3  Displaying uninitialized variable
    int x;
    cout << "x: " << x << endl;
    
    // Task 4 Use the sizeof function to see the size in bytes of
    //        different types on your machine.
    int y = 17;
    int z = 2000000017;
    double pi = 3.14159;
    cout << "The sizes of x, y, z and pi are " << sizeof(x) << "," << sizeof(y) << "," << sizeof(z) << " and " << sizeof(pi) << " respectively." << endl;
    // Task 5  Attempt to assign the wrong type of thing to a variable
    //int x_2 = "felix";
    //compilation error
    
    //
    // Conditions
    //

    // Task 6  Testing for a range
    if((y >= 10) && (y <= 20)){
        cout << "y is between 10 and 20 inclusive." << endl;
    }
    else{
        cout << "y is not between 10 and 20 inclusive." << endl;
    }

    //
    // Loops and files
    //

    // Task 7  Looping, printing values 10 to 20 inclusive

    // First with a for loop
    for(int i = 10; i <= 20; ++i){
        cout << i << ",";
    }
    // Then with a while loop
    cout << endl;
    int l = 10;
    while(l <= 20){
        cout << l << ",";
        l++;
    }
    // Finally with a do-while loop
    cout << endl;
    int l2 = 10;
    do{
        cout << l2 << ",";
        l2++;
    }
    while(l2 <= 20);

    // Task 8  Looping to successfully open a file, asking user for the name
    cout << endl;
    ifstream ifs;
    do{
        string filename;
        cout << "input filename: ";
        cin >> filename;
        ifs.open(filename);
    }while(!ifs);

    // Task 9  Looping, reading file word by "word".
    string words;
    while(ifs >> words){
        cout << words << endl;
    }
    ifs.close();
    // Task 10 Open a file of integers, read it in, and display the sum.
    ifstream lfs;
    lfs.open("integers.txt");
    int nums, res = 0;
    while(lfs >> nums){
        res += nums;
    }
    cout << "The sum is: " << res << endl;
    lfs.close();
    // Taks 11 Open and read a file of integers and words. Display the sum.
    ifstream mfs;
    mfs.open("mixed.txt");
    int nums2, res2 = 0;
    while(mfs >> nums2){
        res2 += nums2;
    }
    cout << "The sum is: " << res2 << endl; // sum terminated as soon as it reached the first word
    mfs.close();

    //
    // Vectors
    //

    // Task 12 Filling a vector of ints
    cout<<endl;
    vector<int> even_nums;
    for(int i = 10; i <= 100; i = i + 2){
        even_nums.push_back(i);
    }
    // Task 13 Displaying the vector THREE times
    //         a) using the indices,
    for(size_t i = 0; i < even_nums.size(); ++i){
        cout << even_nums[i] << ",";
    }
    cout << endl;
    //         b) using a "ranged for"
    for(int value : even_nums){
        cout << value << ",";
    }
    cout << endl;
    //         c) using indices again but backwards
    for(size_t i = even_nums.size(); i > 0; --i){
        cout << even_nums[i - 1] << ",";
    }
    cout << endl;
    // Task 14. Initialize a vector with the primes less than 20.
    vector<int> primes{2, 3, 4, 7, 11, 13, 17, 19};
    for(int val: primes){
        cout << val << ",";
    }
    cout << endl;
    //
    // Function calls
    //
    
    // Task 15  Function to print a vector
    display_vec(even_nums);

    // Task 16  Function to double the values in a vector
    mod_vec_indices(primes);
    display_vec(primes);

    // Task 17  Function to double the values in a vector, using a ranged for
    mod_vec_for(primes);
    display_vec(primes);
    
}

