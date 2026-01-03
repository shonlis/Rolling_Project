#include "doctor.h"
 
Doctor::Doctor(const Worker& worker) : Worker(worker)
{
    this->specialization.clear();
    counter++;
}

Doctor::Doctor(const Doctor& other) : Worker(other)
{
    specialization = other.specialization;
}

bool Doctor::setSpecialization(const char* specialization)
{
    this->specialization = specialization ? specialization : std::string();
    return true;
}

std::ostream& operator<<(std::ostream& os, const Doctor& d)
{
    os << "Doctor: " << d.getName() << ", ID=" << d.getId();
    if (d.getSpecialization()) os << ", Spec=" << d.getSpecialization();
    os << std::endl;
    return os;
}





