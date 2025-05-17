#ifndef COURSE_H
#define COURSE_H

#include <string>
#include <vector>
#include <iostream>
#include <iomanip>

// I needed to add this course management system to make my project more comprehensive
// Using forward declaration to handle the circular dependency with Student class
class Student;

class Course {
private:
    int id;
    std::string code;
    std::string name;
    std::string instructor;
    int credits;
    int maxCapacity;
    std::vector<Student*> enrolledStudents;

public:
    // Constructors
    Course(std::string code = "", std::string name = "", std::string instructor = "", int credits = 0, int maxCapacity = 30);
    Course(int id, std::string code, std::string name, std::string instructor, int credits, int maxCapacity);

    // Getters
    int getId() const;
    std::string getCode() const;
    std::string getName() const;
    std::string getInstructor() const;
    int getCredits() const;
    int getMaxCapacity() const;
    int getCurrentEnrollment() const;
    std::vector<Student*> getEnrolledStudents() const;

    // Setters
    void setId(int id);
    void setCode(std::string code);
    void setName(std::string name);
    void setInstructor(std::string instructor);
    void setCredits(int credits);
    void setMaxCapacity(int maxCapacity);

    // Student management
    bool addStudent(Student* student);
    bool removeStudent(Student* student);
    bool isFull() const;
    bool hasStudent(Student* student) const;

    // Display and other methods
    void display() const;
    void displayDetailed() const;
    void displayEnrollmentList() const;
    std::string toCSV() const; // For file output
};

#endif // COURSE_H
