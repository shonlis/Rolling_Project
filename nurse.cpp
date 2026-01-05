#include "nurse.h"
#include <string>
Nurse::Nurse(const Worker& worker) : Worker(worker)
{
    this->ExperienceYears = 0;
}

void Nurse::setExperienceYears(int experienceYears)
{
    ExperienceYears = experienceYears; 
}

ostream& operator<<(ostream& os, const Nurse& n)
{
    os << "Nurse: " << n.getName() << ", ID=" << n.getId() << ", ExpYears=" << n.getExperienceYears() << endl;
    return os;
}




