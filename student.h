#pragma once

#include <string>
#include <iostream>

using namespace std;

class Student {
private:
  // variables
    int studentID;
    string studentName;
    string studentYear;
    string studentMajor;
    double studentGPA;
    int advisorID;

public:

    Student(int studentID, string studentName, string studentYear, string studentMajor, double studentGPA, int advisorID);
    ~Student(); // destructor

    int getKey() {

        return this->studentID;
    }

    // implemented functions
    double getGPA();
    void setGPA(double studentGPA);

    //string getMajor();
    int getAdvisorID();
    void setAdvisorID(int advisorID);

    void serialize(fstream &outputStream);
    static Student* readFromFile(ifstream &inputFile);

    void printOut();


    bool operator==(const Student& s) { return (this->studentID == s.studentID); }
    bool operator>(const Student& s) { return (this->studentID > s.studentID); }
    bool operator<(const Student& s) { return (this->studentID < s.studentID); }
};


/*
Student records will be stored in a Student class. Student records contain a unique
student ID (an integer), a String name field, a string level field (Freshman, Sophomore,
etc), a String major field, a double GPA field, and an integer advisor field, which will
contain the Faculty ID of their advisor. These are the only fields the class contains.
The Student
*/
