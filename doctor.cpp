#pragma warning(disable: 4996)
#include "Doctor.h"

Doctor::Doctor(const Worker& worker) : Worker(worker)
{
    specialization = nullptr;
}

Doctor::Doctor(const Doctor& other) : Worker(other)
{
    if (other.specialization)
    {
        specialization = new char[strlen(other.specialization) + 1];
        strcpy(specialization, other.specialization);
    }
    else 
        specialization = nullptr;
}

Doctor::Doctor(Doctor&& other) : Worker(std::move(other))
{
	specialization = other.specialization;
	other.specialization = nullptr;
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

ostream& operator<<(ostream& os, const Doctor& d)
{
    os << "Doctor: " << d.getName() << ", ID=" << d.getId();
    if (d.getSpecialization()) os << ", Spec=" << d.getSpecialization();
    os << std::endl;
    return os;
}





