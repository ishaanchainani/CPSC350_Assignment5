#include "Student.h"
#include  <iostream>
using namespace std;
#include <sstream>
#include <fstream>


Student::Student(int studentID, string studentName, string studentYear, string studentMajor, double studentGPA, int advisorID) {
    this->studentID = studentID;
    this->studentName = studentName;
    this->studentYear = studentYear;
    studentYear = 1;
    this->studentMajor = studentMajor;
    this->studentGPA = studentGPA;
    this->advisorID = advisorID;
}

Student::~Student() {

}

// obtain advisor ID
int Student::getAdvisorID() {
    return advisorID;
}

// set new advisor ID
void Student::setAdvisorID(int advisorID) {
    this->advisorID = advisorID;
}

// obtain GPA
double Student::getGPA() {
    return studentGPA;
}

// set GPA for new student
void Student::setGPA(double studentGPA) {
    this->studentGPA = studentGPA;
}

// string Student::getMajor(){
//   return studentMajor;
// }
//
// void Student::setMajor(string studentMajor){
//
// }

Student* Student::readFromFile(ifstream &inputFile) {
    const int numLines = 6;
    string lineInFile[numLines];
    //ifstream inputStream(inputFileName);

    for (int i = 0; i < numLines; ++i) {
        getline(inputFile, lineInFile[i]);
        if (lineInFile[i].empty()) { // empty line
            return (NULL);
        }
    }
    // id, name, year, major, gpa, advisor
    int studentID = stoi(lineInFile[0]);
    string studentName = lineInFile[1];
    string studentYear = lineInFile[2];
    string studentMajor = lineInFile[3];
    double studentGPA = stod(lineInFile[4]);
    int advisorID = stoi(lineInFile[5]);

    Student* newStudent = new Student(studentID, studentName, studentYear, studentMajor, studentGPA, advisorID);
    return (newStudent);
}

void Student::serialize(fstream &outputStream) {
    outputStream << studentID << endl;
    outputStream << studentName << endl;
    outputStream << studentYear << endl;
    outputStream << studentMajor << endl;
    outputStream << studentGPA << endl;
    outputStream << advisorID << endl;
}

void Student::printOut() {
//     cout << "Student ID: " << studentID << " "; cout.flush();
//     cout << "Student Name: " << studentName << " "; cout.flush();
//     cout << "Year: " << studentYear << " "; cout.flush();
//     cout << "Major: " << studentMajor << " "; cout.flush();
//     cout << "GPA: " << studentGPA << " "; cout.flush();
//     cout << "Advisor ID: " << advisorID << endl; cout.flush();
    cout << "Student ID: ";
    cout << studentID;
    cout << endl;
    cout << "Student Name: ";
    cout << studentName;
    cout << endl;
    cout << "Year: ";
    cout << studentYear;
    cout << endl;
    cout << "Major: ";
    cout << studentMajor;
    cout << endl;
    cout << "GPA: ";
    cout << studentGPA;
    cout << endl;
    cout << "Advisor ID: ";
    cout << advisorID;
    cout << endl;
}
