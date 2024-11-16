/*
 Author: Uvindu Salgado
 Purpose: Seperate compilation for hw08
 */

#include <iostream>
#include <vector>
#include "Noble.hpp"
#include "Protector.hpp"
using namespace std;

namespace WarriorCraft{
    //all the codes for Noble class
    Noble::Noble(const string& theName) : name(theName), alive(true) {}
    
    const string& Noble::getName() const { return name; }
    void Noble::changeAliveStatus() { alive = !alive; }
    bool Noble::getAliveStatus() const { return alive; }
    
    void Noble::battle(Noble& enemy){
        cout << name << " battles " << enemy.name << endl;
        //check if both Noble's are dead
        if(!alive && !enemy.alive){
            cout << "Oh, NO! They're both dead! Yuck!" << endl;
        }
        // if only enemy is alive, call defend method for enemy
        else if(!alive && enemy.alive){
            enemy.defend();
            cout << "He's dead, " << enemy.name << endl;
        }
        // if only instance is alive, call defend method for instance
        else if(alive && !enemy.alive){
            defend();
            cout << "He's dead, " << name << endl;
        }
        //both nobles are alive
        else{
            double selfStrength = getStrength();
            double enemyStrength = enemy.getStrength();
            defend();
            enemy.defend();
            //after calling defend method on both, determine which noble must die
            if(selfStrength == enemyStrength){
                die();
                enemy.die();
                cout << "Mutual Annihilation: " << name << " and " <<
                enemy.name << " die at each other's hands" << endl;
            }
            else if(selfStrength > enemyStrength){
                updateStrength(selfStrength, enemyStrength);
                enemy.die();
                cout << name << " defeats " << enemy.name << endl;
            }
            else{
                enemy.updateStrength(enemyStrength, selfStrength);
                die();
                cout << enemy.name << " defeats " << name << endl;
            }
        }
    }
    

    //all the code for Lord Class
    ostream& operator<<(ostream& os, const Lord& rhs){
        os << rhs.getName() << " has an army of size: " << rhs.army.size() << endl;
        if(rhs.army.size() > 0){
            for(Protector* currPtr : rhs.army){
                os << "   " << *currPtr;
            }
        }
        return os;
    }
    
    Lord::Lord(const std::string& theName) : Noble(theName) {}
    double Lord::getStrength() const{
        // idea is to sum up the strengths of all the Warriors in the army
        double totalStrength = 0;
        for(Protector* currPtr : army){
            totalStrength += currPtr -> getStrength();
        }
        return totalStrength;
    }

    void Lord::updateStrength(double winnerStrength, double loserStrength){
        for(Protector* currPtr : army){
            double newStrength = (currPtr->getStrength()) * ((winnerStrength - loserStrength) /
            winnerStrength);
            currPtr -> setStrength(newStrength);
        }
        
    }

    void Lord::defend() const{
        for(Protector* currPtr : army){
            currPtr -> defend();
        }
    }

    bool Lord::hires(Protector& someProtector){
        if(!getAliveStatus()){ //if the lord is not alive
            cout << getName() << " failed to hire " << someProtector.getName() << endl;
            return false;
        }
        if(someProtector.getLord()){ //if the protector is already hired
            cout << getName() << " failed to hire " << someProtector.getName() << endl;
            return false;
        }
        someProtector.setLord(this);
        army.push_back(&someProtector);
        return true;
    }
    
    bool Lord::fires(Protector& someProtector){
        if(!getAliveStatus()){ //if the lord is not alive
            cout << "Lord " << getName() << " is already dead!" << endl;
            return false;
        }
        if(remove(someProtector)){
            cout << someProtector.getName() << ", you don't work for me anymore "
            << "! -- " << getName() << "." << endl;
            return true;
        }
        return false;
    }

    //removing a protector from the army
    bool Lord::remove(Protector& someProtector){
        //remove and maintain the order
        bool found = false;
        size_t index = -1;
        for(size_t i = 0; i < army.size() - 1; i++){
            if(army[i] == &someProtector){
                found = true;
                index = i;
            }
            if(found){
                army[i] = army[i + 1];
            }
        }
        if(found){
            army.pop_back();
            return true;
        }
        //return false if the protector is not hired by the lord
        cout << someProtector.getName() << " is not hired by " <<
        getName() << "!" << endl;
        return false;
    }

    void Lord::die() {
        changeAliveStatus();
        //call another method to make this method shorter
        updateStrength(1, 1);
    }

    // all code for PersonWithStrengthToFight class
    ostream& operator<<(ostream& os, const PersonWithStrengthToFight& rhs){
        os << rhs.getName() << " has strength: " << rhs.strength << endl;
        return os;
    }
    
    PersonWithStrengthToFight::PersonWithStrengthToFight(const std::string&
        theName, int theStrength) : Noble(theName), strength(theStrength) {}
    double PersonWithStrengthToFight::getStrength() const { return strength; }

    void PersonWithStrengthToFight::updateStrength(double winnerStrength,
                                                   double loserStrength){
        strength -= loserStrength;
    }

    void PersonWithStrengthToFight::defend() const { cout << "Ugh!" << endl;}
    void PersonWithStrengthToFight::die() {
        changeAliveStatus();
        strength = 0;
    }
                                                    
}
