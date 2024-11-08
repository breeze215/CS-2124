/*
  rec10.cpp
  Name : Uvindu Salgado
 */

#include <iostream>
#include <vector>
using namespace std;

class Instrument{
public:
    virtual void makeSound() const { cout << "To make a sound... ";}
    virtual void MillOut(ostream& os) const = 0;
    virtual void play() = 0;
};

class Percussion : public Instrument{
public:
    using Instrument::Instrument;
    void makeSound() const override{
        Instrument::makeSound();
        cout << "hit me!" << endl;
    }
};

class Drum : public Percussion{
    using Percussion::Percussion;
    void MillOut(ostream& os) const override{
        os << "Drum" << endl;
    }
    void play() override { cout << "Boom"; }
};

class Cymbal : public Percussion{
    using Percussion::Percussion;
    void MillOut(ostream& os) const override{
        os << "Cymbal" << endl;
    }
    void play() override { cout << "Crash"; }
};

class Brass : public Instrument{
public:
    Brass(int mouthpiece) : mouthpiece(mouthpiece) {}
    void makeSound() const override{
        Instrument::makeSound();
        cout << "blow on a mouthpiece of size " << mouthpiece << endl;
    }
    int getM() const { return mouthpiece; }
private:
    int mouthpiece;
};

class Trombone : public Brass{
    using Brass::Brass;
    void MillOut(ostream& os) const override{
        os << "Trombone: " << Brass::getM() << endl;
    }
    void play() override { cout << "Blat"; }
};

class Trumpet : public Brass{
    using Brass::Brass;
    void MillOut(ostream& os) const override{
        os << "Trumpet: " << Brass::getM() << endl;
    }
    void play() override { cout << "Toot"; }
};

class String : public Instrument{
public:
    String(int pitch) : pitch(pitch) {}
    void makeSound() const override{
        Instrument::makeSound();
        cout << "bow a string with pitch " << pitch << endl;
    }
    int getP() const { return pitch; }
private:
    int pitch;
};

class Cello : public String{
    using String::String;
    void MillOut(ostream& os) const override{
        os << "Cello: " << String::getP() << endl;
    }
    void play() override { cout << "Squawk"; }
};

class Violin : public String{
    using String::String;
    void MillOut(ostream& os) const override{
        os << "Violin: " << String::getP() << endl;
    }
    void play() override { cout << "Screech"; }
};

class MILL{
    friend ostream& operator<<(ostream& os, const MILL& rhs){
        os << "The MILL has the following instruments: ";
        int out = 0;
        for(Instrument* instrP : rhs.inventory){
            if(instrP == nullptr){ out++; }
        }
        if(out == rhs.inventory.size()) {
            os << "None" << endl;
            return os;
        }
        os << endl;
        for(Instrument* instrP : rhs.inventory){
            if(instrP != nullptr){
                os << "    ";
                instrP -> MillOut(os);
            }
        }
        return os;
    }
public:
    void receiveInstr(Instrument& instr){
        instr.makeSound();
        for(Instrument*& instrP : inventory){
            if(instrP == nullptr){
                instrP = &instr;
                return;
            }
        }
        inventory.push_back(&instr);
    }
    
    void dailyTestPlay() const{
        for(Instrument* instrP : inventory){
            if(instrP != nullptr){
                instrP->makeSound();
            }
        }
    }
    
    Instrument* loanOut(){
        for(Instrument*& instrP : inventory){
            if(instrP != nullptr){
                Instrument* instrT = instrP;
                instrP = nullptr;
                return instrT;
            }
        }
        return nullptr;
    }
private:
    vector<Instrument*> inventory;
};
//
// Musician class as provided to the students. Requires an Instrument class.
//

class Musician {
public:
    Musician(const string& name) : instr(nullptr), name(name) {}

    // acceptInstr takes in an instrument for the Musician to later play.
    //  "loses" any instrument that it used to have.
    void acceptInstr(Instrument* instPtr) { instr = instPtr; }

    // giveBackInstr: gives the instrument that the Musicial was holding "back"
    Instrument* giveBackInstr() {
        Instrument* result(instr);
        instr = nullptr;
        return result;
    }

    // testPlay: testing out my instrument
    void testPlay() const {
        if (instr) instr->makeSound();
        else cerr << name << " has no instr\n";
    }

    // play: play the instrument

    //   Not making it const so that Instrument::play method does not
    //   need to be const. Allows the instrument to be modifed in the
    //   process of being played.
    void play() {
        if (instr) instr->play();
        //Don't do anything if we don't have an instrument.
    }
private:
    Instrument* instr;
    string name;
};

class Orch{
public:
    void addPlayer(Musician& member) { members.push_back(&member); }
    
    void play() const{
        for(Musician* memberP : members){
            memberP -> play();
        }
        cout << endl;
    }
private:
    vector<Musician*> members;
};

int main() {

    //
    // PART ONE
    //
    cout << "P A R T  O N E\n";

    cout << "Define some instruments ---------------------------------------\n";
    Drum drum;
    Cello cello(673);
    Cymbal cymbal;
    Trombone tbone(4);
    Trumpet trpt(12) ;
    Violin violin(567) ;
  
    cout << "Define the MILL -----------------------------------------------\n";
    MILL mill;
    cout << "The MILL before adding instruments:\n" << mill << "\n\n";

    cout << "Put the instruments into the MILL -----------------------------\n";
    mill.receiveInstr(trpt);
    mill.receiveInstr(violin);
    mill.receiveInstr(tbone);
    mill.receiveInstr(drum);
    mill.receiveInstr(cello);
    mill.receiveInstr(cymbal);
    cout << "\nThe MILL after adding some instruments:\n" << mill << "\n\n";
  
    cout << "Daily test ----------------------------------------------------\n"
     << "dailyTestPlay()" << endl;
    mill.dailyTestPlay();
    cout << endl;
  
    cout << "Define some Musicians------------------------------------------\n";
    Musician harpo("Harpo");
    Musician groucho("Groucho");
      
    cout << "TESTING: groucho.acceptInstr(mill.loanOut());---------------\n";
    groucho.testPlay();     // Groucho doesn't have an instrument yet.

    groucho.acceptInstr(mill.loanOut());
    groucho.testPlay();

    cout << "\ndailyTestPlay()" << endl;
    mill.dailyTestPlay();
    cout << endl;
  
    groucho.testPlay();
    mill.receiveInstr(*groucho.giveBackInstr());
    harpo.acceptInstr(mill.loanOut());
    groucho.acceptInstr(mill.loanOut());
    groucho.testPlay();
    harpo.testPlay();

    cout << "\ndailyTestPlay()" << endl;
    mill.dailyTestPlay();

    cout << "\nThe MILL after giving out some instruments:\n";
    cout << mill << "\n\n";

    cout << "TESTING: mill.receiveInstr(*groucho.giveBackInstr()); ------\n";
    mill.receiveInstr(*groucho.giveBackInstr());

    cout << "TESTING: mill.receiveInstr(*harpo.giveBackInstr()); ------\n";
    mill.receiveInstr(*harpo.giveBackInstr());
    cout << endl;

    cout << "dailyTestPlay()" << endl;
    mill.dailyTestPlay();
  
    cout << "\nThe MILL at the end of Part One:\n";
    cout << mill << endl;

    //
    // PART TWO
    //
    
    cout << "\nP A R T  T W O\n";
    
    Musician bob("Bob");
    Musician sue("Sue");
    Musician mary("Mary");
    Musician ralph("Ralph");
    Musician jody("Judy");
    Musician morgan("Morgan");

    Orch orch;

    // THE SCENARIO

    //Bob joins the orchestra without an instrument.
    orch.addPlayer(bob);

    //The orchestra performs
    cout << "orch performs\n";
    orch.play();

    //Sue gets an instrument from the MIL2 and joins the orchestra.
    sue.acceptInstr(mill.loanOut());
    orch.addPlayer(sue);

    //Ralph gets an instrument from the MIL2.
    ralph.acceptInstr(mill.loanOut());

    //Mary gets an instrument from the MIL2 and joins the orchestra.
    mary.acceptInstr(mill.loanOut());
    orch.addPlayer(mary);

    //Ralph returns his instrument to the MIL2.
    mill.receiveInstr(*ralph.giveBackInstr());

    //Jody gets an instrument from the MIL2 and joins the orchestra.
    jody.acceptInstr(mill.loanOut());
    orch.addPlayer(jody);

    // morgan gets an instrument from the MIL2
    morgan.acceptInstr(mill.loanOut());

    //The orchestra performs.
    cout << "orch performs\n";
    orch.play();

    //Ralph joins the orchestra.
    orch.addPlayer(ralph);

    //The orchestra performs.
    cout << "orch performs\n";
    orch.play();
    
    // bob gets an instrument from the MIL2
    bob.acceptInstr(mill.loanOut());

    // ralph gets an instrument from the MIL2
    ralph.acceptInstr(mill.loanOut());

    //The orchestra performs.
    cout << "orch performs\n";
    orch.play();

    //Morgan joins the orchestra.
    orch.addPlayer(morgan);

    //The orchestra performs.
    cout << "orch performs\n";
    orch.play();

    cout << endl << mill << endl;
     
}
