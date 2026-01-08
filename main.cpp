#include <iostream>
#include <limits>
#include <ctime>
#include <iomanip>

#include "Hospital.h"
#include "Doctor.h"
#include "Nurse.h"
#include "Visitor.h"
#include "Researcher.h"
#include "Article.h"
#include "Research_Center.h"

using namespace std;

static char* nowDate()
{
    time_t t = time(nullptr);
    tm lt;
#if defined(_MSC_VER)
    localtime_s(&lt, &t);
#else
    localtime_r(&t, &lt);
#endif
    static char buf[32];
    snprintf(buf, sizeof(buf), "%04d-%02d-%02d", lt.tm_year + 1900, lt.tm_mon + 1, lt.tm_mday);
    return (buf);
}

static int askInt(const char* prompt)
{
    cout << prompt;
    int v; cin >> v; cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return v;
}

static char* askLine(const char* prompt)
{
    cout << prompt;
    const size_t bufsize = 256;
    char* s = new char[bufsize];
    cin.getline(s, bufsize);
    return s;
}

int main()
{
    cout << "Afeka - Hospital Interactive System" << endl;

    Hospital hospital("Afeka Hospital");

    // Hard-coded initial data (coded-hard) so system is not empty
    Department* cardiology = hospital.addDepartment("Cardiology");
    Department* emergency = hospital.addDepartment("Emergency");
	cout << "Added departments: " << cardiology->getName() << ", " << emergency->getName() << endl;

    // Create one doctor and one nurse and register them in departments
    {
        // Person args: name, id, birthYear, gender (pass 0 for male)
        Person p1("Dr. Alice", 1001, 1980, (Person::Gender)0);
        Worker w1(p1);
        Doctor* d1 = new Doctor(w1);
        d1->setSpecialization("Cardiology");
        if (cardiology) cardiology->addDoctor(*d1);
        hospital.addDoctor(*d1);

        Person p2("Nurse Carol", 2001, 1990, (Person::Gender)1);
        Worker w2(p2);
        Nurse* n1 = new Nurse(w2);
		n1->setExperienceYears(5);
        if (cardiology) cardiology->addNurse(*n1);
        hospital.addNurse(*n1);

        Person p3("Dr. Pop", 1002, 1980, (Person::Gender)0);
        Worker w3(p3);
        Doctor* d3 = new Doctor(w3);
        d3->setSpecialization("Cardiology");
        if (cardiology) cardiology->addDoctor(*d3);
        hospital.addDoctor(*d3);

        Person p4("Nurse Carol2", 2002, 1990, (Person::Gender)1);
        Worker w4(p4);
        Nurse* n2 = new Nurse(w4);
        n2->setExperienceYears(3);
        if (cardiology) cardiology->addNurse(*n2);
        hospital.addNurse(*n2);

        Person p5("Dr. Bob", 1003, 1985, (Person::Gender)0);
        Worker w5(p5);
        Doctor* d2 = new Doctor(w5);
        d2->setSpecialization("Emergency");
        if (emergency) emergency->addDoctor(*d2);
        hospital.addDoctor(*d2);

        Person p6("Nurse Carol3", 2003, 1990, (Person::Gender)1);
        Worker w6(p6);
        Nurse* n3 = new Nurse(w6);
        n3->setExperienceYears(2);
        if (emergency) emergency->addNurse(*n3);
        hospital.addNurse(*n3);
    }

    // Create a research center and a researcher
    research_center* rc = hospital.addResearchCenter(("Afeka Research"));
	hospital.setResearchCenter(*rc);
	cout << "Added research center: " << rc->getName() << endl;
    if (rc)
    {
        Person pr1("Res. Frank", 3001, 1975, (Person::Gender)0);
        Worker wr1(pr1);
        Researcher* r1 = new Researcher(wr1);
        if (rc->addResearcher(*r1))
        {
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
		hospital.addVisitor(*v1);
        if (emergency) emergency->addVisitor(*v1);
        // add a visit card
        VisitCard vc1("Checkup", nowDate(), *emergency, nullptr);
        v1->addVisitCard(vc1);

        Person pv2("John Doe2", 4002, 1965, (Person::Gender)0);
        Visitor* v2 = new Visitor(pv2);
		hospital.addVisitor(*v2);
        if (emergency) emergency->addVisitor(*v2);
        // add a visit card
        VisitCard vc2("Checkup", nowDate(), *emergency, nullptr);
        v2->addVisitCard(vc2);

        Person pv3("John Doe3", 4003, 1965, (Person::Gender)0);
        Visitor* v3 = new Visitor(pv3);
		hospital.addVisitor(*v3);
        if (emergency) emergency->addVisitor(*v3);
        // add a visit card
        VisitCard vc3("Checkup", nowDate(), *emergency, nullptr);
        v3->addVisitCard(vc3);

    }

    cout << "Initial data added. Today=" << nowDate() << endl;

    // Interactive menu
    while (true)
    {
        cout << "\nMenu:" << endl;
        cout << "1) Add department" << endl;
        cout << "2) Add nurse and assign to department" << endl;
        cout << "3) Add doctor and assign to department" << endl;
        cout << "4) Add visit (existing/new visitor)" << endl;
        cout << "5) Add researcher to research center" << endl;
        cout << "6) Add article for researcher" << endl;
        cout << "7) Show all visitors in a department" << endl;
        cout << "8) Show all medical staff" << endl;
        cout << "9) Show all researchers" << endl;
        cout << "10) Search visitor by id" << endl;
        cout << "11) Exit" << endl;
        cout << "12) Test operators (+= and researcher compare)" << endl;

        int choice = askInt("Select option: ");

        if (choice == 1)
        {
            char* dname = askLine("Department name: ");
            Department* d = hospital.addDepartment(dname);
            if (d) cout << "Added department: " << d->getName() << endl;
            else cout << "Failed to add department" << endl;
        }
        else if (choice == 2)
        {
            char* name = askLine("Nurse name: ");
            int id = askInt("ID (int): ");
            int birth = askInt("Birth year(DDMMYYYY): ");
            hospital.printAllDepartments();
            char* dept = askLine("Department name to assign(): ");
            Person p(name, id, birth, (Person::Gender)0);
            p.setGender((Person::Gender)askInt("Gender (0=Male, 1=Female, 2=Unknown): "));
            Worker w(p);
            Nurse* n = new Nurse(w);
			int exp = askInt("Experience years: ");
			n->setExperienceYears(exp);
            Department* d = hospital.getDepartmentByName(dept);
            if (d && d->addNurse(*n)) cout << "Nurse added to department " << d->getName() << endl;
            else cout << "Failed to add nurse or department not found" << endl;
            hospital.addNurse(*n);
        }
        else if (choice == 3)
        {
            char* name = askLine("Doctor name: ");
            int id = askInt("ID (int): ");
            int birth = askInt("Birth year(DDMMYYYY): "); 
            hospital.printAllDepartments();
            char* dept = askLine("Department name to assign: ");
            char* spec = askLine("Specialization: ");
            Person p(name, id, birth, (Person::Gender)0);
            p.setGender((Person::Gender)askInt("Gender (0=Male, 1=Female, 2=Unknown): "));
            Worker w(p);
            Doctor* d = new Doctor(w);
            d->setSpecialization(spec);
            Department* dep = hospital.getDepartmentByName(dept);
            if (dep && dep->addDoctor(*d)) cout << "Doctor added to department " << dep->getName() << endl;
            else cout << "Failed to add doctor or department not found" << endl;
            hospital.addDoctor(*d);
        }
        else if (choice == 4)
        {
            cout << "Is the visitor already in the system? 1=yes 2=no" << endl;
            int ex = askInt("Choice: ");
            Visitor* v = nullptr;
            if (ex == 1)
            {
                int vid = askInt("Enter visitor ID: ");
                for (int i = 0; i < hospital.countVisitors(); ++i) {
                    Visitor* vv = hospital.findVisitorById(vid);
                    if (vv && vv->getId() == vid) { v = vv; break; }
                }
                if (!v) cout << "Visitor not found" << endl;
            }
            else
            {
                char* name = askLine("Visitor name: ");
                int id = askInt("ID (int): ");
                int birth = askInt("Birth year(DDMMYYYY): ");
                Person p(name, id, birth, (Person::Gender)0);
                p.setGender((Person::Gender)askInt("Gender (0=Male, 1=Female, 2=Unknown): "));
                v = new Visitor(p);
                hospital.addVisitor(p);
            }

            if (!v) continue;

            hospital.printAllDepartments();
            char* dname = askLine("Department name for visit: ");
            Department* dep = hospital.getDepartmentByName(dname);
            if (!dep) { cout << "Department not found" << endl; continue; }

            char* purpose = askLine("Purpose of visit: ");
            char* date = nowDate();

			hospital.printDepartmentMedicalStaff(dname);
			Doctor* host = nullptr;
			char* hostName = askLine("Host doctor/nurse name: ");
            Doctor* dd = hospital.getDoctorByName(hostName);
            if (dd) { host = dd; }
			if (!host) { cout << "Host doctor not found" << endl; continue; }

            if (!dep->VisitorExist(*v)) {
                dep->addVisitor(*v);            // ensure visitor is in department
                cout << "DEBUG: department now has " << dep->getCurrentNumberOfVisitors() << " visitors" << endl;
            }
            VisitCard* vc = new VisitCard(purpose, date, *dep, host);
            if (v->addVisitCard(*vc)) {          // attach visit to the visitor
                cout << "Visit added for visitor id=" << v->getId() << endl;
                cout << "DEBUG: visitor now has " << v->getNumbrtOfCurrentVisits() << " visits" << endl;
            }
            else {
                cout << "Failed to add visit (duplicate?)" << endl;
                delete vc;
            }
        }
        else if (choice == 5)
        {
            char* cname = askLine("Research center name to use: ");
            research_center* use = nullptr;
			use = hospital.getResearchCenter();
            if (!use) { cout << "No research center available" << endl; continue; }

            char* name = askLine("Researcher name: ");
            int id = askInt("ID (int): ");
            int birth = askInt("Birth year(DDMMYYYY): ");
            Person p(name, id, birth, (Person::Gender)0);
            p.setGender((Person::Gender)askInt("Gender (0=Male, 1=Female, 2=Unknown): "));
            Worker w(p);
            Researcher* r = new Researcher(w);
            if (use->addResearcher(*r)) { hospital.addResearcher(*r); cout << "Researcher added" << endl; }
            else { cout << "Failed to add researcher (may already exist)" << endl; delete r; }
        }
        else if (choice == 6)
        {
            int rid = askInt("Enter researcher ID to add article to: ");
            Researcher* rr = nullptr;

            Researcher* r = hospital.findResearcherById(rid);
            if (r && r->getId() == rid) { rr = r;}

            if (!rr) { cout << "Researcher not found" << endl; continue; }
            char* title = askLine("Article title: ");
            char* date = askLine("Publication date(DDMMYYYY): ");
            char* mag = askLine("Magazine name: ");
            Article* a = new Article(title, date, mag);
            if (rr->addArticle(*a)) { hospital.addArticleToResearcher(*a); cout << "Article added" << endl; }
            else { cout << "Failed to add article" << endl; delete a; }
        }
        else if (choice == 7)
        {
            hospital.printAllDepartments();
            char* dname = askLine("Department name: ");
            hospital.printDepartmentVisitors(dname);
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
            Visitor* v = nullptr;
            for (int i = 0; i < hospital.countVisitors(); ++i) {
                Visitor* vv = hospital.findVisitorById(vid);
                if (vv && vv->getId() == vid) { v = vv; break; }
            }
            if (!v) { cout << "Visitor not found" << endl; continue; }
            cout << "Visitor name: " << v->getName() << endl;
            // try to find department by scanning departments and their visitors
            bool found = false;
            for (int i = 0; i < hospital.countDepartments(); ++i) {}
            cout << "Department: (unknown in this minimal implementation)" << endl;
        }
        else if (choice == 11)
        {
            cout << "Exiting..." << endl;
            break;
        }
        else if (choice == 12)
        {
            cout << "Testing operators:" << endl;
            // test hospital += doctor/nurse by creating temporary objects
            Person pd("Dr. Bob", 5001, 1970, (Person::Gender)0);
            Worker wd(pd);
            Doctor tempD(wd);
            tempD.setSpecialization("General");
            hospital += tempD;
            cout << "Added doctor via operator+= to hospital (first department)." << endl;

            Person pn("Nurse Dan", 6001, 1985, (Person::Gender)1);
            Worker wn(pn);
            Nurse tempN(wn);
            tempN.setExperienceYears(5);
            hospital += tempN;
            cout << "Added nurse via operator+= to hospital (first department)." << endl;

            // researcher compare
            if (hospital.countResearchers() >= 2) {
                cout << "Compare researchers: " << *hospital.findResearcherById(1) << *hospital.findResearcherById(2);
                if (*hospital.findResearcherById(1) < *hospital.findResearcherById(2)) cout << hospital.findResearcherById(1)->getName() << " has fewer articles" << endl;
                else if (*hospital.findResearcherById(1) > *hospital.findResearcherById(2)) cout << hospital.findResearcherById(1)->getName() << " has more articles" << endl;
                else cout << "Researchers have equal number of articles" << endl;
            } else cout << "Not enough researchers to compare" << endl;
        }
        else
        {
            cout << "Invalid option" << endl;
        }
    }

    return 0;
}
