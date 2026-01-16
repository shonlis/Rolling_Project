#include "Surgen.h"

Surgen::Surgen(const Doctor& doctor) : Doctor(doctor)
{
	this->numberOfOperations = 0;
}

Surgen::Surgen(const Surgen& surgen) : Doctor(surgen)
{
	this->numberOfOperations = surgen.numberOfOperations;
}

Surgen::Surgen(Surgen&& surgen) : Doctor(move(surgen)), numberOfOperations(surgen.numberOfOperations) {}

void Surgen::setNumberOfOperations(int numberOfOperations)
{
	this->numberOfOperations = numberOfOperations;
}

void Surgen::toOs(ostream& os) const
{
	
	Doctor::toOs(os);
	os << "Number of operations: " << this->numberOfOperations << endl;

}


