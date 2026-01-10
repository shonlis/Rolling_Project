#include <iostream>
using namespace std;
#include "Visitor.h"

Visitor::Visitor(const Person& person) : Person(person)
{
	maxNumberOfVisits = 2;
    visits = new VisitCard* [maxNumberOfVisits];
	currentNumberOfVisits = 0;
}
Visitor::~Visitor()
{
    for (int i = 0; i < currentNumberOfVisits; ++i) {
        delete visits[i];
    }
    delete[] visits;
}
Visitor::Visitor(const Visitor& visitor) :Person(visitor)
{
	maxNumberOfVisits = visitor.maxNumberOfVisits;
	currentNumberOfVisits = visitor.currentNumberOfVisits;
    visits = new VisitCard * [maxNumberOfVisits];
    for (int i = 0; i < currentNumberOfVisits; i++)
    {
        visits[i] = visitor.visits[i];
    }

}
Visitor::Visitor(Visitor&& visitor) :Visitor(visitor)
{
    for (int i = 0; i < currentNumberOfVisits; i++)
    {
        visitor.visits[i] = nullptr;
    }
	visitor.visits = nullptr;
}
bool Visitor::addVisitCard(VisitCard& visitCard)
{
    if (visitCardExist(visitCard))
        return false;

    if (currentNumberOfVisits == maxNumberOfVisits)
    {
        maxNumberOfVisits *= 2;
        VisitCard** temp = new VisitCard * [maxNumberOfVisits];
        for (int i = 0; i < currentNumberOfVisits; i++)
            temp[i] = this->visits[i];

        delete[]this->visits;
        this->visits = temp;
    }
    this->visits[currentNumberOfVisits] = &visitCard;
    currentNumberOfVisits++;
    return true;
}

bool Visitor::visitCardExist(const VisitCard& visitCard)
{
	for (int i = 0; i < currentNumberOfVisits; i++)
	{
		if (visits[i]->getVisitCardNumber() == visitCard.getVisitCardNumber())
			return true;
	}
	return false;
}

ostream& operator<<(ostream& os, const Visitor& Visitor)
{
	os << "Visitor Details: " << Visitor.getName() << ": ID = " << Visitor.getId() << ", number of visits = " << Visitor.getNumbrtOfCurrentVisits() << endl;
	for (int i = 0; i < Visitor.getNumbrtOfCurrentVisits(); i++)
	{
		os << *Visitor.visits[i] << endl;
	}
	return os;
}
