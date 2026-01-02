#include "research_center.h"
#include <iostream>
#include <cstring>

research_center::research_center(const char* name)
{
	this->name = new char[strlen(name) + 1];
	strcpy(this->name, name);
	maxNumberOfResearchers = 2;
	currentNumberOfResearchers = 0;
}

void research_center::setName(const char* name)
{
	delete[]this->name;
	this->name = new char[strlen(name) + 1];
	strcpy(this->name, name);
}

bool research_center::addResearcher(Researcher& researcher)
{
	if (researcherExist(researcher))
		return false;


	if (currentNumberOfResearchers == maxNumberOfResearchers)
	{
		maxNumberOfResearchers *= 2;
		Researcher** temp = new Researcher * [maxNumberOfResearchers];
		for (int i = 0; i < currentNumberOfResearchers; i++)
			temp[i] = this->researchers[i];

		delete[]this->researchers;
		this->researchers = temp;
	}

	this->researchers[currentNumberOfResearchers] = &researcher;
	currentNumberOfResearchers++;
	return true;
}

bool research_center::researcherExist(const Researcher& researcher)
{
	for (int i = 0; i < currentNumberOfResearchers; i++)
	{
		if (researchers[i]->getId() == researcher.getId())
			return true;
	}
	return false;
}
