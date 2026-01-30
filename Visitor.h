#ifndef Visitor__H_
#define Visitor__H_


#include "Person.h"
#include <vector>
#include <memory>

class VisitCard;

class Visitor : public Person
{
private:
    std::vector<std::unique_ptr<VisitCard>> visits; // owns visit cards
public:

    Visitor(const char* name, int id, int birthYear, Gender gender);
    ~Visitor();

    Visitor(const Visitor& visitor);
    Visitor(Visitor&& visitor) noexcept;

    //getters
    int getNumbrtOfCurrentVisits() const { return static_cast<int>(visits.size()); }

    // other methods
    void showthis() const override;
    bool addVisitCard(const VisitCard& visitCard);
    bool visitCardExist(const VisitCard& visitCard) const;

    //operators overloading
    friend std::ostream& operator<<(std::ostream& os, const Visitor& Visitor);
};

#endif // !Visitor__H_
