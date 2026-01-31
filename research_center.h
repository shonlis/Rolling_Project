#ifndef research_center__H_
#define research_center__H_

#include <string>
#include <vector>
#include <iostream>
using namespace std;

class Researcher;
class Doctor;
class ResearcherDoctor;

class research_center
{
	string name;
	vector <Researcher*> researchers;
	int currentNumberOfResearchers;
	int maxNumberOfResearchers;

public:
	research_center(const string& name = "there is no name yet");

	// getters
	const string& getName() const { return name; };
	int getCurrentNumberOfResearchers() const { return currentNumberOfResearchers; }
	const vector <Researcher*>& getResearchers() const { return researchers; };
	
	//setters
	void setName(const string& name);

    // other methods
    bool addResearcher( Researcher& researcher);
    bool researcherExist(const Researcher& researcher);
    friend ostream& operator<<(ostream& os, const research_center& research_center);
};

#endif // !research_center__H_
