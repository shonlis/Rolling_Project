#ifndef research_center__H_
#define research_center__H_

#include "Researcher.h";

class research_center
{
	char* name;
	Researcher* researchers;

public:
	research_center(const char* name);
	~research_center();
	const char* getName() const;
	void print() const;
};

#endif // !research_center__H_