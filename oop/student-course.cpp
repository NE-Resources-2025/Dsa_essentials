#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>

using namespace std;

class Course {
    public:
    string courseName;
    bool available;

    Course(string name, bool avail) : courseName(name), available(avail) {}
};

class Student {
    public:
        string studentName;
        vector<string> courses;
        Student *next;

        Student(string name) : studentName(name), next(nullptr) {}
};

class LinkedList {
    private:
        Student *head;

    public:
    LinkedList() : head(nullptr) {}

    void addStudent(string name) {
        Student *newStudent = new Student(name);
        newStudent->next = head;
        head = newStudent;
    }

    Student* findStudent(string name) {
        Student *current = head;
        while (current != nullptr) {
            if (current->studentName == name) {
                return current;
            }
            current = current->next;
        }
        return nullptr;
    }

    void enrollStudentInCourse(string studentName, string courseName, vector<Course> &courseList) {
        Student *student = findStudent(studentName);
        if (student == nullptr) {
            cout << "Student not found\n";
            return;
        }

        for (auto& course : courseList) {
            if (course.courseName == courseName) {
                if (course.available) {
                    student->courses.push_back(courseName);
                    cout << "Student " << studentName << " enrolled in " << courseName << endl;
                } else {
                    cout << "Course " << courseName << " is not available.\n";
                }
                return;
            }
        }
        cout << "Course " << courseName << " doesn't exist here.\n";
    }

    void saveToCSV(string filename) {
        ofstream file;
        file.open(filename);

        file << "Student Name, Course Name\n";

        Student *current = head;
        
        while (current != nullptr) {
            for (const auto& course : current->courses) {
                file << current->studentName << ", " << course << "\n";
            }
            current = current->next;
        }
        file.close();
        }

    void loadFromCSV(string filename) {
        ifstream file(filename);
        string line, studentName, courseName;

        getline(file, line);

        while (getline(file, line)) {
            stringstream ss(line);
            getline(ss, studentName, ',');
            getline(ss, courseName, ',');

            Student* student = findStudent(studentName);
            if (student == nullptr) {
                addStudent(studentName);
                student = head;
            }
            student->courses.push_back(courseName);
        }
        file.close();
    }

        void displayList()
        {
            cout << left << setw(20) << "Student Name" << "Courses\n";
            cout << "--------------------------------------------------\n";

            Student *current = head;
            while (current != nullptr)
            {
                cout << left << setw(20) << current->studentName;

                for (size_t i = 0; i < current->courses.size(); ++i)
                {
                    if (i != 0)
                        cout << ", ";
                    cout << current->courses[i];
                }
                cout << "\n";
                current = current->next;
            }
        }

        void searchStudent(string studentName)
        {
            Student *student = findStudent(studentName);
            if (student == nullptr)
            {
                cout << "Student not found!\n";
            }
            else
            {
                cout << left << setw(20) << "Student Name" << "Courses\n";
                cout << "--------------------------------------------------\n";
                cout << left << setw(20) << student->studentName;
                for (size_t i = 0; i < student->courses.size(); ++i)
                {
                    if (i != 0)
                        cout << ", ";
                    cout << student->courses[i];
                }
                cout << "\n";
            }
        }
};

int main() {
    LinkedList studentList;

    // Load students from CSV
    studentList.loadFromCSV("students.csv");

    // Adding courses
    vector<Course> courseList = {
            Course("Math", true),
            Course("Physics", true),
            Course("Chemistry", false),
            Course("Java", true)
    };

    char option;
    do {
        cout << "\nOptions:\n";
        cout << "1. Display student list\n";
        cout << "2. Add student\n";
        cout << "3. Enroll student in course\n";
        cout << "4. Search for student\n";
        cout << "5. Exit\n";
        cout << "Choose an option: ";
        cin >> option;

        if (option == '1') {
            cout << "\nStudent Information:\n";
            studentList.displayList();
        } else if (option == '2') {
            string studentName;
            cout << "Enter student name: ";
            cin >> studentName;
            studentList.addStudent(studentName);
        } else if (option == '3') {
            string studentName, courseName;
            cout << "Enter student name: ";
            cin >> studentName;
            cout << "Enter course name to enroll " << studentName << " in: ";
            cin >> courseName;
            studentList.enrollStudentInCourse(studentName, courseName, courseList);
        } else if (option == '4') {
            string studentName;
            cout << "Enter student name to search: ";
            cin >> studentName;
            studentList.searchStudent(studentName);
        }

        // Save to CSV before exiting
        studentList.saveToCSV("students.csv");

    } while (option != '5');


    return 0;
}
