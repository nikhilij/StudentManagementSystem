#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <iostream>
#include <limits>
#include <regex>

// I added these ANSI color codes to make my CLI interface more attractive
// The colors help distinguish between different types of information and make the UI more user-friendly
namespace Color {
    const std::string reset = "\033[0m";   // Reset to default
    const std::string red = "\033[31m";     // Error messages
    const std::string green = "\033[32m";   // Success messages
    const std::string yellow = "\033[33m";  // Warnings
    const std::string blue = "\033[34m";    // Info messages
    const std::string magenta = "\033[35m"; // Special highlights
    const std::string cyan = "\033[36m";    // Titles and menu items
    const std::string bold = "\033[1m";     // Bold text for emphasis
}

// My custom UI utilities to make the console interface look professional
// I created these functions to have consistent formatting throughout the application
namespace UI {
    // Clears the terminal screen for a fresh display
    void clearScreen();
    
    // Creates a nicely formatted title with centered text
    void printTitle(const std::string& title);
    
    // Creates horizontal separator lines to divide sections of output
    void printSeparator(char symbol = '-', int length = 50);
    
    // Shows success messages in green for positive feedback
    void printSuccess(const std::string& message);
    
    // Shows error messages in red for better visibility
    void printError(const std::string& message);
    
    // Print a warning message
    void printWarning(const std::string& message);
    
    // Print an information message
    void printInfo(const std::string& message);
    
    // Wait for user input to continue
    void pressEnterToContinue();
}

// Input validation utilities
namespace Validation {
    // Get a valid integer input
    int getInteger(const std::string& prompt, int min = std::numeric_limits<int>::min(), 
                   int max = std::numeric_limits<int>::max());
    
    // Get a valid float input
    float getFloat(const std::string& prompt, float min = std::numeric_limits<float>::min(), 
                   float max = std::numeric_limits<float>::max());
    
    // Get a valid string input (non-empty)
    std::string getString(const std::string& prompt, bool allowEmpty = false);
    
    // Get a valid email input
    std::string getEmail(const std::string& prompt);
    
    // Get a valid phone number
    std::string getPhone(const std::string& prompt);

    // Check if string contains only alphanumeric characters
    bool isAlphanumeric(const std::string& str);

    // Check if string is a valid email address
    bool isValidEmail(const std::string& email);

    // Check if string is a valid phone number
    bool isValidPhone(const std::string& phone);
}

#endif // UTILS_H
