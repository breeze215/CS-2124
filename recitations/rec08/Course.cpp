#include <iostream>
#include <string>
#include "Course.hpp"
#include "Student.hpp"
using namespace std;

namespace BrooklynPoly{
    ostream& operator<<(ostream& os, const Course& rhs){
        os << rhs.name << ":";
        if(rhs.students.size() == 0){
            os << " No Students";
        }
        else{
            for(const Student* currStu : rhs.students){
                os << " " << currStu -> getName();
            }
        }
        os << endl;
        return os;
    }

    Course::Course(const string& courseName) : name(courseName) {}

    const string& Course::getName() const { return name; }

    bool Course::addStudent(Student* currStu){
        if(currStu -> addCourse(this)){
            students.push_back(currStu);
            return true;
        }
        return false;
    }

    void Course::removeStudentsFromCourse(){
        for(Student* currStu : students){
            currStu -> removedFromCourse(this);
        }
       students.clear();
    }
}
