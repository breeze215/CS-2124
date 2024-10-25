#include "Student.hpp"
#include "Course.hpp"
using namespace std;

namespace BrooklynPoly{
    ostream& operator<<(ostream& os, const Student& rhs){
        os << rhs.name << ":";
        if(rhs.courses.size() == 0){
            os << " No Courses";
        }
        else{
            for(const Course* currC : rhs.courses){
                os << " " << currC -> getName();
            }
        }
        os << endl;
        return os;
    }

    Student::Student(const string& nameT) : name(nameT) {}

    const string& Student::getName() const { return name; }

    bool Student::addCourse(Course* currC){
        for(const Course* currCo : courses){
            if(currCo == currC){
            return false;
            }
        }
        courses.push_back(currC);
        return true;
    }

    void Student::removedFromCourse(Course* currC){
        size_t index;
        for(index = 0; index < courses.size(); index++){
            if(courses[index] == currC){
                break;
            }
        }
        for(size_t i = index; i < courses.size() - 1; i++){
            courses[i] = courses[i + 1];
        }
        courses.pop_back();
    }
}
