#pragma warning(disable: 4996)


#include "Research_center.h"
#include "Researcher.h"
#include "ResearcherDoctor.h"

research_center::research_center(const string& name)
{
	setName(name);
	maxNumberOfResearchers = 2;
	researchers.reserve(maxNumberOfResearchers);
	currentNumberOfResearchers = 0;
}

void research_center::setName(const string& name)
{
	this->name = name;
}

bool research_center::addResearcher(Researcher& researcher)
{
    if (researcherExist(researcher))
        return false;

	if (currentNumberOfResearchers == maxNumberOfResearchers)
	{
		maxNumberOfResearchers *= 2;
		researchers.reserve(maxNumberOfResearchers);
	}

	Researcher* researcherCopy = nullptr;
	ResearcherDoctor* ResearcherDoctorCopy = dynamic_cast<ResearcherDoctor*>(&researcher);
	if (ResearcherDoctorCopy)
	{
		ResearcherDoctorCopy = new ResearcherDoctor(*ResearcherDoctorCopy);
		this->researchers.push_back(ResearcherDoctorCopy);
	}
	else
	{
		researcherCopy = new Researcher(researcher);
		this->researchers.push_back(researcherCopy);
	}
	
	currentNumberOfResearchers++;
	return true;
}

bool research_center::researcherExist(const Researcher& researcher)
{
	vector<Researcher*>::iterator itr = researchers.begin();
	vector<Researcher*>::iterator itrEnd = researchers.end();

	for (; itr < itrEnd; ++itr)
	{
		if ((*itr)->getId() == researcher.getId())
			return true;
	}
	return false;
}

ostream& operator<<(ostream& os, const research_center& research_center)
{
	vector<Researcher*>::const_iterator itr = research_center.researchers.begin();
	vector<Researcher*>::const_iterator itrEnd = research_center.researchers.end();

	os << "research_center Details: \nresearch_center:" << research_center.getName() << "and his researchers:" << endl;
	for (; itr < itrEnd; ++itr)
	{
		os << *itr << endl;
	}
	return os;
}
