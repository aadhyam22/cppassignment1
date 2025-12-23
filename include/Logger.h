#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <fstream>
#include <ctime>   // Needed for date/time
#include <iostream>

class Logger {
private:
    std::ofstream logFile;
    std::string getCurrentTime(); // Helper function for [DATE TIME]

public:
    Logger();
    ~Logger();
    
    // Assignment Requirement: init(), log(), close()
    void init(std::string filename);
    void log(std::string level, std::string message); // Matches assignment
    void close();
};

#endif
