#ifndef Visitor__H_
#define Visitor__H_


#include "Person.h"
#include <vector>
using namespace std;

class VisitCard;

class Visitor : public Person
{
	vector<VisitCard*> visits;
	int maxNumberOfVisits;
	int currentNumberOfVisits;

public:

	Visitor(const string& name, int id, int birthYear, Gender gender);

    //getters
    int getNumbrtOfCurrentVisits() const { return currentNumberOfVisits; }

    // other methods
    void showthis() const override;
    bool addVisitCard(VisitCard& visitCard);
    bool visitCardExist(const VisitCard& visitCard) const;

    //operators overloading
    friend ostream& operator<<(ostream& os, const Visitor& Visitor);
};

#endif // !Visitor__H_
