/*
 Author: Uvindu Salgado
 Purpose: Seperate compilation for hw08
 */

#include "Noble.hpp"
#include "Protector.hpp"
using namespace std;

namespace WarriorCraft{
    //all the Protector code
    ostream& operator<<(ostream& os, const Protector& rhs){
        os << rhs.name << " has strength " << rhs.strength << endl;
        return os;
    }

    Protector::Protector(const string& theName, int theStrength) :
    name(theName), strength(theStrength), lord(nullptr) {}
    
    const string& Protector::getName() const { return name;}
    double Protector::getStrength() const { return strength; }
    void Protector::setStrength(double theStrength) { strength = theStrength; }
    void Protector::setLord(Lord* lordPtr) { lord = lordPtr; }
    Lord* Protector::getLord() const { return lord;}

    bool Protector::runaway(){
        if(strength == 0){ //fail is protector is dead
            cout << name << " is already dead!" << endl;
            return false;
        }
        if(!lord){ //fail if protector is not hired
            cout << name << " doesn't have a lord!" << endl;
            return false;
        }
        string lordName = lord -> getName();
        if(lord -> remove(*this)){
            cout << name << " flees in terror, abandoning his lord, " <<
            lordName << endl;
            return true;
        }
        //fail if the protector is not removed
        return false;
    }

    // all the code for the Warrior, Wizard, Archer and Swordsman classes
    void Warrior::defend() const{
        cout << getName() << " says: Take that in the name of my lord, " <<
        getLord() -> getName() << endl;
    }

    void Wizard::defend() const{
        cout << "POOF!" << endl;
    }

    void Archer::defend() const{
        cout << "TWANG! ";
        Warrior::defend();
    }
    void Swordsman::defend() const{
        cout << "CLANG! ";
        Warrior::defend();
    }
}
