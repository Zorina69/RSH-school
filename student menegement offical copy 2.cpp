#include <iostream>
#include <iomanip>
#include <unistd.h>  /* sleep mode */
#include <string>
#include <fstream>
#include <list>
#include <conio.h> // Windows-specific; use `getch()` for Linux
#include <algorithm> // Convert the user input to lowercase
#include <cstdlib>    // For rand()
#include <cstdio>     // For remove() and rename()
using namespace std;

class Student {
private:
    string id;

public:
    Student* next;
    string name;
    int age;
    string gender;
    string email;

    string getId() {
        return id;
    }

    Student(string id = "RSH_0", string name = "Unknown", int age = 0, string gender = "Unknown", string email = "N/A") {
        this->id = id;
        this->name = name;
        this->age = age;
        this->gender = gender;
        this->email = email;
        next = nullptr; // Initialize next to nullptr
    }

    void input_username_age_gender_email() {
        cout << "\n\nEnter your name: ";
        cin.ignore();
        getline(cin, name);

        cout << "Enter your gender: ";
        getline(cin, gender);

        cout << "Enter your email: ";
        getline(cin, email);

        cout << "Enter your age: ";
        cin >> age;
    }

    void displayStudent_info() const {
        cout << setw(30) << name << setw(15) << gender << setw(40) << email << age << endl;
    }
};

class SchoolSystem {
private:
    Student* studentQueueFront = nullptr;
    Student* studentQueueRear = nullptr;
    list<Student> studentList;
    string schoolName;
    int schoolID;
    string schoolAddress;
    string schoolYear;

    string generateRandomID() {
        string id = "S";
        for (int i = 0; i < 4; ++i) {
            id += to_string(rand() % 10); // Append a random digit (0-9)
        }
        return id;
    }

    bool idExistsInFile(const string& id, string filename) {
        ifstream file(filename);
        string existingId;
        while (file >> existingId) {
            if (existingId == id) {
                return true;
            }
        }
        return false;
    }
     string generateAndSaveID(string filename) {
        string newId;
        
        do {
            newId = generateRandomID();
        } while (idExistsInFile(newId, filename));
        return newId;
    }
    
    

public:
   

    void showLoadingScreen() {
        for (int i = 0; i < 5; i++) {
            cout << "Loading";
            for (int j = 0; j < i; j++) {
                cout << ".";
            }
            cout << "\r";  // Carriage return to overwrite the previous line
            sleep(1);
        }
        cout << endl;
    }

    void display_school_name() {
        cout << left << setw(50) << "" << "******************************" << endl;
        cout << left << setw(50) << "" << " *     RSH Coding Club      *" << endl;
        cout << left << setw(50) << "" << "******************************" << endl;
    }


void writeToFile() {
    ofstream outFile("Information.txt");  
    
    if (!outFile.is_open()) {
        cout << "\n===========================================\n";
        cout << "    Error: Cannot open Information.txt file for writing.\n";
        cout << "===========================================\n";
        return;
    }

    
    outFile << "RSH School offers great subjects for learning.\n";
    outFile << "Subjects: C++, Python, Java, HTML, CSS, JavaScript\n";
    outFile << "Our motto is: Teachers of Tomorrow, Students Today.\n";

    outFile.close();  
    cout << "File written successfully!\n";
}

    void displaySubjects() {
    
    ofstream outFile("offered_subjects.txt");

    
    if (!outFile) {
        cout << "Error opening file!" << endl;
        return;
    }

    cout << "\033[1;36m"; 
    cout << "=====================================" << endl;
    cout << "    RSH School - Coding Classes    " << endl;
    cout << "=====================================" << endl;
    cout << "\033[0m";  

  
    cout << endl;
    cout << "\033[1;32m"; 
    cout << "+-------------------------------------+" << endl;
    cout << "|          Offered Subjects:         |" << endl;
    cout << "+-------------------------------------+" << endl;
    cout << "\033[0m";  

    
    string subjects[] = {"C++", "Python", "Java", "HTML, CSS, JavaScript"};

  
    for (const string& subject : subjects) {
        cout << "|  " << setw(30) << left << subject << " |" << endl;
        outFile << subject << endl;  
    }

    
    cout << "\033[1;32m"; 
    cout << "+-------------------------------------+" << endl;
    cout << "\033[0m";  

    
    cout << endl;

    cout << "\033[1;33m";  
    cout << "The list of subjects has been saved to 'offered_subjects.txt'." << endl;
    cout << "\033[0m";  

    // Close the file
    outFile.close();
}

void displayHistory() {
    // Display the history of the school
    cout << "\033[1;35m";  // Purple text color
    cout << "=====================================" << endl;
    cout << "    History of RSH School           " << endl;
    cout << "=====================================" << endl;
    cout << "\033[0m";  

    cout << "\nRSH stands for ROTH, PISEY, and HOUR. These three founders have "
         << "worked together to create an outstanding coding school, empowering "
         << "students with the skills they need to succeed in the tech industry.\n\n";

    cout << "\033[1;33m";  
    cout << "RSH School is committed to providing high-quality programming education "
         << "in languages like C++, Python, Java, and web development technologies like "
         << "HTML, CSS, and JavaScript.\n\n";
    cout << "\033[0m";  
}



    void write_first_2_line_to_file() {
        string colection_file[4] = { "cpp_students_file.csv", "python_students_file.csv", "java_students_file.csv", "HtmlCssJavascrpit_students_file.csv" };
        
        string iD_each_subject[4] = { "RSHCPP-", "RSHHCJ-", "RSHJAV-", "RSHPYT-" };
        for (int i = 0; i < 4; i++) {

            fstream filename;
            filename.open(colection_file[i], ios::in | ios::out | ios::app);

            if (!filename) {
                cout << colection_file[i] << " is not found!" << endl;
                continue;
            }
            filename.seekg(0, ios::end);
            if (filename.tellg() == 0) {

                filename<<"///"<<"Security code: RSH_FOR_ADMIN_ACESS"<<endl
                << "=============================================================" << colection_file[i]<<endl
                    << left << "ID" << "(" << iD_each_subject[i] << setw(20) << ") :"
                    << setw(30) << "NAME:"
                    << setw(15) << "GENDER:"
                    << setw(40) << "EMAIL:"
                    << "AGE:"
                    << endl;
            }
            filename.close();
        }
    }

    
    void push(Student student) {
        if (studentQueueRear == nullptr) {
            studentQueueFront = studentQueueRear = &student;
        } else {
            studentQueueRear->next = &student;
            studentQueueRear = studentQueueRear->next;
        }
    }

    
    Student pop() {
        if (studentQueueFront == nullptr) {
            throw runtime_error("Queue is empty.");
        }
        Student frontStudent = *studentQueueFront;
        studentQueueFront = studentQueueFront->next;
        if (studentQueueFront == nullptr) {
            studentQueueRear = nullptr;
        }
        return frontStudent;
    }

    
    void processEnrollments() {
        while (studentQueueFront != nullptr) {
            Student student = pop();
            studentList.push_back(student);
            cout << "\nProcessed enrollment for: " << student.name << "\n";
        }
    }

    void Openfile(const Student& student, const string& filename) { 
        fstream write_to_file(filename, ios::out | ios::app);
        if (!write_to_file.is_open()) {
            cerr << "Can't open the file: " << filename << endl;
            return;
        }

        // Generate the ID once here
        string studentID = generateAndSaveID(filename);

        write_to_file << left
            << setw(30) << studentID
            << setw(30) << student.name
            << setw(15) << student.gender
            << setw(40) << student.email
            << student.age << endl;

        cout << "Student details saved to " << filename << " successfully!\n";
    }

    void ynQuestion_ForConfirm_inStudying(string filename) {
        char confirmation;
        cout << "Press  (y/n) to confirm: ";
        cin >> confirmation;
        confirmation = tolower(confirmation);

        // Generate the ID once here
        string studentID = generateAndSaveID(filename);

        if (confirmation == 'y') {
            processEnrollments();
        }
        else {
            pop();  // Remove from queue
            cout << "Student enrollment canceled.\n";
        }
    }

    void displayList_EachSub(string filename) {
        if (studentList.empty()) {
            cout << "No students are enrolled yet.\n";
            return;
        }
        cout << "\033[31m";
        cout << string(115, '-') << endl;
        cout << left << setw(20) << "ID:" << setw(30) << "NAME:" << setw(15) << "GENDER:" << setw(40) << "EMAIL:" << "AGE:" << endl;
        cout << string(115, '-') << endl;
        cout << "\033[0m";
        for (const auto& student : studentList) {
            cout << "|" << left << setw(20) << generateAndSaveID(filename);
            student.displayStudent_info();
        }
    }

    void Enrollment() {
        cout << "Our school provides students 4 programming language choices:\n\n";
        string Subjects[4] = { "C++", "Python", "Html,Css,Javascript", "Java" };
        for (int i = 0; i < 4; i++) {
            cout << Subjects[i] << endl;
        }
        string choice;
        cout << "\n\nEnter your choice :";
        cin >> choice;

        // Convert the user input to lowercase
        transform(choice.begin(), choice.end(), choice.begin(), ::tolower);
        if (choice == "c++") {

            fstream cpp_students_file;
            cpp_students_file.open("cpp_students_file.csv", ios::in | ios::out | ios::app);

            if (!cpp_students_file) {
                cout << "cpp_students_file is not found!" << endl;
                return;
            }

            Student newStudent;
            newStudent.input_username_age_gender_email();
            system("cls");
            push(newStudent);
            cpp_students_file.close();

            cout << "\nYou just finished inputting your information" << endl;
            string filename = "cpp_students_file.csv";
            ynQuestion_ForConfirm_inStudying(filename);
            Openfile(newStudent, filename);
            cout << "\n\n" << endl;
            displayList_EachSub(filename);
        }
        // Handle the rest of the cases (python, html, javascript, java) similarly as in your original code...
         else if(choice =="python") {
                
                
                fstream python_students_file;
                python_students_file.open("python_students_file.csv", ios::in | ios::out | ios::app);
                
                if (!python_students_file) {
                        cout << "python_students_file is not found!" << endl;
                        return;
                    }
                                    
                
                Student newStudent;
                newStudent.input_username_age_gender_email();
                system("cls");
                push(newStudent);
                python_students_file.close();
                
                cout<<"\nYou just finished inputting your information"<<endl;
                string filename="python_students_file.csv";
                ynQuestion_ForConfirm_inStudying(filename);
                
                Openfile(newStudent,filename);
                cout<<"\n\n"<<endl;
                displayList_EachSub(filename);
                python_students_file.close();
            }
            else if(choice =="html,css,javascript" || choice == "html"){
                
                fstream HtmlCssJavascrpit_students_file;
                HtmlCssJavascrpit_students_file.open("HtmlCssJavascrpit_students_file.csv", ios::in | ios::out | ios::app);
                
                if (!HtmlCssJavascrpit_students_file) {
                        cout << "HtmlCssJavascrpit_students_file.csv is not found!" << endl;
                        return;
                    }  
                Student newStudent;
            newStudent.input_username_age_gender_email();
            system("cls");
            push(newStudent);
                HtmlCssJavascrpit_students_file.close();

                cout<<"\nYou just finished inputting your information"<<endl;
                string filename="HtmlCssJavascrpit_students_file.csv";
                ynQuestion_ForConfirm_inStudying(filename);
                Openfile(newStudent,filename);
                cout<<"\n\n"<<endl;
                displayList_EachSub(filename);
                HtmlCssJavascrpit_students_file.close();

            }
            else if(choice=="java"){
              
                fstream java_students_file;
                java_students_file.open("java_students_file.csv", ios::in | ios::out | ios::app);
                
                if (!java_students_file) {
                        cout << "java_students_file is not found!" << endl;
                        return;
                    }
                Student newStudent;
            newStudent.input_username_age_gender_email();
            system("cls");
            push(newStudent);
                java_students_file.close();

                cout<<"\nYou just finished inputting your information"<<endl;
                string filename="java_students_file.csv";
                ynQuestion_ForConfirm_inStudying(filename);
                Openfile(newStudent,filename);
                cout<<"\n\n"<<endl;
                displayList_EachSub(filename);
                
                java_students_file.close();

            }
        }
    

    void displayStudentList() {
    cout << "We have 4 Class for viewer: " << endl;
    cout << "1.C++\n2.HtmlCssJavascript\n3.Java\n4.Python\n5.Display all class" << endl;
    int choice;
    cout << "Enter your choice: ";
    cin >> choice;
    system("cls");
    switch (choice) {
        case 1: {
            ifstream file1("cpp_students_file.csv");
            if (!file1) {
                cout << "cpp_students_file.csv not found" << endl;
                break;
            }
            string line;
            getline(file1, line); // Skip the first line
            cout << "\033[31m";
            while (getline(file1, line)) {
                cout << line << endl;
            }
            cout << "\033[0m";
            file1.close();
            break;
        }
        case 2: {
            ifstream file2("HtmlCssJavascrpit_students_file.csv"); // Fixed filename
            if (!file2) {
                cout << "HtmlCssJavascrpit_students_file.csv not found" << endl;
                break;
            }
            string line;
            getline(file2, line); // Skip the first line
            cout << "\033[31m";
            while (getline(file2, line)) {
                cout << line << endl;
            }
            cout << "\033[0m";
            file2.close();
            break;
        }
        case 3: {
            ifstream file3("java_students_file.csv");
            if (!file3) {
                cout << "java_students_file.csv not found" << endl;
                break;
            }
            string line;
            getline(file3, line); // Skip the first line
            cout << "\033[31m";
            while (getline(file3, line)) {
                cout << line << endl;
            }
            cout << "\033[0m";
            file3.close();
            break;
        }
        case 4: {
            ifstream file4("python_students_file.csv");
            if (!file4) {
                cout << "python_students_file.csv not found" << endl;
                break;
            }
            string line;
            getline(file4, line); // Skip the first line
            cout << "\033[31m";
            while (getline(file4, line)) {
                cout << line << endl;
            }
            cout << "\033[0m";
            file4.close();
            break;
        }
        case 5: {
            string file1 = "cpp_students_file.csv";
            string file2 = "HtmlCssJavascrpit_students_file.csv"; // Fixed filename
            string file3 = "java_students_file.csv";
            string file4 = "python_students_file.csv";
            ofstream writeToStudentList("Students_list.csv");
            if (!writeToStudentList) {
                cout << "Error: Cannot open Students_list.csv for writing" << endl;
                break;
            }

            const string collectionFiles[4] = {file1, file2, file3, file4};

            for (const auto& file : collectionFiles) {
                ifstream readFromEachFile(file);
                if (!readFromEachFile) {
                    cout << "Error: Cannot open " << file << endl;
                    continue;
                }
                string line;
                getline(readFromEachFile, line); // Skip the first line
                while (getline(readFromEachFile, line)) {
                    writeToStudentList << line << endl;
                }
                writeToStudentList << "\n\n";
                readFromEachFile.close();
            }
            writeToStudentList.close();

            ifstream readFromStudentList("Students_list.csv");
            if (!readFromStudentList) {
                cerr << "Error: Cannot open Students_list.csv for reading" << endl;
                break;
            }
            string line;
            cout << "\033[31m";
            while (getline(readFromStudentList, line)) {
                cout << line << endl;
            }
            cout << "\033[0m";
            readFromStudentList.close();
            break;
        }
        default:
            cout << "\033[31m";
            cout << "Invalid choice!" << endl;
            cout << "\033[0m";
            break;
    }
}


    void searchStudentId() {
            string inputId;
            cout << "Enter your ID: ";
            cin >> inputId;
            const string files[] = {
                "cpp_students_file.csv",
                "python_students_file.csv",
                "java_students_file.csv",
                "HtmlCssJavascrpit_students_file.csv"
            };
            bool found = false;
            for (const auto& file : files) {
            ifstream readFromFile(file);
            if (!readFromFile) {
                cout << "Error: Cannot open " << file << endl;
                continue;
            }
            string line;
            while (getline(readFromFile, line)) {
                if (line.find(inputId) != string::npos) { // Check if the ID is in the line
                    cout << "Found in " << file << ": " << line << endl;
                    found = true;
                    break; // Exit the loop if found
                }
            }
            readFromFile.close();
            if (found) break; // Exit the outer loop if found
        }
        if (!found) {
            cout << "Student ID " << inputId << " not found." << endl;
        }
    }
    void searchStudentId(const string& inputId) {
    const string files[] = {
        "cpp_students_file.csv",
        "python_students_file.csv",
        "java_students_file.csv",
        "HtmlCssJavascrpit_students_file.csv"
    };
    bool found = false;
    for (const auto& file : files) {
        ifstream readFromFile(file);
        if (!readFromFile) {
            cout << "Error: Cannot open " << file << endl;
            continue;
        }
        string line;
        while (getline(readFromFile, line)) {
            if (line.find(inputId) != string::npos) { // Check if the ID is in the line
                cout << "Found in " << file << ": " << line << endl;
                found = true;
                break; // Exit the loop if found
            }
        }
        readFromFile.close();
        if (found) break; // Exit the outer loop if found
    }
    if (!found) {
        cout << "Student ID " << inputId << " not found." << endl;
    }
}

void updateStudentInfo() {
    string inputId;
    cout << "Enter the student ID to update: ";
    cin >> inputId;

    
    searchStudentId(inputId);

    
    cout << "Enter the new information for student ID " << inputId << ": ";
    string newInfo;
    cin.ignore();  
    getline(cin, newInfo); // Get the updated info

    const string files[] = {
        "cpp_students_file.csv",
        "python_students_file.csv",
        "java_students_file.csv",
        "HtmlCssJavascrpit_students_file.csv"
    };

    bool updated = false;
    for (auto& file : files) {
        fstream fileStream(file, ios::in | ios::out);
        if (!fileStream) {
            cout << "Error: Cannot open " << file << endl;
            continue;
        }

        string line;
        long pos = -1;
        while (getline(fileStream, line)) {
            if (line.find(inputId) != string::npos) { 
                pos = fileStream.tellg(); // Save the current position
                break;
            }
        }

        if (pos != -1) {
            // Move the file pointer back to the beginning of the line to be updated
            fileStream.seekp(pos - line.size() - 1, ios::beg);
            fileStream << newInfo; // Write the new info to the file
            cout << "Student information updated in " << file << endl;
            updated = true;
            break;
        }

        fileStream.close();
    }

    if (!updated) {
        cout << "Failed to update student information." << endl;
    }
}
    
    void deleteStudent() {
        string inputId;
        cout << "Enter the ID of the student to delete: ";
        cin >> inputId;
        // Ask for confirmation
        char confirmation;
        cout << "Are you sure you want to delete the student with ID " << inputId << "? (y/n): ";
        cin >> confirmation;
        confirmation = tolower(confirmation); 
        if (confirmation != 'y') {
            cout << "Deletion canceled.\n";
            return; 
        }
        const string files[] = {
            "cpp_students_file.csv",
            "python_students_file.csv",
            "java_students_file.csv",
            "HtmlCssJavascrpit_students_file.csv"
        };
        bool found = false;
        for (const auto& file : files) {
            ifstream readFromFile(file);
            if (!readFromFile) {
                cout << "Error: Cannot open " << file << endl;
                continue;
            }
            ofstream tempFile("temp.csv");
            string line;
            bool isHeader = true; // Flag to skip header lines
            while (getline(readFromFile, line)) {
                if (isHeader) {
                    tempFile << line << endl; // Write header
                    if (line.find("ID") != string::npos) {
                        isHeader = false; // Skip the header line
                    }
                    continue; // Skip this line
                }
                if (line.find(inputId) != string::npos) {
                    found = true; 
                    cout << "Deleting student with ID: " << inputId << endl;
                    continue; 
                }
                tempFile << line << endl;
            }
            readFromFile.close();
            tempFile.close();
            remove(file.c_str());
            rename("temp.csv", file.c_str());
            if (found) {
                cout << "Student with ID " << inputId << " has been deleted from " << file << ".\n";
                break; 
            }
            }
            if (!found) {
            cout << "Student ID " << inputId << " not found in any file." << endl;
        }
    }
    
      


};
int main() {
    SchoolSystem RSH;
    RSH.write_first_2_line_to_file();

    const char* menu[] = {
        "1. Information",
        "2. Enrollment",
        "3. Report Information",
        "4. Search Student ID",
        "5. Display students list",
        "6. Exit Application"
    };
    string choice;
    int menuSize = sizeof(menu) / sizeof(menu[0]);

    while (true) {
        system("cls");
        RSH.display_school_name();
        for (int i = 0; i < menuSize; ++i) {
            cout << menu[i] << "\n";
        }
        cout << "\nEnter your choice: ";
        cin >> choice;

        system("cls");
        if (choice == "1") {
            cout << "You selected: Information\n";
            int input_choice;
            cout << "\033[1;36m";
            cout << "=====================================" << endl;
            cout << "         Welcome to RSH School       " << endl;
            cout << "=====================================" << endl;
            cout << "\033[0m";

            cout << "\nPlease choose an option:\n";
            cout << "1. View Offered Subjects\n";
            cout << "2. View History of RSH School\n";
            cout << "3. Back to home page\n";
            cout << "Enter your input_choice: ";
            cin >> input_choice;

            if (input_choice == 1) {
                RSH.displaySubjects();
            } else if (input_choice == 2) {
                RSH.displayHistory();
            } else if (input_choice == 3) {
                cout << "\033[1;32m";
                cout << "Thank you for visiting RSH School. Goodbye!\n";
                cout << "\033[0m";
            } else {
                cout << "\033[1;31m";
                cout << "Invalid input_choice! Please try again.\n";
                cout << "\033[0m";
            }
        } else if (choice == "2") {
            RSH.display_school_name();
            cout << "You selected: Enrollment\n";
            RSH.Enrollment();
        } else if (choice == "3") {
            RSH.display_school_name();
            cout << "You selected: Report Information\n";
            // Implement report generation logic
        } else if (choice == "4") {
            RSH.display_school_name();
            cout << "You selected: Search Student ID\n";
            RSH.searchStudentId();
        } else if (choice == "5") {
            RSH.display_school_name();
            cout << "You selected: Display students list\n";
            RSH.displayStudentList();
        } 
        else if(choice=="RSH_FOR_ADMIN_ACESS"){
            system("cls");
            RSH.display_school_name();
            int Admin_choice;
            cout << "1. Update Student ID\n2. Delete Student Info\n" << endl;
            cout<<"Enter your choice: ";
            cin >> Admin_choice;

            switch (Admin_choice) {
            case 1:
                // Call the function to update student ID
                RSH.updateStudentInfo();
                break;
            case 2:
                // Call the function to delete student information
                cout << "Deleting student information..." << endl;
                RSH.deleteStudent();
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
            }

        }
        else if (choice == "6") {
            cout << "Exiting application...\n";
            return 0;
        } else {
            cout << "Invalid option. Please try again.\n";
        }

        cout << "\n\n";
        system("pause");
    }

    return 0;
}


