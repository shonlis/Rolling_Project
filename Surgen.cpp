#include "Surgen.h"

Surgen::Surgen(const Worker& worker) : Doctor(worker)
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

ostream& operator<<(ostream& os, const Surgen& s)
{
	os << "Surgen: " << s.getName() << ", ID=" << s.getId() << ", NumOperations=" << s.getNumberOfOperations() << endl;
	return os;
}


