/*
  hw04.cpp
  Author : Uvindu Salgado
  Purpose : Simulating battles between Nobles using their army of warriors.
 */

#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Warrior{
    // prototype for the friend function of the the Warrior class
    friend ostream& operator<<(ostream& os, const Warrior& randomWarrior);
public:
    // initialization list for the Warrior class
    Warrior(const string& theName, int theStrength) : name(theName), strength(theStrength), hired(false) {}
    
    // all the getters and setters for the Warrior class
    const string& getName() const { return name; }
    double getStrength() const { return strength; }
    void setStrength(double newStrength) { strength = newStrength; }
    bool getHired() const { return hired; }
    void setHired() { hired = !hired; }
private:
    // all the private variables of the Warrior class
    string name;
    double strength;
    bool hired;
};

class Noble{
    // prototype for the friend function  of the Noble class
    friend ostream& operator<<(ostream& os, const Noble& randomNoble);
public:
    // initialization list
    Noble(const string& nobleName) : name(nobleName), nobleArmy(), alive(true) {}
    
    // adding up the strength of all the warriors that a part of the noble's army and return this value
    double totalArmyStrength() const{
        double totalStrength = 0;
        for(const Warrior* const& currWarrior : nobleArmy){
            totalStrength += currWarrior -> getStrength();
        }
        return totalStrength;
    }
    
    // update the strength of each warrior after battle if the army strength's are different and non zero.
    // The way this is done is by multiplying each warrior strength by the ratio of the army strength's.
    void updateNobleArmyStrength(double winner, double loser){
        for(Warrior* const& currWarrior : nobleArmy){
            double newStrength = (currWarrior -> getStrength()) * ((winner - loser) / winner);
            currWarrior -> setStrength(newStrength);
        }
    }
    
    bool getStatus() const { return alive; }
    const string& getNobleName() const { return name; }
    
    // set all warrior strength's to 0 and set alive to false
    void die(){
        alive = false;
        for(Warrior* const& currWarrior : nobleArmy) { currWarrior -> setStrength(0); }
    }
    
    // function to hire a warrior
    bool hire(Warrior& someWarrior){
        if(!getStatus() || someWarrior.getHired()){
            // fail if noble is dead or warrior is already hired
            cout << getNobleName() << " failed to hire " << someWarrior.getName() << endl;
            return false;
        }
        else{
            someWarrior.setHired();
            nobleArmy.push_back(&someWarrior);
            return true;
        }
    }
    
    // function to fire a warrior
    bool fire(Warrior& someWarrior){
        if(!getStatus()){
            // fail to fire a warrior if the noble is dead
            cout << getNobleName() << " has failed to fire " << someWarrior.getName() << endl;
            return false;
        }
        bool fired = false;
        for(size_t index = 0; index < nobleArmy.size(); index++ ){
            if(fired == false){
                if(nobleArmy[index] == &someWarrior){
                    cout << someWarrior.getName() << ", you don't work for me anymore! -- " << getNobleName() << "." << endl;
                    someWarrior.setHired();
                    fired = true;
                }
            }
            else{
                // if the warrior is fired then shift every warrior after that one to the left and pop the last repeated warrior at the end
                nobleArmy[index - 1] = nobleArmy[index];
            }
        }
        if(fired){
            // removing the warrior that is repeated at the end after our loop, if a warrior is fired
            nobleArmy.pop_back();
        }
        else{
            cout << getNobleName() << " failed to fire " << someWarrior.getName() << endl;
        }
        return fired;
    }
    
    // battle function is now a part of the Noble class instead of the Warrior class
    void battle(Noble& enemy){
        cout << getNobleName() << " battles " << enemy.getNobleName() << endl;
        if(!getStatus() && !enemy.getStatus()){
            cout << "Oh, NO! They're both dead! Yuck!" << endl;
        }
        else if(!getStatus() && enemy.getStatus()){
            cout << "He's dead, " << enemy.getNobleName() << endl;
        }
        else if(getStatus() && !enemy.getStatus()){
            cout << "He's dead, " << name << endl;
        }
        else{
            double myStrength = totalArmyStrength();
            double enemyStrength = enemy.totalArmyStrength();
            if(myStrength == enemyStrength){
                die();
                enemy.die();
                cout << "Mutual Annihilation: " << getNobleName() << " and " << enemy.getNobleName() << " die at each other's hands" << endl;
            }
            else if(myStrength > enemyStrength){
                enemy.die();
                updateNobleArmyStrength(myStrength, enemyStrength);
                cout << getNobleName() << " defeats " << enemy.getNobleName() << endl;
            }
            else{ // enemyStrength > myStrength
                die();
                enemy.updateNobleArmyStrength(enemyStrength, myStrength);
                cout << enemy.getNobleName() << " defeats " << getNobleName() << endl;
            }
        }
    }
    
private:
    // all the private variables of the Noble class
    string name;
    vector<Warrior*> nobleArmy;
    bool alive;
};

int main() {
    // test code provided
    Noble art("King Arthur");
    Noble lance("Lancelot du Lac");
    Noble jim("Jim");
    Noble linus("Linus Torvalds");
    Noble billie("Bill Gates");
    
    Warrior cheetah("Tarzan", 10);
    Warrior wizard("Merlin", 15);
    Warrior theGovernator("Conan", 12);
    Warrior nimoy("Spock", 15);
    Warrior lawless("Xena", 20);
    Warrior mrGreen("Hulk", 8);
    Warrior dylan("Hercules", 3);
    
    jim.hire(nimoy);
    lance.hire(theGovernator);
    art.hire(wizard);
    lance.hire(dylan);
    linus.hire(lawless);
    billie.hire(mrGreen);
    art.hire(cheetah);
    art.hire(nimoy);
    
    cout << "==========\n\n"
         << "Status before all battles, etc.\n";
    cout << jim << endl;
    cout << lance << endl;
    cout << art << endl;
    cout << linus << endl;
    cout << billie << endl;
    cout << "==========\n\n";
    
    art.fire(cheetah);
    cout << art << endl;

    lance.fire(nimoy);
    cout << lance << endl;
    cout << "==========\n\n";

    art.battle(lance);
    jim.battle(lance);
    linus.battle(billie);
    billie.battle(lance);

    cout << "==========\n\n"
         << "Status after all battles, etc.\n";
    cout << jim << endl;
    cout << lance << endl;
    cout << art << endl;
    cout << linus << endl;
    cout << billie << endl;
    cout << "==========\n";
    
}

// overloading the operator for Warrior
ostream& operator<<(ostream& os, const Warrior& randomWarrior){
    os << "        " << randomWarrior.name <<  ": " << randomWarrior.strength;
    return os;
}

// overloading the operator for Noble
ostream& operator<<(ostream& os, const Noble& randomNoble){
    os << randomNoble.name << " has an army of " << randomNoble.nobleArmy.size() << endl;
    for(const Warrior* const& currWarrior : randomNoble.nobleArmy){
        if(currWarrior){
            os << *currWarrior << endl;
        }
    }
    return os;
}
