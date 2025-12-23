#include "../include/AuthManag.h"
#include "../include/User.h"

#include <iostream>
#include <fstream>
#include <algorithm> // Needed for remove_if

AuthManager::AuthManager(Logger* logRef) : logger(logRef) {
    loadUsers();
}

void AuthManager::registerUser() {
    std::string name, user, pass, role;
    std::cout << "\n--- Register New User ---\n";
    std::cout << "Enter Name: "; 
    std::cin.ignore(); 
    std::getline(std::cin, name);
    
    std::cout << "Enter Username: "; std::cin >> user;
    if (isUsernameTaken(user)) {
        std::cout << "[ERROR] Username already exists.\n";
        return;
    }

    std::cout << "Enter Password: "; std::cin >> pass;
    std::cout << "Enter Role (Student/Teacher/Admin): "; std::cin >> role;

    User newUser(name, user, pass, role);
    users.push_back(newUser);
    saveUsers();

    logger->log("INFO", "New user registered: " + user);
    std::cout << "\n[INFO] Registration successful!\n";
}

User* AuthManager::login() {
    std::string user, pass;
    std::cout << "\n--- Login ---\n";
    std::cout << "Enter Username: "; std::cin >> user;
    std::cout << "Enter Password: "; std::cin >> pass;

    for (auto &u : users) {
        if (u.getUsername() == user && u.getPassword() == pass) {
            logger->log("INFO", "Login successful: " + user);
            return &u;
        }
    }
    
    logger->log("WARNING", "Failed login attempt: " + user);
    std::cout << "[ERROR] Invalid credentials.\n";
    return nullptr;
}

// --- NEW FUNCTION: Change Password ---
void AuthManager::changePassword(std::string username) {
    std::string oldPass, newPass;
    std::cout << "\n--- Change Password ---\n";
    std::cout << "Enter Old Password: "; std::cin >> oldPass;

    for (auto &u : users) {
        if (u.getUsername() == username) {
            if (u.getPassword() == oldPass) {
                std::cout << "Enter New Password: "; std::cin >> newPass;
                u.setPassword(newPass); // You need a setPassword setter in User.h!
                saveUsers();
                logger->log("INFO", "Password changed for: " + username);
                std::cout << "[INFO] Password updated successfully.\n";
                return;
            } else {
                std::cout << "[ERROR] Old password incorrect.\n";
                return;
            }
        }
    }
}

// --- NEW FUNCTION: Remove User ---
void AuthManager::removeUser() {
    std::string userToDelete;
    std::cout << "\n--- Remove User (Admin) ---\n";
    std::cout << "Enter Username to delete: "; std::cin >> userToDelete;

    auto it = std::remove_if(users.begin(), users.end(), [&](User& u) {
        return u.getUsername() == userToDelete;
    });

    if (it != users.end()) {
        users.erase(it, users.end());
        saveUsers();
        logger->log("INFO", "User removed: " + userToDelete);
        std::cout << "[INFO] User " << userToDelete << " deleted successfully.\n";
    } else {
        std::cout << "[ERROR] User not found.\n";
    }
}

void AuthManager::saveUsers() {
    std::ofstream file(filename);
    if (!file.is_open()) return;
    for (const auto& u : users) {
        file << u.getUsername() << " " << u.getPassword() << " " << u.getRole() << " " << u.getName() << "\n";
    }
    file.close();
}

void AuthManager::loadUsers() {
    std::ifstream file(filename);
    if (!file.is_open()) return;
    
    users.clear();
    std::string user, pass, role, name;
    while (file >> user >> pass >> role) {
        std::getline(file >> std::ws, name); 
        users.push_back(User(name, user, pass, role));
    }
    file.close();
}

bool AuthManager::isUsernameTaken(std::string username) {
    for (const auto& u : users) {
        if (u.getUsername() == username) return true;
    }
    return false;
}
