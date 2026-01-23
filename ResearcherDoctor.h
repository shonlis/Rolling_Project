#ifndef ResearcherDoctor__H_
#define ResearcherDoctor__H_

#include <iostream>
using namespace std;

#include "Researcher.h"
#include "Doctor.h"


class ResearcherDoctor : public Researcher, public Doctor
{
public:
	ResearcherDoctor(const Researcher& researcher, const Doctor doctor);
	ResearcherDoctor(const ResearcherDoctor& researcherdoctor);
	virtual void toOs(ostream& os) const override;

	virtual void showthis() const override {
		Doctor::showthis();
		Researcher::showthis();
	}
};

#endif // !ResearcherDoctor__H_