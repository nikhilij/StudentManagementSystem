#include "../include/Course.h"
#include "../include/Student.h"

// I designed these Course constructors to be flexible for different initialization scenarios
// The first constructor is for when I don't have an ID yet (new courses)
Course::Course(std::string code, std::string name, std::string instructor, 
               int credits, int maxCapacity)
    : id(0), code(code), name(name), instructor(instructor), 
      credits(credits), maxCapacity(maxCapacity) {}

Course::Course(int id, std::string code, std::string name, std::string instructor, 
               int credits, int maxCapacity)
    : id(id), code(code), name(name), instructor(instructor), 
      credits(credits), maxCapacity(maxCapacity) {}

// Getter implementations
int Course::getId() const { return id; }
std::string Course::getCode() const { return code; }
std::string Course::getName() const { return name; }
std::string Course::getInstructor() const { return instructor; }
int Course::getCredits() const { return credits; }
int Course::getMaxCapacity() const { return maxCapacity; }
int Course::getCurrentEnrollment() const { return enrolledStudents.size(); }
std::vector<Student*> Course::getEnrolledStudents() const { return enrolledStudents; }

// Setter implementations
void Course::setId(int id) { this->id = id; }
void Course::setCode(std::string code) { this->code = code; }
void Course::setName(std::string name) { this->name = name; }
void Course::setInstructor(std::string instructor) { this->instructor = instructor; }
void Course::setCredits(int credits) { this->credits = credits; }
void Course::setMaxCapacity(int maxCapacity) { this->maxCapacity = maxCapacity; }

// Student management methods
bool Course::addStudent(Student* student) {
    if (isFull() || hasStudent(student)) {
        return false;
    }
    enrolledStudents.push_back(student);
    return true;
}

bool Course::removeStudent(Student* student) {
    for (auto it = enrolledStudents.begin(); it != enrolledStudents.end(); ++it) {
        if (*it == student) {
            enrolledStudents.erase(it);
            return true;
        }
    }
    return false;
}

bool Course::isFull() const {
    return static_cast<int>(enrolledStudents.size()) >= maxCapacity;
}

bool Course::hasStudent(Student* student) const {
    for (const auto& s : enrolledStudents) {
        if (s == student) {
            return true;
        }
    }
    return false;
}

// Display methods
void Course::display() const {
    std::cout << "| " << std::left << std::setw(10) << code << " | "
              << std::setw(25) << name << " | "
              << std::setw(20) << instructor << " | "
              << std::setw(7) << credits << " | "
              << std::right << std::setw(3) << enrolledStudents.size() << "/"
              << std::left << std::setw(3) << maxCapacity << " |" << std::endl;
}

void Course::displayDetailed() const {
    std::cout << "+----------------------------------+\n";
    std::cout << "| Course Details                   |\n";
    std::cout << "+----------------------------------+\n";
    std::cout << "| ID        : " << std::left << std::setw(23) << id << " |\n";
    std::cout << "| Code      : " << std::left << std::setw(23) << code << " |\n";
    std::cout << "| Name      : " << std::left << std::setw(23) << name << " |\n";
    std::cout << "| Instructor: " << std::left << std::setw(23) << instructor << " |\n";
    std::cout << "| Credits   : " << std::left << std::setw(23) << credits << " |\n";
    std::cout << "| Capacity  : " << std::left << std::setw(23) << enrolledStudents.size() << "/" << maxCapacity << " |\n";
    std::cout << "+----------------------------------+\n";
}

void Course::displayEnrollmentList() const {
    std::cout << "+----------------------------------+\n";
    std::cout << "| " << code << " - " << name << " Enrollment List |\n";
    std::cout << "+----------------------------------+\n";
    std::cout << "| Roll No   | Student Name         |\n";
    std::cout << "+----------------------------------+\n";
    for (const auto& student : enrolledStudents) {
        std::cout << "| " << std::setw(9) << student->getRollNo() << " | " 
                  << std::setw(20) << student->getName() << " |\n";
    }
    std::cout << "+----------------------------------+\n";
    std::cout << "| Total Enrolled: " << std::setw(17) << enrolledStudents.size() << " |\n";
    std::cout << "+----------------------------------+\n";
}

std::string Course::toCSV() const {
    return std::to_string(id) + "," +
           code + "," +
           name + "," +
           instructor + "," +
           std::to_string(credits) + "," +
           std::to_string(maxCapacity);
}
