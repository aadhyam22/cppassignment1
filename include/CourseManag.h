#ifndef COURSEMANAGER_H
#define COURSEMANAGER_H

#include "Logger.h"
#include <vector>
#include <string>

struct Course {
    std::string id;
    std::string name; // "title" in assignment
    int credits;
    int capacity;         // NEW: Required by assignment
    int enrolledCount;    // To track how many students are in
    
    // Default constructor
    Course() : credits(0), capacity(0), enrolledCount(0) {}
    
    // Constructor for easy creation
    Course(std::string i, std::string n, int c, int cap) 
        : id(i), name(n), credits(c), capacity(cap), enrolledCount(0) {}
};

class CourseManager {
private:
    std::vector<Course> courses;
    std::string filename = "../data/courses.txt";
    Logger* logger;

    // Helper to find index of course by ID
    int findCourseIndex(std::string id);

public:
    CourseManager(Logger* logRef);
    
    // Assignment Requirements:
    void addCourse(std::string id, std::string name, int credits, int capacity);
    void updateCourse(std::string id);
    void deleteCourse(std::string id);
    
    void enrollStudent(std::string studentUsername, std::string courseID);
    void dropStudent(std::string studentUsername, std::string courseID);

    void listCourses();
    void saveCourses();
    void loadCourses();
};
#endif
