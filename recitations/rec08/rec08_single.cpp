/*
  rec08_single.cpp
  Author : Uvindu Salgado
  Everything in one file
 */

#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Student class prototype
class Student;
class Course {
    friend ostream& operator<<(ostream& os, const Course& rhs);
public:
    // Course methods needed by Registrar
    Course(const string& courseName);
    const string& getName() const;
    bool addStudent(Student* currStu);

    // Tell the students that they are no longer in the course
    void removeStudentsFromCourse();

private:
    string name;
    vector<Student*> students;
}; // Course

class Student {
    friend ostream& operator<<(ostream& os, const Student& rhs);
public:
    // Student methods needed by Registrar
    Student(const string& nameT);
    const string& getName() const;
    bool addCourse(Course* currC);

    // Student method needed by Course::removeStudentsFromCourse
    void removedFromCourse(Course* currC);

private:
    string name;
    vector<Course*> courses;
}; // Student

class Registrar {
    friend ostream& operator<<(ostream& os, const Registrar& rhs);
public:
    Registrar();

    // Creates a new course, if none with that name
    bool addCourse(const string& name);
    // Creates a new student, if none with that name
    bool addStudent(const string& name);

    // If the student and the course exist, then enroll the student.
    bool enrollStudentInCourse(const string& studentName, const string& courseName);

    // Unenroll the students from the course and remove the course
    // from the Registrar.
    bool cancelCourse(const string& courseName);

    // Get rid of everything!!!
    void purge();

private:
    size_t findStudent(const string& name) const;
    size_t findCourse(const string& name) const;

    vector<Course*> courses;
    vector<Student*> students;
}; // Registrar

int main()
{

    Registrar registrar;

    cout << "No courses or students added yet\n";
    cout << registrar << endl;
     
    cout << "AddCourse CS101.001\n";
    registrar.addCourse("CS101.001");
    cout << registrar << endl;

    cout << "AddStudent FritzTheCat\n";
    registrar.addStudent("FritzTheCat");
    cout << registrar << endl;

    cout << "AddCourse CS102.001\n";
    registrar.addCourse("CS102.001");
    cout << registrar << endl;

    cout << "EnrollStudentInCourse FritzTheCat CS102.001\n";
    registrar.enrollStudentInCourse("FritzTheCat", "CS102.001");
    cout << "EnrollStudentInCourse FritzTheCat CS101.001\n";
    registrar.enrollStudentInCourse("FritzTheCat", "CS101.001");
    cout << registrar << endl;

    cout << "EnrollStudentInCourse Bullwinkle CS101.001\n";
    cout << "Should fail, i.e. do nothing, "
         << "since Bullwinkle is not a student.\n";
    registrar.enrollStudentInCourse("Bullwinkle", "CS101.001");
    cout << registrar << endl;

    cout << "CancelCourse CS102.001\n";
    registrar.cancelCourse("CS102.001");
    cout << registrar << endl;
   
    cout << "Purge for start of next semester\n";
    registrar.purge();
    cout << registrar << endl;
} // main
  
// code for the Course class
ostream& operator<<(ostream& os, const Course& rhs){
    os << rhs.name << ":";
    if(rhs.students.size() == 0){
        os << " No Students";
    }
    else{
        for(Student* currStu : rhs.students){
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

// code for the Student class
ostream& operator<<(ostream& os, const Student& rhs){
    os << rhs.name << ":";
    if(rhs.courses.size() == 0){
        os << " No Courses";
    }
    else{
        for(Course* currC : rhs.courses){
            os << " " << currC -> getName();
        }
    }
    os << endl;
    return os;
}

Student::Student(const string& nameT) : name(nameT) {}

const string& Student::getName() const { return name; }

bool Student::addCourse(Course* currC){
    for(Course* currCo : courses){
        if(currCo -> getName() == currC -> getName()){
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
    courses[index] = courses.back();
    courses.pop_back();
}

// code for the Registar class
ostream& operator<<(ostream& os, const Registrar& rhs){
    os << "Registrar's Report" << endl;
    os << "Courses:" << endl;
    for (Course* currC : rhs.courses) {
        os << *currC;
    }
    os << "Students:" << endl;
    for (Student* currStu : rhs.students) {
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
        delete courses[courseI];
        courses[courseI] = courses[courses.size() - 1];
        courses.pop_back();
        return true;
    }
    return false;
}

void Registrar::purge(){
    for(Student* currStu : students){
        delete currStu;
    }
    students.clear();
    for(Course* currC : courses){
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

