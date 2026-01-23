#ifndef HOSPITAL_H
#define HOSPITAL_H

#include <memory>

#include "Research_Center.h"

// forward declare global types used across the project
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
	char* name;
	Department** departments;
	research_center& researchCenter;
	Worker** workers;
	Visitor** visitors;

	int currentNumberOfDepartments;
	int maxNumberOfDepartments;

	int currentNumberOfWorkers;
	int maxNumberOfWorkers;
	
	int currentNumberOfVisitors;
	int maxNumberOfVisitors;


public:
	Hospital(const char* name, research_center& researchCenter);
	~Hospital();

	// getters
	const char* getName() const { return name; };
	const research_center& getResearchCenter() const { return researchCenter; };
	int getNumberOfDoctors() const;
	int getNumberOfNurses() const;
	int getNumberOfWorkers() const { return currentNumberOfWorkers; };
	int getNumberOfVisitors() const { return currentNumberOfVisitors; };
	int getNumberOfResearchers() const;
	int getNumberOfDepartments() const { return currentNumberOfDepartments; };
	Department* getDepartmentByName(const char* name) const;
	Doctor* getDoctorByName(const char* name) const;
	Nurse* getNurseByName(const char* name) const;
	Visitor* getVisitorByName(const char* name) const;
	Researcher* getResearcherByName(const char* name) const;


	//setters
	void setName(const char* name);


	
	bool addNurseToDepartment(Nurse& nurse, const char* departmentName);
	bool addDoctorToDepartment(Doctor& doctor, const char* departmentName);


	// other methods
	bool addDepartment(Department& department);
	
	bool addVisitor(Visitor& visitor);
	bool addResearcher(Researcher& researcher);
	bool addDoctor(Doctor& doctor);
	bool addNurse(Nurse& nurse);
	bool addWorker(Worker& worker);

	bool addWorkerToDepartment(Worker& worker, const char* departmentName);
	bool addVisit(Visitor& visitor, VisitCard& Visitcard, const char* department);
	bool addVisitorToDepartment(Visitor& visitor, const char* departmentName);
	bool addArticleToResearchCenter(Researcher& researcher, Article& article);

	// operator to add staff
	Hospital& operator+=(const Doctor& doctor);
	Hospital& operator+=(const Nurse& nurse);

	
	Doctor* findDoctorById(int id) const;
	Nurse* findNurseById(int id) const;
	Visitor* findVisitorById(int id) const;
	Researcher* findResearcherById(int id) const;
	
	

	void printDepartmentVisitors(const char* departmentName) const;
	void printAllMedicalStaff() const;
	void printDepartmentMedicalStaff(const char* departmentName) const;
	void printAllResearchers() const;
	void printAllDepartments() const;
	void printAllSurgens() const;
	
	bool DepartmentExist(const Department& department);
	bool NurseExist(const Nurse& nurse);
	bool DoctorExist(const Doctor& doctor);
	bool visitorExist(const Visitor& visitor);


};

#endif // HOSPITAL_H