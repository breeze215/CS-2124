/*
 hw07-single.cpp
 Author : Uvindu Salgado
 Purpose : cyclic association
*/

#include <fstream>
#include <iostream>
#include <vector>
#include <string>
using namespace std;

//forward declaration
class Noble;

class Warrior{
   // prototype for the friend function of the the Warrior class
   friend ostream& operator<<(ostream& os, const Warrior& randomWarrior);
public:
   // initialization list for the Warrior class
    Warrior(const string& theName, int theStrength);
   
   // all the getters and setters for the Warrior class
    const string& getName() const;
    double getStrength() const;
    void setStrength(double newStrength);
    bool isHired() const;
    void setHired(bool status);
    void setCommander(Noble* command);
    // new runaway method
    bool runaway();
private:
   // all the private variables of the Warrior class
   string name;
   double strength;
   bool hired;
   Noble* commander;
};

class Noble{
   // prototype for the friend function  of the Noble class
   friend ostream& operator<<(ostream& os, const Noble& randomNoble);
public:
   // initialization list
    Noble(const string& nobleName);
   
   // adding up the strength of all the warriors that a part of the noble's army and return this value
    double totalArmyStrength() const;
    
    // function to get the number of warriors employed by the noble
    size_t getNobleArmySize() const;

   // update the strength of each warrior after battle if the army strength's are different and non zero.
   // The way this is done is by multiplying each warrior strength by the ratio of the army strength's.
    void updateNobleArmyStrength(double winner, double loser);
   
    // getters
    vector<Warrior*>& getNobleArmy();
    const string& getNobleName() const;
   
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
   string name;
   vector<Warrior*> nobleArmy;
   bool alive;
};

//function prototype
void displayStatus(vector<Warrior*>& warriors, vector<Noble*>& nobles);

int main() {
    Noble art("King Arthur");
    Noble lance("Lancelot du Lac");
    Noble jim("Jim");
    Noble linus("Linus Torvalds");
    Noble billie("Bill Gates");

    Warrior cheetah("Tarzan", 4);
    Warrior sky("Leia", 6);
    Warrior wizard("Merlin", 9);
    Warrior jaffa("Teal'c", 9);
    Warrior theGovernator("Conan", 12);
    Warrior nimoy("Spock", 15);
    Warrior lawless("Xena", 20);
    Warrior mrGreen("Hulk", 8);
    Warrior dylan("Hercules", 3);

    jim.hire(nimoy);
    lance.hire(theGovernator);
    art.hire(jaffa);
    art.hire(cheetah);
    art.hire(wizard);
    art.hire(sky);
    lance.hire(dylan);
    linus.hire(lawless);
    billie.hire(mrGreen);
    art.hire(nimoy);

    cout << "================ Initial Status ===============" << endl;
    cout << art << endl
     << lance << endl
     << jim << endl
     << linus << endl
     << billie << endl;
    cout << "===============================================\n\n";

    art.fire(cheetah);
    wizard.runaway();
    cout << endl << art << endl;

    art.battle(lance);
    jim.battle(lance);
    linus.battle(billie);
    billie.battle(lance);

    cout << "\n================ Final Status ===============" << endl;
    cout << art << endl
     << lance << endl
     << jim << endl
     << linus << endl
     << billie << endl;

    // Tarzan and Merlin should be unemployed
    cout << "Tarzan's Hire Status: " << boolalpha
     << cheetah.isHired() << endl;
    cout << "Merlin's Hire Status: " << boolalpha
     << wizard.isHired() << endl;
    cout << "===============================================\n\n";
}

// all the Warrior class methods
// overloading the operator for Warrior
ostream& operator<<(ostream& os, const Warrior& randomWarrior){
   os << "        " << randomWarrior.name <<  ": " << randomWarrior.strength;
   return os;
}

Warrior::Warrior(const string& theName, int theStrength) : name(theName), strength(theStrength), hired(false), commander(nullptr) {}

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

//all the Noble class methods
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
            // if the warrior is found then shift every warrior after that one to the left and pop the last repeated warrior at the end
            nobleArmy[index - 1] = nobleArmy[index];
        }
    }
    if(found){
        // removing the warrior that is repeated at the end after our loop, if a warrior is found
        nobleArmy.pop_back();
    }
    return found;
}
