#include <iostream>
#include "../include/StudentManagement.h"
#include "../include/Utils.h"

// My main program entry point for the Student Management System
// I created this function to display a clean, organized menu with color-coded options
// This makes navigation easier for users of my system
void displayMainMenu() {
    UI::clearScreen();
    UI::printTitle("Student Management System");
    
    std::cout << Color::cyan << " 1." << Color::reset << " Add Student" << std::endl;
    std::cout << Color::cyan << " 2." << Color::reset << " Display All Students" << std::endl;
    std::cout << Color::cyan << " 3." << Color::reset << " Search Student" << std::endl;
    std::cout << Color::cyan << " 4." << Color::reset << " Update Student" << std::endl;
    std::cout << Color::cyan << " 5." << Color::reset << " Delete Student" << std::endl;
    std::cout << Color::cyan << " 6." << Color::reset << " Add Course" << std::endl;
    std::cout << Color::cyan << " 7." << Color::reset << " Display All Courses" << std::endl;
    std::cout << Color::cyan << " 8." << Color::reset << " Search Course" << std::endl;
    std::cout << Color::cyan << " 9." << Color::reset << " Update Course" << std::endl;
    std::cout << Color::cyan << "10." << Color::reset << " Delete Course" << std::endl;
    std::cout << Color::cyan << "11." << Color::reset << " Enroll Student in Course" << std::endl;
    std::cout << Color::cyan << "12." << Color::reset << " Drop Student from Course" << std::endl;
    std::cout << Color::cyan << "13." << Color::reset << " Display Enrollment Details" << std::endl;
    std::cout << Color::cyan << "14." << Color::reset << " Display Course Enrollment" << std::endl;
    std::cout << Color::cyan << "15." << Color::reset << " Generate Grade Report" << std::endl;
    std::cout << Color::cyan << "16." << Color::reset << " Generate Attendance Report" << std::endl;
    std::cout << Color::cyan << "17." << Color::reset << " Show Top Performers" << std::endl;
    std::cout << Color::cyan << "18." << Color::reset << " Sort Students by Name" << std::endl;
    std::cout << Color::cyan << "19." << Color::reset << " Sort Students by Grade" << std::endl;
    std::cout << Color::cyan << "20." << Color::reset << " Filter Students by Attendance" << std::endl;
    std::cout << Color::cyan << " 0." << Color::reset << " Exit" << std::endl;
    
    UI::printSeparator();
}

// My main function - the entry point of my Student Management System
// I designed this with a menu-driven approach for intuitive user interaction
int main() {
    StudentManagement sm;
    int choice;
    
    do {
        displayMainMenu();
        choice = Validation::getInteger("Enter your choice: ", 0, 20);
        
        switch (choice) {
            case 1: {
                UI::clearScreen();
                sm.addStudent();
                UI::pressEnterToContinue();
                break;
            }
            case 2: {
                UI::clearScreen();
                sm.displayAllStudents();
                UI::pressEnterToContinue();
                break;
            }
            case 3: {
                UI::clearScreen();
                UI::printTitle("Search Student");
                int rollNo = Validation::getInteger("Enter roll number to search: ", 1);
                const Student* student = sm.searchStudentByRoll(rollNo);
                if (student) {
                    student->displayDetailed();
                } else {
                    UI::printError("Student with roll number " + std::to_string(rollNo) + " not found!");
                }
                UI::pressEnterToContinue();
                break;
            }
            case 4: {
                UI::clearScreen();
                UI::printTitle("Update Student");
                int rollNo = Validation::getInteger("Enter roll number to update: ", 1);
                sm.updateStudent(rollNo);
                UI::pressEnterToContinue();
                break;
            }
            case 5: {
                UI::clearScreen();
                UI::printTitle("Delete Student");
                int rollNo = Validation::getInteger("Enter roll number to delete: ", 1);
                sm.deleteStudent(rollNo);
                UI::pressEnterToContinue();
                break;
            }
            case 6: {
                UI::clearScreen();
                sm.addCourse();
                UI::pressEnterToContinue();
                break;
            }
            case 7: {
                UI::clearScreen();
                sm.displayAllCourses();
                UI::pressEnterToContinue();
                break;
            }
            case 8: {
                UI::clearScreen();
                UI::printTitle("Search Course");
                std::string code = Validation::getString("Enter course code to search: ");
                const Course* course = sm.searchCourseByCode(code);
                if (course) {
                    course->displayDetailed();
                } else {
                    UI::printError("Course with code " + code + " not found!");
                }
                UI::pressEnterToContinue();
                break;
            }
            case 9: {
                UI::clearScreen();
                UI::printTitle("Update Course");
                std::string code = Validation::getString("Enter course code to update: ");
                sm.updateCourse(code);
                UI::pressEnterToContinue();
                break;
            }
            case 10: {
                UI::clearScreen();
                UI::printTitle("Delete Course");
                std::string code = Validation::getString("Enter course code to delete: ");
                sm.deleteCourse(code);
                UI::pressEnterToContinue();
                break;
            }
            case 11: {
                UI::clearScreen();
                sm.enrollStudentInCourse();
                UI::pressEnterToContinue();
                break;
            }
            case 12: {
                UI::clearScreen();
                sm.dropStudentFromCourse();
                UI::pressEnterToContinue();
                break;
            }
            case 13: {
                UI::clearScreen();
                UI::printTitle("Display Enrollment Details");
                int rollNo = Validation::getInteger("Enter roll number: ", 1);
                sm.displayEnrollmentDetails(rollNo);
                UI::pressEnterToContinue();
                break;
            }
            case 14: {
                UI::clearScreen();
                UI::printTitle("Display Course Enrollment");
                std::string code = Validation::getString("Enter course code: ");
                sm.displayCourseEnrollment(code);
                UI::pressEnterToContinue();
                break;
            }
            case 15: {
                UI::clearScreen();
                sm.generateGradeReport();
                UI::pressEnterToContinue();
                break;
            }
            case 16: {
                UI::clearScreen();
                sm.generateAttendanceReport();
                UI::pressEnterToContinue();
                break;
            }
            case 17: {
                UI::clearScreen();
                int count = Validation::getInteger("Enter number of top performers to show: ", 1, 100);
                sm.showTopPerformers(count);
                UI::pressEnterToContinue();
                break;
            }
            case 18: {
                UI::clearScreen();
                sm.sortStudentsByName();
                UI::pressEnterToContinue();
                break;
            }
            case 19: {
                UI::clearScreen();
                sm.sortStudentsByGrade();
                UI::pressEnterToContinue();
                break;
            }
            case 20: {
                UI::clearScreen();
                float minAttendance = Validation::getFloat("Enter minimum attendance percentage: ", 0, 100);
                sm.filterStudentsByAttendance(minAttendance);
                UI::pressEnterToContinue();
                break;
            }
            case 0: {
                UI::clearScreen();
                UI::printTitle("Exiting Program");
                UI::printSuccess("Thank you for using Student Management System!");
                std::cout << "Developed by: Nikhil Soni" << std::endl;
                std::cout << "Version: 2.0 (May 2025)" << std::endl;
                break;
            }
            default:
                UI::printError("Invalid choice! Please try again.");
        }
    } while (choice != 0);
    
    return 0;
}
