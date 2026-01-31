#include "ResearcherDoctor.h"

ResearcherDoctor::ResearcherDoctor(const Researcher& researcher, const Doctor& doctor) :
	Worker(researcher.getName(), researcher.getId(), researcher.getBirthYear(), researcher.getGender()),
	Researcher(researcher),
	Doctor(doctor.getName(), doctor.getId(), doctor.getBirthYear(), doctor.getGender(), doctor.getSpecialization()) {}

ResearcherDoctor::ResearcherDoctor(const ResearcherDoctor& researcherdoctor) : ResearcherDoctor(researcherdoctor, researcherdoctor)
{}
void ResearcherDoctor::toOs(ostream& os) const
{
	Researcher::toOs(os);
	Doctor::toOs(os);
}