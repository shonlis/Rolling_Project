#ifndef NURSE_H
#define NURSE_H

#include "Worker.h"
#include <utility>


class Nurse : public Worker {
    int ExperienceYears;
public:

    Nurse(const char* name, int id, int birthYear, Gender gender, int ExperienceYears = 0);
    Nurse(const Worker& worker);
    Nurse(const Nurse& nurse);
    Nurse(Nurse&& nurse) noexcept;


    // getters
    int getExperienceYears() const { return ExperienceYears; }

    // setters
    void setExperienceYears(int experienceYears);

    // other methods
    virtual void showthis() const override {
        Worker::showthis();
        std::cout << "Experience Years: " << ExperienceYears << std::endl;
    }

    virtual void toOs(std::ostream& os) const override;

};

#endif // NURSE_H
