#include <string>
#include <iostream>
#include <vector> 

// Function to remove multiple spaces from a string
// This function replaces multiple consecutive spaces with a single space
// and trims leading and trailing spaces.
// It returns the modified string.
// Example: "Hello   World" -> "Hello World"
std::string removeMultipleSpaces(const std::string& s) {
    std::string result;
    bool in_space = false;
    for (char c : s) {
        if (c == ' ') {
            if (!in_space) {
                result += c;
                in_space = true;
            }
        } else {
            result += c;
            in_space = false;
        }
    }
    // trim trailing space if needed
    if (!result.empty() && result.back() == ' ') result.pop_back();
    return result;
}