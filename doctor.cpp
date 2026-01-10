
#pragma warning(disable: 4996)
#include "Doctor.h"

Doctor::Doctor(const Worker& worker) : Worker(worker)
{
    specialization = nullptr;
}
Doctor::Doctor(const Doctor& doctor) : Worker(doctor)
{
    if (doctor.specialization)
    {
        specialization = new char[strlen(doctor.specialization) + 1];
        strcpy(specialization, doctor.specialization);
    }
    else
        specialization = nullptr;
}
Doctor::Doctor(Doctor&& doctor) : Worker(move(doctor))
{
    specialization = doctor.specialization;
    doctor.specialization = nullptr;
}

bool Doctor::setSpecialization(const char* specialization)
{
    if (this->specialization) delete[] this->specialization;
    if (specialization) {
        this->specialization = new char[strlen(specialization) + 1];
        strcpy(this->specialization, specialization);
    }
    else this->specialization = nullptr;
    return true;
}
ostream& operator<<(ostream& os, const Doctor& d)
{
    os << "Doctor: " << d.getName() << ", ID=" << d.getId();
    if (d.getSpecialization()) os << ", Spec=" << d.getSpecialization();
    os << std::endl;
    return os;
}
