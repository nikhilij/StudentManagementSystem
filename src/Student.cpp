#include "../include/Student.h"
#include "../include/Course.h"

// I've implemented two constructors here - one simple and one with all details
// This approach gives me flexibility when creating student objects
Student::Student(std::string n, int r, float g, float a) 
    : id(0), name(n), rollNo(r), grade(g), attendance(a), 
      email(""), phone(""), address("") {}

Student::Student(int id, std::string n, int r, float g, float a, 
                 std::string email, std::string phone, std::string address)
    : id(id), name(n), rollNo(r), grade(g), attendance(a), 
      email(email), phone(phone), address(address) {}

// My getter methods - I'm using const qualifiers to ensure these don't modify the object
// This is a good practice I learned to maintain data integrity
int Student::getId() const { return id; }
std::string Student::getName() const { return name; }
int Student::getRollNo() const { return rollNo; }
float Student::getGrade() const { return grade; }
float Student::getAttendance() const { return attendance; }
std::string Student::getEmail() const { return email; }
std::string Student::getPhone() const { return phone; }
std::string Student::getAddress() const { return address; }
std::vector<Course*> Student::getEnrolledCourses() const { return enrolledCourses; }

// Setter implementations
void Student::setId(int id) { this->id = id; }
void Student::setName(std::string n) { name = n; }
void Student::setRollNo(int r) { rollNo = r; }

void Student::setGrade(float g) {
    if (g >= 0 && g <= 100)
        grade = g;
    else
        std::cout << "Invalid grade! Must be between 0 and 100." << std::endl;
}

void Student::setAttendance(float a) {
    if (a >= 0 && a <= 100)
        attendance = a;
    else
        std::cout << "Invalid attendance! Must be between 0 and 100." << std::endl;
}

void Student::setEmail(std::string email) { this->email = email; }
void Student::setPhone(std::string phone) { this->phone = phone; }
void Student::setAddress(std::string address) { this->address = address; }

// Course management methods
void Student::enrollCourse(Course* course) {
    if (!isEnrolledIn(course)) {
        enrolledCourses.push_back(course);
    }
}

void Student::dropCourse(Course* course) {
    for (auto it = enrolledCourses.begin(); it != enrolledCourses.end(); ++it) {
        if (*it == course) {
            enrolledCourses.erase(it);
            return;
        }
    }
}

bool Student::isEnrolledIn(Course* course) const {
    for (const auto& c : enrolledCourses) {
        if (c == course) {
            return true;
        }
    }
    return false;
}

// Display methods
void Student::display() const {
    std::cout << "| " << std::left << std::setw(20) << name << " | "
              << std::setw(8) << rollNo << " | "
              << std::setw(5) << grade << " | "
              << std::setw(10) << attendance << "% |" << std::endl;
}

void Student::displayDetailed() const {
    std::cout << "+----------------------------------+\n";
    std::cout << "| Student Details                  |\n";
    std::cout << "+----------------------------------+\n";
    std::cout << "| ID        : " << std::left << std::setw(23) << id << " |\n";
    std::cout << "| Name      : " << std::left << std::setw(23) << name << " |\n";
    std::cout << "| Roll No   : " << std::left << std::setw(23) << rollNo << " |\n";
    std::cout << "| Grade     : " << std::left << std::setw(23) << grade << " |\n";
    std::cout << "| Attendance: " << std::left << std::setw(22) << attendance << "% |\n";
    std::cout << "| Email     : " << std::left << std::setw(23) << email << " |\n";
    std::cout << "| Phone     : " << std::left << std::setw(23) << phone << " |\n";
    std::cout << "| Address   : " << std::left << std::setw(23) << address << " |\n";
    std::cout << "+----------------------------------+\n";
    
    if (!enrolledCourses.empty()) {
        std::cout << "| Enrolled Courses:                |\n";
        std::cout << "+----------------------------------+\n";
        for (const auto& course : enrolledCourses) {
            std::cout << "| " << std::left << std::setw(32) << course->getCode() + " - " + course->getName() << " |\n";
        }
        std::cout << "+----------------------------------+\n";
    }
}

void Student::displayAttendance() const {
    std::cout << "| " << std::left << std::setw(8) << rollNo 
              << " | " << std::setw(20) << name 
              << " | " << std::setw(10) << attendance << "% |" << std::endl;
}

std::string Student::toCSV() const {
    return std::to_string(id) + "," +
           name + "," +
           std::to_string(rollNo) + "," +
           std::to_string(grade) + "," +
           std::to_string(attendance) + "," +
           email + "," +
           phone + "," +
           address;
}
