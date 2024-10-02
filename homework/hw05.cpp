/*
 hw05.cpp
 Author : Uvindu Salgado
 Purpose : Simulating battles between Nobles using their army of warriors but using the heap this time.
*/

#include <fstream>
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
    
    // function to get the number of warriors employed by the noble
    size_t getNobleArmySize() const { return nobleArmy.size(); }

   // update the strength of each warrior after battle if the army strength's are different and non zero.
   // The way this is done is by multiplying each warrior strength by the ratio of the army strength's.
   void updateNobleArmyStrength(double winner, double loser){
       for(Warrior* const& currWarrior : nobleArmy){
           double newStrength = (currWarrior -> getStrength()) * ((winner - loser) / winner);
           currWarrior -> setStrength(newStrength);
       }
   }
   
    //getters
   bool getStatus() const { return alive; }
   const string& getNobleName() const { return name; }
   
   // set all warrior strength's to 0 and set alive to false
   void die(){
       alive = false;
       for(Warrior* const& currWarrior : nobleArmy) { currWarrior -> setStrength(0); }
   }
   
   // function to hire a warrior
   const bool hire(Warrior& someWarrior){
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
   const bool fire(Warrior& someWarrior){
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

//function prototypes
void openFile(ifstream& nobleWarriorsStream);
Warrior* checkWarriorName(const string& name, const vector<Warrior*>& warriors);
Noble* checkNobleName(const string& name, const vector<Noble*>& nobles);
void deletePointers(vector <Warrior*>& warriors, vector<Noble*>& nobles);
void displayStatus(vector<Warrior*>& warriors, vector<Noble*>& nobles);

int main() {
    //opening the file using our function
    ifstream nobleWarriorStream;
    openFile(nobleWarriorStream);
    
    string command;
    vector<Warrior*> warriors;
    vector<Noble*> nobles;
    
    //read the file, identify the command and take the appropriate actions based on the command word
    while(nobleWarriorStream >> command){
        if(command == "Noble"){
            string name;
            nobleWarriorStream >> name;
            if(checkNobleName(name, nobles)){ //checking if a noble with this name already exists
                cout << "Noble " << name << " already exists. Cannot recreate!" << endl;
            }
            else{
                nobles.emplace_back(new Noble(name));
            }
        }
        else if(command == "Warrior"){
            string name;
            int strength;
            nobleWarriorStream >> name >> strength;
            if(checkWarriorName(name, warriors)){ //checking if a warrior with this name already exists
                cout << "Warrior " << name << " already exists. Cannot recreate!" << endl;
            }
            else{
                warriors.emplace_back(new Warrior(name, strength));
            }
        }
        else if(command == "Status"){
            displayStatus(warriors, nobles);
        }
        else if(command == "Fire"){
            string noble, warrior;
            nobleWarriorStream >> noble >> warrior;
            Noble* noblePointer;
            Warrior* warriorPointer;
            // we must check if both the noble and warrior exist before firing
            noblePointer = checkNobleName(noble, nobles);
            warriorPointer = checkWarriorName(warrior, warriors);
            if(noblePointer && warriorPointer){
                noblePointer -> fire(*warriorPointer);
            }
            else{
                if(!noblePointer){
                    cout << "Attempting to fire using unknown noble: " << noble << endl;
                }
                else if(!warriorPointer){
                    cout << "Attempting to fire using unknown warrior: " << warrior << endl;
                }
                else{ // !noblePointer && !warriorPointer
                    cout << "Attempting to fire using unknown warrior: " << warrior << " and attempting to fire using unknown noble: " << noble << endl;
                }
            }
        }
        else if(command == "Hire"){
            string noble, warrior;
            nobleWarriorStream >> noble >> warrior;
            Noble* noblePointer;
            Warrior* warriorPointer;
            // we must check if both the noble and warrior exist before hiring
            noblePointer = checkNobleName(noble, nobles);
            warriorPointer = checkWarriorName(warrior, warriors);
            if(noblePointer && warriorPointer){
                noblePointer -> hire(*warriorPointer);
            }
            else{
                if(!noblePointer){
                    cout << "Attempting to hire using unknown noble: " << noble << endl;
                }
                else if(!warriorPointer){
                    cout << "Attempting to hire using unknown warrior: " << warrior << endl;
                }
                else{ // !noblePointer && !warriorPointer
                    cout << "Attempting to hire using unknown warrior: " << warrior << " and attempting to hire using unknown noble: " << noble << endl;
                }
            }
        }
        else if(command == "Battle"){
            string nobleOne, nobleTwo;
            nobleWarriorStream >> nobleOne >> nobleTwo;
            Noble* nobleOnePointer;
            Noble* nobleTwoPointer;
            nobleOnePointer = checkNobleName(nobleOne, nobles);
            nobleTwoPointer = checkNobleName(nobleTwo, nobles);
            if(nobleOnePointer && nobleTwoPointer){
                nobleOnePointer -> battle(*nobleTwoPointer);
            }
            else{
                if(!nobleOnePointer){
                    cout << "Attempting to battle using unknown noble: " << nobleOne << endl;
                }
                else if(nobleTwoPointer){
                    cout << "Attempting to battle using unknown noble: " << nobleTwo << endl;
                }
                else{ // !nobleOnePointer && !nobleTwoPointer
                    cout << "Attempting to battle using unknown nobles: " << nobleOne << ", " << nobleTwo << endl;
                }
            }
        }
        else{
            //we free up space on the heap and delete dangling pointers
            deletePointers(warriors, nobles);
            warriors.clear();
            nobles.clear();
        }
    }
    //closing the stream and deleting pointers to the heap as well as deleting dangling pointers
    nobleWarriorStream.close();
    deletePointers(warriors, nobles);
    warriors.clear();
    nobles.clear();
}

//function to open the file and return an error if it does not open
void openFile(ifstream& nobleWarriorsStream){
    nobleWarriorsStream.clear();
    nobleWarriorsStream.open("nobleWarriors.txt");
    if(!nobleWarriorsStream){
        cerr << "Failed to open the file nobleWarriors.txt";
        exit(1);
    }
}

//function to check if a warrior with the same name as the name passed into the function exists
Warrior* checkWarriorName(const string& name, const vector<Warrior*>& warriors){
    for(Warrior* const currWarrior : warriors){
        if(currWarrior -> getName() == name){
            return currWarrior;
        }
    }
    return nullptr;
}

//function to check if a noble with the same name as the name passed into the function exists
Noble* checkNobleName(const string& name, const vector<Noble*>& nobles){
    for(Noble* const currNoble : nobles){
        if(currNoble -> getNobleName() == name){
            return currNoble;
        }
    }
    return nullptr;
}


//function to free up spaces by iterating through the vectors of pointers that point to adresses on the heap and to delete any dangling pointers
void deletePointers(vector <Warrior*>& warriors, vector<Noble*>& nobles){
    for(Warrior* currWarrior : warriors){
        delete currWarrior;
    }
    for(Noble* currNoble : nobles){
        delete currNoble;
    }
}

//function to display the status in the output
void displayStatus(vector<Warrior*>& warriors, vector<Noble*>& nobles){
    cout << "Status" << endl << "=====" << endl << "Nobles:" << endl;
    int hiredWarriors = 0;
    if(nobles.size() > 0){
        for(const Noble* const& currNoble : nobles){
            cout << *currNoble;
            hiredWarriors += currNoble -> getNobleArmySize();
        }
    }
    else{ //if there are no pointers in the nobles vector
        cout << "NONE" << endl;
    }
    cout << endl;
    cout << "Unemployed warriors:" << endl;
    // checking whether the nobleArmy vector has any pointers and if it does, checking whether all the warriors are hire
    if(warriors.size() - hiredWarriors > 0){
        for(const Warrior* const& currWarrior : warriors){
            if(!currWarrior -> getHired()){
                cout << *currWarrior << endl;
            }
        }
    }
    else{
        cout << "NONE" << endl;
    }
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
