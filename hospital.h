#ifndef HOSPITAL_H
#define HOSPITAL_H

#include "Research_Center.h"

class Doctor;
class Nurse;
class Researcher;
class Worker;
class Department;
class Visitor;
class VisitCard;
class Article;


class Hospital
{

	string name;
	vector <Department*> departments;
	research_center& researchCenter;
	vector <Worker*> workers;
	vector <Visitor*> visitors;

	int currentNumberOfDepartments;
	int maxNumberOfDepartments;

	int currentNumberOfWorkers;
	int maxNumberOfWorkers;
	
	int currentNumberOfVisitors;
	int maxNumberOfVisitors;


public:
	Hospital(const string& name, research_center& researchCenter);

	// getters
	const string& getName() const { return name; };
	const research_center& getResearchCenter() const { return researchCenter; };
	int getNumberOfDoctors() const;
	int getNumberOfNurses() const;
	int getNumberOfWorkers() const { return currentNumberOfWorkers; };
	int getNumberOfVisitors() const { return currentNumberOfVisitors; };
	int getNumberOfResearchers() const;
	int getNumberOfDepartments() const { return currentNumberOfDepartments; };
	Department* getDepartmentByName(const string& name) const;
	Doctor* getDoctorByName(const string& name) const;
	Nurse* getNurseByName(const string& name) const;
	Visitor* getVisitorByName(const string& name) const;
	Researcher* getResearcherByName(const string& name) const;


	//setters
	void setName(const string& name);

    bool addNurseToDepartment(Nurse& nurse, const string& departmentName);
    bool addDoctorToDepartment(Doctor& doctor, const string& departmentName);

    // other methods
    bool addDepartment(Department& department);
    bool addVisitor(Visitor& visitor);
    bool addResearcher(Researcher& researcher);
    bool addDoctor(Doctor& doctor);
    bool addNurse(Nurse& nurse);
	bool addArticleToResearchCenter(Researcher& researcher, Article& article);
	bool addVisit(Visitor& visitor, VisitCard& Visitcard, const string& department);
	bool addVisitorToDepartment(Visitor& visitor, const string& departmentName);

	// operator to add staff
	const Hospital& operator+=(const Doctor& doctor);
	const Hospital& operator+=(const Nurse& nurse);

	
	 Doctor* findDoctorById(int id) const;
	 Nurse* findNurseById(int id) const;
	 Visitor* findVisitorById(int id) const;
	 Researcher* findResearcherById(int id) const;
	
	

	void printDepartmentVisitors(const string& departmentName) const;
	void printAllMedicalStaff() const;
	void printAllResearchers() const;
	void printAllDepartments() const;
	void printAllSurgens() const;
	void printAllDoctors() const;
	void printDepartmentMedicalStaff(const string& departmentName) const;

    bool DepartmentExist(const Department& department);
    bool NurseExist(const Nurse& nurse);
    bool DoctorExist(const Doctor& doctor);
    bool visitorExist(const Visitor& visitor);

};

#endif // HOSPITAL_H
