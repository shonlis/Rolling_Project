#include "ResearcherDoctor.h"

ResearcherDoctor::ResearcherDoctor(const Researcher& researcher, const Doctor doctor) : Worker(researcher), Researcher(researcher), Doctor(doctor) {}

void ResearcherDoctor::toOs(ostream& os) const
{
	Researcher::toOs(os);
	Doctor::toOs(os);
}