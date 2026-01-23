#ifndef Visitor__H_
#define Visitor__H_


#include "Person.h"

class VisitCard;

class Visitor : public Person
{
private:

	VisitCard** visits;
	int maxNumberOfVisits;
	int currentNumberOfVisits;
public:

	Visitor(const char* name, int id, int birthYear, Gender gender);
	//Visitor(const Person& person);
	~Visitor();

	Visitor(const Visitor& visitor);
	Visitor(Visitor&& visitor);

	//setters


	//getters
	int getNumbrtOfCurrentVisits() const { return currentNumberOfVisits; }

	// other methods
	void showthis() const override;
	bool addVisitCard(VisitCard& visitCard);
	bool visitCardExist(const VisitCard& visitCard);

	//operators overloading
	friend ostream& operator<<(ostream& os, const Visitor& Visitor);
};

#endif // !Visitor__H_