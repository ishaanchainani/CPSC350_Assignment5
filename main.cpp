#include <iostream>
#include <stdio.h>
#include "gensearchtree.h"
#include "faculty.h"
#include "student.h"
#include "OperationsLog.h"
#include <sstream>
#include <string>

using namespace std;

/*
class member {
public:
    int key;
    void printOut() { cout << key << "\n";  }

    member(int i) { key = i; }
};
int main()
{
    std::cout << "Hello World!\n";

    GenSearchTree<member>* tree = new GenSearchTree<member>();

    for (int i = 0; i < 10; i++) {
        member* m = new member(i);
        tree->insert(m);
    }
    for (int i = 50; i < 60; i++) {
        member* m = new member(i);
        tree->insert(m);
    }
    for (int i = 10; i < 50; i++) {
        member* m = new member(i);
        tree->insert(m);
    }
    for (int i = 60; i < 100; i++) {
        member* m = new member(i);
        tree->insert(m);
    }

    tree->printTree();

    for (int i = 0; i < 52; (i += 2)) {
        cout << "delete " << i << "\n";
        tree->deleteNode(i);
    }
    tree->printTree();
}
*/

// creating objects student and faculty of GenSearchTree
GenSearchTree<Student>* StudentDB;
GenSearchTree<Faculty>* FacultyDB;

// creating objects, used for logging actions of student and faculty
OperationsLog<Student> StudentLog;
OperationsLog<Faculty> FacultyLog;

int printMenu() { // print options to user
    cout << endl;
    cout << "1. Print all students and their information (sorted by ascending id #)" << endl;
    cout << "2. Print all faculty and their information (sorted by ascending id #)" << endl;
    cout << "3. Find and display student information given the students id" << endl;
    cout << "4. Find and display faculty information given the faculty id" << endl;
    cout << "5. Given a student's id, print the name and info of their faculty advisor" << endl;
    cout << "6. Given the faculty id, print ALL the names and info of his/her advisees." << endl;
    cout << "7. Add a new student." << endl;
    cout << "8. Delete a student given the id" << endl;
    cout << "9. Add a new faculty member" << endl;
    cout << "10. Delete a faculty member given the id" << endl;
    cout << "11. Change a student's advisor given the student id and the new faculty id" << endl;
    cout << "12. Remove an advisee from a faculty member given the ids" << endl;
    cout << "13. Rollback" << endl;
    cout << "14. Save & Exit" << endl;
    cout << "15. Exit without saving" << endl;

    int userChoice;
    cout << "Please choose an option: " << endl;
    cin >> userChoice;

    return userChoice;
}

const string studentFileName = "studentTable.txt";
const string facultyFileName = "facultyTable.txt";

int main(int argc, char** argv) {
    // create sutdent database
    StudentDB = new GenSearchTree<Student>();

    ifstream inputStream;

    // open studentTable.txt
    inputStream.open(studentFileName);
    if (inputStream) {
        cout << "Creating Student DB from file" << endl;
        while (!inputStream.eof()) {
            Student* s = Student::readFromFile(inputStream);
            if (s == NULL){
                break;
             }
            StudentDB->insert(s);
        }
        inputStream.close();
    }
    else {
        cout << "No Student file, creating empty Student DB" << endl;
    }
    StudentDB->printTree();
    FacultyDB = new GenSearchTree<Faculty>();

    ifstream inputStream2;

    // open facultyTable.txt
    inputStream2.open(facultyFileName);
    if (inputStream2) {
        cout << "Creating Faculty DB from file" << endl;
        while (!inputStream2.eof()) {
            Faculty* f = Faculty::readFromFile(inputStream2);
            if (f == NULL) {
                break;
            }
            FacultyDB->insert(f);
        }
        inputStream2.close();
    }
    else {
        cout << "No Faculty file, creating empty Faculty DB" << endl;
    }
    // declare variables
    FacultyDB->printTree();
    Student* s = NULL;
    Faculty* f = NULL;
    int studentID, facultyID;
    int newStudentID;
    string newStudentName;
    string newStudentLevel;
    string newStudentMajor;
    double newStudentGPA;
    int newStudentAdvisor;
    int newFacultyID;
    string newFacultyName;
    string newFacultyLevel;
    string newFacultyDepartment;
    int adviseesIDs[100];
    int numOfAdvisees;


    while (1) { // Print all students and their information (sorted by ascending id #)
        cout << "Welcome to the database." << endl;
        cout << "You will be presented with options." << endl;
        int userChoice = printMenu();

        switch (userChoice) {
        case 1: {
            StudentDB->printTree();
            break;
        }
        case 2: { // Print all faculty and their information (sorted by ascending id #)
            FacultyDB->printTree();
            break;
        }
        case 3: { // find and display student information given the students id
            int studentID;
            cout << "Enter a students id: " << endl;
            cin >> studentID;
            // find student in database
            s = StudentDB->find(studentID);
            if (s == NULL) {
                cout << "Student does not exist." << endl;
            }
            else {
                s->printOut();
            }

            break;
        }
        case 4: { // Find and display faculty information given the faculty id
            cout << "Enter a faculty's id: " << endl;
            cin >> facultyID;
            // find faculty in database
            f = FacultyDB->find(facultyID);
            if (f == NULL) {
                cout << "Faculty does not exist." << endl;
            }
            else {
                f->printOut();
            }
            break;
        }
        case 5: { // Given a student’s id, print the name and info of their faculty advisor
            cout << "Enter a students id: " << endl;
            cin >> studentID;
            // find student in databse
            s = StudentDB->find(studentID);
            if (s == NULL) {
                cout << "Student does not exist." << endl;
            }
            else {
                // obtain faculty id
                int facultyID = s->getAdvisorID();
                f = FacultyDB->find(facultyID);
                if (f == NULL) {
                    cout << "Student is not assigned to faculty." << endl;
                }
                else {
                    f->printOut();
                }
            }
            break;
        }
        case 6: { // Given a faculty id, print ALL the names and info of his/her advisees.
            int facultyID;
            cout << "Enter a faculty's id: " << endl;
            cin >> facultyID;
            // find faculty in database
            f = FacultyDB->find(facultyID);
            if (f == NULL) {
                cout << "Faculty does not exist." << endl;
            }

            else { // if faculty exists
                int numStudents;
                fstream flist;
                f->returnStudentList(flist, numStudents);
                int id;
                for (int i = 0; i < numStudents; ++i) {
                    flist >> id;
                    Student* s = StudentDB->find(id);
                    if (s == NULL) {
                        cout << "Program error." << endl;
                        exit(1);
                    }
                    else {
                        s->printOut();
                    }
                }
            }
            break;
        }
        case 7: { // add a new students

            cout << "Enter student ID: " << endl;
            cin >> newStudentID;

            cout << "Enter student name: " << endl;
            cin >> newStudentName;

            cout << "Enter student level: " << endl;
            cin >> newStudentLevel;

            cout << "Enter student major: " << endl;
            cin >> newStudentMajor;

            cout << "Enter student GPA: " << endl;
            cin >> newStudentGPA;

            cout << "Enter faculty advisor ID: " << endl;
            cin >> newStudentAdvisor;

            s = new Student(newStudentID, newStudentName, newStudentLevel, newStudentMajor, newStudentGPA, newStudentAdvisor);
            StudentDB->insert(s);
            // log addition of student
            StudentLog.logInsertion(newStudentID);
            break;
        }
        case 8: { // delete a student given the id
            cout << "Please enter the student's ID: " << endl;
            cin >> studentID;

            s = StudentDB->deleteNode(studentID);
            StudentLog.logDeletion(studentID, s);
            break;
        }
        case 9: { // add a new faculty member


            numOfAdvisees = 0;

            cout << "Enter faculty ID: " << endl;
            cin >> newFacultyID;

            cout << "Enter faculty name: " << endl;
            cin >> newFacultyName;

            cout << "Enter faculty level: " << endl;
            cin >> newFacultyLevel;

            cout << "Enter faculty department: " << endl;
            cin >> newFacultyDepartment;

            cout << "Enter number of advisees: " << endl;
            cin >> numOfAdvisees;

            for (int i = 0; i < numOfAdvisees; ++i) {
                cout << "Enter ID of advisee: " << endl;
                cin >> adviseesIDs[i];
            }

            Faculty* f = new Faculty(newFacultyID, newFacultyName, newFacultyLevel, newFacultyDepartment, numOfAdvisees, adviseesIDs);
            FacultyDB->insert(f);
            FacultyLog.logInsertion(newFacultyID);
            break;
        }

        case 10: { // add a new faculty member
               cout << "Enter the faculty ID: " << endl;
               cin >> facultyID;

               f = FacultyDB->deleteNode(facultyID);
               if (f == NULL) {
                   cout << "Faculty not found." << endl;
               }
               else {
                  // log deletion of faculty
                   FacultyLog.logDeletion(facultyID, f);
               }
               break;
        }

        case 11: { // Change a student’s advisor given the student id and the new faculty id.
            cout << "Enter student ID: " << endl;
            cin >> studentID;

            cout << "Enter new faculty ID: " << endl;
            cin >> newFacultyID;

            // find student member
            Student* s = StudentDB->find(studentID);
            if (s == NULL) {
                cout << "Student not found." << endl;
            }
            else {
                // find faculty member
                Faculty* f = FacultyDB->find(newFacultyID);
                if (f == NULL) {
                    cout << "Faculty not found." << endl;
                }
                else {
                    // add student to faculty
                    f->addStudent(studentID);
                    int oldFacultyID = s->getAdvisorID();
                    // set advisor id to the new advisor id
                    s->setAdvisorID(newFacultyID);
                    // remove student from old faculty
                    Faculty* oldf = FacultyDB->find(oldFacultyID);
                    if (oldf != NULL) {
                        oldf->removeStudent(studentID);
                    }

                }
            }
            break;
        }
        case 12: { // Remove an advisee from a faculty member given the ids
            cout << "Enter faculty ID: " << endl;
            cin >> facultyID;

            cout << "Enter student ID: " << endl;
            cin >> studentID;

            Faculty* f = FacultyDB->find(facultyID);
            if (f == NULL) {
                cout << "Faculty not found." << endl;
            }
            else {
                f->removeStudent(studentID);
                Student* s = StudentDB->find(studentID);
                if (s != NULL) {
                    s->setAdvisorID(0);
                }
            }
            break;
        }
        case 13: { // rollback
            cout << "Enter 'S' for student rollback, or 'F' for faculty rollback: " << endl;
            char userInput;
            cin >> userInput;
            if (tolower(userInput) == 'f') {
                Operation<Faculty>* ops = FacultyLog.undoLastOp();
                if (ops == NULL) {
                    cout << "No previous action, skipping" << endl;
                }
                else {
                    int facultyID = ops->key;
                    switch (ops->operation) {
                      // if operation was instertion
                        case opType::INSERTION: {
                          // delete node from tree
                            Faculty* f = FacultyDB->deleteNode(facultyID);
                            if (f == NULL) {
                                cout << "program bug" << endl;
                                exit(1);
                            }
                            delete f;
                        }
                        break;
                        // if opertaion was deletion
                        case opType::DELETION: {
                            Faculty* f = ops->data;
                            if (f == NULL) {
                                cout << "Program error" << endl;
                                exit(1);
                            }
                            FacultyDB->insert(f);
                        }
                        break;

                        default:
                            cout << "program bug" << endl;
                            exit(1);
                    }
                    delete ops;
                }
            }
            else if (tolower(userInput) == 's') {
                Operation<Student>* ops = StudentLog.undoLastOp();
                if (ops == NULL) {
                    cout << "No previous action, skipping" << endl;
                }
                else {
                    int studentID = ops->key;
                    switch (ops->operation) {
                     case opType::INSERTION: {
                       // if operation was insertion
                         Student *s = StudentDB->deleteNode(studentID);
                         if (s == NULL) {
                             cout << "program bug" << endl;
                             exit(1);
                         }
                         int advisorID = s->getAdvisorID();
                         // find faculty member
                         Faculty* f = FacultyDB->find(advisorID);
                         if (f == NULL) {
                             cout << "Faculty not found." << endl;
                         }
                         else {

                             f->removeStudent(studentID);
                         }
                         delete s;
                     }
                     break;
                     case opType::DELETION: {
                       // if operation was deletion
                         Student* s = ops->data;
                         StudentDB->insert(s);
                         facultyID = s->getAdvisorID();
                         f = FacultyDB->find(studentID);
                         if (f == NULL) {
                             cout << "Faculty not found." << endl;
                         }
                         else {
                             f->addStudent(studentID);
                         }
                     }
                     break;
                     default:
                         cout << "program bug" << endl;
                         exit(1);
                    }
                    delete ops;
                }

            }
            else {
                cout << "Input not valid" << endl;
            }
        }
        break;

        case 14: { // save and exit

            // serialize into new files
            fstream outputStream;

            outputStream.open(studentFileName, fstream::out);
            //outputStream.open(string("testStudent.txt"), fstream::out);
            StudentDB->serialize(outputStream);
            outputStream.close();

            outputStream.open(facultyFileName, fstream::out);
            //outputStream.open(string("testFaculty.txt"), fstream::out);
            FacultyDB->serialize(outputStream);
            outputStream.close();

            exit(0);
        }
        case 15: { // exit
            exit(0);
        }
        default: { // if user does not enter valid input
            cout << "Please enter option from 1 to 14\n";
            break;
        }
        }
    }


}
