#include "Surgen.h"

Surgen::Surgen(const Doctor& doctor) : Worker(doctor), Doctor(doctor)
{
	this->numberOfOperations = 0;
}

Surgen::Surgen(const Surgen& surgen) : Worker(surgen), Doctor(surgen)
{
	this->numberOfOperations = surgen.numberOfOperations;
}

Surgen::Surgen(Surgen&& surgen) noexcept : Worker(std::move(surgen)), Doctor(std::move(surgen)), numberOfOperations(surgen.numberOfOperations) {}

void Surgen::setNumberOfOperations(int numberOfOperations)
{
	this->numberOfOperations = numberOfOperations;
}

void Surgen::toOs(std::ostream& os) const
{
    Doctor::toOs(os);
    os << "Number of operations: " << this->numberOfOperations << std::endl;

}


