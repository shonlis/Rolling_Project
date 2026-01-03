#ifndef HOSPITAL_H
#define HOSPITAL_H

#include <string>
#include <vector>
#include <memory>

#include "Department.h"
#include "Worker.h"
#include "VisitCard.h"
#include "Visitor.h"
#include "research_center.h"

// forward declare global types used across the project
class Doctor;
class Nurse;
class Researcher;

class Hospital {
	char* name;
	Department** departments;
	research_center& researchCenters;
	int currentNumberOfDepartments;
	int maxNumberOfDepartments;

public:
	Hospital(const char* name = "none");
	~Hospital();

	// getters
	const char* getName() const { return name; };

	//setters
	void setName(const char* name);

	// other methods
	Department* addDepartment(const char* name);
	research_center* addResearchCenter(const std::string& name);

	Doctor* addDoctor(const Doctor& doctor);
	Nurse* addNurse(const Nurse& nurse);
    // operator to add staff
    Hospital& operator+=(const Doctor& doctor);
    Hospital& operator+=(const Nurse& nurse);
	Visitor* addVisitor(const Person& person);
	void addVisit(const VisitCard& vc);
	Researcher* addResearcher(Researcher& researcher);
	Article* addArticleToResearcher(const Article& article);

	Doctor* findDoctorById(int id);
	Nurse* findNurseById(int id);
	Department* getDepartmentByName(const char* name) const;

	int countDoctors() const;
	int countNurses() const;
	int countVisitors() const;
	int countResearchers() const;
	int countDepartments() const;

	void printDepartmentVisitors(const char* departmentName) const;
	void printAllMedicalStaff() const;
	void printAllResearchers() const;
	void searchVisitorById(int id) const;
	};

#endif // HOSPITAL_H
