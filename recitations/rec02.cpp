/*
 Name : Uvindu Salgado
 rec02.cpp
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;


struct Hydrocarbon{
    // function to display an induvidual formula
    void display() const{
        cout << "C" << carbonAtoms << "H" << hydrogenAtoms;
        for (const string& name : names){
            cout << " " << name;
        }
        cout << endl;
    }
    
    // function to add name of hydrocarbon to the names vector
    void addName(const string& name){
        names.push_back(name);
    }
    
    // functions to get number of carbon and hydrogen atoms in hydrocarbon
    int getNumOfC() const{
        return carbonAtoms;
    }
    
    int getNumOfH() const{
        return hydrogenAtoms;
    }
    
    int carbonAtoms;
    int hydrogenAtoms;
    vector<string> names;
};

// function prototypes here
void openFile(ifstream& hydroCarbonStream);
void displayHydroCarbonVector(const vector<Hydrocarbon>& hydroCarbonVector);
size_t checkNameInVector(vector<Hydrocarbon>& hydroCarbonVector, const string& name, const int& carbonAtoms, const int& hydrogenAtoms);
void fillHydroCarbonVector(vector<Hydrocarbon>& hydroCarbonVector, ifstream& hydroCarbonStream);
void swapHydroCarbons(vector<Hydrocarbon>& hydroCarbonVector, int indexOne, int indexTwo);
void sortHydroCarbonVector(vector<Hydrocarbon>& hydroCarbonVector);

int main() {
    // opening the file
    ifstream hydroCarbonStream;
    openFile(hydroCarbonStream);
    
    // filling the hydroCarbonVector and closing the file
    vector<Hydrocarbon> hydroCarbonVector;
    fillHydroCarbonVector(hydroCarbonVector, hydroCarbonStream);
    hydroCarbonStream.close();
    
    // displaying the unsorted hydroCarbonVector, sorting the hydroCarbonVector and then displaying it
    cout << endl;
    cout << "Unsorted: " << endl;
    displayHydroCarbonVector(hydroCarbonVector);
    cout << endl;
    cout << "Sorted: " << endl;
    sortHydroCarbonVector(hydroCarbonVector);
    displayHydroCarbonVector(hydroCarbonVector);
    return 0;
}

// function to open the file
void openFile(ifstream& hydroCarbonStream){
    do{
        string nameOfFile;
        cout << "Input the file name: ";
        cin >> nameOfFile;
        hydroCarbonStream.open(nameOfFile);
    } while(!hydroCarbonStream);
}

// function to display the hydrocarbon vector
void displayHydroCarbonVector(const vector<Hydrocarbon>& hydroCarbonVector){
    for(const Hydrocarbon& currentHydroCarbonStruct : hydroCarbonVector){
        currentHydroCarbonStruct.display();
    }
}

// function to check if the formula for the hydrocarbon was already mentioned previously
size_t checkNameInVector(vector<Hydrocarbon>& hydroCarbonVector, const string& name, const int& carbonAtoms, const int& hydrogenAtoms){
    for (size_t index = 0; index < hydroCarbonVector.size(); index++){
        if (hydroCarbonVector[index].getNumOfC() == carbonAtoms && hydroCarbonVector[index].getNumOfH() == hydrogenAtoms){
            hydroCarbonVector[index].addName(name);
            return index;
        }
    }
    return hydroCarbonVector.size();
}

// function to fill the hydrocarbon vector with the hydrocarbon formulas
void fillHydroCarbonVector(vector<Hydrocarbon>& hydroCarbonVector, ifstream& hydroCarbonStream){
    string name;
    int hydrogen, carbon;
    char whitespace;
    while (hydroCarbonStream >> name >> whitespace >> carbon >> whitespace >> hydrogen){
        // check if this formula was previously read in
        if (checkNameInVector(hydroCarbonVector, name, carbon, hydrogen) == hydroCarbonVector.size()){
            Hydrocarbon newHydroCarbon{carbon, hydrogen};
            newHydroCarbon.addName(name);
            hydroCarbonVector.push_back(newHydroCarbon);
        }
    }
}

// function to swap the positions of hydrocarbons in the hydroCarbonVector, this will make our insertion sort easier to write
void swapHydroCarbons(vector<Hydrocarbon>& hydroCarbonVector, int indexOne, int indexTwo){
    Hydrocarbon tempHydroCarbonHolder = hydroCarbonVector[indexOne];
    hydroCarbonVector[indexOne] = hydroCarbonVector[indexTwo];
    hydroCarbonVector[indexTwo] = tempHydroCarbonHolder;
}

// function to sort the hydroCarbonVector in place using insertion sort
void sortHydroCarbonVector(vector<Hydrocarbon>& hydroCarbonVector){
    for(size_t indexOne = 1; indexOne < hydroCarbonVector.size(); indexOne++){
        for(size_t indexTwo = indexOne; indexTwo > 0; indexTwo--){
            if(hydroCarbonVector[indexTwo - 1].getNumOfC() > hydroCarbonVector[indexTwo].getNumOfC()){
                swapHydroCarbons(hydroCarbonVector, indexTwo, indexTwo - 1);
            }
            else if(hydroCarbonVector[indexTwo - 1].getNumOfC() == hydroCarbonVector[indexTwo].getNumOfC()){
                if(hydroCarbonVector[indexTwo - 1].getNumOfH() > hydroCarbonVector[indexTwo].getNumOfH()){
                    swapHydroCarbons(hydroCarbonVector, indexTwo, indexTwo - 1);
                }
                else{
                    break;
                }
            }
            else{
                break;
            }
        }
    }
}
