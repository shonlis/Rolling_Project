#ifndef HOSPITAL_H
#define HOSPITAL_H

#include <memory>

#include "Department.h"
#include "Worker.h"
#include "VisitCard.h"
#include "Visitor.h"
#include "Research_Center.h"

// forward declare global types used across the project
class Doctor;
class Nurse;
class Researcher;

class Hospital {
	char* name;
	Department** departments;
	research_center& researchCenter;
	Doctor** doctors;
	Nurse** nurses;
	Visitor** visitors;

	int currentNumberOfDepartments;
	int maxNumberOfDepartments;

	int currentNumberOfDoctors;
	int maxNumberOfDoctors;
	
	int currentNumberOfNurses;
	int maxNumberOfNurses;
	
	int currentNumberOfVisitors;
	int maxNumberOfVisitors;


public:
	Hospital(const char* name, research_center& researchCenter);
	~Hospital();

	// getters
	const char* getName() const { return name; };
	const research_center& getResearchCenter() const { return researchCenter; };

	//setters
	void setName(const char* name);

	// other methods
	bool addDepartment(Department& department);
	bool addDoctor(Doctor& doctor);
	bool addNurse(Nurse& nurse);
	bool addVisitor(Visitor& visitor);
	bool addResearcher(Researcher& researcher);

	bool addVisit(Visitor& visitor, VisitCard& Visitcard, const char* department);
	bool addNurseToDepartment(Nurse& nurse, const char* departmentName);
	bool addDoctorToDepartment(Doctor& doctor, const char* departmentName);
	bool addVisitorToDepartment(Visitor& visitor, const char* departmentName);
	bool addArticleToResearchCenter(Researcher& researcher, Article& article);

	// operator to add staff
	Hospital& operator+=(const Doctor& doctor);
	Hospital& operator+=(const Nurse& nurse);

	int countDoctors() const;
	int countNurses() const;
	int countVisitors() const;
	int countResearchers() const;
	int countDepartments() const;

	Doctor* findDoctorById(int id) const;
	Nurse* findNurseById(int id) const;
	Visitor* findVisitorById(int id) const;
	Researcher* findResearcherById(int id) const;
	
	Department* getDepartmentByName(const char* name) const;
	Doctor* getDoctorByName(const char* name) const;
	Nurse* getNurseByName(const char* name) const;
	Visitor* getVisitorByName(const char* name) const;
	Researcher* getResearcherByName(const char* name) const;

	void printDepartmentVisitors(const char* departmentName) const;
	void printAllMedicalStaff() const;
	void printDepartmentMedicalStaff(const char* departmentName) const;
	void printAllResearchers() const;
	void printAllDepartments() const;
	
	bool DepartmentExist(const Department& department);
	bool NurseExist(const Nurse& nurse);
	bool DoctorExist(const Doctor& doctor);
	bool visitorExist(const Visitor& visitor);


};

#endif // HOSPITAL_H