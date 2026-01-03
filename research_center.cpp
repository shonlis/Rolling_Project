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

	if (!this->researchers) {
		researchers = new Researcher * [maxNumberOfResearchers];
		for (int i = 0; i < maxNumberOfResearchers; ++i) researchers[i] = nullptr;
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

ostream& operator<<(ostream& os, const research_center& research_center)
{
	os << "research_center Details: \nresearch_center:" << research_center.getName()<< "and his researchers:" << endl;
	for (int i = 0; i < research_center.currentNumberOfResearchers; i++)
	{
		os << *(research_center.researchers[i]) << endl;
	}
	return os;
}