/*
 hw01.cpp
 Author : Uvindu Salgado
 Purpose : Decrypting an encrypted file with the Caesar cypher algorithm.
 */

#include <vector>
#include <fstream>
#include <iostream>
#include <string>
using namespace std;
 
//decrypting a character
char decrypt_character(char ch, int rotation){
    //let's ensure the character is uppercase
    if(ch >= 'A' && ch <= 'Z'){
        ch = ch - rotation; // Apply the rotation
        if (ch < 'A') { // Wrap around if it goes before 'A'
                 ch = ch + 26;
        }
        if (ch > 'Z') { // Wrap around if it goes beyond 'Z'
                 ch = ch - 26;
        }
    }
    return ch;
    
}

//decrypting an entire string
void decrypt_string(string& str, int rotation){
    for(char& ch : str){
        ch = decrypt_character(ch, rotation); //for loop to decrypt each char in string one by one
    }
}

int main() {
    //opening the encrypted file
    ifstream encrypt("encrypted.txt");
    if(!encrypt){ //if the file fails to open
        cerr << "The file did not open" << endl;
        exit(1);
    }
    string line;
    vector<string> file_lines;
    //getting the first line, the rotation factor
    int rotation;
    encrypt >> rotation;
    getline(encrypt, line); // To skip the newline character after the rotation integer
    
    //reading the remaining lines
    while(getline(encrypt, line)){
        file_lines.push_back(line);
    }
    //closing the file
    encrypt.close();
    
    //reading the vector backwards
    for(size_t i = file_lines.size(); i > 0; --i){
        decrypt_string(file_lines[i - 1], rotation); //using our decryption function
        cout << file_lines[i - 1] << endl;
    }
    return 0;
}
