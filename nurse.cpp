#include "Nurse.h"

Nurse::Nurse(const string name, int id, int birthYear, Gender gender, int ExperienceYears)
	: Worker(name, id, birthYear, gender), ExperienceYears(ExperienceYears)
{
}

Nurse::Nurse(const Worker& worker) : Worker(worker)
{
    this->ExperienceYears = 0;
}
Nurse::Nurse(const Nurse& nurse) : Worker(nurse)
{
	this->ExperienceYears = nurse.ExperienceYears;
}
Nurse::Nurse(Nurse&& nurse) noexcept : Worker(std::move(nurse)), ExperienceYears(nurse.ExperienceYears) {}
void Nurse::setExperienceYears(int experienceYears)
{
    ExperienceYears = experienceYears;
}

void Nurse::toOs(std::ostream& os) const
{
    Worker::toOs(os);
    os << "Experience Years: " << ExperienceYears << std::endl;
}
