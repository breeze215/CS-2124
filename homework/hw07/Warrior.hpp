/*
 Author: Uvindu Salgado
 Purpose: Seperate compilation for hw07
 */

#ifndef WARRIOR_HPP
#define WARRIOR_HPP

#include <iostream>
#include <vector>
#include <string>

namespace WarriorCraft{
    class Noble;
    class Warrior{
        // prototype for the friend function of the the Warrior class
        friend std::ostream& operator<<(std::ostream& os, const Warrior& randomWarrior);
    public:
        // initialization list for the Warrior class
        Warrior(const std::string& theName, int theStrength);
           
        // all the getters and setters for the Warrior class
        const std::string& getName() const;
        double getStrength() const;
        void setStrength(double newStrength);
        bool isHired() const;
        void setHired(bool status);
        void setCommander(Noble* command);
        // new runaway method
        bool runaway();
    private:
        // all the private variables of the Warrior class
        std::string name;
        double strength;
        bool hired;
        Noble* commander;
    };
}

#endif
