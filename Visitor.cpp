
#include "Visitor.h"
#include "VisitCard.h"

Visitor::Visitor(const string& name, int id, int birthYear, Gender gender)
	: Person(name, id, birthYear, gender), maxNumberOfVisits(2), currentNumberOfVisits(0)
{
	this->visits.reserve(maxNumberOfVisits);
}

void Visitor::showthis() const
{
    vector<VisitCard*>::const_iterator itr = visits.begin();
    vector<VisitCard*>::const_iterator itrEnd = visits.end();

    Person::showthis();
    cout << "Number of visits: " << currentNumberOfVisits << endl;
    for (int i = 0; itr < itrEnd; ++itr)
    {
       cout << *itr << endl;
	}
}

bool Visitor::addVisitCard(VisitCard& visitCard)
{
    if (visitCardExist(visitCard))
        return false;

    if (currentNumberOfVisits == maxNumberOfVisits)
    {
        maxNumberOfVisits *= 2;
        this->visits.reserve(maxNumberOfVisits);
    }
    
    VisitCard* Visitcard = new VisitCard(visitCard.getPurposeOfVisit(), visitCard.getVisitingDate() , visitCard.getDepartmentsToVisit() , visitCard.getHostWorker());
    this->visits.push_back(Visitcard);
    currentNumberOfVisits++;
    return true;
}

bool Visitor::visitCardExist(const VisitCard& visitCard) const
{

	vector<VisitCard*>::const_iterator itr = visits.begin();
    vector<VisitCard*>::const_iterator itrEnd = visits.end();

    for ( ; itr < itrEnd; ++itr)
    {
        if ((*itr)->getVisitCardNumber() == visitCard.getVisitCardNumber())
            return true;
    }
    return false;
}

ostream& operator<<(ostream& os, const Visitor& Visitor)
{
	
    vector<VisitCard*>::const_iterator itr = Visitor.visits.begin();
    vector<VisitCard*>::const_iterator itrEnd = Visitor.visits.end();

    os << "Visitor Details: " << Visitor.getName() << ": ID = " << Visitor.getId() << ", number of visits = " << Visitor.getNumbrtOfCurrentVisits() << endl;
    for (; itr < itrEnd; ++itr)
    {
        os << *(*itr) << endl;
    }
    return os;
}
