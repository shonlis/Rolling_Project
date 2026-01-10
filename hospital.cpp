#pragma warning(disable: 4996)
#include <iostream>
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



Hospital::Hospital(const char* name, research_center& researchCenter) : researchCenter(researchCenter)
{
    this->name = new char[strlen(name) + 1];
    strcpy(this->name, name);

    maxNumberOfDepartments = 2;
    departments = new Department * [maxNumberOfDepartments];
    currentNumberOfDepartments = 0;

    maxNumberOfDoctors = 2;
    doctors = new Doctor * [maxNumberOfDoctors];
    currentNumberOfDoctors = 0;

    maxNumberOfNurses = 2;
    nurses = new Nurse * [maxNumberOfNurses];
    currentNumberOfNurses = 0;
    
    maxNumberOfVisitors = 2;
    visitors = new Visitor * [maxNumberOfVisitors];
    currentNumberOfVisitors = 0;
    
}
Hospital::~Hospital()
{
    delete[] name;

        for (int i = 0; i < currentNumberOfDepartments; ++i) {
            delete departments[i];
        }
        delete[] departments;

        for (int i = 0; i < currentNumberOfDoctors; ++i) {
            delete doctors[i];
        }
        delete[] doctors;

        for (int i = 0; i < currentNumberOfNurses; ++i) {
            delete nurses[i];
        }
        delete[] nurses;

        for (int i = 0; i < currentNumberOfVisitors; ++i) {
            delete visitors[i];
        }
        delete[] visitors;
}
bool Hospital::addDepartment(Department& department)
{
    if (DepartmentExist(department))
        return false;

    // Resize if needed
    if (currentNumberOfDepartments == maxNumberOfDepartments)
    {
        maxNumberOfDepartments *= 2;
        Department** temp = new Department * [maxNumberOfDepartments];
        for (int i = 0; i < currentNumberOfDepartments; i++)
            temp[i] = this->departments[i];

        delete[]this->departments;
        this->departments = temp;
    }

	Department* departmentCopy = new Department(department);
    this->departments[currentNumberOfDepartments] = departmentCopy;
    currentNumberOfDepartments++;
    return true;
}
bool Hospital::addDoctor(Doctor& doctor)
{
    if (DoctorExist(doctor))
        return false;

    if (currentNumberOfDoctors == maxNumberOfDoctors)
    {
        maxNumberOfDoctors *= 2;
        Doctor** temp = new Doctor * [maxNumberOfDoctors];
        for (int i = 0; i < currentNumberOfDoctors; i++)
            temp[i] = this->doctors[i];

        delete[]this->doctors;
        this->doctors = temp;
    }
    Doctor* doctorCopy = new Doctor(doctor);
    this->doctors[currentNumberOfDoctors] = doctorCopy;
    currentNumberOfDoctors++;
    return true;
}
bool Hospital::addNurse(Nurse& nurse)
{
    if (NurseExist(nurse))
        return false;

    if (currentNumberOfNurses == maxNumberOfNurses)
    {
        maxNumberOfNurses *= 2;
        Nurse** temp = new Nurse * [maxNumberOfNurses];
        for (int i = 0; i < currentNumberOfNurses; i++)
            temp[i] = this->nurses[i];

        delete[]this->nurses;
        this->nurses = temp;
    }

    Nurse* nurseCopy = new Nurse(nurse);
    this->nurses[currentNumberOfNurses] = nurseCopy;
    currentNumberOfNurses++;
    return true;
}
bool Hospital::addVisitor(Visitor& visitor)
{
    if (visitorExist(visitor))
        return false;

    if (currentNumberOfVisitors == maxNumberOfVisitors)
    {
        maxNumberOfVisitors *= 2;
        Visitor** temp = new Visitor * [maxNumberOfVisitors];
        for (int i = 0; i < currentNumberOfVisitors; i++)
            temp[i] = this->visitors[i];

        delete[]this->visitors;
        this->visitors = temp;
    }

    Visitor* visitorCopy = new Visitor(visitor);
    this->visitors[currentNumberOfVisitors] = visitorCopy;
    currentNumberOfVisitors++;
    return true;
}
bool Hospital::addResearcher(Researcher& researcher)
{
    return this->researchCenter.addResearcher(researcher);
}
bool Hospital::addVisit(Visitor& visitor, VisitCard& Visitcard, const char* department)
{
    /*
	* this function getts a visitor ,visitcard and department.
	* checking if the department exists in the hospital. 
	* add the visitor to the hospitals visitors list.
	* add the visitcard to the visitor's visitcards list.
	* add the visitor to the department's visitors list.
    */
    for (int i = 0; i < currentNumberOfDepartments; i++)
    {
        if (strcmp(departments[i]->getName(), department) == 0)
        {
            addVisitor(visitor);
                for (int j = 0; j < currentNumberOfVisitors; j++)
                {
                    if (visitors[j]->getId() == visitor.getId())
                    {
                        visitors[j]->addVisitCard(Visitcard);
                        departments[i]->addVisitor(visitors[j]);
                        return true;
                    }
                }
        }
        else
        {
            return false;
        }
    }
    return false;
}
bool Hospital::addNurseToDepartment(Nurse& nurse, const char* departmentName)
{
    /*
	* this function getts a nurse and department name.
	* first checking if the department exists in the hospital.
	* add the nurse to the hospitals nurses list.
	* find the nurse in the hospital's nurses list and add it to the department's nurses list.
    */
    for (int i = 0; i < currentNumberOfDepartments; i++)
    {
        if (strcmp(departments[i]->getName(), departmentName) == 0)
        {
            addNurse(nurse);
            for (int j = 0; j < currentNumberOfNurses; j++)
            {
                if (nurses[j]->getId() == nurse.getId())
                {
                    departments[i]->addNurse(nurses[j]);
                    return true;
                }
            }
        }
        else
        {
            return false;
        }
    }
    return false;
}
bool Hospital::addDoctorToDepartment(Doctor& doctor, const char* departmentName)
{
    /*
    * this function getts a doctor and department name.
    * first checking if the department exists in the hospital.
    * add the doctor to the hospitals doctors list.
    * find the doctor in the hospital's doctors list and add it to the department's doctors list.
    */
    for (int i = 0; i < currentNumberOfDepartments; i++)
    {
        if (strcmp(departments[i]->getName(), departmentName) == 0)
        {
            addDoctor(doctor);
            for (int j = 0; j < currentNumberOfDoctors; j++)
            {
                if (doctors[j]->getId() == doctor.getId())
                {
                    departments[i]->addDoctor(doctors[j]);
                    return true;
                }
            }
        }
        else
        {
            return false;
        }
    }
    return false;
}
bool Hospital::addResearcherToResearchCenter(Researcher& researcher, Article& article)
{
	addResearcher(researcher);
	for (int i = 0; i < researchCenter.getCurrentNumberOfResearchers(); i++)
	{
		if (researchCenter.getResearchers()[i]->getId() == researcher.getId())
		{
			researchCenter.getResearchers()[i]->addArticle(article);
			return true;
		}
	}
    return false;
}

/***************************************************************************************************/
Hospital& Hospital::operator+=(const Doctor& doctor)
{
    // create a copy and add to first department if exists
    Doctor* doctorCopy = new Doctor(doctor);
    if (departments && currentNumberOfDepartments > 0) {
        departments[0]->addDoctor(doctorCopy);
    }
    return *this;
}
Hospital& Hospital::operator+=(const Nurse& nurse)
{
    Nurse* n = new Nurse(nurse);
    if (departments && currentNumberOfDepartments > 0) {
        departments[0]->addNurse(n);
    }
    return *this;
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
/**/
// find department by name, check all departments and if dont found return nullptr
/**/
Department* Hospital::getDepartmentByName(const char* name) const
{
    if (departments) {
        for (int i = 0; i < currentNumberOfDepartments; i++) {
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
        for (int i = 0; i < currentNumberOfDepartments; i++) {
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
        for (int i = 0; i < currentNumberOfDepartments; i++) {
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
        for (int i = 0; i < currentNumberOfDepartments; i++) {
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
    }
    else {
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
        }
        else {
            cout << "Department " << departmentName << " not found." << endl;
        }
    }
}
void Hospital::printAllResearchers() const
{
    if (researchCenter.getCurrentNumberOfResearchers() > 0) {
        cout << "Researchers in Hospital " << name << ":" << endl;
        for (int i = 0; i < researchCenter.getCurrentNumberOfResearchers(); ++i) {
            Researcher* researcher = researchCenter.getResearchers()[i];
            cout << *researcher << endl;
        }
    }
    else {
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
    }
    else {
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
/***************************************************************************************************/

bool Hospital::DepartmentExist(const Department& department)
{
    for (int i = 0; i < currentNumberOfDepartments; i++)
    {
        if (departments[i]->getName() == department.getName())
            return true;
    }
    return false;
}
bool Hospital::NurseExist(const Nurse& nurse)
{
    for (int i = 0; i < currentNumberOfNurses; i++)
    {
        if (nurses[i]->getId() == nurse.getId())
            return true;
    }
    return false;
}
bool Hospital::DoctorExist(const Doctor& doctor)
{
    for (int i = 0; i < currentNumberOfDoctors; i++)
    {
        if (doctors[i]->getId() == doctor.getId())
            return true;
    }
    return false;
}
bool Hospital::visitorExist(const Visitor& visitor)
{
    for (int i = 0; i < currentNumberOfVisitors; i++)
    {
        if (visitors[i]->getId() == visitor.getId())
            return true;
    }
    return false;
}

