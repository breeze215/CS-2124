/*
  rec05.cpp
 Purpose : Model the basic CS 2124 lab structure.
 Author : Uvindu Salgado
 */
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// class prototype to avoid undefined behaviour in StudentRecords
class Section;

class StudentRecord{
    // ensure that the Section class can access methods of StudentRecords by making it a friend
    friend ostream& operator<<(ostream& os, const Section& randomSection);
public:
    // constructor for the StudentRecord class
    // studentGrades(14, -1) initializes a vector of 14 values with all the values set to -1
    StudentRecord(const string& theStudentName) : studentName(theStudentName), studentGrades(14, -1) {}
    
    // getters and setters
    const string& getStudentName() const { return studentName; }
    void setStudentGrades(int grade, int labNumber){
        // we must use labNumber minus 1 because we started counting from 0 in the vector
        studentGrades[labNumber - 1] = grade;
    }
private:
    string studentName;
    vector<int> studentGrades;
};

class Section{
    // friend function prototype
    friend ostream& operator<<(ostream& os, const Section& randomSection);
public:
    // TimeSlot class embedded in the Section class
    class TimeSlot{
        // ensure that the Section class can access methods of the TimeSlot class by making it a friend
        friend ostream& operator<<(ostream& os, const Section& randomSection);
    public:
        // constructor for the TimeSlot class
        TimeSlot(const string& theDay, int theTime) : day(theDay), timing(theTime) {}
    private:
        // all the private variables of the class TimeSlot
        string day;
        int timing;
    };
    
    // constructor for the Section class
    // vector will initialize to a vector of 14 "-1" values
    Section(const string& theSectionName, const string& sectionDay, int sectionTime) : sectionName(theSectionName), theTiming(sectionDay, sectionTime) {}
    
    // copy constructor for the Section class
    Section(const Section& anotherSection) : sectionName(anotherSection.sectionName), theTiming(anotherSection.theTiming){
        for(size_t index = 0; index < anotherSection.recordsOfGrades.size(); index++){
            recordsOfGrades.emplace_back(new StudentRecord(*anotherSection.recordsOfGrades[index]));
        }
    }
    
    // getters and setters
    vector<StudentRecord*>& getRecordOfGrades() { return recordsOfGrades; }
    void addStudent(const string& studentName){
        recordsOfGrades.emplace_back(new StudentRecord(studentName));
    }
    
    // destructor for the Section class
    ~Section(){
        cout << "Section " << sectionName << " is being deleted" << endl;
        for(StudentRecord* currStudent : recordsOfGrades){
            cout << "Deleting " << currStudent -> getStudentName() << endl;
            delete currStudent;
        }
    }
private:
    // all the private variables of the class Section
    string sectionName;
    TimeSlot theTiming;
    // vector of pointers to StudentRecord because we must be able to modify grades from within the Section class methods
    vector<StudentRecord*> recordsOfGrades;
};

class LabWorker{
    // friend function prototype
    friend ostream& operator<<(ostream& os, const LabWorker& randomWorker);
public:
    // constructor for the LabWorker class
    LabWorker(const string& workerName) : name(workerName), sec(nullptr) {}
    
    //setters
    void addSection(Section& workerSection) { sec = &workerSection; }
    bool addGrade(const string& studentName, int grade, int labNumber){
        // we must check if we can find the student in the recordsOfGrades in the Section class, if not we must return false in order to not fail silently
        for(StudentRecord*& currStudent : sec -> getRecordOfGrades()){
            if(currStudent -> getStudentName() == studentName){
                currStudent -> setStudentGrades(grade, labNumber);
                return true;
            }
        }
        return false;
    }
private:
    // all the private variables of the class LabWorker
    string name;
    Section* sec;
};

// Test code
void doNothing(Section sec) { cout << sec << endl; }

int main() {

    cout << "Test 1: Defining a section\n";
    Section secA2("A2", "Tuesday", 16);
    cout << secA2 << endl;

    cout << "\nTest 2: Adding students to a section\n";
    secA2.addStudent("John");
    secA2.addStudent("George");
    secA2.addStudent("Paul");
    secA2.addStudent("Ringo");
    cout << secA2 << endl;

    cout << "\nTest 3: Defining a lab worker.\n";
    LabWorker moe( "Moe" );
    cout << moe << endl;

    cout << "\nTest 4: Adding a section to a lab worker.\n";
    moe.addSection( secA2 );
    cout << moe << endl;

    cout << "\nTest 5: Adding a second section and lab worker.\n";
    LabWorker jane( "Jane" );
    Section secB3( "B3", "Thursday", 11 );
    secB3.addStudent("Thorin");
    secB3.addStudent("Dwalin");
    secB3.addStudent("Balin");
    secB3.addStudent("Kili");
    secB3.addStudent("Fili");
    secB3.addStudent("Dori");
    secB3.addStudent("Nori");
    secB3.addStudent("Ori");
    secB3.addStudent("Oin");
    secB3.addStudent("Gloin");
    secB3.addStudent("Bifur");
    secB3.addStudent("Bofur");
    secB3.addStudent("Bombur");
    jane.addSection( secB3 );
    cout << jane << endl;

    cout << "\nTest 6: Adding some grades for week one\n";
    moe.addGrade("John", 17, 1);
    moe.addGrade("Paul", 19, 1);
    moe.addGrade("George", 16, 1);
    moe.addGrade("Ringo", 7, 1);
    cout << moe << endl;

    cout << "\nTest 7: Adding some grades for week three (skipping week 2)\n";
    moe.addGrade("John", 15, 3);
    moe.addGrade("Paul", 20, 3);
    moe.addGrade("Ringo", 0, 3);
    moe.addGrade("George", 16, 3);
    cout << moe << endl;

    cout << "\nTest 8: We're done (almost)! \nWhat should happen to all "
         << "those students (or rather their records?)\n";

    cout << "\nTest 9: Oh, IF you have covered copy constructors in lecture, "
         << "then make sure the following call works:\n";
    doNothing(secA2);
    cout << "Back from doNothing\n\n";

} // main

// overloading the operator for LabWorker class
ostream& operator<<(ostream& os, const LabWorker& randomWorker){
    // if randomWorker has nullptr as sec, then he/she is not assigned a section
    if(!randomWorker.sec){
        os << randomWorker.name << " does not have a section" << endl;
    }
    else{
        os << randomWorker.name << " has " << *randomWorker.sec;
    }
    return os;
}

// overloading the operator for Section class
ostream& operator<<(ostream& os, const Section& randomSection){
    os << "Section: " << randomSection.sectionName << ", Time Slot: [Day: " << randomSection.theTiming.day << ", Start time: ";
    // input is in 24 hour time so we must convert to 12 hour clock with the appropriate ending
    if(randomSection.theTiming.timing > 12){
        os << randomSection.theTiming.timing - 12 << "pm], Students: ";
    }
    else{
        os << randomSection.theTiming.timing << "am], Students: ";
    }
    // if there are no students in the section
    if(randomSection.recordsOfGrades.size() == 0){
        os << " None" << endl;
    }
    else{
        os << endl;
        for(StudentRecord* currStudent : randomSection.recordsOfGrades){
            os << "Name: " << currStudent -> studentName << ", Grades:";
            for(int currGrade : currStudent -> studentGrades){
                os << " " << currGrade;
            }
            os << endl;
        }
    }
    return os;
}
