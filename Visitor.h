#ifndef Visitor__H_
#define Visitor__H_


#include "Person.h"
#include "VisitCard.h"

class Visitor : public Person 
{
private:

	VisitCard* visits;

public:
	Visitor(const char* purpose);
	~Visitor();
};

#endif // !Visitor__H_