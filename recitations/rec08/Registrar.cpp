#include <iostream>
#include <vector>
#include <string>
#include "Course.hpp"
#include "Student.hpp"
#include "Registrar.hpp"
using namespace std;

namespace BrooklynPoly{
    ostream& operator<<(ostream& os, const Registrar& rhs){
        os << "Registrar's Report" << endl;
        os << "Courses:" << endl;
        for (const Course* currC : rhs.courses) {
            os << *currC;
        }
        os << "Students:" << endl;
        for (const Student* currStu : rhs.students) {
            os << *currStu;
        }
        return os;
    }

    Registrar::Registrar() {}

    bool Registrar::addCourse(const string& name){
        if(findCourse(name) == courses.size()){
            courses.push_back(new Course(name));
            return true;
        }
        return false;
    }

    bool Registrar::addStudent(const string& name){
        if(findStudent(name) == students.size()){
            students.push_back(new Student(name));
            return true;
        }
        return false;
    }

    bool Registrar::enrollStudentInCourse(const string& studentName, const string& courseName){
        size_t courseI = findCourse(courseName);
        size_t studentI = findStudent(studentName);
        if(studentI < students.size() && courseI < courses.size()){
            return courses[courseI] -> addStudent(students[studentI]);
        }
        return false;
    }

    bool Registrar::cancelCourse(const string& courseName){
        size_t courseI = findCourse(courseName);
        if(courseI < courses.size()){
            courses[courseI] -> removeStudentsFromCourse();
            size_t index;
            for(index = 0; index < courses.size(); index++){
                if(courses[index] -> getName() == courseName){
                    break;
                }
            }
            delete courses[courseI];
            for(size_t i = index; i < courses.size() - 1; i++){
                courses[i] = courses[i + 1];
            }
            courses.pop_back();
            return true;
        }
        return false;
    }

    void Registrar::purge(){
        for(const Student* currStu : students){
            delete currStu;
        }
        students.clear();
        for(const Course* currC : courses){
            delete currC;
        }
        courses.clear();
    }

    size_t Registrar::findStudent(const string& name) const{
        for(size_t index = 0; index < students.size(); index++){
            if(students[index] -> getName() == name){
                return index;
            }
        }
        return students.size();
    }

    size_t Registrar::findCourse(const string& name) const{
        for(size_t index = 0; index < courses.size(); index++){
            if(courses[index] -> getName() == name){
                return index;
            }
        }
        return courses.size();
    }
}
