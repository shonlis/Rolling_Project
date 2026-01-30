#ifndef research_center__H_
#define research_center__H_

#include <string>
#include <vector>

class Researcher;
class Doctor;
class ResearcherDoctor;

class research_center
{
    std::string name;
    std::vector<Researcher*> researchers;

public:
    research_center(const string name = "There is no Name");
    ~research_center();

    // getters
    const string getName() const { return name.c_str(); };
    int getCurrentNumberOfResearchers() const { return static_cast<int>(researchers.size()); }
    std::vector<Researcher*> const& getResearchers() const { return researchers; };
    
    //setters
    void setName(const string name);

    // other methods
    bool addResearcher( Researcher& researcher);
    bool researcherExist(const Researcher& researcher);
    friend std::ostream& operator<<(std::ostream& os, const research_center& research_center);
};

#endif // !research_center__H_
