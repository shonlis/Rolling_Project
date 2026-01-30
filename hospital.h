#ifndef HOSPITAL_H
#define HOSPITAL_H

#include <string>
#include <vector>

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
    std::string name;
    std::vector<Department*> departments;
    research_center& researchCenter;
    std::vector<Worker*> workers;
    std::vector<Visitor*> visitors;

public:
    Hospital(const string name, research_center& researchCenter);
    ~Hospital();

    // getters
    const string getName() const { return name.c_str(); };
    const research_center& getResearchCenter() const { return researchCenter; };
    int getNumberOfDoctors() const;
    int getNumberOfNurses() const;
    int getNumberOfWorkers() const { return static_cast<int>(workers.size()); };
    int getNumberOfVisitors() const { return static_cast<int>(visitors.size()); };
    int getNumberOfResearchers() const;
    int getNumberOfDepartments() const { return static_cast<int>(departments.size()); };
    Department* getDepartmentByName(const string name) const;
    Doctor* getDoctorByName(const string name) const;
    Nurse* getNurseByName(const string name) const;
    Visitor* getVisitorByName(const string name) const;
    Researcher* getResearcherByName(const string name) const;


    //setters
    void setName(const string name);

    bool addNurseToDepartment(Nurse& nurse, const string departmentName);
    bool addDoctorToDepartment(Doctor& doctor, const string departmentName);

    // other methods
    bool addDepartment(Department& department);
    bool addVisitor(Visitor& visitor);
    bool addResearcher(Researcher& researcher);
    bool addDoctor(Doctor& doctor);
    bool addNurse(Nurse& nurse);
    bool addWorker(Worker& worker);

    bool addWorkerToDepartment(Worker& worker, const string departmentName);
    bool addVisit(Visitor& visitor, VisitCard& Visitcard, const string department);
    bool addVisitorToDepartment(Visitor& visitor, const string departmentName);
    bool addArticleToResearchCenter(Researcher& researcher, Article& article);

    // operator to add staff
    Hospital& operator+=(const Doctor& doctor);
    Hospital& operator+=(const Nurse& nurse);

    Doctor* findDoctorById(int id) const;
    Nurse* findNurseById(int id) const;
    Visitor* findVisitorById(int id) const;
    Researcher* findResearcherById(int id) const;

    void printDepartmentVisitors(const string departmentName) const;
    void printAllMedicalStaff() const;
    void printDepartmentMedicalStaff(const string departmentName) const;
    void printAllResearchers() const;
    void printAllDepartments() const;
    void printAllSurgens() const;
    void printAllDoctors() const;

    bool DepartmentExist(const Department& department);
    bool NurseExist(const Nurse& nurse);
    bool DoctorExist(const Doctor& doctor);
    bool visitorExist(const Visitor& visitor);

};

#endif // HOSPITAL_H
