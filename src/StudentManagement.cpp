#include "../include/StudentManagement.h"
#include "../include/Utils.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <sstream>
#include <filesystem>

// Using the filesystem library for more robust file operations
namespace fs = std::filesystem;

// This is the main class that ties everything together
// I designed this class as the central management system that handles all operations
StudentManagement::StudentManagement() {
    // I'm making sure the data directory exists before trying to access files
    // This prevents errors when running the program for the first time
    if (!fs::exists("data")) {
        fs::create_directory("data");
    }

    loadStudentsFromFile();
    loadCoursesFromFile();
    loadEnrollmentsFromFile();
}

// I added these helper methods to handle common tasks that are used throughout the system
// This method ensures we don't have duplicate roll numbers - something I found important for data integrity
bool StudentManagement::isRollNoUnique(int rollNo) const {
    for (const auto& student : students) {
        if (student.getRollNo() == rollNo) {
            return false;
        }
    }
    return true;
}

bool StudentManagement::isCourseCodeUnique(const std::string& code) const {
    for (const auto& course : courses) {
        if (course.getCode() == code) {
            return false;
        }
    }
    return true;
}

int StudentManagement::generateStudentId() const {
    int maxId = 0;
    for (const auto& student : students) {
        if (student.getId() > maxId) {
            maxId = student.getId();
        }
    }
    return maxId + 1;
}

int StudentManagement::generateCourseId() const {
    int maxId = 0;
    for (const auto& course : courses) {
        if (course.getId() > maxId) {
            maxId = course.getId();
        }
    }
    return maxId + 1;
}

// My file operation methods - I designed these to keep data persistent between program runs
// I chose CSV format for easier integration with other tools if needed
void StudentManagement::saveStudentsToFile() const {
    std::ofstream outFile(studentFile);
    if (!outFile) {
        UI::printError("Error opening student file for writing!");
        return;
    }
    
    // I'm adding a header row to make the CSV more readable and self-documenting
    outFile << "id,name,rollNo,grade,attendance,email,phone,address" << std::endl;
    
    // Write student data
    for (const auto& student : students) {
        outFile << student.toCSV() << std::endl;
    }
    outFile.close();
}

void StudentManagement::saveCoursesToFile() const {
    std::ofstream outFile(courseFile);
    if (!outFile) {
        UI::printError("Error opening course file for writing!");
        return;
    }
    
    // Write header
    outFile << "id,code,name,instructor,credits,maxCapacity" << std::endl;
    
    // Write course data
    for (const auto& course : courses) {
        outFile << course.toCSV() << std::endl;
    }
    outFile.close();
}

void StudentManagement::saveEnrollmentsToFile() const {
    std::ofstream outFile(enrollmentFile);
    if (!outFile) {
        UI::printError("Error opening enrollment file for writing!");
        return;
    }
    
    // Write header
    outFile << "studentId,courseId" << std::endl;
    
    // Write enrollment data
    for (const auto& student : students) {
        for (const auto& course : student.getEnrolledCourses()) {
            outFile << student.getId() << "," << course->getId() << std::endl;
        }
    }
    outFile.close();
}

void StudentManagement::loadStudentsFromFile() {
    std::ifstream inFile(studentFile);
    if (!inFile) {
        UI::printInfo("No existing student data file found. Starting fresh.");
        return;
    }
    
    students.clear();
    std::string line;
    
    // Skip header
    std::getline(inFile, line);
    
    while (std::getline(inFile, line)) {
        std::stringstream ss(line);
        std::string token;
        std::vector<std::string> tokens;
        
        while (std::getline(ss, token, ',')) {
            tokens.push_back(token);
        }
        
        if (tokens.size() >= 8) {
            int id = std::stoi(tokens[0]);
            std::string name = tokens[1];
            int rollNo = std::stoi(tokens[2]);
            float grade = std::stof(tokens[3]);
            float attendance = std::stof(tokens[4]);
            std::string email = tokens[5];
            std::string phone = tokens[6];
            std::string address = tokens[7];
            
            students.emplace_back(id, name, rollNo, grade, attendance, email, phone, address);
        }
    }
    
    inFile.close();
}

void StudentManagement::loadCoursesFromFile() {
    std::ifstream inFile(courseFile);
    if (!inFile) {
        UI::printInfo("No existing course data file found. Starting fresh.");
        return;
    }
    
    courses.clear();
    std::string line;
    
    // Skip header
    std::getline(inFile, line);
    
    while (std::getline(inFile, line)) {
        std::stringstream ss(line);
        std::string token;
        std::vector<std::string> tokens;
        
        while (std::getline(ss, token, ',')) {
            tokens.push_back(token);
        }
        
        if (tokens.size() >= 6) {
            int id = std::stoi(tokens[0]);
            std::string code = tokens[1];
            std::string name = tokens[2];
            std::string instructor = tokens[3];
            int credits = std::stoi(tokens[4]);
            int maxCapacity = std::stoi(tokens[5]);
            
            courses.emplace_back(id, code, name, instructor, credits, maxCapacity);
        }
    }
    
    inFile.close();
}

void StudentManagement::loadEnrollmentsFromFile() {
    std::ifstream inFile(enrollmentFile);
    if (!inFile) {
        UI::printInfo("No existing enrollment data file found. Starting fresh.");
        return;
    }
    
    std::string line;
    
    // Skip header
    std::getline(inFile, line);
    
    // Create maps for fast lookup
    std::map<int, Student*> studentMap;
    std::map<int, Course*> courseMap;
    
    for (auto& student : students) {
        studentMap[student.getId()] = &student;
    }
    
    for (auto& course : courses) {
        courseMap[course.getId()] = &course;
    }
    
    // Load enrollments
    while (std::getline(inFile, line)) {
        std::stringstream ss(line);
        std::string token;
        std::vector<std::string> tokens;
        
        while (std::getline(ss, token, ',')) {
            tokens.push_back(token);
        }
        
        if (tokens.size() >= 2) {
            int studentId = std::stoi(tokens[0]);
            int courseId = std::stoi(tokens[1]);
            
            if (studentMap.count(studentId) && courseMap.count(courseId)) {
                Student* student = studentMap[studentId];
                Course* course = courseMap[courseId];
                
                student->enrollCourse(course);
                course->addStudent(student);
            }
        }
    }
    
    inFile.close();
}

// Student management methods
void StudentManagement::addStudent() {
    UI::printTitle("Add New Student");
    
    std::string name = Validation::getString("Enter student name: ");
    
    int rollNo;
    bool rollNoValid = false;
    do {
        rollNo = Validation::getInteger("Enter roll number: ", 1);
        
        if (!isRollNoUnique(rollNo)) {
            UI::printError("Roll number already exists! Please enter a unique roll number.");
        } else {
            rollNoValid = true;
        }
    } while (!rollNoValid);
    
    float grade = Validation::getFloat("Enter grade (0-100): ", 0, 100);
    float attendance = Validation::getFloat("Enter attendance (0-100%): ", 0, 100);
    
    std::string email = Validation::getEmail("Enter email (optional): ");
    std::string phone = Validation::getPhone("Enter phone (optional): ");
    std::string address = Validation::getString("Enter address (optional): ", true);
    
    int id = generateStudentId();
    
    students.emplace_back(id, name, rollNo, grade, attendance, email, phone, address);
    saveStudentsToFile();
    
    UI::printSuccess("Student added successfully!");
}

void StudentManagement::displayAllStudents() const {
    if (students.empty()) {
        UI::printInfo("No students found!");
        return;
    }
    
    UI::printTitle("All Students");
    
    std::cout << "+----------------------+----------+-------+------------+" << std::endl;
    std::cout << "| " << Color::cyan << "Name" << Color::reset 
              << "                 | " << Color::cyan << "Roll No" << Color::reset 
              << "  | " << Color::cyan << "Grade" << Color::reset 
              << " | " << Color::cyan << "Attendance" << Color::reset << " |" << std::endl;
    std::cout << "+----------------------+----------+-------+------------+" << std::endl;
    
    for (const auto& student : students) {
        student.display();
    }
    
    std::cout << "+----------------------+----------+-------+------------+" << std::endl;
    std::cout << "| Total students: " << std::left << std::setw(22) << students.size() << " |" << std::endl;
    std::cout << "+----------------------+----------+-------+------------+" << std::endl;
}

Student* StudentManagement::searchStudentByRoll(int rollNo) {
    for (auto& student : students) {
        if (student.getRollNo() == rollNo) {
            return &student;
        }
    }
    return nullptr;
}

const Student* StudentManagement::searchStudentByRoll(int rollNo) const {
    for (const auto& student : students) {
        if (student.getRollNo() == rollNo) {
            return &student;
        }
    }
    return nullptr;
}

void StudentManagement::updateStudent(int rollNo) {
    Student* student = searchStudentByRoll(rollNo);
    
    if (!student) {
        UI::printError("Student with roll number " + std::to_string(rollNo) + " not found!");
        return;
    }
    
    UI::printTitle("Update Student");
    student->displayDetailed();
    
    std::cout << "\nEnter new details (leave empty to keep current):\n";
    
    std::string name = Validation::getString("Enter new name [" + student->getName() + "]: ", true);
    if (!name.empty()) {
        student->setName(name);
    }
    
    std::string gradeStr = Validation::getString("Enter new grade (0-100) [" + std::to_string(student->getGrade()) + "]: ", true);
    if (!gradeStr.empty()) {
        float grade = std::stof(gradeStr);
        student->setGrade(grade);
    }
    
    std::string attendanceStr = Validation::getString("Enter new attendance (0-100%) [" + std::to_string(student->getAttendance()) + "]: ", true);
    if (!attendanceStr.empty()) {
        float attendance = std::stof(attendanceStr);
        student->setAttendance(attendance);
    }
    
    std::string email = Validation::getString("Enter new email [" + student->getEmail() + "]: ", true);
    if (!email.empty()) {
        student->setEmail(email);
    }
    
    std::string phone = Validation::getString("Enter new phone [" + student->getPhone() + "]: ", true);
    if (!phone.empty()) {
        student->setPhone(phone);
    }
    
    std::string address = Validation::getString("Enter new address [" + student->getAddress() + "]: ", true);
    if (!address.empty()) {
        student->setAddress(address);
    }
    
    saveStudentsToFile();
    UI::printSuccess("Student updated successfully!");
}

void StudentManagement::deleteStudent(int rollNo) {
    auto it = std::find_if(students.begin(), students.end(), [rollNo](const Student& s) {
        return s.getRollNo() == rollNo;
    });
    
    if (it != students.end()) {
        // Remove student from all courses
        for (auto& course : courses) {
            for (auto* enrolledStudent : course.getEnrolledStudents()) {
                if (enrolledStudent->getRollNo() == rollNo) {
                    course.removeStudent(enrolledStudent);
                    break;
                }
            }
        }
        
        students.erase(it);
        saveStudentsToFile();
        saveEnrollmentsToFile();
        UI::printSuccess("Student with roll number " + std::to_string(rollNo) + " deleted successfully!");
    } else {
        UI::printError("Student with roll number " + std::to_string(rollNo) + " not found!");
    }
}

// Course management methods
void StudentManagement::addCourse() {
    UI::printTitle("Add New Course");
    
    std::string code;
    bool codeValid = false;
    do {
        code = Validation::getString("Enter course code: ");
        
        if (!isCourseCodeUnique(code)) {
            UI::printError("Course code already exists! Please enter a unique code.");
        } else {
            codeValid = true;
        }
    } while (!codeValid);
    
    std::string name = Validation::getString("Enter course name: ");
    std::string instructor = Validation::getString("Enter instructor name: ");
    int credits = Validation::getInteger("Enter number of credits: ", 1, 10);
    int maxCapacity = Validation::getInteger("Enter maximum capacity: ", 1, 200);
    
    int id = generateCourseId();
    
    courses.emplace_back(id, code, name, instructor, credits, maxCapacity);
    saveCoursesToFile();
    
    UI::printSuccess("Course added successfully!");
}

void StudentManagement::displayAllCourses() const {
    if (courses.empty()) {
        UI::printInfo("No courses found!");
        return;
    }
    
    UI::printTitle("All Courses");
    
    std::cout << "+------------+---------------------------+----------------------+---------+---------+" << std::endl;
    std::cout << "| " << Color::cyan << "Code" << Color::reset 
              << "       | " << Color::cyan << "Name" << Color::reset 
              << "                        | " << Color::cyan << "Instructor" << Color::reset 
              << "           | " << Color::cyan << "Credits" << Color::reset 
              << " | " << Color::cyan << "Enrolled" << Color::reset << " |" << std::endl;
    std::cout << "+------------+---------------------------+----------------------+---------+---------+" << std::endl;
    
    for (const auto& course : courses) {
        course.display();
    }
    
    std::cout << "+------------+---------------------------+----------------------+---------+---------+" << std::endl;
    std::cout << "| Total courses: " << std::left << std::setw(49) << courses.size() << " |" << std::endl;
    std::cout << "+------------+---------------------------+----------------------+---------+---------+" << std::endl;
}

Course* StudentManagement::searchCourseByCode(const std::string& code) {
    for (auto& course : courses) {
        if (course.getCode() == code) {
            return &course;
        }
    }
    return nullptr;
}

const Course* StudentManagement::searchCourseByCode(const std::string& code) const {
    for (const auto& course : courses) {
        if (course.getCode() == code) {
            return &course;
        }
    }
    return nullptr;
}

void StudentManagement::updateCourse(const std::string& code) {
    Course* course = searchCourseByCode(code);
    
    if (!course) {
        UI::printError("Course with code " + code + " not found!");
        return;
    }
    
    UI::printTitle("Update Course");
    course->displayDetailed();
    
    std::cout << "\nEnter new details (leave empty to keep current):\n";
    
    std::string name = Validation::getString("Enter new name [" + course->getName() + "]: ", true);
    if (!name.empty()) {
        course->setName(name);
    }
    
    std::string instructor = Validation::getString("Enter new instructor [" + course->getInstructor() + "]: ", true);
    if (!instructor.empty()) {
        course->setInstructor(instructor);
    }
    
    std::string creditsStr = Validation::getString("Enter new credits [" + std::to_string(course->getCredits()) + "]: ", true);
    if (!creditsStr.empty()) {
        int credits = std::stoi(creditsStr);
        course->setCredits(credits);
    }
    
    std::string maxCapacityStr = Validation::getString("Enter new max capacity [" + std::to_string(course->getMaxCapacity()) + "]: ", true);
    if (!maxCapacityStr.empty()) {
        int maxCapacity = std::stoi(maxCapacityStr);
        course->setMaxCapacity(maxCapacity);
    }
    
    saveCoursesToFile();
    UI::printSuccess("Course updated successfully!");
}

void StudentManagement::deleteCourse(const std::string& code) {
    auto it = std::find_if(courses.begin(), courses.end(), [&code](const Course& c) {
        return c.getCode() == code;
    });
    
    if (it != courses.end()) {
        // Remove course from all students
        for (auto& student : students) {
            for (auto* enrolledCourse : student.getEnrolledCourses()) {
                if (enrolledCourse->getCode() == code) {
                    student.dropCourse(enrolledCourse);
                    break;
                }
            }
        }
        
        courses.erase(it);
        saveCoursesToFile();
        saveEnrollmentsToFile();
        UI::printSuccess("Course with code " + code + " deleted successfully!");
    } else {
        UI::printError("Course with code " + code + " not found!");
    }
}

// Enrollment management methods
void StudentManagement::enrollStudentInCourse() {
    UI::printTitle("Enroll Student in Course");
    
    // List all students
    std::cout << "Available students:" << std::endl;
    for (const auto& student : students) {
        std::cout << "Roll No: " << student.getRollNo() << ", Name: " << student.getName() << std::endl;
    }
    
    int rollNo = Validation::getInteger("\nEnter student roll number: ", 1);
    Student* student = searchStudentByRoll(rollNo);
    
    if (!student) {
        UI::printError("Student with roll number " + std::to_string(rollNo) + " not found!");
        return;
    }
    
    // List all courses
    std::cout << "\nAvailable courses:" << std::endl;
    for (const auto& course : courses) {
        std::cout << "Code: " << course.getCode() 
                  << ", Name: " << course.getName() 
                  << ", Enrollment: " << course.getCurrentEnrollment() << "/" << course.getMaxCapacity() 
                  << (course.isFull() ? " (FULL)" : "") << std::endl;
    }
    
    std::string code = Validation::getString("\nEnter course code: ");
    Course* course = searchCourseByCode(code);
    
    if (!course) {
        UI::printError("Course with code " + code + " not found!");
        return;
    }
    
    if (course->isFull()) {
        UI::printError("Course is full. Cannot enroll more students!");
        return;
    }
    
    if (student->isEnrolledIn(course)) {
        UI::printError("Student is already enrolled in this course!");
        return;
    }
    
    student->enrollCourse(course);
    course->addStudent(student);
    
    saveEnrollmentsToFile();
    UI::printSuccess("Student successfully enrolled in the course!");
}

void StudentManagement::dropStudentFromCourse() {
    UI::printTitle("Drop Student from Course");
    
    int rollNo = Validation::getInteger("Enter student roll number: ", 1);
    Student* student = searchStudentByRoll(rollNo);
    
    if (!student) {
        UI::printError("Student with roll number " + std::to_string(rollNo) + " not found!");
        return;
    }
    
    const auto& enrolledCourses = student->getEnrolledCourses();
    
    if (enrolledCourses.empty()) {
        UI::printError("Student is not enrolled in any courses!");
        return;
    }
    
    std::cout << "\nCourses enrolled by " << student->getName() << ":" << std::endl;
    for (size_t i = 0; i < enrolledCourses.size(); i++) {
        std::cout << (i + 1) << ". " << enrolledCourses[i]->getCode() 
                  << " - " << enrolledCourses[i]->getName() << std::endl;
    }
    
    int choice = Validation::getInteger("\nSelect course number to drop (1-" + std::to_string(enrolledCourses.size()) + "): ", 
                                       1, enrolledCourses.size());
    
    Course* course = enrolledCourses[choice - 1];
    student->dropCourse(course);
    course->removeStudent(student);
    
    saveEnrollmentsToFile();
    UI::printSuccess("Student successfully dropped from the course!");
}

void StudentManagement::displayEnrollmentDetails(int rollNo) const {
    const Student* student = searchStudentByRoll(rollNo);
    
    if (!student) {
        UI::printError("Student with roll number " + std::to_string(rollNo) + " not found!");
        return;
    }
    
    UI::printTitle("Enrollment Details");
    student->displayDetailed();
}

void StudentManagement::displayCourseEnrollment(const std::string& code) const {
    const Course* course = searchCourseByCode(code);
    
    if (!course) {
        UI::printError("Course with code " + code + " not found!");
        return;
    }
    
    UI::printTitle("Course Enrollment");
    course->displayEnrollmentList();
}

// I'm particularly proud of these reporting features I added to provide useful insights
// The grade report helps identify students' academic performance at a glance
void StudentManagement::generateGradeReport() const {
    if (students.empty()) {
        UI::printInfo("No students found!");
        return;
    }
    
    UI::printTitle("Grade Report");
    
    std::cout << "+----------+----------------------+-------+-----------------+" << std::endl;
    std::cout << "| " << Color::cyan << "Roll No" << Color::reset 
              << "   | " << Color::cyan << "Name" << Color::reset 
              << "                 | " << Color::cyan << "Grade" << Color::reset 
              << " | " << Color::cyan << "Grade Letter" << Color::reset << "     |" << std::endl;
    std::cout << "+----------+----------------------+-------+-----------------+" << std::endl;
    
    for (const auto& student : students) {
        float grade = student.getGrade();
        std::string gradeLetter;
        
        if (grade >= 90) gradeLetter = "A (Excellent)";
        else if (grade >= 80) gradeLetter = "B (Very Good)";
        else if (grade >= 70) gradeLetter = "C (Good)";
        else if (grade >= 60) gradeLetter = "D (Satisfactory)";
        else if (grade >= 50) gradeLetter = "E (Pass)";
        else gradeLetter = "F (Fail)";
        
        std::cout << "| " << std::left << std::setw(8) << student.getRollNo() 
                  << " | " << std::setw(20) << student.getName() 
                  << " | " << std::setw(5) << grade 
                  << " | " << std::setw(15) << gradeLetter << " |" << std::endl;
    }
    
    std::cout << "+----------+----------------------+-------+-----------------+" << std::endl;
}

void StudentManagement::generateAttendanceReport() const {
    if (students.empty()) {
        UI::printInfo("No students found!");
        return;
    }
    
    UI::printTitle("Attendance Report");
    
    std::cout << "+----------+----------------------+------------+-----------------+" << std::endl;
    std::cout << "| " << Color::cyan << "Roll No" << Color::reset 
              << "   | " << Color::cyan << "Name" << Color::reset 
              << "                 | " << Color::cyan << "Attendance" << Color::reset 
              << " | " << Color::cyan << "Status" << Color::reset << "          |" << std::endl;
    std::cout << "+----------+----------------------+------------+-----------------+" << std::endl;
    
    for (const auto& student : students) {
        float attendance = student.getAttendance();
        std::string status;
        
        if (attendance >= 90) status = "Excellent";
        else if (attendance >= 80) status = "Good";
        else if (attendance >= 75) status = "Satisfactory";
        else status = "Low (Warning)";
        
        std::cout << "| " << std::left << std::setw(8) << student.getRollNo() 
                  << " | " << std::setw(20) << student.getName() 
                  << " | " << std::setw(10) << attendance << "% | " 
                  << std::setw(15) << status << " |" << std::endl;
    }
    
    std::cout << "+----------+----------------------+------------+-----------------+" << std::endl;
}

void StudentManagement::showTopPerformers(int count) const {
    if (students.empty()) {
        UI::printInfo("No students found!");
        return;
    }
    
    // Create a copy of students vector to sort
    std::vector<Student> sortedStudents = students;
    
    // Sort by grade in descending order
    std::sort(sortedStudents.begin(), sortedStudents.end(), [](const Student& a, const Student& b) {
        return a.getGrade() > b.getGrade();
    });
    
    // Take only the requested number of students
    count = std::min(static_cast<int>(sortedStudents.size()), count);
    
    UI::printTitle("Top " + std::to_string(count) + " Performers");
    
    std::cout << "+------+----------+----------------------+-------+------------+" << std::endl;
    std::cout << "| " << Color::cyan << "Rank" << Color::reset 
              << " | " << Color::cyan << "Roll No" << Color::reset 
              << "   | " << Color::cyan << "Name" << Color::reset 
              << "                 | " << Color::cyan << "Grade" << Color::reset 
              << " | " << Color::cyan << "Attendance" << Color::reset << " |" << std::endl;
    std::cout << "+------+----------+----------------------+-------+------------+" << std::endl;
    
    for (int i = 0; i < count; i++) {
        std::cout << "| " << std::left << std::setw(4) << (i + 1) 
                  << " | " << std::setw(8) << sortedStudents[i].getRollNo() 
                  << " | " << std::setw(20) << sortedStudents[i].getName() 
                  << " | " << std::setw(5) << sortedStudents[i].getGrade() 
                  << " | " << std::setw(10) << sortedStudents[i].getAttendance() << "% |" << std::endl;
    }
    
    std::cout << "+------+----------+----------------------+-------+------------+" << std::endl;
}

// I implemented these sorting and filtering functions to make data analysis easier
// Using C++ lambdas here made the code much cleaner and more maintainable
void StudentManagement::sortStudentsByName() {
    std::sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
        return a.getName() < b.getName();
    });
    
    UI::printSuccess("Students sorted by name.");
    displayAllStudents();
}

void StudentManagement::sortStudentsByGrade() {
    std::sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
        return a.getGrade() > b.getGrade();
    });
    
    UI::printSuccess("Students sorted by grade (descending).");
    displayAllStudents();
}

void StudentManagement::filterStudentsByAttendance(float minAttendance) const {
    UI::printTitle("Students with Attendance >= " + std::to_string(minAttendance) + "%");
    
    std::cout << "+----------------------+----------+-------+------------+" << std::endl;
    std::cout << "| " << Color::cyan << "Name" << Color::reset 
              << "                 | " << Color::cyan << "Roll No" << Color::reset 
              << "  | " << Color::cyan << "Grade" << Color::reset 
              << " | " << Color::cyan << "Attendance" << Color::reset << " |" << std::endl;
    std::cout << "+----------------------+----------+-------+------------+" << std::endl;
    
    int count = 0;
    for (const auto& student : students) {
        if (student.getAttendance() >= minAttendance) {
            student.display();
            count++;
        }
    }
    
    std::cout << "+----------------------+----------+-------+------------+" << std::endl;
    std::cout << "| Filtered students: " << std::left << std::setw(17) << count << " |" << std::endl;
    std::cout << "+----------------------+----------+-------+------------+" << std::endl;
}
