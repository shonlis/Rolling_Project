#include "Nurse.h"

Nurse::Nurse(const string& name, int id, int birthYear, Gender gender, int ExperienceYears)
	: Worker(name, id, birthYear, gender), ExperienceYears(ExperienceYears)
{}


void Nurse::setExperienceYears(int experienceYears)
{
    ExperienceYears = experienceYears;
}

void Nurse::toOs(ostream& os) const
{
    Worker::toOs(os);
    os << "Experience Years: " << ExperienceYears << std::endl;
}
