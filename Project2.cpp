// ProjectTwo.cpp
// ABCU Advising Assistance Program
// Reads course data from a CSV file into a hash table (unordered_map),
// then allows the user to list all courses or view details for a single course.

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <cctype>

using namespace std;

// ---------- Data Structures ----------

struct Course {
    string courseNumber;
    string courseName;
    vector<string> prerequisites;
};

// ---------- Utility Functions ----------

// Trim whitespace from both ends of a string
static string trim(const string& s) {
    size_t start = s.find_first_not_of(" \t\r\n");
    if (start == string::npos) return "";
    size_t end = s.find_last_not_of(" \t\r\n");
    return s.substr(start, end - start + 1);
}

// Convert a string to uppercase
static string toUpper(const string& s) {
    string result = s;
    for (char& c : result) {
        c = toupper(static_cast<unsigned char>(c));
    }
    return result;
}

// ---------- Core Functionality ----------

// Load course data from CSV file into hash table.
// Returns true on success, false if file cannot be opened.
bool loadCourses(const string& filename,
                 unordered_map<string, Course>& courses)
{
    ifstream infile(filename);
    if (!infile.is_open()) {
        cerr << "Error: Unable to open file \"" << filename << "\".\n";
        return false;
    }

    courses.clear();

    string line;
    while (getline(infile, line)) {
        if (trim(line).empty())
            continue;  // skip empty lines

        // Parse CSV tokens
        vector<string> tokens;
        istringstream ss(line);
        string token;
        while (getline(ss, token, ',')) {
            tokens.push_back(trim(token));
        }
        if (tokens.size() < 2) {
            cerr << "Error: Invalid format in line: " << line << "\n";
            continue;
        }

        // Build Course object
        Course c;
        c.courseNumber = toUpper(tokens[0]);
        c.courseName   = tokens[1];
        for (size_t i = 2; i < tokens.size(); ++i) {
            if (!tokens[i].empty())
                c.prerequisites.push_back(toUpper(tokens[i]));
        }

        // Insert into hash table
        courses[c.courseNumber] = c;
    }

    infile.close();

    // Validate prerequisites
    for (auto& pair : courses) {
        for (const string& p : pair.second.prerequisites) {
            if (courses.find(p) == courses.end()) {
                cerr << "Warning: Prerequisite " << p
                     << " for course " << pair.first
                     << " not found in data.\n";
            }
        }
    }

    return true;
}

// Print all courses in alphanumeric order
void printCourseList(const unordered_map<string, Course>& courses) {
    if (courses.empty()) {
        cout << "No course data loaded.\n";
        return;
    }
    // Extract keys and sort
    vector<string> keys;
    keys.reserve(courses.size());
    for (auto const& kv : courses) {
        keys.push_back(kv.first);
    }
    sort(keys.begin(), keys.end());

    cout << "\nHere is a course list:\n\n";
    for (auto const& code : keys) {
        const Course& c = courses.at(code);
        cout << c.courseNumber << ", " << c.courseName << "\n";
    }
    cout << "\n";
}

// Print details for a single course
void printCourseDetails(const unordered_map<string, Course>& courses) {
    cout << "What course do you want to know about? ";
    string input;
    getline(cin, input);
    string code = toUpper(trim(input));

    auto it = courses.find(code);
    if (it == courses.end()) {
        cout << code << " not found.\n\n";
        return;
    }

    const Course& c = it->second;
    cout << "\n" << c.courseNumber << ", " << c.courseName << "\n";
    cout << "Prerequisites: ";
    if (c.prerequisites.empty()) {
        cout << "None\n\n";
    } else {
        for (size_t i = 0; i < c.prerequisites.size(); ++i) {
            const string& pre = c.prerequisites[i];
            cout << pre;
            if (i + 1 < c.prerequisites.size()) cout << ", ";
        }
        cout << "\n\n";
    }
}

// ---------- Main Menu ----------

int main() {
    cout << "Welcome to the course planner.\n";

    unordered_map<string, Course> courses;
    bool loaded = false;

    while (true) {
        // Display menu
        cout << "\n1. Load Data Structure.\n"
             << "2. Print Course List.\n"
             << "3. Print Course.\n"
             << "9. Exit.\n\n"
             << "What would you like to do? ";

        string choice_line;
        getline(cin, choice_line);
        int choice = 0;
        try {
            choice = stoi(choice_line);
        } catch (...) {
            choice = -1;
        }

        switch (choice) {
            case 1: {
                cout << "Enter filename: ";
                string filename;
                getline(cin, filename);
                if (loadCourses(filename, courses)) {
                    loaded = true;
                    cout << "Data loaded successfully.\n";
                }
                break;
            }
            case 2:
                if (!loaded) {
                    cout << "Please load data first.\n";
                } else {
                    printCourseList(courses);
                }
                break;

            case 3:
                if (!loaded) {
                    cout << "Please load data first.\n";
                } else {
                    printCourseDetails(courses);
                }
                break;

            case 9:
                cout << "Thank you for using the course planner!\n";
                return 0;

            default:
                cout << choice_line << " is not a valid option.\n";
                break;
        }
    }

    return 0;
}
