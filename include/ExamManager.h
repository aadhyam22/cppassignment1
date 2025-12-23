#ifndef EXAMMANAGER_H
#define EXAMMANAGER_H

#include <string>
#include <map>
#include <vector>
#include <iostream>
#include <algorithm>
#include "Logger.h"

// 1. Custom Exception Class
class InvalidInputException : public std::exception {
    std::string msg;
public:
    InvalidInputException(const std::string& m) : msg(m) {}
    const char* what() const noexcept override { return msg.c_str(); }
};

// 2. Exam Structure
struct Exam {
    std::string courseID;
    std::string date;
    int maxMarks;
    std::map<std::string, int> studentMarks; // Map<StudentID, Marks>

    // 4. Overload < for sorting (Assignment Requirement)
    bool operator<(const Exam& other) const {
        return date < other.date;
    }
};

// 3. Template Class for Reports (Assignment Requirement)
template <typename T>
class ReportGenerator {
public:
    static void generate(const std::vector<T>& items) {
        std::cout << "\n--- Generated Report ---\n";
        for (const auto& item : items) {
            std::cout << item << "\n"; // Assumes item has << overloaded
        }
        std::cout << "------------------------\n";
    }
};

class ExamManager {
private:
    std::vector<Exam> exams;
    std::string filename = "../data/exams.txt";
    Logger* logger;

public:
    ExamManager(Logger* logRef);
    
    void scheduleExam(std::string courseID, std::string date, int maxMarks);
    void enterMarks(std::string courseID, std::string studentID, int marks);
    void viewResults(std::string courseID);
    
    void saveExams();
    void loadExams();
};

#endif
