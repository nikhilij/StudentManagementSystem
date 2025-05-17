#ifndef STUDENT_MANAGEMENT_H
#define STUDENT_MANAGEMENT_H

#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <memory>
#include <map>
#include "Student.h"
#include "Course.h"

class StudentManagement {
private:
    std::vector<Student> students;
    std::vector<Course> courses;
    const std::string studentFile = "data/students.csv";
    const std::string courseFile = "data/courses.csv";
    const std::string enrollmentFile = "data/enrollments.csv";
    
    // Helper methods
    bool isRollNoUnique(int rollNo) const;
    bool isCourseCodeUnique(const std::string& code) const;
    int generateStudentId() const;
    int generateCourseId() const;
    
    // File operations
    void saveStudentsToFile() const;
    void saveCoursesToFile() const;
    void saveEnrollmentsToFile() const;
    void loadStudentsFromFile();
    void loadCoursesFromFile();
    void loadEnrollmentsFromFile();

public:
    // Constructor
    StudentManagement();
    
    // Student management
    void addStudent();
    void displayAllStudents() const;
    Student* searchStudentByRoll(int rollNo);
    const Student* searchStudentByRoll(int rollNo) const;
    void updateStudent(int rollNo);
    void deleteStudent(int rollNo);
    
    // Course management
    void addCourse();
    void displayAllCourses() const;
    Course* searchCourseByCode(const std::string& code);
    const Course* searchCourseByCode(const std::string& code) const;
    void updateCourse(const std::string& code);
    void deleteCourse(const std::string& code);
    
    // Enrollment management
    void enrollStudentInCourse();
    void dropStudentFromCourse();
    void displayEnrollmentDetails(int rollNo) const;
    void displayCourseEnrollment(const std::string& code) const;
    
    // Statistics and reports
    void generateGradeReport() const;
    void generateAttendanceReport() const;
    void showTopPerformers(int count = 5) const;
    
    // Sorting and filtering
    void sortStudentsByName();
    void sortStudentsByGrade();
    void filterStudentsByAttendance(float minAttendance) const;
};

#endif // STUDENT_MANAGEMENT_H
