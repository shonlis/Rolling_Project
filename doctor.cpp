#pragma warning(disable: 4996)
#include "Doctor.h"
#include "Worker.h"


Doctor::Doctor(const char* name, int id, int birthYear, Gender gender, const char* specialization)
    : Worker(name, id, birthYear, gender), specialization(specialization ? specialization : std::string()) {}

Doctor::Doctor(const Doctor& doctor) : Worker(doctor), specialization(doctor.specialization) {}

Doctor::Doctor(Doctor&& doctor) noexcept : Worker(std::move(doctor)), specialization(std::move(doctor.specialization)) {}

bool Doctor::setSpecialization(const char* specialization)
{
    this->specialization = specialization ? specialization : std::string();
    return true;
}

void Doctor::toOs(ostream& os) const
{
    Worker::toOs(os);
    os << "Specialization: " << (specialization.empty() ? "not defined" : specialization.c_str()) << std::endl;
}
