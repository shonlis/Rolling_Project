#ifndef DOCTOR_H
#define DOCTOR_H

#include "Worker.h"
#include <string>

class Doctor : public Worker {
public:
    std::string specialization;

    // streaming
    friend std::ostream& operator<<(std::ostream& os, const Doctor& d);

    Doctor(const Worker& Worker);
    Doctor(const Doctor& other);
    ~Doctor() = default;

    // getters
    const char* getSpecialization() const { return specialization.empty() ? nullptr : specialization.c_str(); };

    // setters
    bool setSpecialization(const char* specialization);

    // other methods

};

#endif // DOCTOR_H
