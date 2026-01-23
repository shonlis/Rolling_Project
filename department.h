#ifndef DEPARTMENT_H
#define DEPARTMENT_H

class Doctor;
class Nurse;
class Visitor;

class Department {
	char* name;
	Doctor** doctors;
	Nurse** nurses;
	Visitor** visitors;

	int currentNumberOfDoctors;
	int maxNumberOfDoctors;
	
	int currentNumberOfNurses;
	int maxNumberOfNurses;
	
	int currentNumberOfVisitors;
	int maxNumberOfVisitors;

public:
	Department(const char* name = "none");
	~Department();

	// getters
	const char* getName() const { return name; };
	int getCurrentNumberOfDoctors() const { return currentNumberOfDoctors; }
	int getCurrentNumberOfNurses() const { return currentNumberOfNurses; }
	int getCurrentNumberOfVisitors() const { return currentNumberOfVisitors; }

	Doctor* const* const getDoctors() const { return doctors; }
	Nurse* const* const getNurses() const { return nurses; }
	Visitor* const* const getVisitors() const { return visitors; }

	//setters
	void setName(const char* name);

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