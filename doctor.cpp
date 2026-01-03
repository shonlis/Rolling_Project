#include "doctor.h"
 
Doctor::Doctor(const Worker& worker) : Worker(worker)
{
    specialization = nullptr;
    counter++;
}

Doctor::Doctor(const Doctor& other) : Worker(other)
{
    if (other.specialization) {
        specialization = new char[strlen(other.specialization) + 1];
        strcpy(specialization, other.specialization);
    } else specialization = nullptr;
}

Doctor::~Doctor()
{
    delete[] specialization;
}

bool Doctor::setSpecialization(const char* specialization)
{
    if (this->specialization) delete[] this->specialization;
    if (specialization) {
        this->specialization = new char[strlen(specialization) + 1];
        strcpy(this->specialization, specialization);
    } else this->specialization = nullptr;
    return true;
}

std::ostream& operator<<(std::ostream& os, const Doctor& d)
{
    os << "Doctor: " << d.getName() << ", ID=" << d.getId();
    if (d.getSpecialization()) os << ", Spec=" << d.getSpecialization();
    os << std::endl;
    return os;
}





