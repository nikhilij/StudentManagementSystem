#include "../include/Utils.h"
#include <iostream>
#include <stdlib.h>

// I created these UI helper functions to make my CLI interface look more professional
// The clearScreen function works cross-platform (Windows and Linux/Mac)
void UI::clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void UI::printTitle(const std::string& title) {
    int padding = (50 - title.length()) / 2;
    std::cout << Color::cyan << Color::bold;
    printSeparator('=', 50);
    std::cout << std::string(padding, ' ') << title << std::endl;
    printSeparator('=', 50);
    std::cout << Color::reset << std::endl;
}

void UI::printSeparator(char symbol, int length) {
    std::cout << std::string(length, symbol) << std::endl;
}

void UI::printSuccess(const std::string& message) {
    std::cout << Color::green << "[SUCCESS] " << message << Color::reset << std::endl;
}

void UI::printError(const std::string& message) {
    std::cout << Color::red << "[ERROR] " << message << Color::reset << std::endl;
}

void UI::printWarning(const std::string& message) {
    std::cout << Color::yellow << "[WARNING] " << message << Color::reset << std::endl;
}

void UI::printInfo(const std::string& message) {
    std::cout << Color::blue << "[INFO] " << message << Color::reset << std::endl;
}

void UI::pressEnterToContinue() {
    std::cout << "\nPress Enter to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

// Input validation functions
int Validation::getInteger(const std::string& prompt, int min, int max) {
    int value;
    bool valid = false;
    
    do {
        std::cout << prompt;
        std::cin >> value;
        
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << Color::red << "Invalid input. Please enter an integer." << Color::reset << std::endl;
        } else if (value < min || value > max) {
            std::cout << Color::red << "Value must be between " << min << " and " << max << "." << Color::reset << std::endl;
        } else {
            valid = true;
        }
    } while (!valid);
    
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return value;
}

float Validation::getFloat(const std::string& prompt, float min, float max) {
    float value;
    bool valid = false;
    
    do {
        std::cout << prompt;
        std::cin >> value;
        
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << Color::red << "Invalid input. Please enter a number." << Color::reset << std::endl;
        } else if (value < min || value > max) {
            std::cout << Color::red << "Value must be between " << min << " and " << max << "." << Color::reset << std::endl;
        } else {
            valid = true;
        }
    } while (!valid);
    
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return value;
}

std::string Validation::getString(const std::string& prompt, bool allowEmpty) {
    std::string value;
    bool valid = false;
    
    do {
        std::cout << prompt;
        std::getline(std::cin, value);
        
        if (!allowEmpty && value.empty()) {
            std::cout << Color::red << "Input cannot be empty." << Color::reset << std::endl;
        } else {
            valid = true;
        }
    } while (!valid);
    
    return value;
}

std::string Validation::getEmail(const std::string& prompt) {
    std::string email;
    bool valid = false;
    
    do {
        std::cout << prompt;
        std::getline(std::cin, email);
        
        if (email.empty()) {
            std::cout << Color::yellow << "Email is optional. Leaving blank." << Color::reset << std::endl;
            return "";
        } else if (!isValidEmail(email)) {
            std::cout << Color::red << "Invalid email format." << Color::reset << std::endl;
        } else {
            valid = true;
        }
    } while (!valid);
    
    return email;
}

std::string Validation::getPhone(const std::string& prompt) {
    std::string phone;
    bool valid = false;
    
    do {
        std::cout << prompt;
        std::getline(std::cin, phone);
        
        if (phone.empty()) {
            std::cout << Color::yellow << "Phone is optional. Leaving blank." << Color::reset << std::endl;
            return "";
        } else if (!isValidPhone(phone)) {
            std::cout << Color::red << "Invalid phone number format." << Color::reset << std::endl;
        } else {
            valid = true;
        }
    } while (!valid);
    
    return phone;
}

bool Validation::isAlphanumeric(const std::string& str) {
    return std::all_of(str.begin(), str.end(), [](char c) {
        return std::isalnum(c) || std::isspace(c);
    });
}

bool Validation::isValidEmail(const std::string& email) {
    // Simple email validation regex
    const std::regex pattern("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");
    return std::regex_match(email, pattern);
}

bool Validation::isValidPhone(const std::string& phone) {
    // Simple phone validation - allowing digits, spaces, dashes, parentheses
    const std::regex pattern("[\\d\\s\\-\\(\\)]+");
    return std::regex_match(phone, pattern) && phone.length() >= 6;
}
