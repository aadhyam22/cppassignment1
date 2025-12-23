#ifndef USER_H
#define USER_H

#include "Person.h"
#include <string>
#include <iostream>

class User : public Person {
protected:
    std::string username;
    std::string password;
    std::string role; // Acts as Student/Teacher/Admin differentiator

public:
    // Constructor
    User(std::string n, std::string u, std::string p, std::string r)
        : Person(n), username(u), password(p), role(r) {}
    
    // Inline Getters (Requested by assignment)
    inline std::string getUsername() const { return username; }
    inline std::string getPassword() const { return password; }
    inline std::string getRole() const { return role; }

    // Inline Setter
    inline void setPassword(std::string newPass) { password = newPass; }

    // Override Virtual Function
    void printProfile() const override {
        std::cout << "------------------------\n";
        std::cout << "Name: " << name << "\n";
        std::cout << "Role: " << role << "\n";
        std::cout << "Username: " << username << "\n";
        std::cout << "------------------------\n";
    }
};
#endif
