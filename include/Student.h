#ifndef STUDENT_H
#define STUDENT_H
#include "User.h"

class Student : public User {
public:
    Student(std::string n, std::string u, std::string p) 
        : User(n, u, p, "Student") {}
        
    void study() {
        std::cout << name << " is studying.\n";
    }
};
#endif
