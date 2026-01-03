#include "hospital.h"
#include "doctor.h"
#include "nurse.h"
#include "Researcher.h"
#include <algorithm>
#include <ctime>
#include <cstring>
#include <memory>
#include <vector>
#include <iostream>


Hospital::Hospital(const char* name)
    : name(nullptr), departments(nullptr), researchCenters(*(new research_center())), currentNumberOfDepartments(0), maxNumberOfDepartments(2)
{
    this->name = new char[strlen(name) + 1];
    strcpy(this->name, name);
}

Hospital::~Hospital()
{
    delete[] name;
    if (departments) {
        for (int i = 0; i < currentNumberOfDepartments; ++i) {
            delete departments[i];
        }
        delete[] departments;
    }
}

Department* Hospital::addDepartment(const char* name) {
    // Ensure departments array exists and has capacity
    if (!departments) {
        departments = new Department*[maxNumberOfDepartments];
        for (int i = 0; i < maxNumberOfDepartments; ++i) departments[i] = nullptr;
    }

    // Resize if needed
    if (currentNumberOfDepartments >= maxNumberOfDepartments) {
        int newMax = maxNumberOfDepartments * 2;
        Department** newArr = new Department*[newMax];
        for (int i = 0; i < newMax; ++i) newArr[i] = nullptr;
        for (int i = 0; i < currentNumberOfDepartments; ++i) newArr[i] = departments[i];
        delete[] departments;
        departments = newArr;
        maxNumberOfDepartments = newMax;
    }

    Department* d = new Department(name);
    departments[currentNumberOfDepartments++] = d;
    return d;
}

research_center* Hospital::addResearchCenter(const std::string &name) {
    research_center* rc = new research_center(name.c_str());
	return rc;
}

Doctor* Hospital::addDoctor(const Doctor& doctor)
{
    Doctor* newDoctor = new Doctor(doctor);
    return newDoctor;
}

Hospital& Hospital::operator+=(const Doctor& doctor)
{
    // create a copy and add to first department if exists
    Doctor* d = new Doctor(doctor);
    if (departments && currentNumberOfDepartments > 0) {
        departments[0]->addDoctor(*d);
    }
    return *this;
}

Nurse* Hospital::addNurse(const Nurse& nurse)
{
    Nurse* newNurse = new Nurse(nurse);
    return newNurse;
}

Hospital& Hospital::operator+=(const Nurse& nurse)
{
    Nurse* n = new Nurse(nurse);
    if (departments && currentNumberOfDepartments > 0) {
        departments[0]->addNurse(*n);
    }
    return *this;
}

Visitor* Hospital::addVisitor(const Person& person) {
    Visitor* newVisitor = new Visitor(person);
    return newVisitor;
}

void Hospital::addVisit(const VisitCard& vc) {
    for (int i = 0; i < currentNumberOfDepartments; ++i) {
        Department* dept = departments[i];
        if (strcmp(dept->getName(), vc.getDepartmentsToVisit().getName()) == 0) {
            Visitor* visitor = nullptr;
            for (int j = 0; j < dept->getCurrentNumberOfVisitors(); ++j) {
                if (dept->getVisitors()[j]->getId() == vc.getHostWorker()->getId()) {
                    visitor = dept->getVisitors()[j];
                    break;
                }
            }
            if (visitor) {
                // Create a new VisitCard using the available constructor, not the copy constructor
                VisitCard* newVisitCard = new VisitCard(
                    vc.getPurposeOfVisit(),
                    vc.getVisitingDate(),
                    const_cast<Department&>(vc.getDepartmentsToVisit()),
                    const_cast<Worker*>(vc.getHostWorker())
                );
                visitor->addVisitCard(*newVisitCard);
            }
            break;
        }
    }
}

Researcher* Hospital::addResearcher(Researcher& researcher)
{
	researchCenters.addResearcher(researcher);
    Researcher* newResearcher = new Researcher(researcher);
	return newResearcher;
}

Article* Hospital::addArticleToResearcher(const Article& article)
{
    Article* newArticle = new Article(
        article.getTitle(),
        article.getPublicationDate(),
        article.getMagazinName()
    );
    return newArticle;
}

int Hospital::countDoctors() const {
    int c = 0;

    if (departments) {
        for (int i = 0; i < currentNumberOfDepartments; ++i) {
            Department* dept = departments[i];
            for (int j = 0; j < dept->getCurrentNumberOfDoctors(); ++j) {
                c++;
            }
        }
    }
	return c;
}

int Hospital::countNurses() const {
    int c = 0;
    if (departments) {
        for (int i = 0; i < currentNumberOfDepartments; ++i) {
            Department* dept = departments[i];
            for (int j = 0; j < dept->getCurrentNumberOfNurses(); ++j) {
                c++;
            }
        }
    }
	return c;
}

int Hospital::countDepartments() const {
    return currentNumberOfDepartments;
}

// find department by name, check all departments and if dont found return nullptr
Department* Hospital::getDepartmentByName(const char* name) const
{
    if (departments) {
		for(int i=0; i<currentNumberOfDepartments; i++) {
            if (strcmp(departments[i]->getName(), name) == 0) {
                return departments[i];
            }
		}
	}
	return nullptr;
}

void Hospital::printDepartmentVisitors(const char* departmentName) const
{
    Department* dept = getDepartmentByName(departmentName);
    if (dept) {
        cout << "Visitors in Department " << departmentName << endl;
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
    if (departments) {
        cout << "Medical Staff in Hospital " << name << ":\n";
        for (int i = 0; i < currentNumberOfDepartments; ++i) {
            Department* dept = departments[i];
            cout << "Department: " << dept->getName() << "\n";
            for (int j = 0; j < dept->getCurrentNumberOfDoctors(); ++j) {
                cout << *(dept->getDoctors()[j]) << "\n";
            }
            for (int k = 0; k < dept->getCurrentNumberOfNurses(); ++k) {
                cout << *(dept->getNurses()[k]) << "\n";
            }
        }
    } else {
        cout << "No departments in the hospital.\n";
	}
}

void Hospital::printAllResearchers() const
{
    if (researchCenters.getCurrentNumberOfResearchers() > 0) {
        cout << "Researchers in Hospital " << name << ":\n";
        for (int i = 0; i < researchCenters.getCurrentNumberOfResearchers(); ++i) {
            Researcher* researcher = researchCenters.getResearchers()[i];
            cout << *researcher << "\n";
        }
    } else {
        cout << "No researchers in the hospital.\n";
	}
}

void Hospital::searchVisitorById(int id) const
{
    if (departments) {
        for (int i = 0; i < currentNumberOfDepartments; ++i) {
            Department* dept = departments[i];
            for (int j = 0; j < dept->getCurrentNumberOfVisitors(); ++j) {
                Visitor* visitor = dept->getVisitors()[j];
                if (visitor->getId() == id) {
                    cout << "Visitor found:\n" << *visitor << "\n";
                    return;
                }
            }
        }
	}
	cout << "Visitor with ID " << id << " not found.\n";
}



