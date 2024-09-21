/*
 hw02.cpp
 Author : Uvindu Salgado
 Date : 11/09/24
 Purpose : Modelling a simple medieval game by reading in a file of commands and executing them one at a time.
 */

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

// Structure for tbe warrior with their names and strength in that order.
struct Warrior{
    string name;
    int strength;
};

// all function prototypes here
void openFile(ifstream& warriorStream);
void printWarriorVector(const vector<Warrior>& warrior_vector);
void stimulateBattle(Warrior& warrior_one, Warrior& warrior_two);
size_t searchWarriorVector(const string& name, const vector<Warrior>& warrior_vector);

int main() {
    // calling our function to open the file
    ifstream warriorStream;
    openFile(warriorStream);
    
    vector<Warrior> warriorVector; // The vector that will hold the details of the warriors.
    string command; // As we go through each line of the file, we must read each command from the stream
    
    // Identifying the first (command) word and taking appropriate action based on what it is.
    while (warriorStream >> command){
        if(command == "Warrior"){
            Warrior myWarrior;
            warriorStream >> myWarrior.name >> myWarrior.strength;
            // Putting the warrior we just initialized into our vector of warriors.
            warriorVector.push_back(myWarrior);
        }
        else if(command == "Status"){
            printWarriorVector(warriorVector);
        }
        else{
            string warriorOne, warriorTwo;
            warriorStream >> warriorOne >> warriorTwo;
            // use the search_warrior_vector function to find the indexes of warrior_one and warrior_two in the warrior_vector
            // check if warrior_one and warrior_two exist before stimulating battle
            size_t warriorOneIndex = searchWarriorVector(warriorOne, warriorVector);
            size_t warriorTwoIndex = searchWarriorVector(warriorTwo, warriorVector);
            if(warriorOneIndex == warriorVector.size() || warriorTwoIndex == warriorVector.size()){ // checking if the warriors were found in the warrior vector
                cerr << "One or both of the Warriors entered do not exist" << endl;
                exit(1);
            }
            stimulateBattle(warriorVector[warriorOneIndex], warriorVector[warriorTwoIndex]);
        }
    }
    warriorStream.close();
    return 0;
}

// Function to open the file and raise an error if it does not open
void openFile(ifstream& warriorStream){
    warriorStream.open("warriors.txt");
    if(!warriorStream){
        cerr << "File did not open" << endl;
        exit(1);
    }
}

// Displaying all the warriors' information in the warrior vector
void printWarriorVector(const vector<Warrior>& warriorVector){
    cout << "There are: " << warriorVector.size() << " warriors" << endl;
    for(const Warrior& currentWarrior: warriorVector){
        cout << "Warrior: " << currentWarrior.name << ", strength: " << currentWarrior.strength << endl;
    }
}

// stimulate a battle, modify the strength of Warriors and output different  messages based on each Warrior's condition
void stimulateBattle(Warrior& warriorOne, Warrior& warriorTwo){
    cout << warriorOne.name << " battles " << warriorTwo.name << endl;
    if(warriorOne.strength == 0 && warriorTwo.strength == 0){
        cout << "Oh, NO! They're both dead! Yuck!" << endl;
    }
    else if(warriorOne.strength == 0 && warriorTwo.strength > 0){
        cout << "He's dead, " <<  warriorTwo.name << endl;
    }
    else if(warriorTwo.strength == 0 && warriorOne.strength > 0){
        cout << "He's dead, " <<  warriorOne.name << endl;
    }
    else{
        if(warriorOne.strength == warriorTwo.strength){
            warriorOne.strength = warriorTwo.strength = 0;
            cout << "Mutual Annihilation: " << warriorOne.name << " and " << warriorTwo.name << " die at each other's hands" << endl;
        }
        else if(warriorOne.strength > warriorTwo.strength){
            warriorOne.strength -=  warriorTwo.strength;
            warriorTwo.strength = 0;
            cout << warriorOne.name << " defeats " << warriorTwo.name << endl;
        }
        else{ // This is the case where warrior_two has more strength than warrior_one
            warriorTwo.strength -= warriorOne.strength;
            warriorOne.strength = 0;
            cout << warriorTwo.name << " defeats " << warriorOne.name << endl;
        }
    }
}

// Search for a specified Warrior, gievn the name, in a given vector, warrior_vector in our case and return the index.
// return the size of the warrior_vector if it does not find the warrior.
size_t searchWarriorVector(const string& name, const vector<Warrior>& warriorVector){
    for(size_t index = 0; index < warriorVector.size(); index++){
        if(warriorVector[index].name == name){
            return index;
        }
    }
    return warriorVector.size();
}


