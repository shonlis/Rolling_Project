#pragma warning(disable: 4996)
#include "department.h"
#include "doctor.h"
#include "nurse.h"
#include "Visitor.h"

Department::Department(const char* name)
{
	this->name = new char[strlen(name) + 1];
	strcpy(this->name, name);
	doctors = nullptr;
	nurses = nullptr;
	visitors = nullptr;
	currentNumberOfDoctors = 0;
	maxNumberOfDoctors = 2;
	currentNumberOfNurses = 0;
	maxNumberOfNurses = 2;
	currentNumberOfVisitors = 0;
	maxNumberOfVisitors = 2;
}

Department& Department::operator+=(Doctor& doctor)
{
    addDoctor(doctor);
    return *this;
}

Department::~Department()
{
	delete[] name;
	delete[] doctors;
	delete[] nurses;
	delete[] visitors;
}

Department& Department::operator+=(Nurse& nurse)
{
    addNurse(nurse);
    return *this;
}

void Department::setName(const char* name)
{
	delete[]this->name;
	this->name = new char[strlen(name) + 1];
	strcpy(this->name, name);
}

bool Department::addDoctor(Doctor& doctor)
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

	if (!this->doctors) {
	    doctors = new Doctor*[maxNumberOfDoctors];
	    for (int i=0;i<maxNumberOfDoctors;++i) doctors[i]=nullptr;
	}

	this->doctors[currentNumberOfDoctors] = &doctor;
	currentNumberOfDoctors++;
	return true;
}

bool Department::DoctorExist(const Doctor& doctor)
{
	for (int i = 0; i < currentNumberOfDoctors; i++)
	{
		if (doctors[i]->getId() == doctor.getId())
			return true;
	}
	return false;
}

bool Department::addNurse(Nurse& nurse)
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

	if (!this->nurses) {
		nurses = new Nurse * [maxNumberOfNurses];
		for (int i = 0; i < maxNumberOfNurses; ++i) nurses[i] = nullptr;
	}

	this->nurses[currentNumberOfNurses] = &nurse;
	currentNumberOfNurses++;
	return true;
}

bool Department::NurseExist(const Nurse& nurse)
{
	for (int i = 0; i < currentNumberOfNurses; i++)
	{
		if (nurses[i]->getId() == nurse.getId())
			return true;
	}
	return false;
}

bool Department::addVisitor(Visitor& visitor)
{
	if (VisitorExist(visitor))
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

	if (!this->visitors) {
		visitors = new Visitor * [maxNumberOfVisitors];
		for (int i = 0; i < maxNumberOfVisitors; ++i) visitors[i] = nullptr;
	}

	this->visitors[currentNumberOfVisitors] = &visitor;
	currentNumberOfVisitors++;
	return true;
}

bool Department::VisitorExist(const Visitor& visitor)
{
	for (int i = 0; i < currentNumberOfVisitors; i++)
	{
		if (visitors[i]->getId() == visitor.getId())
			return true;
	}
	return false;
}

