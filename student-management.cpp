#include <iostream>
#include <iomanip>
#include <unistd.h>  /* sleep mode */
#include <string>
#include<fstream>

#include <conio.h>// Windows-specific; use `getch()` for Linux
#include <algorithm> // Convert the user input to lowercase
using namespace std;

class SchoolSystem{
    private: 
        string schoolName;
        int schoolID;
        string schoolAddress;
        string schoolYear;
    public: 
         SchoolSystem(string name, int id, string address, string year)
        : schoolName(name), schoolID(id), schoolAddress(address), schoolYear(year) {}


};
class Student {
    private: 
        string id;  
    public:
        string name;
        int age;
        string gender;
        string email;

        string getId() {
            return id;
        }
        

    

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
        void display_school_name() {
            cout << left << setw(50) << "" << "******************************" << endl;
            cout << left << setw(50) << "" << " *     RSH Coding Club      *" << endl;
            cout << left << setw(50) << "" << "******************************" << endl;
            
    
            
        }


    
        void Enrollment(void (Student::*input_username_age_gender_email)()) {
            
            cout << "Our school provides students 4 programming language choices:\n\n";
            string Subjects[5] = {"C++", "Python", "Html,Css,Javascript", "Java", "html"};
            for (int i = 0; i < 5; i++) {
                cout << Subjects[i] << endl;
            }
            string choice;
            cout<<"\n\nEnter your choice :";
            cin >> choice;
            
            // Convert the user input to lowercase
            transform(choice.begin(), choice.end(), choice.begin(), ::tolower);

            if (choice == "c++") { 
                ofstream cpp_students_file;
                
                cpp_students_file.open("cpp_students_file.csv", ios::app);

                (this->*input_username_age_gender_email)();
                
                cpp_students_file << left
                        << "NAME: "<<setw(30)<<name 
                        << "GENDER: "<< setw(30) << gender   
                        << "EMAIL: " << setw(30) << email   
                        << "AGE: " << age << endl;
                if(!cpp_students_file){
                    cout<<"cpp_students_file is not found!"<<endl;
                }
                            
                cpp_students_file.close();

            } else if(choice =="python") {
                
                fstream python_students_file;
                
                python_students_file.open("python_students_file.csv", ios::app);

                (this->*input_username_age_gender_email)();
                
                python_students_file << left
                        << "NAME: "<<setw(30)<<name 
                        << "GENDER: "<< setw(30) << gender   
                        << "EMAIL: " << setw(30) << email   
                        << "AGE: " << age << endl;
                if(!python_students_file){
                    cout<<"python_students_file is not found!"<<endl;
                }
                            
                python_students_file.close();
                
            }
            else if(choice =="html,css,javascript" || choice == "html"){
                fstream HtmlCssJavascrpit_students_file;
                
                
                HtmlCssJavascrpit_students_file.open("HtmlCssJavascrpit_students_file.csv", ios::app);

                (this->*input_username_age_gender_email)();
                
                HtmlCssJavascrpit_students_file << left
                        << "NAME: "<<setw(30)<<name 
                        << "GENDER: "<< setw(30) << gender   
                        << "EMAIL: " << setw(30) << email   
                        << "AGE: " << age << endl;
                if(!HtmlCssJavascrpit_students_file){
                    cout<<"HtmlCssJavascrpit_students_file is not found!"<<endl;
                }
                            
                HtmlCssJavascrpit_students_file.close();
            }
            else if(choice=="java"){
                fstream java_students_file;
                
                java_students_file.open("java_students_file.csv", ios::app);

                (this->*input_username_age_gender_email)();
                
                java_students_file << left
                        << "NAME: "<<setw(30)<<name 
                        << "GENDER: "<< setw(30) << gender   
                        << "EMAIL: " << setw(30) << email   
                        << "AGE: " << age << endl;
                if(!java_students_file){
                    cout<<"java_students_file is not found!"<<endl;
                }
                            
                java_students_file.close();
            }
        }
    
};

int main() {
    Student stu;
    /* stu.showLoadingScreen(); */
    stu.display_school_name();
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

        stu.display_school_name();
        for (int i = 0; i < menuSize; ++i) {
            cout << menu[i] << "\n";
        }

        cout << "\nEnter your choice: ";
        cin >> choice;

        system("cls");
        switch (choice) {
            case 1: // "1. Information"
                stu.display_school_name();
                cout << "You selected: Information\n";
                // Add your logic for Information here
                break;

            case 2: // "2. Enrollment"
                stu.display_school_name();
                cout << "You selected: Enrollment\n";
                stu.Enrollment(&Student::input_username_age_gender_email);
                break;

            case 3: // "3. View our students' source code"
                stu.display_school_name();
                cout << "You selected: View our students' source code\n";
                // Add your logic for viewing source code here
                break;

            case 4: // "4. Search Student ID"
                stu.display_school_name();
                cout << "You selected: Search Student ID\n";
                // Add your logic for searching Student ID here
                break;

            case 5: // "5. Update Student ID"
                stu.display_school_name();
                cout << "You selected: Update Student ID\n";
                // Add your logic for updating Student ID here
                break;

            case 6: // "6. Display students list"
                stu.display_school_name();
                cout << "You selected: Display students list\n";
                // Add your logic for displaying students list here
                break;

            case 7: // "7. Exit Application"
                cout << "Exiting application...\n";
                return 0; // Exit the program

            default:
                cout << "Invalid option. Please try again.\n";
                break;
        }

        system("pause"); // Wait before returning to the menu
    }
    return 0;
}