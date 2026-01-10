#include <iostream>
using namespace std;
#include "Visitor.h"

// default initial max visits value kept as before
Visitor::Visitor(const Person& person) : Person(person)
{
    maxNumberOfVisits = 2;
    visits = new VisitCard * [maxNumberOfVisits];
    for (int i = 0; i < maxNumberOfVisits; ++i) visits[i] = nullptr;
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
    for (int i = 0; i < maxNumberOfVisits; ++i) visits[i] = nullptr;

    for (int i = 0; i < currentNumberOfVisits; i++)
    {
        if (visitor.visits[i])
            visits[i] = new VisitCard(*visitor.visits[i]); // deep copy
        else
            visits[i] = nullptr;
    }

}
Visitor::Visitor(Visitor&& visitor) : Person(std::move(visitor))
{
    // steal resources
    this->visits = visitor.visits;
    this->currentNumberOfVisits = visitor.currentNumberOfVisits;
    this->maxNumberOfVisits = visitor.maxNumberOfVisits;

    // leave moved-from in safe state
    visitor.visits = nullptr;
    visitor.currentNumberOfVisits = 0;
    visitor.maxNumberOfVisits = 0;
}
bool Visitor::addVisitCard(VisitCard& visitCard)
{
    if (visitCardExist(visitCard))
        return false;

    if (currentNumberOfVisits == maxNumberOfVisits)
    {
        maxNumberOfVisits *= 2;
        VisitCard** temp = new VisitCard * [maxNumberOfVisits];
        for (int i = 0; i < maxNumberOfVisits; ++i) temp[i] = nullptr;
        for (int i = 0; i < currentNumberOfVisits; i++)
            temp[i] = this->visits[i];

        delete[]this->visits;
        this->visits = temp;
    }

    // create a heap copy (own the VisitCard)
    this->visits[currentNumberOfVisits] = new VisitCard(visitCard);
    currentNumberOfVisits++;
    return true;
}

bool Visitor::visitCardExist(const VisitCard& visitCard)
{
    for (int i = 0; i < currentNumberOfVisits; i++)
    {
        if (visits[i] && visits[i]->getVisitCardNumber() == visitCard.getVisitCardNumber())
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