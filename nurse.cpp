#include "nurse.h"

Nurse::Nurse(const Worker& worker) : Worker(worker)
{
    this->ExperienceYears = 0;
    // increment Worker::counter (inherited protected static)
    counter++;
}

Nurse::~Nurse()
{
}

std::ostream& operator<<(std::ostream& os, const Nurse& n)
{
    os << "Nurse: " << n.getName() << ", ID=" << n.getId() << ", ExpYears=" << n.getExperienceYears() << std::endl;
    return os;
}




