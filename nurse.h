#ifndef NURSE_H
#define NURSE_H

#include "Worker.h"


class Nurse : public Worker {
    int ExperienceYears;
public:

	Nurse(const char* name, int id, int birthYear, Gender gender, int ExperienceYears = 0);
    Nurse(const Worker& worker);
	Nurse(const Nurse& nurse);
	Nurse(Nurse&& nurse);


	// getters
	int getExperienceYears() const { return ExperienceYears; }

	// setters
	void setExperienceYears(int experienceYears);

	// other methods
	virtual void showthis() const override {
		Worker::showthis();
		cout << "Experience Years: " << ExperienceYears << endl;
	}

	virtual void toOs(ostream& os) const override;

};

#endif // NURSE_H
