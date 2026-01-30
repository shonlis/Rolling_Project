#pragma warning(disable: 4996)

#include <iostream>
using namespace std;
#include <vector>
#include "Research_center.h"
#include "Researcher.h"
#include "ResearcherDoctor.h"

research_center::research_center(const string name)
{
    this->name == name ? name : std::string("There is no Name");
    researchers.reserve(2);
}

research_center::~research_center()
{
    for (auto r : researchers)
    {
        delete r;
    }
}

void research_center::setName(const string name)
{
    this->name == name ? name : std::string();
}

bool research_center::addResearcher(Researcher& researcher)
{
    if (researcherExist(researcher))
        return false;

    ResearcherDoctor* rd = dynamic_cast<ResearcherDoctor*>(&researcher);
    if (rd)
    {
        researchers.push_back(new ResearcherDoctor(*rd));
    }
    else
    {
        researchers.push_back(new Researcher(researcher));
    }
    return true;
}

bool research_center::researcherExist(const Researcher& researcher)
{
    for (auto r : researchers)
    {
        if (r && r->getId() == researcher.getId())
            return true;
    }
    return false;
}

ostream& operator<<(ostream& os, const research_center& research_center)
{
    os << "research_center Details: \nresearch_center:" << research_center.getName() << "and his researchers:" << endl;
    for (auto r : research_center.researchers)
    {
        os << *r << endl;
    }
    return os;
}
