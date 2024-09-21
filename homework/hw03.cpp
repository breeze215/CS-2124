/*
 hw03.cpp
 Author : Uvindu Salgado
 Date : 18/09/24
 Purpose : Modelling a simple medieval game by reading in a file of commands and executing them one at a time, using classes this time.
 */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

class Warrior{
    // prototyping the nested class to ensure that the weapon friend function is defined without error
    class Weapon;
    friend ostream& operator<<(ostream& os, const Warrior& randomWarrior);
    friend ostream& operator<<(ostream& os, const Weapon& randomWeapon);
    
public:
    // the initialization list
    Warrior(const string& name, const string& weaponName, int theStrength) : nameOfWarrior(name), warriorWeapon(weaponName, theStrength) {}
    
    // getter and setter methods to acess data outside the class
    string getName() const { return nameOfWarrior; }
    int getWeaponStrength() const { return warriorWeapon.getStrength(); }
    void setWeaponStrength(int strength) { warriorWeapon.setStrength(strength); }
    
    // turn battle into a method with different outputs based on the battle conditions
    // modify the strength of the warriors within the vector
    void warriorBattle(Warrior& enemyWarrior){
        cout << nameOfWarrior << " battles " << enemyWarrior.nameOfWarrior << endl;
        if(getWeaponStrength() == 0 && enemyWarrior.getWeaponStrength() == 0){
            cout << "Oh, NO! They're both dead! Yuck!" << endl;
        }
        else if(getWeaponStrength() == 0 && enemyWarrior.getWeaponStrength() > 0){
            cout << "He's dead, " << enemyWarrior.nameOfWarrior << endl;
        }
        else if(getWeaponStrength() > 0 && enemyWarrior.getWeaponStrength() == 0){
            cout << "He's dead, " << nameOfWarrior << endl;
        }
        else{
            if(getWeaponStrength() == enemyWarrior.getWeaponStrength()){
                setWeaponStrength(0);
                enemyWarrior.setWeaponStrength(0);
                cout << "Mutual Annihilation: " << nameOfWarrior << " and " << enemyWarrior.nameOfWarrior << " die at each other's hands" << endl;
            }
            else if(getWeaponStrength() > enemyWarrior.getWeaponStrength()){
                setWeaponStrength(getWeaponStrength() - enemyWarrior.getWeaponStrength());
                enemyWarrior.setWeaponStrength(0);
                cout << nameOfWarrior << " defeats " << enemyWarrior.nameOfWarrior << endl;
            }
            else{ // case where enemy's weapon strength is greater than the other warrior
                enemyWarrior.setWeaponStrength(enemyWarrior.getWeaponStrength() - getWeaponStrength());
                setWeaponStrength(0);
                cout << enemyWarrior.nameOfWarrior << " defeats " << nameOfWarrior;
            }
        }
    }
    
private:
    // the nested weapon class within the warrior class
    class Weapon{
        friend ostream& operator<<(ostream& os, const Weapon& randomWeapon);
        
    public:
        // the initialization list
        Weapon(const string& weaponName, int strength) : nameOfWeapon(weaponName), weaponStrength(strength) {}
        int getStrength() const { return weaponStrength; }
        void setStrength(int strength) {weaponStrength = strength; }
        
    private:
        // the private variables only accesible within the Weapon class
        string nameOfWeapon;
        int weaponStrength;
    };
    
    // the private variables only accesible within the Warrior class
    string nameOfWarrior;
    Weapon warriorWeapon;
};

// all function prototypes here
void openFile(ifstream& warriorStream);
void displayWarriors(const vector<Warrior>& warriorVector);
size_t searchWarrior(const string& name, const vector<Warrior>& warriorVector);

int main() {
    // creating our stream and calling our function to open the file
    ifstream warriorStream;
    openFile(warriorStream);
    
    // vector to store the Warrior structures and "command" is used to read the command word from the stream
    vector<Warrior> warriorVector;
    string command;
    
    while(warriorStream >> command){
        // taking different actions based on the command word
        if(command == "Warrior"){
            string name, weapon;
            int strength;
            warriorStream >> name >> weapon >> strength;
            // construct a new Warrior and put it at the end of the warriorVector
            warriorVector.emplace_back(name, weapon, strength);
        }
        else if(command == "Status"){
            displayWarriors(warriorVector);
        }
        else{ // the command word is "Battle" here
            
            string warriorOne, warriorTwo;
            warriorStream >> warriorOne >> warriorTwo;
            size_t warriorOneIndex = searchWarrior(warriorOne, warriorVector);
            size_t warriorTwoIndex = searchWarrior(warriorTwo, warriorVector);
            
            // check to see if both the Warriors were found in the warriorVector
            if(warriorOneIndex == warriorVector.size() || warriorTwoIndex == warriorVector.size()){
                cerr << "One or both of the warriors were not found within the warrior vector" << endl;
                exit(1);
            }
            warriorVector[warriorOneIndex].warriorBattle(warriorVector[warriorTwoIndex]);
        }
    }
    warriorStream.close();
    return 0;
}

// function to open file and return an error message if the file doesn't open.
void openFile(ifstream& warriorStream){
    warriorStream.clear();
    warriorStream.open("warriors.txt");
    if(!warriorStream){
        cerr << "The file warriors.txt failed to open" << endl;
        exit(1);
    }
}

// function to display all the warriors in the warriorVector as well as their information
void displayWarriors(const vector<Warrior>& warriorVector){
    cout << "There are "  << warriorVector.size() << " warriors" << endl;
    for(const Warrior& currentWarrior : warriorVector){
        cout << currentWarrior;
    }
}

// function to search for a given Warrior in the warriorVector given its name and return the index if found, if the Warrior is not found then return the size of the warriorVector
size_t searchWarrior(const string& name, const vector<Warrior>& warriorVector){
    for(size_t index = 0; index < warriorVector.size(); index++){
        if(warriorVector[index].getName() == name){
            return index;
        }
    }
    return warriorVector.size();
}

// operator overload for Warrior
ostream& operator<<(ostream& os, const Warrior& randomWarrior){
    os << "Warrior: " << randomWarrior.nameOfWarrior << ", " << randomWarrior.warriorWeapon;
    return os;
}

// operator overload for Weapon
ostream& operator<<(ostream& os, const Warrior::Weapon& randomWeapon){
    os << "weapon: " << randomWeapon.nameOfWeapon << ", " << randomWeapon.weaponStrength << endl;
    return os;
}
