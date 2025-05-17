#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>

using namespace std;

class Student
{
private:
    string name;
    int rollNo;
    float grade;
    float attendance;

public:
    // constructor
    Student(string n = "", int r = 0, float g = 0.0, float a = 0.0) : name(n), rollNo(r), grade(g), attendance(a) {}

    // getters
    string getName() const { return name; }
    int getRollNo() const { return rollNo; }
    float getGrade() const { return grade; }
    float getAttendance() const { return attendance; }

    // setters with validation
    void setName(string n) { name = n; }
    void setRollNo(int r) { rollNo = r; }
    void setGrade(float g)
    {
        if (g >= 0 && g <= 100)
            grade = g;
        else
            cout << "Invalid grade! Must be between 0 and 100." << endl;
    }
    void setAttendance(float a)
    {
        if (a >= 0 && a <= 100)
            attendance = a;
        else
            cout << "Invalid attendance! Must be between 0 and 100." << endl;
    }

    // displaying student details
    void display() const
    {
        cout << "| " << left << setw(20) << name << " | "
             << setw(8) << rollNo << " | "
             << setw(5) << grade << " | "
             << setw(10) << attendance << "% |" << endl;
    }
};

class StudentManagment
{
private:
    vector<Student> students;
    const string filename = "students.txt";

    bool isRollNoUnique(int rollNo)
    {
        for (const auto &student : students)
        {
            if (student.getRollNo() == rollNo)
            {
                return false;
            }
        }
        return true;
    }

    // I created this function to save student data to a file
// This ensures data persistence between program runs
    void saveToFile() const
    {
        ofstream outFile(filename);
        if (!outFile)
        {
            cout << "Error opening file for writing!" << endl;
            return;
        }

        // I decided to write student data directly without headers for simplicity
        // This format is easier to parse when reading back
        for (const auto &student : students)
        {
            outFile << student.getName() << endl
                   << student.getRollNo() << " "
                   << student.getGrade() << " " 
                   << student.getAttendance() << endl;
        }
        outFile.close();
    }
    void loadFromFile()
    {
        ifstream inFile(filename);
        if (!inFile)
        {
            cout << "No existing data file found. Starting fresh.\n";
            return;
        }
        students.clear();
        string name;
        int rollNo;
        float grade, attendance;
        
        while (getline(inFile, name))
        {
            if (inFile >> rollNo >> grade >> attendance) 
            {
                inFile.ignore(); // Ignore the newline character after attendance
                Student student(name, rollNo, grade, attendance);
                students.emplace_back(student);
            }
        }
        inFile.close();
    }

public:
    StudentManagment()
    {
        loadFromFile();
    }

    // add a new student
    void addStudent()
    {
        string name;
        int rollNo;
        float grade, attendance;

        cout << "Enter student name: ";
        cin.ignore(1, '\n'); // clear the input buffer
        getline(cin, name);
        cout << "Enter roll number: ";
        cin >> rollNo;

        // Check if roll number is unique
        while (!isRollNoUnique(rollNo))
        {
            cout << "Roll number already exists! Enter a unique roll number: ";
            cin >> rollNo;
        }

        cout << "Enter grade (0-100): ";
        cin >> grade;
        cout << "Enter attendance (0-100%): ";
        cin >> attendance;

        Student student(name, rollNo, grade, attendance);
        students.push_back(student);
        saveToFile();
        cout << "Student added successfully!" << endl;
    }

    // display all students
    void displayAll() const
    {
        if (students.empty())
        {
            cout << "No students found!" << endl;
            return;
        }
        cout << "+----------------------+----------+-------+------------+" << endl;
        cout << "| Name                 | Roll No  | Grade | Attendance |" << endl;
        cout << "+----------------------+----------+-------+------------+" << endl;
        for (const auto &student : students)
        {
            student.display();
        }
        cout << "+----------------------+----------+-------+------------+" << endl;
    }

    void searchStudent(int rollNo) const
    {
        for (const auto &student : students)
        {
            if (student.getRollNo() == rollNo)
            {
                student.display();
                return;
            }
        }
        cout << "Student with roll number " << rollNo << " not found!" << endl;
    }

    void updateStudent(int rollNo)
    {
        for (auto &student : students)
        {
            if (student.getRollNo() == rollNo)
            {
                string name;
                float grade, attendance;
                cout << "Enter new name: ";
                cin.ignore(1, '\n');
                getline(cin, name);
                cout << "Enter new grade (0-100): ";
                cin >> grade;
                cout << "Enter new attendance (0-100%): ";
                cin >> attendance;

                student.setName(name);
                student.setGrade(grade);
                student.setAttendance(attendance);
                saveToFile();
                cout << "Student updated successfully!" << endl;
                return;
            }
        }
        cout << "Student with roll number " << rollNo << " not found!" << endl;
    }
    // delete a student
    void deleteStudent(int rollNo)
    {
        auto it = remove_if(students.begin(), students.end(),
                            [rollNo](const Student &s)
                            {
                                {
                                    return s.getRollNo() == rollNo;
                                }
                            });
        if (it != students.end())
        {
            students.erase(it, students.end());
            saveToFile();
            cout << "Student with roll number " << rollNo << " deleted successfully!" << endl;
        }
        else
        {
            cout << "Student with roll number " << rollNo << " not found!" << endl;
        }
    }
};

int main()
{
    StudentManagment sm;
    int choice;
    do
    {
        cout << "\n===== Student Management System =====\n";
        cout << "1. Add Student\n";
        cout << "2. Display All Students\n";
        cout << "3. Search Student by Roll Number\n";
        cout << "4. Update Student\n";
        cout << "5. Delete Student\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            sm.addStudent();
            break;
        case 2:
            sm.displayAll();
            break;
        case 3:
        {
            int rollNo;
            cout << "Enter roll number to search: ";
            cin >> rollNo;
            sm.searchStudent(rollNo);
            break;
        }
        case 4:
        {
            int rollNo;
            cout << "Enter roll number to update: ";
            cin >> rollNo;
            sm.updateStudent(rollNo);
            break;
        }
        case 5:
        {
            int rollNo;
            cout << "Enter roll number to delete: ";
            cin >> rollNo;
            sm.deleteStudent(rollNo);
            break;
        }
        case 0:
            cout << "Exiting the program." << endl;
            break;
        default:
            cout << "Invalid choice! Please try again." << endl;
        }
    } while (choice != 0);
    return 0;
};