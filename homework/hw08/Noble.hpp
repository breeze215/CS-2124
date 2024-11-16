/*
 Author: Uvindu Salgado
 Purpose: Seperate compilation for hw08
 */

#ifndef NOBLE_HPP
#define NOBLE_HPP

#include <iostream>
#include <vector>
#include <string>

namespace WarriorCraft{
    class Protector;
    
    // Noble class in the header file
    class Noble{
    public:
        //constructor
        Noble(const std::string& theName);
        
        //all the getters and setters
        const std::string& getName() const;
        
        //battle method between Noble's
        void battle(Noble& enemy);
        
        // all the pure virtual methods
        virtual double getStrength() const = 0;
        // if it is a Lord, update the strength of every protector under it
        // else, update the instance's strength itself
        virtual void updateStrength(double winnerStrength, double loserStrength) = 0;
        // if lord, call method for every protector under it
        // else, output "Ugh!"
        virtual void defend() const = 0;
        // function to set the strength to 0 and change alive status
        virtual void die() = 0;
    protected:
        void changeAliveStatus();
        bool getAliveStatus() const;
    private:
        std::string name;
        bool alive;
    };

    class Lord : public Noble{
        //output operator
        friend std::ostream& operator<<(std::ostream& os, const Lord& rhs);
    public:
        //constructor
        Lord(const std::string& theName);
        
        double getStrength() const override;
        //multiply strength of every protector by a ratio
        void updateStrength(double winnerStrength, double loserStrength) override;
        //call the method on all the protectors of the lord instance
        void defend() const override;
        //methods to hire and fire a protector
        bool hires(Protector& someProtector);
        bool fires(Protector& someProtector);
        //method to remove a protector
        bool remove(Protector& someProtector);
        void die() override;
    private:
        std::vector<Protector*> army;
    };

    class PersonWithStrengthToFight : public Noble{
        //output operator
        friend std::ostream& operator<<(std::ostream& os, const PersonWithStrengthToFight& rhs);
    public:
        //constructor
        PersonWithStrengthToFight(const std::string& theName, int theStrength);
        
        double getStrength() const override;
        //update strength of the instance itself
        void updateStrength(double winnerStrength, double loserStrength) override;
        //output "Ugh!"
        void defend() const override;
        void die() override;
    private:
        double strength;
    };
}

#endif
