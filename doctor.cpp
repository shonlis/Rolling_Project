#pragma warning(disable: 4996)
#include "Doctor.h"


Doctor::Doctor(const string& name, int id, int birthYear, Gender gender, const string& specialization)
    : Worker(name, id, birthYear, gender)
{
	this->specialization = specialization;
}

Doctor::Doctor(const Doctor& doctor) : Doctor(doctor.getName(), doctor.getId(), doctor.getBirthYear(), doctor.getGender(), doctor.getSpecialization())
{}


bool Doctor::setSpecialization(const string& specialization)
{
    this->specialization = specialization;
	return true;
}

void Doctor::toOs(ostream& os) const
{
    Worker::toOs(os);
    os << "Specialization: " << (specialization.empty() ? "not defined" : specialization) << endl;
}
