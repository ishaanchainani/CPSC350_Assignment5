#include "Faculty.h"
#include  <iostream>
using namespace std;
#include <sstream>
#include <fstream>


Advisee::Advisee(int id) {
    studentID = id;
}

void Advisee::printOut() {
    cout << studentID << " ";
}

void Advisee::serialize(fstream& outputStream) {
    outputStream << studentID << " ";
}

// constructor
Faculty::Faculty(int facultyID, string facultyName, string facultyLevel, string facultyDept, int numStudents) {
	this->facultyID = facultyID;
	this->facultyName = facultyName;
	this->facultyName = facultyName;
	this->facultyLevel = facultyLevel;
	this->facultyDept = facultyDept;
	this->numStudents = numStudents;
}

// overloaded constructor
Faculty::Faculty(int facultyID, string facultyName, string facultyLevel, string facultyDept, int numStudents, int studentList[]) {
    this->facultyID = facultyID;
    this->facultyName = facultyName;
    this->facultyName = facultyName;
    this->facultyLevel = facultyLevel;
    this->facultyDept = facultyDept;
    this->numStudents = numStudents;

    for (int i = 0; i < numStudents; ++i) {
        Advisee* a = new Advisee(studentList[i]);
        this->students.insert(a);
    }

}

// destructor
Faculty::~Faculty() {
}

// reading lines from file
Faculty* Faculty::readFromFile(ifstream &inputFile) {
    const int numLines = 5;
    string line = "";
    string lineInFile[numLines];
    //ifstream inputStream(inputFileName);

    // go through lines in file
    for (int i = 0; i < numLines; ++i) {
        getline(inputFile, line);
        if (line.empty()) { // empty line
            return NULL;
        }
        lineInFile[i] = line;
    }
    // id, name, level, department, number of students
    int facultyID = stoi(lineInFile[0]);
    string facultyName = lineInFile[1];
    string facultyLevel = lineInFile[2];
    string facultyDept = lineInFile[3];

    // creating newfaculty object
    Faculty* newFaculty = new Faculty(facultyID, facultyName, facultyLevel, facultyDept, 0);

    stringstream is;
    is.str(lineInFile[4]);

    int temp;
    int numStudents = 0;
    while (!is.eof()) {
        is >> temp;
        Advisee* a;
        a = new Advisee(temp);
        newFaculty->students.insert(a);
        numStudents++;
    }
    newFaculty->numStudents = numStudents;
    return newFaculty;
}

void Faculty::serialize(fstream &outputStream) {

    outputStream << facultyID << endl;
    outputStream << facultyName << endl;
    outputStream << facultyLevel << endl;
    outputStream << facultyDept << endl;
    students.serialize(outputStream);
    outputStream << endl;
}

// prints out information to console
void Faculty::printOut() {
    cout << "Faculty ID: ";
    cout << facultyID;
    cout << endl;
    cout << "Faculty Name: ";
    cout << facultyName;
    cout << endl;
    cout << "Faculty Level: ";
    cout << facultyLevel;
    cout << endl;
    cout << "Dept: ";
    cout << facultyDept;
    cout << endl;

    if (numStudents == 0) {
        cout << "No associated students!" << endl;
    }
    else {
        cout << "List of Student IDs: " << endl;
        students.printTree();
        cout << endl;
    }
}

// returns list of students of faculty
void Faculty::returnStudentList(fstream &f, int& numStudents) {
    numStudents = this->numStudents;
    serialize(f);
    return;
}

// deletes student from faculty
void Faculty::removeStudent(int studentID) {
    Advisee* a = students.deleteNode(studentID);
    if (a != NULL) {
        delete a;
    }
}

// add student to faculty
void Faculty::addStudent(int studentID) {
    Advisee* a = new Advisee(studentID);
    students.insert(a);
}
