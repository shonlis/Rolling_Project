#include <iostream>
using namespace std;
#include "Visitor.h"
#include "VisitCard.h"

Visitor::Visitor(const string name, int id, int birthYear, Gender gender)
    : Person(name, id, birthYear, gender) {}

Visitor::~Visitor() = default;

Visitor::Visitor(const Visitor& visitor) : Person(visitor)
{
    visits.clear();
    for (const auto& v : visitor.visits) visits.push_back(v ? v->clone() : nullptr);
}

Visitor::Visitor(Visitor&& visitor) noexcept : Person(std::move(visitor)), visits(std::move(visitor.visits)) {}

void Visitor::showthis() const
{
    Person::showthis();
    std::cout << "Number of visits: " << getNumbrtOfCurrentVisits() << std::endl;
    for (const auto& v : visits) {
        if (v) std::cout << *v << std::endl;
    }
}

bool Visitor::addVisitCard(const VisitCard& visitCard)
{
    if (visitCardExist(visitCard)) return false;
    visits.push_back(visitCard.clone());
    return true;
}

bool Visitor::visitCardExist(const VisitCard& visitCard) const
{
    for (const auto& v : visits) {
        if (v && v->getVisitCardNumber() == visitCard.getVisitCardNumber()) return true;
    }
    return false;
}

ostream& operator<<(ostream& os, const Visitor& Visitor)
{
    os << "Visitor Details: " << Visitor.getName() << ": ID = " << Visitor.getId() << ", number of visits = " << Visitor.getNumbrtOfCurrentVisits() << endl;
    for (const auto& v : Visitor.visits) os << *v << endl;
    return os;
}
