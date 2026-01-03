#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <ctime>
#include <iomanip>

#include "hospital.h"
#include "doctor.h"
#include "nurse.h"
#include "Visitor.h"
#include "Researcher.h"
#include "Article.h"
#include "research_center.h"

using namespace std;

static string nowDate()
{
    time_t t = time(nullptr);
    tm lt;
#if defined(_MSC_VER)
    localtime_s(&lt, &t);
#else
    localtime_r(&t, &lt);
#endif
    char buf[32];
    snprintf(buf, sizeof(buf), "%04d-%02d-%02d", lt.tm_year + 1900, lt.tm_mon + 1, lt.tm_mday);
    return string(buf);
}

static int askInt(const string &prompt)
{
    cout << prompt;
    int v; cin >> v; cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return v;
}

static string askLine(const string &prompt)
{
    cout << prompt;
    string s; getline(cin, s); return s;
}

int main()
{
    cout << "Afeka - Hospital Interactive System" << endl;

    Hospital hospital("Afeka Hospital");

    // Hard-coded initial data (coded-hard) so system is not empty
    Department* cardiology = hospital.addDepartment("Cardiology");
    Department* emergency = hospital.addDepartment("Emergency");
	cout << "Added departments: " << cardiology->getName() << ", " << emergency->getName() << "\n";

    vector<Doctor*> doctors;
    vector<Nurse*> nurses;
    vector<Visitor*> visitors;
    vector<research_center*> centers;
    vector<Researcher*> researchers;

    // Create one doctor and one nurse and register them in departments
    {
        // Person args: name, id, birthYear, gender (pass 0 for unknown)
        Person p1("Dr. Alice", 1001, 1980, (Person::Gender)0);
        Worker w1(p1);
        Doctor* d1 = new Doctor(w1);
        d1->setSpecialization("Cardiology");
        if (cardiology) cardiology->addDoctor(*d1);
        hospital.addDoctor(*d1);
        doctors.push_back(d1);

        Person p2("Nurse Carol", 2001, 1990, (Person::Gender)0);
        Worker w2(p2);
        Nurse* n1 = new Nurse(w2);
        if (cardiology) cardiology->addNurse(*n1);
        hospital.addNurse(*n1);
        nurses.push_back(n1);

        Person p3("Dr. Pop", 1002, 1980, (Person::Gender)0);
        Worker w3(p3);
        Doctor* d3 = new Doctor(w3);
        d3->setSpecialization("Cardiology");
        if (cardiology) cardiology->addDoctor(*d3);
        hospital.addDoctor(*d3);
        doctors.push_back(d3);

        Person p4("Nurse Carol", 2002, 1990, (Person::Gender)0);
        Worker w4(p4);
        Nurse* n2 = new Nurse(w4);
        if (cardiology) cardiology->addNurse(*n2);
        hospital.addNurse(*n2);
        nurses.push_back(n2);

        Person p5("Dr. Bob", 1003, 1985, (Person::Gender)0);
        Worker w5(p5);
        Doctor* d2 = new Doctor(w5);
        d2->setSpecialization("Emergency");
        if (emergency) emergency->addDoctor(*d2);
        hospital.addDoctor(*d2);
        doctors.push_back(d2);

        Person p6("Nurse Carol", 2003, 1990, (Person::Gender)0);
        Worker w6(p6);
        Nurse* n3 = new Nurse(w6);
        if (emergency) emergency->addNurse(*n3);
        hospital.addNurse(*n3);
        nurses.push_back(n3);


    }

    // Create a research center and a researcher
    research_center* rc = hospital.addResearchCenter(string("Afeka Research"));
	cout << "Added research center: " << rc->getName() << "\n";
    if (rc) centers.push_back(rc);
    if (rc)
    {
        Person pr1("Res. Frank", 3001, 1975, (Person::Gender)0);
        Worker wr1(pr1);
        Researcher* r1 = new Researcher(wr1);
        if (rc->addResearcher(*r1))
        {
            researchers.push_back(r1);
            hospital.addResearcher(*r1);
            // add one article
            Article* a1 = new Article("Cardiac Study", "2023-05-01", "Journal of Heart");
            r1->addArticle(*a1);
            hospital.addArticleToResearcher(*a1);
        }

        Person pr2("Res. Prank", 3002, 1975, (Person::Gender)0);
        Worker wr2(pr2);
        Researcher* r2 = new Researcher(wr2);
        if (rc->addResearcher(*r2))
        {
            researchers.push_back(r2);
            hospital.addResearcher(*r2);
            // add one article
            Article* a2 = new Article("Cardiac 2", "2025-05-01", "Journal of Heart1");
            r2->addArticle(*a2);
            hospital.addArticleToResearcher(*a2);
            Article* a3 = new Article("Cardiac 3", "2026-01-01", "Journal of Heart2");
            r2->addArticle(*a3);
            hospital.addArticleToResearcher(*a3);
        }
    }

    // Add a visitor
    {
        Person pv1("John Doe1", 4001, 1965, (Person::Gender)0);
        Visitor* v1 = new Visitor(pv1);
		visitors.push_back(v1);
		hospital.addVisitor(*v1);
        if (emergency) emergency->addVisitor(*v1);
        // add a visit card
        VisitCard vc1("Checkup", nowDate().c_str(), *emergency, nullptr);
        v1->addVisitCard(vc1);

        Person pv2("John Doe2", 4002, 1965, (Person::Gender)0);
        Visitor* v2 = new Visitor(pv2);
		visitors.push_back(v2);
		hospital.addVisitor(*v2);
        if (emergency) emergency->addVisitor(*v2);
        // add a visit card
        VisitCard vc2("Checkup", nowDate().c_str(), *emergency, nullptr);
        v2->addVisitCard(vc2);

        Person pv3("John Doe3", 4003, 1965, (Person::Gender)0);
        Visitor* v3 = new Visitor(pv3);
		visitors.push_back(v3);
		hospital.addVisitor(*v3);
        if (emergency) emergency->addVisitor(*v3);
        // add a visit card
        VisitCard vc3("Checkup", nowDate().c_str(), *emergency, nullptr);
        v3->addVisitCard(vc3);

    }

    cout << "Initial data added. Today=" << nowDate() << "\n";

    // Interactive menu
    while (true)
    {
        cout << "\nMenu:\n";
        cout << "1) Add department\n";
        cout << "2) Add nurse and assign to department\n";
        cout << "3) Add doctor and assign to department\n";
        cout << "4) Add visit (existing/new visitor)\n";
        cout << "5) Add researcher to research center\n";
        cout << "6) Add article for researcher\n";
        cout << "7) Show all visitors in a department\n";
        cout << "8) Show all medical staff\n";
        cout << "9) Show all researchers\n";
        cout << "10) Search visitor by id\n";
        cout << "11) Exit\n";
        cout << "12) Test operators (+= and researcher compare)\n";

        int choice = askInt("Select option: ");

        if (choice == 1)
        {
            string dname = askLine("Department name: ");
            Department* d = hospital.addDepartment(dname.c_str());
            if (d) cout << "Added department: " << d->getName() << '\n';
            else cout << "Failed to add department\n";
        }
        else if (choice == 2)
        {
            string name = askLine("Nurse name: ");
            int id = askInt("ID (int): ");
            int birth = askInt("Birth year: ");
            string dept = askLine("Department name to assign: ");
            Person p(name.c_str(), id, birth, (Person::Gender)0);
            Worker w(p);
            Nurse* n = new Nurse(w);
            Department* d = hospital.getDepartmentByName(dept.c_str());
            if (d && d->addNurse(*n)) cout << "Nurse added to department " << d->getName() << '\n';
            else cout << "Failed to add nurse or department not found\n";
            nurses.push_back(n);
            hospital.addNurse(*n);
        }
        else if (choice == 3)
        {
            string name = askLine("Doctor name: ");
            int id = askInt("ID (int): ");
            int birth = askInt("Birth year: ");
            string dept = askLine("Department name to assign: ");
            string spec = askLine("Specialization: ");
            Person p(name.c_str(), id, birth, (Person::Gender)0);
            Worker w(p);
            Doctor* d = new Doctor(w);
            d->setSpecialization(spec.c_str());
            Department* dep = hospital.getDepartmentByName(dept.c_str());
            if (dep && dep->addDoctor(*d)) cout << "Doctor added to department " << dep->getName() << '\n';
            else cout << "Failed to add doctor or department not found\n";
            doctors.push_back(d);
            hospital.addDoctor(*d);
        }
        else if (choice == 4)
        {
            cout << "Is the visitor already in the system? 1=yes 2=no\n";
            int ex = askInt("Choice: ");
            Visitor* v = nullptr;
            if (ex == 1)
            {
                int vid = askInt("Enter visitor ID: ");
                for (auto vv : visitors) if (vv->getId() == vid) { v = vv; break; }
                if (!v) cout << "Visitor not found\n";
            }
            else
            {
                string name = askLine("Visitor name: ");
                int id = askInt("ID (int): ");
                int birth = askInt("Birth year: ");
                Person p(name.c_str(), id, birth, (Person::Gender)0);
                v = new Visitor(p);
                visitors.push_back(v);
                hospital.addVisitor(p);
            }

            if (!v) continue;

            string dname = askLine("Department name for visit: ");
            Department* dep = hospital.getDepartmentByName(dname.c_str());
            if (!dep) { cout << "Department not found\n"; continue; }

            string purpose = askLine("Purpose of visit: ");
            string date = nowDate();

            // choose host worker (pick first doctor in department if any)
            Doctor* host = nullptr;
            // department keeps array, attempt to use getCurrentNumberOfDoctors and getDoctors() if available
            // here we try to get first doctor pointer via Department methods
            if (dep->getCurrentNumberOfDoctors() > 0)
            {
                host = dep->getDoctors()[0];
            }

            if (!dep->VisitorExist(*v)) {
                dep->addVisitor(*v);            // ensure visitor is in department
                cout << "DEBUG: department now has " << dep->getCurrentNumberOfVisitors() << " visitors\n";
            }
            VisitCard* vc = new VisitCard(purpose.c_str(), date.c_str(), *dep, host);
            if (v->addVisitCard(*vc)) {          // attach visit to the visitor
                cout << "Visit added for visitor id=" << v->getId() << '\n';
                cout << "DEBUG: visitor now has " << v->getNumbrtOfCurrentVisits() << " visits\n";
            }
            else {
                cout << "Failed to add visit (duplicate?)\n";
                delete vc;
            }
        }
        else if (choice == 5)
        {
            if (centers.empty())
            {
                research_center* rc2 = hospital.addResearchCenter(string("Default Center"));
                if (rc2) centers.push_back(rc2);
            }
            string cname = askLine("Research center name to use: ");
            research_center* use = nullptr;
            for (auto c : centers) if (string(c->getName()) == cname) use = c;
            if (!use && !centers.empty()) use = centers.front();
            if (!use) { cout << "No research center available\n"; continue; }

            string name = askLine("Researcher name: ");
            int id = askInt("ID (int): ");
            int birth = askInt("Birth year: ");
            Person p(name.c_str(), id, birth, (Person::Gender)0);
            Worker w(p);
            Researcher* r = new Researcher(w);
            if (use->addResearcher(*r)) { researchers.push_back(r); hospital.addResearcher(*r); cout << "Researcher added\n"; }
            else { cout << "Failed to add researcher (may already exist)\n"; delete r; }
        }
        else if (choice == 6)
        {
            if (researchers.empty()) { cout << "No researchers available\n"; continue; }
            int rid = askInt("Enter researcher ID to add article to: ");
            Researcher* rr = nullptr;
            for (auto r : researchers) if (r->getId() == rid) { rr = r; break; }
            if (!rr) { cout << "Researcher not found\n"; continue; }
            string title = askLine("Article title: ");
            string date = askLine("Publication date: ");
            string mag = askLine("Magazine name: ");
            Article* a = new Article(title.c_str(), date.c_str(), mag.c_str());
            if (rr->addArticle(*a)) { hospital.addArticleToResearcher(*a); cout << "Article added\n"; }
            else { cout << "Failed to add article\n"; delete a; }
        }
        else if (choice == 7)
        {
            string dname = askLine("Department name: ");
            hospital.printDepartmentVisitors(dname.c_str());
        }
        else if (choice == 8)
        {
            hospital.printAllMedicalStaff();
        }
        else if (choice == 9)
        {
            hospital.printAllResearchers();
        }
        else if (choice == 10)
        {
            int vid = askInt("Enter visitor ID: ");
            // search visitors vector
            Visitor* vv = nullptr;
            for (auto v : visitors) if (v->getId() == vid) { vv = v; break; }
            if (!vv) { cout << "Visitor not found\n"; continue; }
            cout << "Visitor name: " << vv->getName() << '\n';
            // try to find department by scanning departments and their visitors
            bool found = false;
            for (int i = 0; i < hospital.countDepartments(); ++i) {}
            cout << "Department: (unknown in this minimal implementation)\n";
        }
        else if (choice == 11)
        {
            cout << "Exiting...\n";
            break;
        }
        else if (choice == 12)
        {
            cout << "Testing operators:\n";
            // test hospital += doctor/nurse by creating temporary objects
            Person pd("Dr. Bob", 5001, 1970, (Person::Gender)0);
            Worker wd(pd);
            Doctor tempD(wd);
            tempD.setSpecialization("General");
            hospital += tempD;
            cout << "Added doctor via operator+= to hospital (first department).\n";

            Person pn("Nurse Dan", 6001, 1985, (Person::Gender)0);
            Worker wn(pn);
            Nurse tempN(wn);
            tempN.setExperienceYears(5);
            hospital += tempN;
            cout << "Added nurse via operator+= to hospital (first department).\n";

            // researcher compare
            if (researchers.size() >= 2) {
                cout << "Compare researchers: " << *researchers[0] << *researchers[1];
                if (*researchers[0] < *researchers[1]) cout << researchers[0]->getName() << " has fewer articles\n";
                else if (*researchers[0] > *researchers[1]) cout << researchers[0]->getName() << " has more articles\n";
                else cout << "Researchers have equal number of articles\n";
            } else cout << "Not enough researchers to compare\n";
        }
        else
        {
            cout << "Invalid option\n";
        }
    }

    return 0;
}
