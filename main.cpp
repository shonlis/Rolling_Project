using namespace std;
#include <iostream>
#include <limits>
#include <ctime>


#include <crtdbg.h>

#include "Hospital.h"
#include "Doctor.h"
#include "Surgen.h"
#include "Surgery.h"
#include "Nurse.h"
#include "Visitor.h"
#include "Researcher.h"
#include "Article.h"
#include "Research_Center.h"
#include "Department.h"
#include "VisitCard.h"
#include "ResearcherDoctor.h"



#define new DBG_NEW

#ifdef _DEBUG
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#else
#define DBG_NEW new
#endif

static std::string nowDate()
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
    return std::string(buf);
}

static int askInt(const std::string& prompt)
{
    std::cout << prompt;
    int v; std::cin >> v; std::cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
    return v;
}

static std::string askLine(const std::string& prompt)
{
    std::cout << prompt;
    std::string s;
    std::getline(std::cin, s);
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
        Doctor d1("Dr. Alice", 1001, 1980, (Person::Gender)0, "Cardiology");
        d1.setSpecialization("Cardiology");
        hospital.addDoctorToDepartment(d1, department1.getName());
        
        Nurse n1("Nurse Carol", 2001, 1990, (Person::Gender)1, 5);
        n1.setExperienceYears(5);
        hospital.addNurseToDepartment(n1, department1.getName());

        Doctor d2("Dr. Pop", 1002, 1980, (Person::Gender)0, "Cardiology");
        d2.setSpecialization("Cardiology");
        hospital.addDoctorToDepartment(d2, department2.getName());

        Nurse n2("Nurse Carol2", 2002, 1990, (Person::Gender)1, 3);
        n2.setExperienceYears(3);
		hospital.addNurseToDepartment(n2, department2.getName());

        Doctor d3("Dr. Bob", 1003, 1985, (Person::Gender)0, "Emergency");
        d3.setSpecialization("Emergency");
		hospital.addDoctorToDepartment(d3, department3.getName());

        Doctor d4("Dr. Surgeon", 1022, 1922, (Person::Gender)0, "Emergency");
		d4.setSpecialization("Emergency");
        Surgen s1(d4);
        s1.setNumberOfOperations(10);
		hospital.addDoctorToDepartment(s1, department3.getName());

        Nurse n3("Nurse Carol3", 2003, 1990, (Person::Gender)1, 2);
        n3.setExperienceYears(2);
		hospital.addNurseToDepartment(n3, department1.getName());

        Researcher r1 =  Researcher("Res. Frank", 3001, 1975, (Person::Gender)0);
        
        hospital.addResearcher(r1);
            // add one article
        Article a1 = Article("Cardiac Study", "2023-05-01", "Journal of Heart");
        hospital.addArticleToResearchCenter(r1, a1);

        Researcher r2 = Researcher("Res. Fun", 3002, 1975, (Person::Gender)0);
     
        hospital.addResearcher(r2);
            // add one article
        Article a2 = Article("Cardiac 2", "2025-05-01", "Journal of Heart1");
        hospital.addArticleToResearchCenter(r2, a2);

        Article a3 = Article("Cardiac 3", "2026-01-01", "Journal of Heart2");
        hospital.addArticleToResearchCenter(r2, a3);

        Researcher r3 = Researcher("Res. Fun", 3002, 1975, (Person::Gender)0);
		ResearcherDoctor rd1(r3, d2);
        hospital.addResearcher(rd1);
        // add one article
        Article a4 = Article("Cardiologgg", "2025-02-01", "Journal of Heart18");
        hospital.addArticleToResearchCenter(rd1, a4);


        Visitor v1("John Doe1", 4001, 1965, (Person::Gender)0);
        // add a visit card
        VisitCard vc1("test", nowDate(), *hospital.getDepartmentByName("Emergency"), std::string());
        hospital.addVisit(v1, vc1, "Emergency");

        Visitor v2("John Doe2", 4002, 1965, (Person::Gender)0);
        // add a visit card
        VisitCard vc2("test", nowDate(), *hospital.getDepartmentByName("Emergency"), std::string());
        hospital.addVisit(v2, vc2, "Cardiology");

        Visitor v3("John Doe3", 4003, 1965, (Person::Gender)0);
        // add a visit card
        VisitCard vc3("test", nowDate(), *hospital.getDepartmentByName("Emergency"), std::string());
        hospital.addVisit(v3, vc3, "Oncology");
 

    cout << "Initial data added. Today=" << nowDate() << endl;

    std::string name;
    // Interactive menu
    while (true)
    {
        cout << "\nMenu:" << endl;
        cout << "1) Add department" << endl;
        cout << "2) Add nurse and assign to department" << endl;
        cout << "3) Add doctor(surgeon) and assign to department" << endl;
        cout << "4) Add visit (existing/new visitor)" << endl;
        cout << "5) Add researcher(doctor) to research center" << endl;
        cout << "6) Add article for researcher" << endl;
        cout << "7) Show all visitors in a department" << endl;
        cout << "8) Show all medical staff" << endl;
        cout << "9) Show all surgeons" << endl;
        cout << "10) Show all researchers" << endl;
        cout << "11) Search visitor by id" << endl;
        cout << "12) Exit" << endl;
        cout << "13) Test operators (+= and researcher compare)" << endl;

        int choice = askInt("Select option: ");

        if (choice == 1)
        {
            name = askLine("Department name: ");
            Department dept(name.c_str());
            hospital.addDepartment(dept);
            cout << "Added department: " << name << endl;
        }
        else if (choice == 2)
        {
            name = askLine("Nurse name: ");
            int id = askInt("ID (int): ");
            int birth = askInt("Birth year(YYYY): ");
            Nurse n(name.c_str(), id, birth, (Person::Gender)askInt("Gender (0=Male, 1=Female, 2=Unknown): "));
            int exp = askInt("Experience years: ");
            n.setExperienceYears(exp);
            
            hospital.printAllDepartments();
            name = askLine("Department name to assign(): ");
            cout << "Nurse added to department " << name << endl;
            hospital.addNurse(n);
            hospital.addNurseToDepartment(n, name.c_str());
        }
        else if (choice == 3)
        {
            name = askLine("Doctor name: ");
            int id = askInt("ID (int): ");
            int birth = askInt("Birth year(YYYY): ");
            Doctor d(name.c_str(), id, birth, (Person::Gender)askInt("Gender (0=Male, 1=Female, 2=Unknown): "));
            name = askLine("Specialization: ");
            d.setSpecialization(name.c_str());
            std::string is_sutgen = askLine("Doctor is surgeon (1=Yes, 0=No): ");
            if(is_sutgen == "1" || is_sutgen == "Yes" || is_sutgen == "y" || is_sutgen == "Y") {
                Surgen s(d);
				int num_ops = askInt("Number of operations performed: ");
				s.setNumberOfOperations(num_ops);

                hospital.printAllDepartments();
                name = askLine("Department name to assign: ");
                hospital.getDepartmentByName(name.c_str());
                cout << "Doctor added to department " << name << endl;
                hospital.addDoctor(s);
                hospital.addDoctorToDepartment(s, name.c_str());
            }
            else
            {
                hospital.printAllDepartments();
                name = askLine("Department name to assign: ");
                hospital.getDepartmentByName(name.c_str());
                cout << "Doctor added to department " << name << endl;
                hospital.addDoctor(d);
                hospital.addDoctorToDepartment(d, name.c_str());
            }
        }
        else if (choice == 4)
        {
            std::string departmentName;
            int found = 0;
            int id;
            int vid = askInt("Enter visitor ID: ");
            if (hospital.findVisitorById(vid))
            {
                if (hospital.findVisitorById(vid)->getId() == vid) { found = 1;}
            }
            if (!found){
                std::string vname = askLine("Visitor name: ");
                id = askInt("ID (int): ");
                int birth = askInt("Birth year(YYYY): ");
                Visitor  v(vname.c_str(), id, birth, (Person::Gender)askInt("Gender (0=Male, 1=Female, 2=Unknown): "));
                hospital.addVisitor(v);
            }
            hospital.printAllDepartments();
            departmentName = askLine("Department name for visit: ");
            if (!hospital.getDepartmentByName(departmentName.c_str())) { cout << "Department not found" << endl; continue; }

            std::string purpose = askLine("Purpose of visit: test or surgery ");
            while(purpose != "test" && purpose != "surgery") {
                cout << "Invalid purpose. Please enter 'test' or 'surgery'." << endl;
                purpose = askLine("Purpose of visit: test or surgery ");
            }
            std::string date = nowDate();
            if(purpose == "surgery") {
                Surgery s(purpose.c_str(), date.c_str(), *hospital.getDepartmentByName(departmentName.c_str()), std::string(),
                    askInt("Surgery room number: "), 
                    (askInt("Is it a fast surgery? (1=Yes, 0=No): ") == 1) ? true : false);
            }

            VisitCard vc(purpose, date, *hospital.getDepartmentByName(departmentName.c_str()), std::string());
            hospital.printDepartmentMedicalStaff(departmentName.c_str());
            name = askLine("Host doctor/nurse name: ");
            printf("Host worker: %d and %d", !hospital.getDoctorByName(name.c_str()), !hospital.getNurseByName(name.c_str()));
            if (!hospital.getDoctorByName(name.c_str()) && !hospital.getNurseByName(name.c_str()))
            {
                cout << "Host doctor not found" << endl;
            }
            else
            {
                vc.setHostWorker(hospital.getDoctorByName(name.c_str()) ? hospital.getDoctorByName(name.c_str())->getName() : hospital.getNurseByName(name.c_str())->getName());
            }
            if (found)
            {
                hospital.findVisitorById(vid)->addVisitCard(vc);
                hospital.addVisitorToDepartment(*hospital.findVisitorById(vid), departmentName.c_str());
            }
            else
            {
                hospital.findVisitorById(id)->addVisitCard(vc);
                hospital.addVisitorToDepartment(*hospital.findVisitorById(id), departmentName.c_str());
            }
        }
        else if (choice == 5)
        {
            std::string is_doctor = askLine("Researcher is a doctor (1=Yes, 0=No): ");
            if (is_doctor == "1" || is_doctor == "Yes" || is_doctor == "y" || is_doctor == "Y") {
				hospital.printAllDoctors();
                name = askLine("Doctor name to promote to researcher: ");
                Doctor* doc = hospital.getDoctorByName(name.c_str());
                if (!doc) { cout << "Doctor not found" << endl; continue; }
				Researcher r(doc->getName().c_str(),doc->getId(), doc->getBirthYear(), doc->getGender());
                ResearcherDoctor rd(r, *doc);
                hospital.addResearcher(rd);
				cout << "Researcher " << name << " added" << endl;
            }
            else {
                name = askLine("Researcher name: ");
                int id = askInt("ID (int): ");
                int birth = askInt("Birth year(YYYY): ");
                Researcher r(name.c_str(), id, birth, (Person::Gender)askInt("Gender (0=Male, 1=Female, 2=Unknown): "));

                hospital.addResearcher(r);
                cout << "Researcher " << name << " added" << endl;
            }
        }
        else if (choice == 6)
        {
            hospital.printAllResearchers();
            int rid = askInt("Enter researcher ID to add article to: ");
            if (!hospital.findResearcherById(rid)) { cout << "Researcher not found" << endl; continue; }
            std::string title = askLine("Article title: ");
            std::string date = askLine("Publication date(DDMMYYYY): ");
            std::string mag = askLine("Magazine name: ");
            Article a  = Article(title.c_str(), date.c_str(), mag.c_str());
            hospital.addArticleToResearchCenter(*hospital.findResearcherById(rid), a);
            cout << "Article " << a.getTitle() << " added" << endl;
        }
        else if (choice == 7)
        {
            hospital.printAllDepartments();
            std::string dname = askLine("Department name: ");
            hospital.printDepartmentVisitors(dname.c_str());
        }
        else if (choice == 8)
        {
            hospital.printAllMedicalStaff();
        }
        else if (choice == 9)
        {
            hospital.printAllSurgens();
        }
        else if (choice == 10)
        {
            hospital.printAllResearchers();
        }
        else if (choice == 11)
        {
            int vid = askInt("Enter visitor ID: ");
            if (hospital.findVisitorById(vid))
            {
                cout << "Visitor name: " << hospital.findVisitorById(vid)->getName() << endl;
				cout << "Visits: " << hospital.findVisitorById(vid) << endl;
            }
            
        }
        else if (choice == 12)
        {
            cout << "Exiting..." << endl;
            break;
        }
        else if (choice == 13)
        {
            cout << "Testing operators:" << endl;
            // add temporary doctor/nurse via operator+= as before
            Doctor tempD("Dr. Bob", 5001, 1970, (Person::Gender)0, "General");
            hospital += tempD;
            cout << "Added doctor via operator+= to hospital (first department)." << endl;

            Nurse tempN("Nurse Dan", 6001, 1985, (Person::Gender)1, 5);
            hospital += tempN;
            cout << "Added nurse via operator+= to hospital (first department)." << endl;

            // Compare researchers safely: do not assume IDs 1 and 2 exist
            if (hospital.getNumberOfResearchers() >= 2) {
                hospital.printAllResearchers();
                int id1 = askInt("Enter first researcher ID to compare: ");
                int id2 = askInt("Enter second researcher ID to compare: ");
                Researcher* r1 = hospital.findResearcherById(id1);
                Researcher* r2 = hospital.findResearcherById(id2);
                if (!r1 || !r2) {
                    cout << "One or both researchers not found." << endl;
                }
                else {
                    cout << "Compare researchers: " << *r1 << *r2;
                    if (*r1 < *r2) cout << r1->getName() << " has fewer articles" << endl;
                    else if (*r1 > *r2) cout << r1->getName() << " has more articles" << endl;
                    else cout << "Researchers have equal number of articles" << endl;
                }
            }
            else {
                cout << "Not enough researchers to compare" << endl;
            }
            }
        else
        {
            cout << "Invalid option" << endl;
        }
    }

    //delete name;

    return 0;
}