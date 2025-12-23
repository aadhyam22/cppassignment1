#include "../include/CourseManag.h"
#include <iostream>
#include <fstream>
#include <algorithm>

CourseManager::CourseManager(Logger* logRef) : logger(logRef) {
    loadCourses();
}

int CourseManager::findCourseIndex(std::string id) {
    for (size_t i = 0; i < courses.size(); ++i) {
        if (courses[i].id == id) return i;
    }
    return -1;
}

void CourseManager::addCourse(std::string id, std::string name, int credits, int capacity) {
    if (findCourseIndex(id) != -1) {
        std::cout << "[ERROR] Course ID already exists.\n";
        return;
    }
    courses.push_back(Course(id, name, credits, capacity));
    saveCourses();
    logger->log("INFO", "Course added: " + name + " (" + id + ")");
    std::cout << "[INFO] Course added successfully.\n";
}

void CourseManager::updateCourse(std::string id) {
    int idx = findCourseIndex(id);
    if (idx == -1) {
        std::cout << "[ERROR] Course not found.\n";
        return;
    }
    
    std::cout << "Updating Course: " << courses[idx].name << "\n";
    std::cout << "Enter New Name: "; std::cin >> courses[idx].name;
    std::cout << "Enter New Credits: "; std::cin >> courses[idx].credits;
    std::cout << "Enter New Capacity: "; std::cin >> courses[idx].capacity;
    
    saveCourses();
    logger->log("INFO", "Course updated: " + id);
    std::cout << "[INFO] Course updated successfully.\n";
}

void CourseManager::deleteCourse(std::string id) {
    int idx = findCourseIndex(id);
    if (idx == -1) {
        std::cout << "[ERROR] Course not found.\n";
        return;
    }
    
    courses.erase(courses.begin() + idx);
    saveCourses();
    logger->log("INFO", "Course deleted: " + id);
    std::cout << "[INFO] Course deleted successfully.\n";
}

void CourseManager::enrollStudent(std::string studentUsername, std::string courseID) {
    int idx = findCourseIndex(courseID);
    if (idx == -1) {
        std::cout << "[ERROR] Course not found.\n";
        return;
    }
    
    if (courses[idx].enrolledCount >= courses[idx].capacity) {
        std::cout << "[ERROR] Course is full!\n";
        logger->log("WARNING", "Enrollment failed (Full): " + studentUsername + " -> " + courseID);
        return;
    }
    
    // In a real system, we would check if student is ALREADY enrolled.
    // For this assignment, we just increment the counter.
    courses[idx].enrolledCount++;
    saveCourses();
    
    logger->log("INFO", "Student enrolled: " + studentUsername + " -> " + courseID);
    std::cout << "[INFO] Enrolled successfully in " << courses[idx].name << "\n";
}

void CourseManager::dropStudent(std::string studentUsername, std::string courseID) {
    int idx = findCourseIndex(courseID);
    if (idx == -1) {
        std::cout << "[ERROR] Course not found.\n";
        return;
    }

    if (courses[idx].enrolledCount > 0) {
        courses[idx].enrolledCount--;
        saveCourses();
        logger->log("INFO", "Student dropped: " + studentUsername + " from " + courseID);
        std::cout << "[INFO] Dropped successfully.\n";
    } else {
        std::cout << "[ERROR] No students enrolled in this course.\n";
    }
}

void CourseManager::listCourses() {
    std::cout << "\n--- Available Courses ---\n";
    if (courses.empty()) {
        std::cout << "No courses available.\n";
        return;
    }
    for (const auto& c : courses) {
        std::cout << "[" << c.id << "] " << c.name 
                  << " | Credits: " << c.credits 
                  << " | Seats: " << c.enrolledCount << "/" << c.capacity << "\n";
    }
}

void CourseManager::saveCourses() {
    std::ofstream file(filename);
    if (!file.is_open()) return;
    for (const auto& c : courses) {
        file << c.id << " " << c.name << " " << c.credits << " " << c.capacity << " " << c.enrolledCount << "\n";
    }
    file.close();
}

void CourseManager::loadCourses() {
    std::ifstream file(filename);
    if (!file.is_open()) return;
    
    courses.clear();
    std::string id, name;
    int cr, cap, count;
    
    while (file >> id >> name >> cr >> cap >> count) {
        Course c(id, name, cr, cap);
        c.enrolledCount = count;
        courses.push_back(c);
    }
    file.close();
}
