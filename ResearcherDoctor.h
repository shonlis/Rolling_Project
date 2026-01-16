#ifndef ResearcherDoctor__H_
#define ResearcherDoctor__H_

#include <iostream>
using namespace std;

#include "Researcher.h"
#include "Doctor.h"


class ResearcherDoctor : public Researcher , public Doctor
{
	ResearcherDoctor(const Researcher& researcher, const Doctor doctor);

	virtual void toOs(ostream& os) const override;

	virtual void showthis() const override {
		Doctor::showthis();
		Researcher::showthis();
	}
};

#endif // !ResearcherDoctor__H_