#include "research_center.h"
#include <iostream>
#include <cstring>

research_center::research_center(const char* name)
{
	this->name = new char[strlen(name) + 1];
	strcpy(this->name, name);
}
research_center::~research_center()
{
	delete[] name;
}
const char* research_center::getName() const
{
	return name;
}
void research_center::print() const
{
	std::cout << "Research Center Name: " << getName() << std::endl;
}
