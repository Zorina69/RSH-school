#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <string>
using namespace std;

class Student {
private:
    string id;

public:
    string name;
    int age;
    string gender;
    string email;

    void inputDetails() {
        cout << "Enter your name: ";
        cin.ignore();
        getline(cin, name);

        cout << "Enter your gender: ";
        getline(cin, gender);

        cout << "Enter your email: ";
        getline(cin, email);

        cout << "Enter your age: ";
        cin >> age;
    }

    void displaySchoolName() {
        cout << "******************************" << endl;
        cout << "*     Simple Coding Club    *" << endl;
        cout << "******************************" << endl;
    }

    void enroll() {
        cout << "Our school offers the following programming languages:\n";
        string subjects[] = {"C++", "Python", "HTML/CSS/JavaScript", "Java"};
        for (const string &subject : subjects) {
            cout << "- " << subject << endl;
        }

        cout << "\nEnter your choice: ";
        string choice;
        cin >> choice;

        ofstream file;
        string filename;

        if (choice == "C++") {
            filename = "cpp_students.txt";
        } else if (choice == "Python") {
            filename = "python_students.txt";
        } else if (choice == "HTML" || choice == "HTML/CSS/JavaScript") {
            filename = "html_students.txt";
        } else if (choice == "Java") {
            filename = "java_students.txt";
        } else {
            cout << "Invalid choice!" << endl;
            return;
        }

        inputDetails();

        file.open(filename, ios::app);
        if (file.is_open()) {
            file << left << setw(20) << "Name: " << name
                 << setw(15) << " Gender: " << gender
                 << setw(25) << " Email: " << email
                 << setw(10) << " Age: " << age << endl;
            file.close();
            cout << "Enrollment successful!" << endl;
        } else {
            cout << "Failed to open file!" << endl;
        }
    }
};

void displayMenu() {
    cout << "1. View School Information\n";
    cout << "2. Enroll in a Course\n";
    cout << "3. Exit\n";
}

int main() {
    Student student;
    int choice;

    while (true) {
        system("cls"); // Clear screen
        student.displaySchoolName();
        displayMenu();

        cout << "\nEnter your choice: ";
        cin >> choice;

        system("cls");

        switch (choice) {
        case 1:
            student.displaySchoolName();
            cout << "Welcome to Simple Coding Club!" << endl;
            break;
        case 2:
            student.displaySchoolName();
            student.enroll();
            break;
        case 3:
            cout << "Exiting... Goodbye!" << endl;
            return 0;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }

        cout << "\nPress Enter to return to the menu...";
        cin.ignore();
        cin.get();
    }

    return 0;
}
