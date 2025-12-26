#ifndef hospital__H_
#define hospital__H_

#include "research_center.h"
#include "department.h"

class hospital
{
	char* name;
	department* departments;
	research_center& researchCenters;

public:	
	hospital(const char* name);
	~hospital();
	const char* getName() const;
	void print() const;
};

#endif // !hospital__H_