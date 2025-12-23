#include "../include/ExamManager.h"
#include <fstream>
#include <sstream>

ExamManager::ExamManager(Logger* logRef) : logger(logRef) {
    loadExams();
}

void ExamManager::scheduleExam(std::string courseID, std::string date, int maxMarks) {
    // Basic validation
    if (maxMarks <= 0) {
        // Exception Handling (Assignment Requirement)
        throw InvalidInputException("Max Marks must be positive.");
    }

    Exam e;
    e.courseID = courseID;
    e.date = date;
    e.maxMarks = maxMarks;
    
    exams.push_back(e);
    saveExams();
    logger->log("INFO", "Exam Scheduled: " + courseID + " on " + date);
    std::cout << "[INFO] Exam scheduled successfully.\n";
}

void ExamManager::enterMarks(std::string courseID, std::string studentID, int marks) {
    for (auto& exam : exams) {
        if (exam.courseID == courseID) {
            if (marks < 0 || marks > exam.maxMarks) {
                throw InvalidInputException("Marks must be between 0 and Max Marks.");
            }
            
            exam.studentMarks[studentID] = marks;
            saveExams();
            logger->log("INFO", "Marks entered: " + studentID + " -> " + std::to_string(marks));
            std::cout << "[INFO] Marks updated.\n";
            return;
        }
    }
    std::cout << "[ERROR] No exam found for this course.\n";
}

void ExamManager::viewResults(std::string courseID) {
    std::cout << "\n--- Results for " << courseID << " ---\n";
    for (const auto& exam : exams) {
        if (exam.courseID == courseID) {
            std::cout << "Date: " << exam.date << " | Max Marks: " << exam.maxMarks << "\n";
            
            // Using Map Iterator
            for (const auto& pair : exam.studentMarks) {
                std::cout << "Student: " << pair.first << " | Marks: " << pair.second << "\n";
            }
            return;
        }
    }
    std::cout << "[INFO] No exam records found.\n";
}

void ExamManager::saveExams() {
    std::ofstream file(filename);
    if (!file.is_open()) return;
    
    for (const auto& e : exams) {
        // Format: CourseID Date MaxMarks Count [Student Marks]...
        file << e.courseID << " " << e.date << " " << e.maxMarks << " " << e.studentMarks.size();
        for (const auto& pair : e.studentMarks) {
            file << " " << pair.first << " " << pair.second;
        }
        file << "\n";
    }
    file.close();
}

void ExamManager::loadExams() {
    std::ifstream file(filename);
    if (!file.is_open()) return;
    
    exams.clear();
    std::string cid, date;
    int max, count;
    
    while (file >> cid >> date >> max >> count) {
        Exam e;
        e.courseID = cid;
        e.date = date;
        e.maxMarks = max;
        
        for (int i = 0; i < count; ++i) {
            std::string sid;
            int m;
            file >> sid >> m;
            e.studentMarks[sid] = m;
        }
        exams.push_back(e);
    }
    file.close();
}
