#pragma once

#pragma once

#include <string>
#include <iostream>
#include <sstream>
#include "gensearchtree.h"

using namespace std;

class Advisee {
public:
    int studentID;

    Advisee(int id);

    int getKey() { return this->studentID; }
    void printOut();
    void serialize(fstream& outputStream);
};


class Faculty {
private:
    int facultyID;
    string facultyName;
    string facultyLevel;
    string facultyDept;

    GenSearchTree<Advisee> students;
    int numStudents;

public:

    Faculty(int facultyID, string facultyName, string facultyLevel, string facultyDept, int numStudents);
    Faculty(int facultyID, string facultyName, string facultyLevel, string facultyDept, int numStudents, int students[]);
    ~Faculty(); // destructor


    // implemented functions
    int getKey() {
        return this->facultyID;
    }
    static Faculty* readFromFile(ifstream &inputFile);

    void serialize(fstream &outputStream);

    void printOut();

    void returnStudentList(fstream &f, int& numStudents);
    void removeStudent(int studentID);
    void addStudent(int studentID);

    bool operator==(const Faculty& s) { return (this->facultyID == s.facultyID); }
    bool operator>(const Faculty& s) { return (this->facultyID > s.facultyID); }
    bool operator<(const Faculty& s) { return (this->facultyID < s.facultyID); }
};