#pragma once
class department;
#include "research_center.h"
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

