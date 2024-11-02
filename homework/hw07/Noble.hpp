/*
 Author: Uvindu Salgado
 Purpose: Seperate compilation for hw07
 */

#ifndef NOBLE_HPP
#define NOBLE_HPP

#include <vector>
#include <string>
#include <iostream>

namespace WarriorCraft{
    class Warrior;
    class Noble{
        // prototype for the friend function  of the Noble class
        friend std::ostream& operator<<(std::ostream& os, const Noble& randomNoble);
    public:
        // initialization list
        Noble(const std::string& nobleName);
           
        // adding up the strength of all the warriors that a part of the 
        //noble's army and return this value
        double totalArmyStrength() const;
            
        // function to get the number of warriors employed by the noble
        size_t getNobleArmySize() const;

        // update the strength of each warrior after battle if the
        //army strength's are different and non zero.
        // The way this is done is by multiplying each warrior
        //strength by the ratio of the army strength's.
        void updateNobleArmyStrength(double winner, double loser);
           
        // getters
        std::vector<Warrior*>& getNobleArmy();
        const std::string& getNobleName() const;
           
        // set all warrior strength's to 0 and set alive to false
        void die();
           
        //method to hire a warrior
        bool hire(Warrior& someWarrior);
           
        //method to fire a warrior
        bool fire(Warrior& someWarrior);
           
        //methods to clean up the code in battle
        void updateStrength(Noble& winner, Noble& loser);
        void updateWinner(Noble& winner, Noble& loser, double win, double lose);
            
        void battle(Noble& enemy);
            
        //method to use in other methods
        bool removeWarrior(Warrior& someWarrior);
    private:
        // all the private variables of the Noble class
        std::string name;
        std::vector<Warrior*> nobleArmy;
        bool alive;
    };
}

#endif

