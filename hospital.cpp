#include "hospital.h"
#include <iostream>
#include <cstring>

hospital::hospital(const char* name)
{
	this->name = new char[strlen(name) + 1];
	strcpy(this->name, name);
}
hospital::~hospital()
{
	delete[] name;
}
const char* hospital::getName() const
{
	return name;
}
void hospital::print() const
{
	std::cout << "Hospital Name: " << getName() << std::endl;
}