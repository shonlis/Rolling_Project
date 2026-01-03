#ifndef NURSE_H
#define NURSE_H

#include "Worker.h"
#include <string>

class Worker;

class Nurse : public Worker {
public:
    int ExperienceYears;

    friend std::ostream& operator<<(std::ostream& os, const Nurse& n);

    Nurse(const Worker& worker);
    ~Nurse();

	// getters
	int getExperienceYears() const { return ExperienceYears; }

	// setters
	void setExperienceYears(int experienceYears) { ExperienceYears = experienceYears; }

	// other methods
	

};

#endif // NURSE_H
