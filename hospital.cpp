#pragma warning(disable: 4996)

#include <iostream>
using namespace std;

#include "Worker.h"
#include "Hospital.h"
#include "Doctor.h"
#include "Nurse.h"
#include "Research_Center.h"
#include "Researcher.h"
#include "Article.h"
#include "Surgen.h"
#include "Department.h"
#include "Visitor.h"
#include "VisitCard.h"
#include "ResearcherDoctor.h"


#include <algorithm>
#include <ctime>
#include <cstring>
#include <memory>



Hospital::Hospital(const string name, research_center& researchCenter) : researchCenter(researchCenter)
{
    this->name == name ? name : std::string("");
    departments.reserve(2);
    workers.reserve(2);
    visitors.reserve(2);
}

Hospital::~Hospital()
{
    for (auto d : departments) delete d;
    for (auto w : workers) delete w;
    for (auto v : visitors) delete v;
}

bool Hospital::addDepartment(Department& department)
{
    if (DepartmentExist(department))
        return false;

    Department* departmentCopy = new Department(department.getName());
    departments.push_back(departmentCopy);
    return true;
}

bool Hospital::addDoctor(Doctor& doctor)
{
    if (DoctorExist(doctor))
        return false;
    Worker* doctorCopy = new Doctor(doctor);
    workers.push_back(doctorCopy);
    return true;
}

bool Hospital::addNurse(Nurse& nurse)
{
    if (NurseExist(nurse))
        return false;
    Worker* nurseCopy = new Nurse(nurse);
    workers.push_back(nurseCopy);
    return true;
}

bool Hospital::addVisitor(Visitor& visitor)
{
    if (visitorExist(visitor))
        return false;
    Visitor* visitorCopy = new Visitor(visitor);
    visitors.push_back(visitorCopy);
    return true;
}

bool Hospital::addResearcher(Researcher& researcher)
{
    return this->researchCenter.addResearcher(researcher);
}

bool Hospital::addWorker(Worker& worker)
{
    // use dynamic_cast to test type
    if (auto tempDoctor = dynamic_cast<Doctor*>(&worker)) return addDoctor(*tempDoctor);
    if (auto tempNurse = dynamic_cast<Nurse*>(&worker)) return addNurse(*tempNurse);
    return false;
}

bool Hospital::addWorkerToDepartment(Worker& worker, const string departmentName)
{
    if (auto tempDoctor = dynamic_cast<Doctor*>(&worker)) return addDoctorToDepartment(*tempDoctor, departmentName);
    if (auto tempNurse = dynamic_cast<Nurse*>(&worker)) return addNurseToDepartment(*tempNurse, departmentName);
    return false;
}

bool Hospital::addVisit(Visitor& visitor, VisitCard& Visitcard, const string department)
{
    for (auto d : departments) {
        if (strcmp(d->getName(), department) == 0) {
            addVisitor(visitor);
            for (auto v : visitors) {
                if (v->getId() == visitor.getId()) {
                    v->addVisitCard(Visitcard);
                    d->addVisitor(v);
                    return true;
                }
            }
            return false;
        }
    }
    return false;
}

bool Hospital::addNurseToDepartment(Nurse& nurse, const string departmentName)
{
    for (auto d : departments) {
        if (strcmp(d->getName(), departmentName) == 0) {
            addNurse(nurse);
            for (auto w : workers) {
                if (auto tempNurse = dynamic_cast<Nurse*>(w)) {
                    if (tempNurse->getId() == nurse.getId()) {
                        d->addNurse(tempNurse);
                        return true;
                    }
                }
            }
            return false;
        }
    }
    return false;
}

bool Hospital::addDoctorToDepartment(Doctor& doctor, const string departmentName)
{
    for (auto d : departments) {
        if (strcmp(d->getName(), departmentName) == 0) {
            addDoctor(doctor);
            for (auto w : workers) {
                if (auto tempDoctor = dynamic_cast<Doctor*>(w)) {
                    if (tempDoctor->getId() == doctor.getId()) {
                        d->addDoctor(tempDoctor);
                        return true;
                    }
                }
            }
            return false;
        }
    }
    return false;
}

bool Hospital::addVisitorToDepartment(Visitor& visitor, const string departmentName)
{
    for (auto d : departments) {
        if (strcmp(d->getName(), departmentName) == 0) {
            addVisitor(visitor);
            for (auto v : visitors) {
                if (v->getId() == visitor.getId()) {
                    d->addVisitor(v);
                    return true;
                }
            }
            return false;
        }
    }
    return false;
}

bool Hospital::addArticleToResearchCenter(Researcher& researcher, Article& article)
{
    for (auto r : researchCenter.getResearchers()) {
        if (r->getId() == researcher.getId()) {
            r->addArticle(article);
            return true;
        }
    }
    return false;
}

Hospital& Hospital::operator+=(const Doctor& doctor)
{
    Doctor* doctorCopy = new Doctor(doctor);
    if (!departments.empty()) departments[0]->addDoctor(doctorCopy);
    return *this;
}

Hospital& Hospital::operator+=(const Nurse& nurse)
{
    Nurse* n = new Nurse(nurse);
    if (!departments.empty()) departments[0]->addNurse(n);
    return *this;
}

int Hospital::getNumberOfNurses() const
{
    int numberOfNurses = 0;
    for (auto w : workers) if (dynamic_cast<Nurse*>(w)) ++numberOfNurses;
    return numberOfNurses;
}

int Hospital::getNumberOfDoctors() const
{
    int numberOfDoctors = 0;
    for (auto w : workers) if (dynamic_cast<Doctor*>(w)) ++numberOfDoctors;
    return numberOfDoctors;
}

int Hospital::getNumberOfResearchers() const
{
    return researchCenter.getCurrentNumberOfResearchers();
}

Doctor* Hospital::findDoctorById(int id) const
{
    for (auto w : workers) {
        if (auto d = dynamic_cast<Doctor*>(w)) {
            if (d->getId() == id) return d;
        }
    }
    cout << "Doctor with ID " << id << " not found." << endl;
    return nullptr;
}

Nurse* Hospital::findNurseById(int id) const
{
    for (auto w : workers) {
        if (auto n = dynamic_cast<Nurse*>(w)) {
            if (n->getId() == id) return n;
        }
    }
    cout << "Nurse with ID " << id << " not found." << endl;
    return nullptr;
}

Visitor* Hospital::findVisitorById(int id) const
{
    for (auto v : visitors) {
        if (v->getId() == id) return v;
    }
    cout << "Visitor with ID " << id << " not found." << endl;
    return nullptr;
}

Researcher* Hospital::findResearcherById(int id) const
{
    for (auto r : researchCenter.getResearchers()) if (r->getId() == id) return r;
    cout << "Researcher with ID " << id << " not found." << endl;
    return nullptr;
}

Department* Hospital::getDepartmentByName(const string name) const
{
    for (auto d : departments) if (strcmp(d->getName(), name) == 0) return d;
    return nullptr;
}

Doctor* Hospital::getDoctorByName(const string name) const
{
    for (auto w : workers) if (auto d = dynamic_cast<Doctor*>(w)) if (strcmp(d->getName(), name) == 0) return d;
    return nullptr;
}

Nurse* Hospital::getNurseByName(const string name) const
{
    for (auto w : workers) if (auto n = dynamic_cast<Nurse*>(w)) if (strcmp(n->getName(), name) == 0) return n;
    return nullptr;
}

Visitor* Hospital::getVisitorByName(const string name) const
{
    for (auto v : visitors) if (strcmp(v->getName(), name) == 0) return v;
    return nullptr;
}

Researcher* Hospital::getResearcherByName(const string name) const
{
    for (auto r : researchCenter.getResearchers()) if (strcmp(r->getName(), name) == 0) return r;
    return nullptr;
}

void Hospital::setName(const string name)
{
    this->name = name ? name : std::string();
}

void Hospital::printDepartmentVisitors(const string departmentName) const
{
    const Department* dept = getDepartmentByName(departmentName);
    if (dept) {
        cout << "Visitors in Department " << departmentName << ":" << endl;
        for (int i = 0; i < dept->getCurrentNumberOfVisitors(); ++i) {
            cout << *(dept->getVisitors()[i]) << endl;
        }
    }
    else {
        cout << "Department " << departmentName << " not found." << endl;
    }
}

void Hospital::printAllMedicalStaff() const
{
    if (!departments.empty()) {
        cout << "Medical Staff in Hospital " << name << ":" << endl;
        for (auto dept : departments) {
            cout << "Department: " << dept->getName() << endl;
            for (int j = 0; j < dept->getCurrentNumberOfDoctors(); ++j) {
                cout << *(dept->getDoctors()[j]) << endl;
            }
            for (int k = 0; k < dept->getCurrentNumberOfNurses(); ++k) {
                cout << *(dept->getNurses()[k]) << endl;
            }
        }
    }
    else {
        cout << "No departments in the hospital." << endl;
    }
}

void Hospital::printDepartmentMedicalStaff(const string departmentName) const
{
    const Department* dept = getDepartmentByName(departmentName);
    if (dept) {
        cout << "Medical Staff in Department " << departmentName << ":" << endl;
        cout << "Doctors:";
        dept->printDoctors();
        cout << endl;
        cout << "Nurses:";
        dept->printNurses();
        cout << endl;
    }
    else {
        cout << "Department " << departmentName << " not found." << endl;
    }
}

void Hospital::printAllResearchers() const
{
    if (researchCenter.getCurrentNumberOfResearchers() > 0) {
        cout << "Researchers in Hospital " << name << ":" << endl;
        for (auto researcher : researchCenter.getResearchers()) {
            if (auto rd = dynamic_cast<ResearcherDoctor*>(researcher)) cout << rd << endl;
            else cout << researcher << endl;
        }
    }
    else {
        cout << "No researchers in the hospital." << endl;
    }
}

void Hospital::printAllDepartments() const
{
    if (!departments.empty()) {
        cout << "Departments in Hospital " << name << ": ";
        for (size_t i = 0; i < departments.size(); ++i) {
            cout << departments[i]->getName();
            if (i + 1 < departments.size()) cout << ", ";
        }
        cout << endl;
    }
    else {
        cout << "No departments in the hospital." << endl;
    }
}

void Hospital::printAllSurgens() const
{
    if (!workers.empty()) {
        cout << "Surgeons in Hospital " << name << ":" << endl;
        for (auto w : workers) {
            if (auto d = dynamic_cast<Doctor*>(w)) {
                if (auto s = dynamic_cast<Surgen*>(d)) cout << *s << endl;
            }
        }
    }
    else {
        cout << "No workers in the hospital." << endl;
    }
}

void Hospital::printAllDoctors() const
{
    if (!workers.empty()) {
        cout << "Doctors in Hospital " << name << ":" << endl;
        for (auto w : workers) if (auto d = dynamic_cast<Doctor*>(w)) cout << *d << endl;
    }
    else {
        cout << "No workers in the hospital." << endl;
    }
}

bool Hospital::DepartmentExist(const Department& department)
{
    for (auto d : departments) if (d->getName() == department.getName()) return true;
    return false;
}

bool Hospital::NurseExist(const Nurse& nurse)
{
    for (auto w : workers) if (auto n = dynamic_cast<Nurse*>(w)) if (n->getId() == nurse.getId()) return true;
    return false;
}

bool Hospital::DoctorExist(const Doctor& doctor)
{
    for (auto w : workers) if (auto d = dynamic_cast<Doctor*>(w)) if (d->getId() == doctor.getId()) return true;
    return false;
}

bool Hospital::visitorExist(const Visitor& visitor)
{
    for (auto v : visitors) if (v->getId() == visitor.getId()) return true;
    return false;
}

