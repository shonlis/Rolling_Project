#ifndef research_center__H_
#define research_center__H_

#include "Researcher.h"
#include "ResearcherDoctor.h"

class research_center
{
	char* name;
	Researcher** researchers;
	int currentNumberOfResearchers;
	int maxNumberOfResearchers;

public:
	research_center(const char* name = "There is no Name");
	~research_center();

	// getters
	const char* getName() const { return name; };
	int getCurrentNumberOfResearchers() const { return currentNumberOfResearchers; }
	Researcher* const* getResearchers() const { return researchers; };
	
	//setters
	void setName(const char* name);

	// other methods
	bool addResearcher(const Researcher& researcher, const Doctor doctor);
	bool researcherExist(const Researcher& researcher);
	friend ostream& operator<<(ostream& os, const research_center& research_center);
};

#endif // !research_center__H_