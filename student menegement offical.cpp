#include <iostream>
#include <iomanip>
#include <unistd.h>  /* sleep mode */
#include <string>
#include<fstream>
#include<queue>
#include<list>
#include <conio.h>// Windows-specific; use `getch()` for Linux
#include <algorithm> // Convert the user input to lowercase

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
        
        Student(string id ="RSH_0",string name = "Unknown", int age = 0, string gender = "Unknown", string email = "N/A") {
            this->id=id;
            this->name = name;
            this->age = age;
            this->gender = gender;
            this->email = email;
        }
        void input_username_age_gender_email(){
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
            cout<< setw(30) << name << setw(15) << gender << setw(40) << email << age << endl;
            

        }

};

class SchoolSystem{
    private: 
        queue<Student>studentQueue;
        list<Student>studentList;
        string schoolName;
        int schoolID;
        string schoolAddress;
        string schoolYear; 
        string generateRandomID() {
            string id = "S";
            for (int i = 0; i <4; ++i) {
                id += to_string(rand() % 10); // Append a random digit (0-9)
            }
            return id;
        }  
        bool idExistsInFile(const string& id,string filename) {
            ifstream file(filename);
            string existingId;
            while (file >> existingId) {
                if (existingId == id) {
                    return true;
                }
            }
            return false;
        }       
    public: 
   
        string generateAndSaveID(string filename) {
            string newId;

            // Generate a unique ID
            do {
                newId = generateRandomID();
            } while (idExistsInFile(newId,filename));
            return newId;
        }
        /*  SchoolSystem(string name, int id, string address, string year)
        : schoolName(name), schoolID(id), schoolAddress(address), schoolYear(year) {} */
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
        void write_first_2_line_to_file(){
            
            string colection_file[4]={"cpp_students_file.csv","python_students_file.csv","java_students_file.csv","HtmlCssJavascrpit_students_file.csv"};
            string iD_each_subject[4]={"RSHCPP-","RSHHCJ-","RSHJAV-","RSHPYT-"};
            for(int i = 0; i<4; i++){

                fstream filename;
                filename.open(colection_file[i],ios::in | ios::out | ios::app );

                if (!filename) {
                    cout <<colection_file[i]<< "is not found!" << endl;
                    continue;
                }
                 filename.seekg(0, ios::end);
                if (filename.tellg() == 0) {
                    filename <<"=================================="<<colection_file[i]<<"===========================================================================================================\n"
                    << left <<"ID"<<"("<<iD_each_subject[i]<< setw(20)<<"):"
                    << setw(30) << "NAME:" 
                    << setw(15) << "GENDER:" 
                    << setw(40) << "EMAIL:" 
                    << "AGE:" 
                    << endl;
                }
                filename.close();
            } 

        }
         

        // Function to generate and save a unique student ID
        void processEnrollments() {
            while (!studentQueue.empty()) {
                Student student = studentQueue.front();
                studentQueue.pop(); // Remove from queue
                
                studentList.push_back(student); // Add to the linked list
                cout << "\nProcessed enrollment for: " << student.name << "\n";
            }
        }
        void Openfile(const Student& student, const string& filename) {
            
            fstream write_to_file(filename, ios::out | ios::app);
            if (!write_to_file.is_open()) {
                cerr << "Can't open the file: " << filename << endl;
                return;
            }
            write_to_file << left
                        << setw(30)<<generateAndSaveID(filename)
                        << setw(30)<< student.name
                        << setw(15) << student.gender
                        << setw(40) << student.email
                        << student.age << endl;

            cout << "Student details saved to " << filename << " successfully!\n";
        }

        void ynQuestion_ForConfirm_inStudying(string filename){
            char confirmation;
            cout << "Press  (y/n) to confirm: ";
            cin >> confirmation;
            confirmation = tolower(confirmation);

            if (confirmation == 'y') {
                processEnrollments();
                if(filename=="cpp_students_file.csv"){
                    cout<<"Your ID is: RSHCPP-"<<generateAndSaveID(filename)<<endl;
                }
                else if(filename=="HtmlCssJavascrpit_students_file.csv"){
                    cout<<"Your ID is: RSHHCJ-"<<generateAndSaveID(filename)<<endl;
                }
                else if(filename=="Javascrpit_students_file.csv"){
                    cout<<"Your ID is: RSHJVS-"<<generateAndSaveID(filename)<<endl;

                }
                else{
                    cout<<"Your ID is: RSHPYT-"<<generateAndSaveID(filename)<<endl;
                }

            } else {
                studentQueue.pop(); 
                cout << "Student enrollment canceled.\n";
            }  
        }
        void displayList_EachSub(string filename) {
            if (studentList.empty()) {
                cout << "No students are enrolled yet.\n";
                return;
            }
            cout<<"-------------------------------------------------------------------------------------------------------------------"<<endl;
            cout << left <<setw(20)<<"ID:"<< setw(30) << "NAME:" << setw(15) << "GENDER:" << setw(40) << "EMAIL:" << "AGE:" << endl;
            cout << string(115, '-') << endl;
            
            for (const auto &student : studentList) {
                cout<<"|" << left <<setw(20)<<generateAndSaveID(filename);
                student.displayStudent_info();
            }
        }
        void Enrollment() {
            
            cout << "Our school provides students 4 programming language choices:\n\n";
            string Subjects[4] = {"C++", "Python", "Html,Css,Javascript", "Java"};
            for (int i = 0; i < 4; i++) {
                cout << Subjects[i] << endl;
            }
            string choice;
            cout<<"\n\nEnter your choice :";
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
                studentQueue.push(newStudent);
                cpp_students_file.close();

                cout<<"\nYou just finished inputting your information"<<endl;
                string filename="cpp_students_file.csv";
                ynQuestion_ForConfirm_inStudying(filename);
                Openfile(newStudent,filename);
                cout<<"\n\n"<<endl;
                displayList_EachSub(filename);
                    
            }

            
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
                studentQueue.push(newStudent);
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
                studentQueue.push(newStudent);
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
                studentQueue.push(newStudent);
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
        void displayStudentList(){
            cout<<"We have 4 Class for viewer: "<<endl;
            cout<<"1.C++\n2.HtmlCssJavascrpit\n3.Java\n4.Python\n5.Display all class"<<endl;
            int choice;
            cout<<"Enter your choice: "; 
            cin>>choice;
            system("cls");
            switch (choice) {
                case 1: {
                    ifstream file1("cpp_students_file.csv");
                    if (!file1) {
                        cout << "cpp_students_file.csv not found" << endl;
                        break;
                    }
                    string line;
                    while (getline(file1, line)) {
                        cout << line << endl;
                    }
                    file1.close();
                    break;
                }

                case 2: {
                    ifstream file2("python_students_file.csv");
                    if (!file2) {
                        cout << "python_students_file.csv not found" << endl;
                        break;
                    }
                    string line;
                    while (getline(file2, line)) {
                        cout << line << endl;
                    }
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
                    while (getline(file3, line)) {
                        cout << line << endl;
                    }
                    file3.close();
                    break;
                }

                case 4: {
                    ifstream file4("HtmlCssJavascript_students_list.csv");
                    if (!file4) {
                        cout << "HtmlCssJavascript_students_list.csv not found" << endl;
                        break;
                    }
                    string line;
                    while (getline(file4, line)) {
                        cout << line << endl;
                    }
                    file4.close();
                    break;
                }

                case 5: {
                    string file1 = "cpp_students_file.csv";
                    string file2 = "python_students_file.csv";
                    string file3 = "java_students_file.csv";
                    string file4 = "HtmlCssJavascript_students_file.csv";
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
                    while (getline(readFromStudentList, line)) {
                        cout << line << endl;
                    }
                    readFromStudentList.close();
                    break;
                }

                default:
                    cout << "Invalid choice!" << endl;
                    break;
            }

                        
            
        }
        void serchStudentId(){
            string inputId;
            cout<<"Enter your ID: ";
            cin>>inputId;
            
        }


};

int main() {
    SchoolSystem RSH;
    RSH.write_first_2_line_to_file();
    
    /* RSH.showLoadingScreen(); */
    RSH.display_school_name();
    /* stu.input_username_age_gender_email();  */

   
    system("cls"); 
      const char* menu[] = {
        "1. Information",
        "2. Enrollment",
        "3. View our students' source code",
        "4. Search Student ID",
        "5. Update Student ID",
        "6. Display students list",
        "7. Exit Application"
    };

    int choice;
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
        switch (choice) {
            case 1:
                RSH.display_school_name();
                cout << "You selected: Information\n";
              
                break;

            case 2:
                RSH.display_school_name();
                cout << "You selected: Enrollment\n";
                RSH.Enrollment();
                break;

            case 3: 
                RSH.display_school_name();
                cout << "You selected: View our students' source code\n";
                
                break;

            case 4: 
                RSH.display_school_name();
                cout << "You selected: Search Student ID\n";
              
                break;

            case 5: 
                RSH.display_school_name();
                cout << "You selected: Update Student ID\n";
                RSH.serchStudentId();
                
                break;

            case 6: 
                RSH.display_school_name();
                cout << "You selected: Display students list\n";
                RSH.displayStudentList();
                
                break;

            case 7: 
                cout << "Exiting application...\n";
                return 0; 

            default:
                cout << "Invalid option. Please try again.\n";
                break;
        }
        cout<<"\n\n"<<endl;

        system("pause"); 
    }
    return 0;
}
