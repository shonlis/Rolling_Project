#pragma warning(disable: 4996)

#include "Department.h"
#include "Doctor.h"
#include "Nurse.h"
#include "Visitor.h"


Department::Department(const string& name)
{
	setName(name);
	
	maxNumberOfDoctors = 2;
	this->doctors.reserve(maxNumberOfDoctors);
	currentNumberOfDoctors = 0;

	maxNumberOfNurses = 2;
	this->nurses.reserve(maxNumberOfNurses);
	currentNumberOfNurses = 0;

	maxNumberOfVisitors = 2;
	this->visitors.reserve(maxNumberOfVisitors);
	currentNumberOfVisitors = 0;

}

bool Department::addDoctor(Doctor* doctor)
{
    
	if (DoctorExist(*doctor))
		return false;

	if (currentNumberOfDoctors == maxNumberOfDoctors)
	{
		maxNumberOfDoctors *= 2;
		this->doctors.reserve(maxNumberOfDoctors);
	}

	this->doctors.push_back(doctor);
	currentNumberOfDoctors++;
	return true;
}

bool Department::DoctorExist(const Doctor& doctor)
{
	vector<Doctor*>::iterator itr = doctors.begin();
	vector<Doctor*>::iterator itrEnd = doctors.end();

	for (; itr < itrEnd; ++itr)
	{
		if ((*itr)->getId() == doctor.getId())
			return true;
	}
	return false;
}

bool Department::addNurse(Nurse* nurse)
{
	if (NurseExist(*nurse))
		return false;

	if (currentNumberOfNurses == maxNumberOfNurses)
	{
		maxNumberOfNurses *= 2;
		this->nurses.reserve(maxNumberOfNurses);
	}

	this->nurses.push_back(nurse);
	currentNumberOfNurses++;
	return true;
}

bool Department::NurseExist(const Nurse& nurse)
{

	vector<Nurse*>::iterator itr = nurses.begin();
	vector<Nurse*>::iterator itrEnd = nurses.end();

	for (; itr < itrEnd; ++itr)
	{
		if ((*itr)->getId() == nurse.getId())
			return true;
	}
	return false;
}

bool Department::addVisitor(Visitor* visitor)
{

	if (VisitorExist(*visitor))
		return false;

	if (currentNumberOfVisitors == maxNumberOfVisitors)
	{
		maxNumberOfVisitors *= 2;
		this->visitors.reserve(maxNumberOfVisitors);
	}

	this->visitors.push_back(visitor);
	currentNumberOfVisitors++;
	return true;
}

bool Department::VisitorExist(const Visitor& visitor)
{

	vector<Visitor*>::iterator itr = visitors.begin();
	vector<Visitor*>::iterator itrEnd = visitors.end();

	for (; itr < itrEnd; ++itr)
	{
		if ((*itr)->getId() == visitor.getId())
			return true;
	}
	return false;
}

void Department::printDoctors() const
{

	vector<Doctor*>::const_iterator itr = doctors.begin();
	vector<Doctor*>::const_iterator itrEnd = doctors.end();

	for (int i = 0; itr < itrEnd; ++itr, i++)
	{
		cout << (*itr)->getName();
		if (i < currentNumberOfDoctors - 1)
		{
			cout << ", ";
		}
	}
	cout << endl;
}

void Department::printNurses() const 
{

	vector<Nurse*>::const_iterator itr = nurses.begin();
	vector<Nurse*>::const_iterator itrEnd = nurses.end();

	for (int i = 0; itr < itrEnd; ++itr, i++)
	{
		cout << (*itr)->getName();
		if (i < currentNumberOfNurses - 1)
		{
			cout << ", ";
		}
	}
	cout << endl;
}

Department& Department::operator+=(Nurse& nurse)
{
    addNurse(&nurse);
    return *this;
}

Department& Department::operator+=(Doctor& doctor)
{
    addDoctor(&doctor);
    return *this;
}

void Department::setName(const string& name)
{
	this->name = name;
	
}
