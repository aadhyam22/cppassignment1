#ifndef AUTHMANAGER_H
#define AUTHMANAGER_H

#include <string>
#include <vector>
#include "User.h"    // <--- MUST BE HERE. If this fails, check file path.
#include "Logger.h"

class AuthManager {
private:
    std::vector<User> users; // Needs full User definition from User.h
    std::string filename = "../data/users.txt"; 
    Logger* logger;

    void loadUsers();
    void saveUsers();

public:
    AuthManager(Logger* logRef);
    void registerUser();
    User* login();
    void changePassword(std::string username);
    void removeUser();
    bool isUsernameTaken(std::string username);
};
#endif
