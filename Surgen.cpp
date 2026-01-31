#include "Surgen.h"

Surgen::Surgen(const Doctor& doctor) : 
	Doctor(doctor.getName(), doctor.getId(), doctor.getBirthYear(), doctor.getGender() ,doctor.getSpecialization()), 
	Worker(doctor.getName(), doctor.getId(), doctor.getBirthYear(), doctor.getGender())
{
	this->numberOfOperations = 0;
}

Surgen::Surgen(const Surgen& surgen) : Worker(surgen), Doctor(surgen)
{
	this->numberOfOperations = surgen.numberOfOperations;
}

void Surgen::setNumberOfOperations(int numberOfOperations)
{
	this->numberOfOperations = numberOfOperations;
}

void Surgen::toOs(std::ostream& os) const
{
    Doctor::toOs(os);
    os << "Number of operations: " << this->numberOfOperations <<endl;

}