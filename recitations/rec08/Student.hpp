#ifndef STUDENT_HPP
#define STUDENT_HPP

#include <vector>
#include <string>
#include <iostream>

namespace BrooklynPoly{
    class Course;

    class Student{
        friend std::ostream& operator<<(std::ostream& os, const Student& rhs);
    public:
        Student(const std::string& nameT);
        const std::string& getName() const;
        bool addCourse(Course* currC);
        void removedFromCourse(Course* currC);
    private:
        std::string name;
        std::vector<Course*> courses;
    };
}
#endif
