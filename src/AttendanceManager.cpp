#include "../include/AttendanceManager.h"
#include <fstream>
#include <algorithm>

AttendanceManager::AttendanceManager(Logger* logRef) : logger(logRef) {
    loadAttendance();
}

void AttendanceManager::markAttendance(std::string courseID, std::string studentUser, std::string date, std::string status) {
    AttendanceRecord newRecord = {courseID, studentUser, date, status};
    records.push_back(newRecord);
    saveAttendance();
    
    logger->log("INFO", "Attendance Marked: " + studentUser + " in " + courseID + " on " + date);
    std::cout << "[INFO] Attendance marked successfully.\n";
}

void AttendanceManager::viewAttendance(std::string courseID) {
    std::cout << "\n--- Attendance for " << courseID << " ---\n";
    bool found = false;
    for (const auto& rec : records) {
        if (rec.courseID == courseID) {
            // Using the Overloaded << Operator here!
            std::cout << rec << "\n"; 
            found = true;
        }
    }
    if (!found) std::cout << "No records found.\n";
}

void AttendanceManager::viewAttendanceByDateRange(std::string courseID, std::string startDate, std::string endDate) {
    std::cout << "\n--- Attendance Report (" << startDate << " to " << endDate << ") ---\n";
    
    // Sort by date using Overloaded < Operator
    std::sort(records.begin(), records.end()); 

    for (const auto& rec : records) {
        if (rec.courseID == courseID && rec.date >= startDate && rec.date <= endDate) {
            std::cout << rec << "\n";
        }
    }
}

void AttendanceManager::saveAttendance() {
    std::ofstream file(filename);
    if (!file.is_open()) return;
    for (const auto& r : records) {
        file << r.courseID << " " << r.studentUsername << " " << r.date << " " << r.status << "\n";
    }
    file.close();
}

void AttendanceManager::loadAttendance() {
    std::ifstream file(filename);
    if (!file.is_open()) return;
    records.clear();
    std::string c, u, d, s;
    while (file >> c >> u >> d >> s) {
        records.push_back({c, u, d, s});
    }
    file.close();
}
