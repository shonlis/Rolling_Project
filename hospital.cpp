#pragma warning(disable: 4996)
#include "Hospital.h"
#include "Doctor.h"
#include "Nurse.h"
#include "Research_Center.h"
#include "Researcher.h"
#include "Article.h"
#include <algorithm>
#include <ctime>
#include <cstring>
#include <memory>
#include <iostream>


Hospital::Hospital(const char* name)
    : name(nullptr), departments(nullptr), researchCenters(*(new research_center())), currentNumberOfDepartments(0), maxNumberOfDepartments(2)
{
    this->name = new char[strlen(name) + 1];
    strcpy(this->name, name);
    departments = new Department * [maxNumberOfDepartments];
    for (int i = 0; i < maxNumberOfDepartments; ++i) departments[i] = nullptr;
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

bool Hospital::setResearchCenter(research_center& center)
{
	researchCenters = center;
    return false;
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

research_center* Hospital::addResearchCenter(const char* name) {
    research_center* rc = new research_center(name);
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
			c += dept->getCurrentNumberOfDoctors();
        }
    }
	return c;
}

int Hospital::countNurses() const {
    int c = 0;
    if (departments) {
        for (int i = 0; i < currentNumberOfDepartments; ++i) {
            Department* dept = departments[i];
            c += dept->getCurrentNumberOfNurses();

        }
    }
	return c;
}

int Hospital::countVisitors() const
{
    int c = 0;
    if (departments) {
        for (int i = 0; i < currentNumberOfDepartments; ++i) {
            Department* dept = departments[i];
            c += dept->getCurrentNumberOfVisitors();
        }
    }
    return c;
}

int Hospital::countResearchers() const
{
    return 0;
}

int Hospital::countDepartments() const {
    return currentNumberOfDepartments;
}

Doctor* Hospital::findDoctorById(int id) const
{
    if (departments) {
        for (int i = 0; i < currentNumberOfDepartments; ++i) {
            Department* dept = departments[i];
            for (int j = 0; j < dept->getCurrentNumberOfDoctors(); ++j) {
                Doctor* doctor = dept->getDoctors()[j];
                if (doctor->getId() == id) {
                    return doctor;
                }
            }
        }
    }
    cout << "Visitor with ID " << id << " not found." << endl;
    return nullptr;
}

Nurse* Hospital::findNurseById(int id) const
{
    if (departments) {
        for (int i = 0; i < currentNumberOfDepartments; ++i) {
            Department* dept = departments[i];
            for (int j = 0; j < dept->getCurrentNumberOfNurses(); ++j) {
                Nurse* nusre = dept->getNurses()[j];
                if (nusre->getId() == id) {
                    return nusre;
                }
            }
        }
    }
    cout << "Visitor with ID " << id << " not found." << endl;
    return nullptr;
}

Visitor* Hospital::findVisitorById(int id) const
{
    if (departments) {
        for (int i = 0; i < currentNumberOfDepartments; ++i) {
            Department* dept = departments[i];
            for (int j = 0; j < dept->getCurrentNumberOfVisitors(); ++j) {
                Visitor* visitor = dept->getVisitors()[j];
                if (visitor->getId() == id) {
                    return visitor;
                }
            }
        }
    }
    cout << "Visitor with ID " << id << " not found." << endl;
	return nullptr;
}

Researcher* Hospital::findResearcherById(int id) const
{
    for (int j = 0; j < researchCenters.getCurrentNumberOfResearchers(); ++j) {
        Researcher* researcher = researchCenters.getResearchers()[j];
        if (researcher->getId() == id) {
            return researcher;
        }
    }
    cout << "Researcher with ID " << id << " not found." << endl;
    return nullptr;
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

Doctor* Hospital::getDoctorByName(const char* name) const
{
    if (departments) {
		for(int i=0; i<currentNumberOfDepartments; i++) {
            Department* dept = departments[i];
            for (int j = 0; j < dept->getCurrentNumberOfDoctors(); ++j) {
                Doctor* doctor = dept->getDoctors()[j];
                if (strcmp(doctor->getName(), name) == 0) {
                    return doctor;
                }
            }
		}
	}
	return nullptr;
}

Nurse* Hospital::getNurseByName(const char* name) const
{
    if (departments) {
		for(int i=0; i<currentNumberOfDepartments; i++) {
            Department* dept = departments[i];
            for (int j = 0; j < dept->getCurrentNumberOfNurses(); ++j) {
                Nurse* nurse = dept->getNurses()[j];
                if (strcmp(nurse->getName(), name) == 0) {
                    return nurse;
                }
            }
		}
	}
	return nullptr;
}

Visitor* Hospital::getVisitorByName(const char* name) const
{
    if (departments) {
		for(int i=0; i<currentNumberOfDepartments; i++) {
            Department* dept = departments[i];
            for (int j = 0; j < dept->getCurrentNumberOfVisitors(); ++j) {
                Visitor* visitor = dept->getVisitors()[j];
                if (strcmp(visitor->getName(), name) == 0) {
                    return visitor;
                }
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
        cout << "Medical Staff in Hospital " << name << ":" << endl;
        for (int i = 0; i < currentNumberOfDepartments; ++i) {
            Department* dept = departments[i];
            cout << "Department: " << dept->getName() << endl;
            for (int j = 0; j < dept->getCurrentNumberOfDoctors(); ++j) {
                cout << *(dept->getDoctors()[j]) << endl;
            }
            for (int k = 0; k < dept->getCurrentNumberOfNurses(); ++k) {
                cout << *(dept->getNurses()[k]) << endl;
            }
        }
    } else {
        cout << "No departments in the hospital." << endl;
	}
}

void Hospital::printDepartmentMedicalStaff(const char* departmentName) const
{
    if (departments) {
        Department* dept = getDepartmentByName(departmentName);
        if (dept) {
            cout << "Medical Staff in Department " << departmentName << ":" << endl;
            cout << "Doctors:";
            dept->printDoctors();
            cout << endl;
			cout << "Nurses:";
            dept->printNurses();
            cout << endl;
        } else {
            cout << "Department " << departmentName << " not found." << endl;
        }
    }
}

void Hospital::printAllResearchers() const
{
    if (researchCenters.getCurrentNumberOfResearchers() > 0) {
        cout << "Researchers in Hospital " << name << ":" << endl;
        for (int i = 0; i < researchCenters.getCurrentNumberOfResearchers(); ++i) {
            Researcher* researcher = researchCenters.getResearchers()[i];
            cout << *researcher << endl;
        }
    } else {
        cout << "No researchers in the hospital." << endl;
	}
}

void Hospital::printAllDepartments() const
{
    if (departments) {
		cout << "Departments in Hospital " << name << ": ";
        for (int i = 0; i < currentNumberOfDepartments; ++i) 
        {
            Department* department = departments[i];
            cout << department->getName();
            if (i < currentNumberOfDepartments - 1)
            {
                cout << ", ";
            }
        }
        cout << endl;
    } else {
        cout << "No departments in the hospital." << endl;
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
                    cout << "Visitor found:" << endl << *visitor << endl;
                    return;
                }
            }
        }
	}
	cout << "Visitor with ID " << id << " not found." << endl;
}



