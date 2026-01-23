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

    maxNumberOfWorkers = 2;
    workers = new Worker * [maxNumberOfWorkers];
    currentNumberOfWorkers = 0;

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

        for (int i = 0; i < currentNumberOfWorkers; ++i) {
            delete workers[i];
        }
        delete[] workers;
       
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

    Department* departmentCopy = new Department(department.getName());
    this->departments[currentNumberOfDepartments] = departmentCopy;
    currentNumberOfDepartments++;
    return true;
}
bool Hospital::addDoctor(Doctor& doctor)
{
    if (DoctorExist(doctor))
        return false;

    if (currentNumberOfWorkers == maxNumberOfWorkers)
    {
        maxNumberOfWorkers *= 2;
        Worker** temp = new Worker * [maxNumberOfWorkers];
        for (int i = 0; i < currentNumberOfWorkers; i++)
            temp[i] = this->workers[i];

        delete[]this->workers;
        this->workers = temp;
    }
    Worker* doctorCopy = new Doctor(doctor);
    this->workers[currentNumberOfWorkers] = doctorCopy;
    currentNumberOfWorkers++;
    return true;
}
bool Hospital::addNurse(Nurse& nurse)
{
    if (NurseExist(nurse))
        return false;

    if (currentNumberOfWorkers == maxNumberOfWorkers)
    {
        maxNumberOfWorkers *= 2;
        Worker** temp = new Worker * [maxNumberOfWorkers];
        for (int i = 0; i < currentNumberOfWorkers; i++)
            temp[i] = this->workers[i];

        delete[]this->workers;
        this->workers = temp;
    }

    Worker* nurseCopy = new Nurse(nurse);
    this->workers[currentNumberOfWorkers] = nurseCopy;
    currentNumberOfWorkers++;
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
bool Hospital::addWorker(Worker& worker)
{
    Doctor& tempDoctor = dynamic_cast<Doctor&>(worker);
    if (typeid(tempDoctor) == typeid(Doctor))
    {
        
        return addDoctor(tempDoctor);
    }
    Nurse& tempNurse = dynamic_cast<Nurse&>(worker);
    if (typeid(tempNurse) == typeid(Nurse))
    {
        
        return addNurse(tempNurse);
    }
    else
    {
        return false;
    }
}
bool Hospital::addWorkerToDepartment(Worker& worker, const char* departmentName)
{

    Doctor& tempDoctor = dynamic_cast<Doctor&>(worker);
    if (typeid(tempDoctor) == typeid(Doctor))
    {

        return addDoctorToDepartment(tempDoctor, departmentName);
    }
    Nurse& tempNurse = dynamic_cast<Nurse&>(worker);
    if (typeid(tempNurse) == typeid(Nurse))
    {

        return addNurseToDepartment(tempNurse, departmentName);
    }
    else
    {
        return false;
    }
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
            // found department but didn't find visitor in hospital -> fail
            return false;
        }
    }
    // department not found
    return false;
}
bool Hospital::addNurseToDepartment(Nurse& nurse, const char* departmentName)
{
    for (int i = 0; i < currentNumberOfDepartments; i++)
    {
        if (strcmp(departments[i]->getName(), departmentName) == 0)
        {
            addNurse(nurse);
            for (int j = 0; j < currentNumberOfWorkers; j++)
            {
				Nurse* tempNurse = dynamic_cast<Nurse*>(workers[j]);
                if (tempNurse)
                {
                    if (tempNurse->getId() == nurse.getId())
                    {
                        departments[i]->addNurse(tempNurse);
                        return true;
                    }
                }
                
            }
            // found department but nurse not present in hospital -> fail
            return false;
        }
    }
    // department not found
    return false;
}

bool Hospital::addDoctorToDepartment(Doctor& doctor, const char* departmentName)
{
    for (int i = 0; i < currentNumberOfDepartments; i++)
    {
        if (strcmp(departments[i]->getName(), departmentName) == 0)
        {
            addDoctor(doctor);
            for (int j = 0; j < currentNumberOfWorkers; j++)
            {
				Doctor* tempDoctor = dynamic_cast<Doctor*>(workers[j]);
                if (tempDoctor)
                {
                    if (tempDoctor->getId() == doctor.getId())
                    {
                        departments[i]->addDoctor(tempDoctor);
                        return true;
                    }
                }
                
            }
            // found department but doctor not present in hospital -> fail
            return false;
        }
    }
    // department not found
    return false;
}

bool Hospital::addVisitorToDepartment(Visitor& visitor, const char* departmentName)
{
    /*
    * this function getts a visitor and department name.
    * first checking if the department exists in the hospital.
    * add the visitor to the hospitals visitors list.
    * find the visitor in the hospital's visitors list and add it to the department's visitors list.
    */
    for (int i = 0; i < currentNumberOfDepartments; i++)
    {
        if (strcmp(departments[i]->getName(), departmentName) == 0)
        {
            addVisitor(visitor);
            for (int j = 0; j < currentNumberOfVisitors; j++)
            {
                if (visitors[j]->getId() == visitor.getId())
                {
                    departments[i]->addVisitor(visitors[j]);
                    return true;
                }
            }
            // found department but visitor not present in hospital -> fail
            return false;
        }
    }
    // department not found
    return false;
}
bool Hospital::addArticleToResearchCenter(Researcher& researcher, Article& article)
{
	
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


int Hospital::getNumberOfNurses() const
{
	int numberOfNurses = 0;
    for (int j = 0; j < currentNumberOfWorkers; j++)
    {
        Nurse* tempNurse = dynamic_cast<Nurse*>(workers[j]);
        if (tempNurse)
        {
            numberOfNurses++;
        }

    }
	return numberOfNurses;
}

int Hospital::getNumberOfDoctors() const
{
    int numberOfDoctors = 0;
    for (int j = 0; j < currentNumberOfWorkers; j++)
    {
        Doctor* tempDoctor = dynamic_cast<Doctor*>(workers[j]);
        if (tempDoctor)
        {
            numberOfDoctors++;
        }

    }
	return numberOfDoctors;
}

int Hospital::getNumberOfResearchers() const
{
    if (researchCenter.getCurrentNumberOfResearchers() > 0) {
        return researchCenter.getCurrentNumberOfResearchers();
	}
    return 0;
}



 Doctor* Hospital::findDoctorById(int id) const
{
    if (workers)
    {
        for (int i = 0; i < currentNumberOfWorkers; i++)
        {
			Doctor* tempDoctor = dynamic_cast<Doctor*>(workers[i]);
            if (tempDoctor)
            {
                if (tempDoctor->getId() == id)
                {
                    return tempDoctor;
                }
            }
            
        }
    }
    cout << "Doctor with ID " << id << " not found." << endl;
    return nullptr;
}

 Nurse* Hospital::findNurseById(int id) const
{
    if (workers) {
        for (int i = 0; i < currentNumberOfWorkers; i++)
        {
			Nurse* tempNurse = dynamic_cast<Nurse*>(workers[i]);
			if (tempNurse)
			{
				if (tempNurse->getId() == id)
				{
					return tempNurse;
				}
			}
        }
    }
    cout << "Nurse with ID " << id << " not found." << endl;
    return nullptr;
}

 Visitor* Hospital::findVisitorById(int id) const
{
    if (visitors) {
        for (int i = 0; i < currentNumberOfVisitors; ++i) {
            if (visitors[i]->getId() == id) {
                return visitors[i];
            }
        }
    }
    cout << "Visitor with ID " << id << " not found." << endl;
	return nullptr;
}

 Researcher* Hospital::findResearcherById(int id) const
{
    if (researchCenter.getResearchers()) {
        for (int i = 0; i < researchCenter.getCurrentNumberOfResearchers(); ++i) {
            if (researchCenter.getResearchers()[i]->getId() == id) {
                return researchCenter.getResearchers()[i];
            }
        }
    }
    cout << "Researcher with ID " << id << " not found." << endl;
    return nullptr;
}

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
    if (workers)
    {
        for (int i = 0; i < currentNumberOfWorkers; i++)
        {
			Doctor* tempDoctor = dynamic_cast<Doctor*>(workers[i]);
			if (tempDoctor)
			{
				if (strcmp(tempDoctor->getName(), name) == 0)
                {
					return tempDoctor;
				}
			}
        }
    }
    return nullptr;
}

 Nurse* Hospital::getNurseByName(const char* name) const
{
    if (workers)
    {
        for (int i = 0; i < currentNumberOfWorkers; i++)
        {
			Nurse* tempNurse = dynamic_cast<Nurse*>(workers[i]);
            if (tempNurse)
            {
				if (strcmp(tempNurse->getName(), name) == 0)
                {
					return tempNurse;
				}
            }
        }
    }
    return nullptr;
}   

 Visitor* Hospital::getVisitorByName(const char* name) const
{
    if (visitors) {
        for (int i = 0; i < currentNumberOfVisitors; i++) {
            if (strcmp(visitors[i]->getName(), name) == 0) {
                return visitors[i];
            }
        }
    }
    return nullptr;
}

 Researcher* Hospital::getResearcherByName(const char* name) const
{
    if (researchCenter.getResearchers()) {
        for (int i = 0; i < researchCenter.getCurrentNumberOfResearchers(); i++) {
            if (strcmp(researchCenter.getResearchers()[i]->getName(), name) == 0) {
                return researchCenter.getResearchers()[i];
            }
        }
	}
	return nullptr;
}

void Hospital::setName(const char* name)
{
	delete[] this->name;
	this->name = new char[strlen(name) + 1];
	strcpy(this->name, name);
}

void Hospital::printDepartmentVisitors(const char* departmentName) const
{
    if (departments) {
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

void Hospital::printAllSurgens() const
{
	if (workers)
    {
		cout << "Surgeons in Hospital " << name << ":" << endl;
		for (int i = 0; i < currentNumberOfWorkers; ++i)
        {
			Doctor* tempDoctor = dynamic_cast<Doctor*>(workers[i]);
			if (tempDoctor)
            {
                Surgen* tempSurgen = dynamic_cast<Surgen*>(tempDoctor);
                if (tempSurgen)
                {
					cout << *tempSurgen << endl;
					
                }
			}
		}
	}
	else
    {
		cout << "No workers in the hospital." << endl;
	}
}

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
    for (int i = 0; i < currentNumberOfWorkers; i++)
    {
        Nurse* tempDoctor = dynamic_cast<Nurse*>(workers[i]);
        if (tempDoctor)
        {
            if (tempDoctor->getId() == nurse.getId())
                return true;
        }
    }
    return false;
}
bool Hospital::DoctorExist(const Doctor& doctor)
{
	
    for (int i = 0; i < currentNumberOfWorkers; i++)
    {
		Doctor* tempDoctor = dynamic_cast<Doctor*>(workers[i]);
        if (tempDoctor)
        {
			if (tempDoctor->getId() == doctor.getId())
				return true;
        }
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

