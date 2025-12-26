#pragma once


#include "Person.h"
class VisitCard;

class Visitor : public Person 
{
private:

	VisitCard* visits;

public:
	Visitor(const char* purpose);
	~Visitor();
};

