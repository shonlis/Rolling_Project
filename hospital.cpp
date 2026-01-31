#pragma warning(disable: 4996)

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

Hospital::Hospital(const string& name, research_center& researchCenter) : researchCenter(researchCenter)
{
    setName(name);

    maxNumberOfDepartments = 2;
    this->departments.reserve(maxNumberOfDepartments);
    currentNumberOfDepartments = 0;

    maxNumberOfWorkers = 2;
    this->workers.reserve(maxNumberOfWorkers);
    currentNumberOfWorkers = 0;

    maxNumberOfVisitors = 2;
    this->visitors.reserve(maxNumberOfVisitors);
    currentNumberOfVisitors = 0;
    
}

bool Hospital::addDepartment(Department& department)
{
    if (DepartmentExist(department))
        return false;

    // Resize if needed
    if (currentNumberOfDepartments == maxNumberOfDepartments)
    {
        maxNumberOfDepartments *= 2;
        this->departments.reserve(maxNumberOfDepartments);
    }

    Department* departmentCopy = new Department(department.getName());
    departments.push_back(departmentCopy);
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
        this->workers.reserve(maxNumberOfWorkers);
    }
    Surgen* tempSurgen = dynamic_cast<Surgen*>(&doctor);
    if (tempSurgen)
    {
        Worker* SurgenCopy = new Surgen(*tempSurgen);
        this->workers.push_back(SurgenCopy);
    }
    else
    {
        Worker* doctorCopy = new Doctor(doctor.getName(), doctor.getId(), doctor.getBirthYear(), doctor.getGender(), doctor.getSpecialization());
        this->workers.push_back(doctorCopy);
    }
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
        this->workers.reserve(maxNumberOfWorkers);
    }

    Worker* nurseCopy = new Nurse(nurse.getName(), nurse.getId(), nurse.getBirthYear(), nurse.getGender(), nurse.getExperienceYears());
    this->workers.push_back(nurseCopy);
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
        this->visitors.reserve(maxNumberOfVisitors);
    }

    Visitor* visitorCopy = new Visitor(visitor.getName(), visitor.getId(), visitor.getBirthYear(), visitor.getGender());
    visitors.push_back(visitorCopy);
    currentNumberOfVisitors++;
    return true;
}

bool Hospital::addResearcher(Researcher& researcher)
{
    return this->researchCenter.addResearcher(researcher);
}


bool Hospital::addVisit(Visitor& visitor, VisitCard& Visitcard, const string& department)
{
	vector<Department*>::iterator departmentItr = departments.begin();
    vector<Department*>::iterator departmentItrEnd = departments.end();
    vector<Department*>::iterator foundDepartment = find_if(departmentItr, departmentItrEnd, [&department](const Department* def)
        {return def->getName() == department; });

        

        if (foundDepartment != departmentItrEnd)
        {
            addVisitor(visitor);

            vector<Visitor*>::iterator visitorItr = visitors.begin();
            vector<Visitor*>::iterator visitorItrEnd = visitors.end();
            vector<Visitor*>::iterator foundVisitor = find_if(visitorItr, visitorItrEnd, [&visitor](const Visitor* v)
                {return v->getName() == visitor.getName(); });

            if (foundVisitor != visitorItrEnd)
            {
                (*foundVisitor)->addVisitCard(Visitcard);
                (*foundDepartment)->addVisitor(*foundVisitor);
                return true;
            }
            else
                return false;
        }
        else
            return false;// department not found
}
bool Hospital::addNurseToDepartment(Nurse& nurse, const string& departmentName)
{
    Department* department = getDepartmentByName(departmentName);

    if (department != nullptr)
    {
        addNurse(nurse);
        vector <Worker*>::iterator workerItr = workers.begin();
        vector <Worker*>::iterator workerItrEnd = workers.end();

        for ( ; workerItr < workerItrEnd; ++workerItr)
        {
            Nurse* tempNurse = dynamic_cast<Nurse*>(*workerItr);
            if (tempNurse)
            {
                if (tempNurse->getId() == nurse.getId())
                {
                    department->addNurse(tempNurse);
                    return true;
                }
            }

        }
    }
    return false;
}

bool Hospital::addDoctorToDepartment(Doctor& doctor, const string& departmentName)
{
    Department* department = getDepartmentByName(departmentName);

    if (department != nullptr)
    {

        addDoctor(doctor);
        vector <Worker*>::iterator workerItr = workers.begin();
        vector <Worker*>::iterator workerItrEnd = workers.end();

        for (; workerItr < workerItrEnd; ++workerItr)
        {
			Doctor* tempDoctor = dynamic_cast<Doctor*>(*workerItr);
            if (tempDoctor)
            {
                if (tempDoctor->getId() == doctor.getId())
                {
                     department->addDoctor(tempDoctor);
                    return true;
                }
            }
                
        }
            // found department but doctor not present in hospital -> fail
            return false;
    }
    return false;
}

bool Hospital::addVisitorToDepartment(Visitor& visitor, const string& departmentName)
{
    Department* department = getDepartmentByName(departmentName);

    if (department != nullptr)
    {
            addVisitor(visitor);
            vector <Visitor*>::iterator visitorItr = visitors.begin();
            vector <Visitor*>::iterator visitorItrEnd = visitors.end();

            for ( ; visitorItr < visitorItrEnd; visitorItr++)
            {
                if ((*visitorItr)->getId() == visitor.getId())
                {
                    department->addVisitor(*visitorItr);
                    return true;
                }
            }
            return false;
    }
    return false;
}

bool Hospital::addArticleToResearchCenter(Researcher& researcher, Article& article)
{
    vector <Researcher*>::const_iterator ResearcherItr = researchCenter.getResearchers().begin();
    vector <Researcher*>::const_iterator ResearcherItrEnd = researchCenter.getResearchers().end();

    for ( ;ResearcherItr < ResearcherItrEnd; ++ResearcherItr)
    {
        if ((*ResearcherItr)->getId() == researcher.getId())
        {
            (*ResearcherItr)->addArticle(article);
            return true;
        }
    }
    return false;
}

const Hospital& Hospital::operator+=(const Doctor& doctor)
{
    const Surgen* surgen = dynamic_cast<const Surgen*>(&doctor);
    if (surgen)
    {
        Surgen* doctorCopy = new Surgen(*surgen);
        if (!departments.empty()) departments[0]->addDoctor(doctorCopy);
    }
    else {
        Doctor* doctorCopy = new Doctor(doctor.getName(), doctor.getId(), doctor.getBirthYear(), doctor.getGender(), doctor.getSpecialization());
        if (!departments.empty()) departments[0]->addDoctor(doctorCopy);
    }
    return *this;
}

const Hospital& Hospital::operator+=(const Nurse& nurse)
{
    Nurse* nurseCopy = new Nurse(nurse.getName(), nurse.getId(), nurse.getBirthYear(), nurse.getGender(), nurse.getExperienceYears());
    if (!departments.empty())
    {
        departments[0]->addNurse(nurseCopy);
    }
    return *this;
}

int Hospital::getNumberOfNurses() const
{

    vector <Worker*>::const_iterator workerItr = workers.begin();
    vector <Worker*>::const_iterator workerItrEnd = workers.end();

	int numberOfNurses = 0;
    for ( ; workerItr < workerItrEnd; ++workerItr)
    {
        Nurse* tempNurse = dynamic_cast<Nurse*>(*workerItr);
        if (tempNurse)
        {
            numberOfNurses++;
        }

    }
	return numberOfNurses;
}

int Hospital::getNumberOfDoctors() const
{
    vector <Worker*>::const_iterator workerItr = workers.begin();
    vector <Worker*>::const_iterator workerItrEnd = workers.end();

    int numberOfDoctors = 0;

    for ( ; workerItr < workerItrEnd; ++workerItr)
    {
        Doctor* tempDoctor = dynamic_cast<Doctor*>(*workerItr);
        if (tempDoctor)
        {
            numberOfDoctors++;
        }

    }
	return numberOfDoctors;
}

int Hospital::getNumberOfResearchers() const
{
    return researchCenter.getCurrentNumberOfResearchers();
}

  Doctor* Hospital::findDoctorById(int id) const
{
     vector <Worker*>::const_iterator workerItr = workers.begin();
     vector <Worker*>::const_iterator workerItrEnd = workers.end();

    if (!workers.empty())
    {
        for ( ; workerItr < workerItrEnd; ++workerItr)
        {
			Doctor* tempDoctor = dynamic_cast<Doctor*>(*workerItr);
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
     vector <Worker*>::const_iterator workerItr = workers.begin();
     vector <Worker*>::const_iterator workerItrEnd = workers.end();

    if (!workers.empty())
    {
        for ( ; workerItr < workerItrEnd; ++workerItr)
        {
			Nurse* tempNurse = dynamic_cast<Nurse*>(*workerItr);
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
     vector <Visitor*>::const_iterator visitorItr = visitors.begin();
     vector <Visitor*>::const_iterator visitorItrEnd = visitors.end();

    if (!visitors.empty())
    {
        for ( ; visitorItr < visitorItrEnd; ++visitorItr)
        {
            if ((*visitorItr)->getId() == id)
            {
                return *visitorItr;
            }
        }
    }
    cout << "Visitor with ID " << id << " not found." << endl;
    return nullptr;
}

  Researcher* Hospital::findResearcherById(int id) const
{
     vector <Researcher*> Researchers = researchCenter.getResearchers();
    if (!Researchers.empty())
    {
        vector <Researcher*>::const_iterator researcherItr = Researchers.begin();
        vector <Researcher*>::const_iterator researcherItrEnd = Researchers.end();

        for ( ; researcherItr < researcherItrEnd; ++researcherItr)
        {
            if ((*researcherItr)->getId() == id)
            {
                return *researcherItr;
            }
        }
    }
    cout << "Researcher with ID " << id << " not found." << endl;
    return nullptr;
}


 void Hospital::setName(const string& name)
 {
     this->name = name;
 }
 Department* Hospital::getDepartmentByName(const string& name) const
{
     vector <Department*>::const_iterator departmentItr = departments.begin();
     vector <Department*>::const_iterator departmentItrEnd = departments.end();

    if (!departments.empty())
    {
        vector <Department*>::const_iterator foundDepartment = find_if(departmentItr, departmentItrEnd, [&name](const Department* def)
            {return def->getName() == name; });
        if (foundDepartment != departmentItrEnd)
            return *foundDepartment;
        else
            return nullptr;
    }
    return nullptr;
}

 Doctor* Hospital::getDoctorByName(const string& name) const
{
     vector <Worker*>::const_iterator workerItr = workers.begin();
     vector <Worker*>::const_iterator workerItrEnd = workers.end();

    if (!workers.empty())
    {
        for ( ; workerItr < workerItrEnd; ++workerItr)
        {
			Doctor* tempDoctor = dynamic_cast<Doctor*>(*workerItr);
			if (tempDoctor)
			{
				if (tempDoctor->getName() == name)
                {
					return tempDoctor;
				}
			}
        }
    }
    return nullptr;
}

Nurse* Hospital::getNurseByName(const string& name) const
{
     vector <Worker*>::const_iterator workerItr = workers.begin();
     vector <Worker*>::const_iterator workerItrEnd = workers.end();

    if (!workers.empty())
    {
        for ( ; workerItr < workerItrEnd; ++workerItr)
        {
			Nurse* tempNurse = dynamic_cast<Nurse*>(*workerItr);
            if (tempNurse)
            {
				if (tempNurse->getName() == name)
                {
					return tempNurse;
				}
            }
        }
    }
    return nullptr;
}   

Visitor* Hospital::getVisitorByName(const string& name) const
{
     vector <Visitor*>::const_iterator visitorItr = visitors.begin();
     vector <Visitor*>::const_iterator visitorItrEnd = visitors.end();

    if (!visitors.empty())
    {
        vector <Visitor*>::const_iterator foundVisitor = find_if(visitorItr, visitorItrEnd, [&name](const Visitor* visitor)
            {return visitor->getName() == name; });
        if (foundVisitor != visitorItrEnd)
            return *foundVisitor;
        else
            return nullptr;
    }
    return nullptr;
}

Researcher* Hospital::getResearcherByName(const string& name) const
{
     vector <Researcher*> Researchers = researchCenter.getResearchers();
    if (!Researchers.empty())
    {
        vector <Researcher*>::const_iterator researcherItr = Researchers.begin();
        vector <Researcher*>::const_iterator researcherItrEnd = Researchers.end();
        vector <Researcher*>::const_iterator foundResearcherItr = find_if(researcherItr, researcherItrEnd, [&name](const Researcher* res)
            {return res->getName() == name; });

            if (foundResearcherItr != researcherItrEnd)
                return *foundResearcherItr;
            else
                return nullptr;
	}
	return nullptr;
}

void Hospital::printDepartmentVisitors(const string& departmentName) const
{
    
    if (!departments.empty())
    {
        Department* department = getDepartmentByName(departmentName);
        
        if (department)
        {
            vector<Visitor*>::const_iterator visitorItr = department->getVisitors().begin();
            vector<Visitor*>::const_iterator visitorItrEnd = department->getVisitors().end();

            cout << "Visitors in Department " << departmentName << ":" << endl;
            for ( ; visitorItr < visitorItrEnd; ++visitorItr)
            {
                cout << *(*visitorItr) << endl;
            }
        }
        else {
            cout << "Department " << departmentName << " not found." << endl;
        }
	}
}

void Hospital::printDepartmentMedicalStaff(const string& departmentName) const
{
    Department* department = this->getDepartmentByName(departmentName);
    if (department)
    {
        cout << "Medical Staff in Department " << departmentName << ":" << endl;
            vector<Doctor*>::const_iterator doctorItr = department->getDoctors().begin();
            vector<Doctor*>::const_iterator doctorItrEnd = department->getDoctors().end();

            vector<Nurse*>::const_iterator nurseItr = department->getNurses().begin();
            vector<Nurse*>::const_iterator nurseItrEnd = department->getNurses().end();

            for (; doctorItr < doctorItrEnd; ++doctorItr)
            {
                cout << *(*doctorItr) << endl;
            }
            for (; nurseItr < nurseItrEnd; ++nurseItr)
            {
                cout << *(*nurseItr) << endl;
            }
    }
    else {
        cout << "No department in the hospital." << endl;
    }
}

void Hospital::printAllMedicalStaff() const
{
    
    if (!departments.empty())
    {
        vector<Department*>::const_iterator departmentItr = departments.begin();
        vector<Department*>::const_iterator departmentItrEnd = departments.end();

        cout << "Medical Staff in Hospital " << name << ":" << endl;
        for ( ; departmentItr < departmentItrEnd; ++departmentItr)
        {
            vector<Doctor*>::const_iterator doctorItr = (*departmentItr)->getDoctors().begin();
            vector<Doctor*>::const_iterator doctorItrEnd = (*departmentItr)->getDoctors().end();

            vector<Nurse*>::const_iterator nurseItr = (*departmentItr)->getNurses().begin();
            vector<Nurse*>::const_iterator nurseItrEnd = (*departmentItr)->getNurses().end();

            cout << "Department: " << (*departmentItr)->getName() << endl;
            for ( ; doctorItr < doctorItrEnd; ++doctorItr)
            {
                cout << *(*doctorItr) << endl;
            }
            for ( ; nurseItr < nurseItrEnd; ++nurseItr)
            {
                cout << *(*nurseItr) << endl;
            }
        }
    }
    else {
        cout << "No departments in the hospital." << endl;
    }
}


void Hospital::printAllResearchers() const
{
    if (!researchCenter.getResearchers().empty())
    {
        cout << "Researchers in Hospital " << name << ":" << endl;
        vector <Researcher*>::const_iterator researcherItr = researchCenter.getResearchers().begin();
        vector <Researcher*>::const_iterator researcherItrEnd = researchCenter.getResearchers().end();

        for ( ; researcherItr < researcherItrEnd; ++researcherItr)
        {
                ResearcherDoctor* ResearcherDoctorCopy = dynamic_cast<ResearcherDoctor*>(*researcherItr);
                if (ResearcherDoctorCopy)
                {
                    cout << *ResearcherDoctorCopy << endl;
                }
                else
                {
                    cout << *(*researcherItr) << endl;
                }
        }
    }
    else
        cout << "No researchers in the hospital." << endl;
}

void Hospital::printAllDepartments() const
{

    if (!departments.empty())
    {
        vector<Department*>::const_iterator departmentItr = departments.begin();
        vector<Department*>::const_iterator departmentItrEnd = departments.end();

        cout << "Departments in Hospital " << name << ": ";
        for (int i = 0 ; departmentItr < departmentItrEnd; ++departmentItr, ++i)
        {
            
            cout << (*departmentItr)->getName();
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

	if (!workers.empty())
    {
        vector<Worker*>::const_iterator workerItr = workers.begin();
        vector<Worker*>::const_iterator workerItrEnd = workers.end();

		cout << "Surgens in Hospital " << name << ":" << endl;
		for (; workerItr < workerItrEnd; ++workerItr)
        {
			Doctor* tempDoctor = dynamic_cast<Doctor*>(*workerItr);
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

void Hospital::printAllDoctors() const
{

	if (!workers.empty())
	{
        vector<Worker*>::const_iterator workerItr = workers.begin();
        vector<Worker*>::const_iterator workerItrEnd = workers.end();

		cout << "Doctors in Hospital " << name << ":" << endl;
		for (; workerItr < workerItrEnd; ++workerItr)
		{
			Doctor* tempDoctor = dynamic_cast<Doctor*>(*workerItr);
			if (tempDoctor)
			{
				cout << *tempDoctor << endl;
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
	vector<Department*>::iterator departmentItr = departments.begin();
	vector<Department*>::iterator departmentItrEnd = departments.end();

    for (; departmentItr < departmentItrEnd; ++departmentItr)
    {
        if ((*departmentItr)->getName() == department.getName())
            return true;
    }
    return false;
}
bool Hospital::NurseExist(const Nurse& nurse)
{
	vector<Worker*>::iterator workerItr = workers.begin();
	vector<Worker*>::iterator workerItrEnd = workers.end();

    for (; workerItr < workerItrEnd; ++workerItr)
    {
        Nurse* tempNurse = dynamic_cast<Nurse*>(*workerItr);
        if (tempNurse)
        {
            if (tempNurse->getId() == nurse.getId())
                return true;
        }
    }
    return false;
}
bool Hospital::DoctorExist(const Doctor& doctor)
{
	vector<Worker*>::iterator workerItr = workers.begin();
	vector<Worker*>::iterator workerItrEnd = workers.end();

    for (; workerItr < workerItrEnd; ++workerItr)
    {
		Doctor* tempDoctor = dynamic_cast<Doctor*>(*workerItr);
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
	vector<Visitor*>::iterator visitorItr = visitors.begin();
	vector<Visitor*>::iterator visitorItrEnd = visitors.end();

    for (; visitorItr < visitorItrEnd; ++visitorItr)
    {
        if ((*visitorItr)->getId() == visitor.getId())
            return true;
    }
    return false;
}

