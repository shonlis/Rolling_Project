#ifndef NURSE_H
#define NURSE_H

#include "Worker.h"

class Nurse : public Worker
{
    int ExperienceYears;
public:

	Nurse(const string& name, int id, int birthYear, Gender gender, int ExperienceYears = 0);

    // getters
    int getExperienceYears() const { return ExperienceYears; }

    // setters
    void setExperienceYears(int experienceYears);

    // other methods
    virtual void showthis() const override
    {
        Worker::showthis();
        cout << "Experience Years: " << ExperienceYears << std::endl;
    }

    virtual void toOs(ostream& os) const override;

};

#endif // NURSE_H
