/*
 Author: Uvindu Salgado
 Purpose: Seperate compilation for hw07
 */

#include <iostream>
#include <string>
#include <vector>
#include "Warrior.hpp"
#include "Noble.hpp"
using namespace std;

namespace WarriorCraft{
    // overloading the operator for Warrior
    ostream& operator<<(ostream& os, const Warrior& randomWarrior){
        os << "        " << randomWarrior.name <<  ": " << randomWarrior.strength;
        return os;
    }

    Warrior::Warrior(const string& theName, int theStrength) :
    name(theName), strength(theStrength), hired(false), commander(nullptr) {}

    const string& Warrior::getName() const { return name; }
    double Warrior::getStrength() const { return strength; }
    void Warrior::setStrength(double newStrength) { strength = newStrength; }
    bool Warrior::isHired() const { return hired; }
    void Warrior::setHired(bool status) { hired = status; }
    void Warrior::setCommander(Noble* command) { commander = command; }

    bool Warrior::runaway(){
        if(commander == nullptr){
            // can't run away if the warrior has no noble
            return false;
        }
        else{
            // after running away, the warrior is no longer hired and has no noble
            cout << name << " flees in terror, abandoning his lord, "
            << commander -> getNobleName() << endl;
            commander -> removeWarrior(*this);
            commander = nullptr;
            setHired(false);
            return true;
        }
    }
}
