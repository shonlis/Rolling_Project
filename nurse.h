#ifndef NURSE_H
#define NURSE_H

#include "Worker.h"


class Nurse : public Worker {
public:
    int ExperienceYears;

    friend ostream& operator<<(ostream& os, const Nurse& n);

    Nurse(const Worker& worker);

	// getters
	int getExperienceYears() const { return ExperienceYears; }

	// setters
	void setExperienceYears(int experienceYears);

	// other methods
	

};

#endif // NURSE_H
