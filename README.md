# Enhanced Student Management System

## Overview
This is my enhanced version of a Student Management System that I developed to practice my C++ skills. It includes advanced features for managing students, courses, enrollments, and generating various reports. I built this application using a modular architecture and object-oriented programming principles to make the code clean and maintainable.

## Features
- **Student Management**
  - Add, update, delete, and search students
  - Store student details including name, roll number, grade, attendance, email, phone, and address
  
- **Course Management**
  - Add, update, delete, and search courses
  - Store course details including code, name, instructor, credits, and maximum capacity
  
- **Enrollment Management**
  - Enroll students in courses
  - Drop students from courses
  - View enrollment details for students and courses
  
- **Reporting**
  - Generate grade reports
  - Generate attendance reports
  - View top-performing students
  
- **Data Analysis**
  - Sort students by name
  - Sort students by grade
  - Filter students by attendance

- **User Interface**
  - Colorful, user-friendly terminal interface
  - Input validation
  - Clear menus and navigation

## Project Structure
- **include/** - Header files
  - Student.h - My implementation of the Student class
  - Course.h - My design for the Course management system
  - StudentManagement.h - My central controller class
  - Utils.h - My UI and validation utilities for better user experience
  
- **src/** - Implementation files
  - Student.cpp - My implementation of student-related functionality
  - Course.cpp - My course management system implementation
  - StudentManagement.cpp - My core business logic implementation
  - Utils.cpp - My UI and validation functions implementation
  - main.cpp - My main program with menu system
  
- **data/** - Data storage
  - students.csv - Student data
  - courses.csv - Course data
  - enrollments.csv - Enrollment relationships

## How to Build and Run
```
make
./StudentManagementSystem
```

## Requirements
- C++17 or higher
- ANSI terminal for color support

## Author
Developed by: Nikhil Soni  
Version: 2.0 (May 2025)
