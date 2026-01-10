#include <iostream>
#include <limits>
#include <ctime>


#include <crtdbg.h>

#include "Hospital.h"
#include "Doctor.h"
#include "Nurse.h"
#include "Visitor.h"
#include "Researcher.h"
#include "Article.h"
#include "Research_Center.h"

using namespace std;

#define new DBG_NEW

#ifdef _DEBUG
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#else
#define DBG_NEW new
#endif

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
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    cout << "Afeka - Hospital Interactive System" << endl;
    research_center research_center;
    Hospital hospital("Afeka Hospital", research_center);

    // Hard-coded initial data (coded-hard) so system is not empty
    Department department1 = Department("Cardiology");
    Department department2 = Department("Emergency");
    Department department3 = Department("Oncology");

    hospital.addDepartment(department1);
    hospital.addDepartment(department2);
	hospital.addDepartment(department3);

    hospital.printAllDepartments();
    // Create one doctor and one nurse and register them in departments
        // Person args: name, id, birthYear, gender (pass 0 for male)
        Person p1("Dr. Alice", 1001, 1980, (Person::Gender)0);
        Worker w1(p1);
        Doctor d1(w1);
        d1.setSpecialization("Cardiology");
        hospital.addDoctorToDepartment(d1, department1.getName());
        
        Person p2("Nurse Carol", 2001, 1990, (Person::Gender)1);
        Worker w2(p2);
        Nurse n1(w2);
        n1.setExperienceYears(5);
        hospital.addNurseToDepartment(n1, department1.getName());

        Person p3("Dr. Pop", 1002, 1980, (Person::Gender)0);
        Worker w3(p3);
        Doctor d3(w3);
        d3.setSpecialization("Cardiology");
        hospital.addDoctorToDepartment(d3, department1.getName());

        Person p4("Nurse Carol2", 2002, 1990, (Person::Gender)1);
        Worker w4(p4);
        Nurse n2(w4);
        n2.setExperienceYears(3);
		hospital.addNurseToDepartment(n2, department1.getName());

        Person p5("Dr. Bob", 1003, 1985, (Person::Gender)0);
        Worker w5(p5);
        Doctor d2(w5);
        d2.setSpecialization("Emergency");
		hospital.addDoctorToDepartment(d2, department2.getName());

        Person p6("Nurse Carol3", 2003, 1990, (Person::Gender)1);
        Worker w6(p6);
        Nurse n3(w6);
        n3.setExperienceYears(2);
		hospital.addNurseToDepartment(n3, department1.getName());

    
        Person pr1("Res. Frank", 3001, 1975, (Person::Gender)0);
        Worker wr1(pr1);
        Researcher r1 =  Researcher(wr1);
        
        hospital.addResearcher(r1);
            // add one article
        Article a1 = Article("Cardiac Study", "2023-05-01", "Journal of Heart");
        hospital.addArticleToResearchCenter(r1, a1);


        Person pr2("Res. Prank", 3002, 1975, (Person::Gender)0);
        Worker wr2(pr2);
        Researcher r2 = Researcher(wr2);
     
        hospital.addResearcher(r2);
            // add one article
        Article a2 = Article("Cardiac 2", "2025-05-01", "Journal of Heart1");
        hospital.addArticleToResearchCenter(r2, a2);

        Article a3 = Article("Cardiac 3", "2026-01-01", "Journal of Heart2");
        hospital.addArticleToResearchCenter(r2, a3);

    // Add a visitor
    {
        Person p1("John Doe1", 4001, 1965, (Person::Gender)0);
        Visitor v1(p1);
        // add a visit card
        VisitCard vc1("Checkup", nowDate(), *hospital.getDepartmentByName("Emergency"), nullptr);
        v1.addVisitCard(vc1);
        hospital.addVisitor(v1);
		hospital.getDepartmentByName("Emergency")->addVisitor(hospital.getVisitorByName("John Doe1"));


        Person p2("John Doe2", 4002, 1965, (Person::Gender)0);
        Visitor v2(p2);
        // add a visit card
        VisitCard vc2("Checkup", nowDate(), *hospital.getDepartmentByName("Emergency"), nullptr);
        v2.addVisitCard(vc2);
        hospital.addVisitor(v2);
        hospital.getDepartmentByName("Emergency")->addVisitor(hospital.getVisitorByName("John Doe2"));

        Person p3("John Doe3", 4003, 1965, (Person::Gender)0);
        Visitor v3(p3);
        // add a visit card
        VisitCard vc3("Checkup", nowDate(), *hospital.getDepartmentByName("Emergency"), nullptr);
        v3.addVisitCard(vc3);
        hospital.addVisitor(v3);
		hospital.getDepartmentByName("Emergency")->addVisitor(hospital.getVisitorByName("John Doe3"));

    }

    cout << "Initial data added. Today=" << nowDate() << endl;

    char* name;
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
            name = askLine("Department name: ");
			Department dept(name);
            hospital.addDepartment(dept);
            cout << "Added department: " << name << endl;
        }
        else if (choice == 2)
        {
            name = askLine("Nurse name: ");
            int id = askInt("ID (int): ");
            int birth = askInt("Birth year(DDMMYYYY): ");
            Person p(name, id, birth, (Person::Gender)0);
            p.setGender((Person::Gender)askInt("Gender (0=Male, 1=Female, 2=Unknown): "));
            Worker w(p);

            Nurse n(w);
            int exp = askInt("Experience years: ");
            n.setExperienceYears(exp);

            hospital.printAllDepartments();
            name = askLine("Department name to assign(): ");
            hospital.getDepartmentByName(name);
            cout << "Nurse added to department " << name << endl;
            hospital.addNurse(n);

        }
        else if (choice == 3)
        {
            name = askLine("Doctor name: ");
            int id = askInt("ID (int): ");
            int birth = askInt("Birth year(DDMMYYYY): ");

            Person p(name, id, birth, (Person::Gender)0);
            p.setGender((Person::Gender)askInt("Gender (0=Male, 1=Female, 2=Unknown): "));
            Worker w(p);
            Doctor d(w);
            name = askLine("Specialization: ");
            d.setSpecialization(name);

            hospital.printAllDepartments();
            name = askLine("Department name to assign: ");
            hospital.getDepartmentByName(name);
            cout << "Doctor added to department " << name << endl;
            hospital.addDoctor(d);
        }
        else if (choice == 4)
        {
            int found = 0;
            int id;
            int vid = askInt("Enter visitor ID: ");
            if (hospital.findVisitorById(vid))
            {
                if (hospital.findVisitorById(vid)->getId() == vid) { found = 1;}
            }
            if (!found){

                char* name = askLine("Visitor name: ");
                id = askInt("ID (int): ");
                int birth = askInt("Birth year(DDMMYYYY): ");
                Person p(name, id, birth, (Person::Gender)0);
                p.setGender((Person::Gender)askInt("Gender (0=Male, 1=Female, 2=Unknown): "));
				Visitor  v(p);
                hospital.addVisitor(v);
            }

            hospital.printAllDepartments();
            name = askLine("Department name for visit: ");
            if (!hospital.getDepartmentByName(name)) { cout << "Department not found" << endl; continue; }

            char* purpose = askLine("Purpose of visit: ");
            char* date = nowDate();

            VisitCard vc(purpose, date, *hospital.getDepartmentByName(name), nullptr);
            hospital.printDepartmentMedicalStaff(name);
            name = askLine("Host doctor/nurse name: ");
            if (!hospital.getDoctorByName(name) && !hospital.getNurseByName(name))
            {
                cout << "Host doctor not found" << endl;

            }
            else
            {
                vc.setHostWorker(hospital.getDoctorByName(name) ? hospital.getDoctorByName(name)->getName() : hospital.getNurseByName(name)->getName());
            }
            if(found)
                hospital.findVisitorById(vid)->addVisitCard(vc);
            else
				hospital.findVisitorById(id)->addVisitCard(vc);
        }
        else if (choice == 5)
        {
            name = askLine("Researcher name: ");
            int id = askInt("ID (int): ");
            int birth = askInt("Birth year(DDMMYYYY): ");
            Person p(name, id, birth, (Person::Gender)0);
            p.setGender((Person::Gender)askInt("Gender (0=Male, 1=Female, 2=Unknown): "));
            Worker w(p);
            Researcher r(w);
            hospital.addResearcher(r);
            cout << "Researcher " << name << " added" << endl;
        }
        else if (choice == 6)
        {
            hospital.printAllResearchers();
            int rid = askInt("Enter researcher ID to add article to: ");
            if (hospital.findResearcherById(rid)) { cout << "Researcher not found" << endl; continue; }

            char* title = askLine("Article title: ");
            char* date = askLine("Publication date(DDMMYYYY): ");
            char* mag = askLine("Magazine name: ");
            Article a  = Article(title, date, mag);
            hospital.findResearcherById(rid)->addArticle(a);
            cout << "Article " << a.getTitle() << " added" << endl;
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
            int found = 0;
            int vid = askInt("Enter visitor ID: ");
            // search visitors vector
            for (int i = 0; i < hospital.countVisitors(); ++i)
            {
                hospital.findVisitorById(vid);
                if (hospital.findVisitorById(vid)->getId() == vid) { found = 1;}
            }
            if (found) 
            {
                cout << "Visitor name: " << hospital.findVisitorById(vid)->getName() << endl;
            }
            else
            { 
                cout << "Visitor not found" << endl;
            }
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
            }
            else cout << "Not enough researchers to compare" << endl;
        }
        else
        {
            cout << "Invalid option" << endl;
        }
    }

    //delete name;

    return 0;
}
