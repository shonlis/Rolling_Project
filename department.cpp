#pragma warning(disable: 4996)
#include <iostream>
using namespace std;
#include "Department.h"
#include "Doctor.h"
#include "Nurse.h"
#include "Visitor.h"

Department::Department(const char* name)
{
	this->name = new char[strlen(name) + 1];
	strcpy(this->name, name);
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
Department::~Department()
{
	delete[] name;
	if (doctors) {
		for (int i = 0; i < currentNumberOfDoctors; ++i) {
			delete doctors[i];
		}
		delete[] doctors;
	}

	if (nurses) {
		for (int i = 0; i < currentNumberOfNurses; ++i) {
			delete nurses[i];
		}
		delete[] nurses;
	}
	if (visitors) {
		for (int i = 0; i < currentNumberOfVisitors; ++i) {
			delete visitors[i];
		}
		delete[] visitors;
	}
}
bool Department::addDoctor(Doctor* doctor)
{
	if (DoctorExist(*doctor))
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

	this->doctors[currentNumberOfDoctors] = doctor;
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
bool Department::addNurse(Nurse* nurse)
{
	if (NurseExist(*nurse))
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

	this->nurses[currentNumberOfNurses] = nurse;
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
bool Department::addVisitor(Visitor* visitor)
{
	if (VisitorExist(*visitor))
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

	this->visitors[currentNumberOfVisitors] = visitor;
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
/*******************************************************************************/
void Department::printDoctors()
{
	for (int i = 0; i < currentNumberOfDoctors; i++)
	{
		cout << doctors[i]->getName();
		if (i < currentNumberOfDoctors - 1)
		{
			cout << ", ";
		}
	}
	cout << endl;
}
void Department::printNurses()
{
	for (int i = 0; i < currentNumberOfNurses; i++)
	{
		cout << nurses[i]->getName();
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
void Department::setName(const char* name)
{
	delete[]this->name;
	this->name = new char[strlen(name) + 1];
	strcpy(this->name, name);
}
/*******************************************************************************/