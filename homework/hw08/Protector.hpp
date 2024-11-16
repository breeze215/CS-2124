/*
 Author: Uvindu Salgado
 Purpose: Seperate compilation for hw08
 */

#ifndef PROTECTOR_HPP
#define PROTECTOR_HPP

#include <fstream>
#include <iostream>
#include <string>

namespace WarriorCraft{
    class Lord;
        
    class Protector{
        //output operator
        friend std::ostream& operator<<(std::ostream& os, const Protector& rhs);
    public:
        //constructor
        Protector(const std::string& theName, int theStrength);
        
        // getters and setters
        const std::string& getName() const;
        double getStrength() const;
        void setStrength(double theStrength);
        void setLord(Lord* noblePtr);
        Lord* getLord() const;

        // method to allow the Protector to runaway
        bool runaway();
        
        // pure virtual methods
        virtual void defend() const = 0;
    private:
        std::string name;
        double strength;
        Lord* lord;
    };
    
    class Warrior : public Protector{
    public:
        using Protector::Protector;
        void defend() const override;
    };

    class Wizard : public Protector{
    public:
        using Protector::Protector;
        void defend() const override;
    };

    class Archer : public Warrior{
    public:
        using Warrior::Warrior;
        void defend() const override;
    };

    class Swordsman : public Warrior{
    public:
        using Warrior::Warrior;
        void defend() const override;
    };
}

#endif
