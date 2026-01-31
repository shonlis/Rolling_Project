#ifndef DEPARTMENT_H
#define DEPARTMENT_H

#include <string>
#include <vector>
#include <iostream>
using namespace std;

class Doctor;
class Nurse;
class Visitor;

class Department
{
	string name;
	vector <Doctor*> doctors;
	vector <Nurse*> nurses;
	vector <Visitor*> visitors;

	int currentNumberOfDoctors;
	int maxNumberOfDoctors;
	
	int currentNumberOfNurses;
	int maxNumberOfNurses;
	
	int currentNumberOfVisitors;
	int maxNumberOfVisitors;

public:
	Department(const string& name);

	// getters
	const string& getName() const { return name; };
	int getCurrentNumberOfDoctors() const { return currentNumberOfDoctors; }
	int getCurrentNumberOfNurses() const { return currentNumberOfNurses; }
	int getCurrentNumberOfVisitors() const { return currentNumberOfVisitors; }

	const vector <Doctor*>& getDoctors() const { return doctors; }
	const vector <Nurse*>& getNurses() const { return nurses; }
	const vector <Visitor*>& getVisitors() const { return visitors; }

	//setters
	void setName(const string& name);

    // operators
    Department& operator+=(Doctor& doctor);
    Department& operator+=(Nurse& nurse);

    // other methods
    bool addDoctor(Doctor* doctor);
    bool DoctorExist(const Doctor& doctor);

    bool addNurse(Nurse* nurse);
    bool NurseExist(const Nurse& nurse);
    
    bool addVisitor(Visitor* visitor);
    bool VisitorExist(const Visitor& visitor);

    void printDoctors() const;
    void printNurses() const;

};

#endif // DEPARTMENT_H
