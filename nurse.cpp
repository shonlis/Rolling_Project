#include "Nurse.h"

Nurse::Nurse(const Worker& worker) : Worker(worker)
{
    this->ExperienceYears = 0;
}
Nurse::Nurse(const Nurse& nurse) : Worker(nurse)
{
	this->ExperienceYears = nurse.ExperienceYears;
}
Nurse::Nurse(Nurse&& nurse) : Worker(move(nurse)),ExperienceYears(nurse.ExperienceYears) {}
void Nurse::setExperienceYears(int experienceYears)
{
    ExperienceYears = experienceYears;
}
ostream& operator<<(ostream& os, const Nurse& n)
{
    os << "Nurse: " << n.getName() << ", ID=" << n.getId() << ", ExpYears=" << n.getExperienceYears() << endl;
    return os;
}