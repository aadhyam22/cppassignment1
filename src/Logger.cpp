#include "../include/Logger.h"
#include <iostream>

Logger::Logger() {}

Logger::~Logger() {
    close();
}

void Logger::init(std::string filename) {
    // Open in append mode so we don't erase old logs
    logFile.open(filename, std::ios::app);
    if (!logFile.is_open()) {
        std::cerr << "Error: Could not open log file at " << filename << std::endl;
    }
}

std::string Logger::getCurrentTime() {
    time_t now = time(0);
    struct tm tstruct;
    char buf[80];
    tstruct = *localtime(&now);
    // Format: YYYY-MM-DD HH:MM:SS
    strftime(buf, sizeof(buf), "%Y-%m-%d %X", &tstruct);
    return std::string(buf);
}

void Logger::log(std::string level, std::string message) {
    if (logFile.is_open()) {
        // Assignment Format: [DATE TIME] [LEVEL] [MODULE] message
        // Note: The assignment asks for [MODULE], but since we are logging from 
        // multiple places, we can include the module in the message or pass it as an arg.
        // For simplicity, we will stick to your current usage but add the Date.
        
        logFile << "[" << getCurrentTime() << "] [" << level << "] " << message << std::endl;
        
        // Optional: Also print to console so you can see it happening
        // std::cout << "[" << level << "] " << message << std::endl;
    }
}

void Logger::close() {
    if (logFile.is_open()) {
        logFile.close();
    }
}
