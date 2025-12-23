#ifndef ATTENDANCEMANAGER_H
#define ATTENDANCEMANAGER_H

#include "Logger.h"
#include <string>
#include <vector>
#include <iostream>

struct AttendanceRecord {
    std::string courseID;
    std::string studentUsername;
    std::string date; // Format: YYYY-MM-DD
    std::string status; // "Present", "Absent"

    // Requirement: Operator Overloading for Comparison (Dates)
    bool operator<(const AttendanceRecord& other) const {
        return date < other.date;
    }

    // Requirement: Operator Overloading for Output Stream
    friend std::ostream& operator<<(std::ostream& os, const AttendanceRecord& record) {
        os << record.date << " | " << record.courseID << " | " << record.studentUsername << " | " << record.status;
        return os;
    }
};

class AttendanceManager {
private:
    std::vector<AttendanceRecord> records;
    std::string filename = "../data/attendance.txt";
    Logger* logger;

public:
    AttendanceManager(Logger* logRef);
    
    void markAttendance(std::string courseID, std::string studentUser, std::string date, std::string status);
    void viewAttendance(std::string courseID);
    void viewAttendanceByDateRange(std::string courseID, std::string startDate, std::string endDate);
    
    void saveAttendance();
    void loadAttendance();
};

#endif
