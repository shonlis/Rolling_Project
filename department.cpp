#include "department.h"
#include <cstring>
#include <iostream>

department::department(const char* name)
{
	this->name = new char[strlen(name) + 1];
	strcpy(this->name, name);
}

department::~department()
{
	delete[] name;
}

const char* department::getName() const
{
	return name;
}

void department::print() const
{
	std::cout << "Department Name: " << getName() << std::endl;
}