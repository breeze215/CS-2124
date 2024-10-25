#ifndef COURSE_HPP
#define COURSE_HPP

#include <iostream>
#include <vector>
#include <string>

namespace BrooklynPoly{
 class Student;
    class Course{
        friend std::ostream& operator<<(std::ostream& os, const Course& rhs);
    public:
        Course(const std::string& courseName);
        const std::string& getName() const;
        bool addStudent(Student* currStu);
        void removeStudentsFromCourse();
    private:
        std::string name;
        std::vector<Student*> students;
    };
}
#endif
