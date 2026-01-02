#ifndef research_center__H_
#define research_center__H_

#include "Researcher.h";

class research_center
{
	char* name;
	Researcher** researchers;
	int currentNumberOfResearchers;
	int maxNumberOfResearchers;

public:
	research_center(const char* name = "There is no Name");
	~research_center() { delete[]researchers; };

	// getters
	const char* getName() const { return name; };
	
	//setters
	void setName(const char* name);

	// other methods
	bool addResearcher(Researcher& researcher);
	bool researcherExist(const Researcher& researcher);
	
};

#endif // !research_center__H_