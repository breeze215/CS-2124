/*
 Author: Uvindu Salgado
 Purpose: Seperate compilation for hw07
 */

#include <vector>
#include <string>
#include <iostream>
#include "Warrior.hpp"
#include "Noble.hpp"
using namespace std;

namespace WarriorCraft{
    // overloading the operator for Noble
    ostream& operator<<(ostream& os, const Noble& randomNoble){
        os << randomNoble.name << " has an army of " << randomNoble.nobleArmy.size() << endl;
        for(const Warrior* const currWarrior : randomNoble.nobleArmy){
            if(currWarrior){
                os << *currWarrior << endl;
            }
        }
        return os;
    }

    Noble::Noble(const string& nobleName) : name(nobleName), nobleArmy(), alive(true) {}

    double Noble::totalArmyStrength() const{
        double totalStrength = 0;
        for(const Warrior* const currWarrior : nobleArmy){
            totalStrength += currWarrior -> getStrength();
        }
        return totalStrength;
    }

    size_t Noble::getNobleArmySize() const { return nobleArmy.size(); }

    void Noble::updateNobleArmyStrength(double winner, double loser){
        for(Warrior* const currWarrior : nobleArmy){
            double newStrength = (currWarrior -> getStrength()) * ((winner - loser) / winner);
            currWarrior -> setStrength(newStrength);
        }
    }

    vector<Warrior*>& Noble::getNobleArmy() { return nobleArmy; };
    const string& Noble::getNobleName() const { return name; }

    void Noble::die(){
        alive = false;
        for(Warrior* const currWarrior : nobleArmy) { currWarrior -> setStrength(0); }
    }

    bool Noble::hire(Warrior& someWarrior){
       if(!alive || someWarrior.isHired()){
           // fail if noble is dead or warrior is already hired
           cout << name << " failed to hire " << someWarrior.getName() << endl;
           return false;
       }
       else{
           someWarrior.setHired(true);
           someWarrior.setCommander(this);
           nobleArmy.push_back(&someWarrior);
           return true;
       }
    }

    bool Noble::fire(Warrior& someWarrior){
        if(!alive){
            // fail to fire a warrior if the noble is dead
            cout << name << " has failed to fire " << someWarrior.getName() << endl;
            return false;
        }
        // calls on removeWarrior to make the process easier
        bool status = removeWarrior(someWarrior);
        if(status){
            cout << someWarrior.getName() << ", you don't work for me anymore! -- " << name << "." << endl;
            someWarrior.setHired(false);
            someWarrior.setCommander(nullptr);
        }
        else{
            cout << name << " failed to fire " << someWarrior.getName() << endl;
        }
        return status;
    }

    //method called in battle method to simplify it
    void Noble::updateStrength(Noble& winner, Noble& loser){
        double win = winner.totalArmyStrength();
        double lose = loser.totalArmyStrength();
        if(win == lose){
            winner.die();
            loser.die();
            cout << "Mutual Annihilation: " << winner.name << " and " <<
            loser.name << " die at each other's hands" << endl;
            return;
        }
        updateWinner(winner, loser, win, lose);
    }

    //method that is called in updateStrength to simplify it
    void Noble::updateWinner(Noble& winner, Noble& loser, double win, double lose){
        if(win > lose){
            loser.die();
            updateNobleArmyStrength(win, lose);
            cout << winner.name << " defeats " << loser.name << endl;
            return;
        }
        winner.die();
        updateNobleArmyStrength(lose, win);
        cout << loser.name << " defeats " << winner.name << endl;
    }

    void Noble::battle(Noble& enemy){
        cout << name << " battles " << enemy.name << endl;
        if(!alive && !enemy.alive){
            cout << "Oh, NO! They're both dead! Yuck!" << endl;
        }
        else if(!alive && enemy.alive){
            cout << "He's dead, " << enemy.name << endl;
        }
        else if(alive && !enemy.alive){
            cout << "He's dead, " << name << endl;
        }
        else{
            updateStrength(*this, enemy);
        }
    }

    // method to use in other methods
    bool Noble::removeWarrior(Warrior& someWarrior){
        bool found = false;
        for(size_t index = 0; index < nobleArmy.size(); index++ ){
            if(found == false){
                if(nobleArmy[index] == &someWarrior){
                    found = true;
                }
            }
            else{
                // if the warrior is found then shift every warrior after that one to the left 
                //and pop the last repeated warrior at the end
                nobleArmy[index - 1] = nobleArmy[index];
            }
        }
        if(found){
            // removing the warrior that is repeated at the end after our loop, if a warrior is found
            nobleArmy.pop_back();
        }
        return found;
    }
}
