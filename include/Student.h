#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <iostream>
#include <iomanip>
#include <vector>

// My custom Student class for managing student data
// I'm using forward declaration here to avoid circular dependencies
class Course;

class Student {
private:
    int id;
    std::string name;
    int rollNo;
    float grade;
    float attendance;
    std::string email;
    std::string phone;
    std::string address;
    std::vector<Course*> enrolledCourses;

public:
    // Constructors
    Student(std::string n = "", int r = 0, float g = 0.0, float a = 0.0);
    Student(int id, std::string n, int r, float g, float a, std::string email = "", 
            std::string phone = "", std::string address = "");

    // Getters
    int getId() const;
    std::string getName() const;
    int getRollNo() const;
    float getGrade() const;
    float getAttendance() const;
    std::string getEmail() const;
    std::string getPhone() const;
    std::string getAddress() const;
    std::vector<Course*> getEnrolledCourses() const;

    // Setters
    void setId(int id);
    void setName(std::string n);
    void setRollNo(int r);
    void setGrade(float g);
    void setAttendance(float a);
    void setEmail(std::string email);
    void setPhone(std::string phone);
    void setAddress(std::string address);

    // Course management
    void enrollCourse(Course* course);
    void dropCourse(Course* course);
    bool isEnrolledIn(Course* course) const;

    // Display and other methods
    void display() const;
    void displayDetailed() const;
    void displayAttendance() const;
    std::string toCSV() const; // For file output
};

#endif // STUDENT_H
