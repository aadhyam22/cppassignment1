#ifndef PERSON_H
#define PERSON_H
#include <string>
#include <iostream>

class Person {
protected:
    std::string name;
    std::string email;

public:
    // Constructor
    Person(std::string n, std::string e = "") : name(n), email(e) {}
    
    // Virtual Destructor (Critical for inheritance)
    virtual ~Person() {} 

    // Pure Virtual Function (Abstract Class)
    virtual void printProfile() const = 0;

    // Inline Getter
    inline std::string getName() const { return name; }
};
#endif
