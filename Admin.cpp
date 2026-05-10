#include <iostream>
#include "Admin.h"
#include "Validator.h"
#include "InvalidInputException.h"
#include "Filehandler.h"
#include "storage.h"
#include "text.h"
#include "errorpage.h"
#include "inputsfml.h"
#include <string>
using namespace std;

Admin::Admin():Person()
{ }
Admin::Admin(int id, const char* n, const char* pass) :Person(id,n,pass)
{
}
void Admin::menu()
{
    cout << "Admin Panel-MediCore\n";
    cout << "==============================\n";
    int choice;

    do
    {
        try
        {
            cout << "1. Add Doctor\n";
            cout << "2. Remove Doctor\n";
            cout << "3. Add Patient\n";
            cout << "4. View all Patients\n";
            cout << "5. View All Doctors\n";
            cout << "6. View All Appointments\n";
            cout << "7. View Unpaid Bills\n";
            cout << "8. Discharge Patient\n";
            cout << "9. View Security Log\n";
            cout << "10. Generate Daily Report\n";
            cout << "11. Logout\n";
            cout << "Enter your choice: ";

            if (!(cin >> choice))
            {
                cin.clear();
                cin.ignore(1000, '\n');
                throw InvalidInputException("Invalid input type");
            }


            if (!Validator::isMenuChoice(choice, 11))
            {
                throw InvalidInputException("The menu choice is invalid");
            }

            switch (choice)
            {
            case 1:
                AddDoctor();
                break;

            case 2:
                RemoveDoctor();
                break;
            case 3:
                AddPatient();
                break;
            case 4:
                ViewAllPatients();
                break;

            case 5:
                ViewAllDoctors();
                break;

            case 6:
                ViewAllAppointments();
                break;
            case 7:
                ViewUnpaidBills();
                break;
            case 8:
                DischargePatient();
                break;
            case 9:
                viewSecurityLog();
                break;
            case 10:
                GenerateDailyReport();
                break;
            case 11:
                cout << "Logging out...\n";
                return;
            }

        }
        catch (exception& e)
        {
            cout << e.what() << endl;
        }

    } while (choice != 11);
}
void Admin::display()
{
    cout << id << " |";
    for (int i = 0; name[i] != 0; i++)
    {
        cout << name[i];
    }
    cout << " | ";
    for (int i = 0; password[i] != 0; i++)
    {
        cout << password[i];
    }
    
}
void Admin::AddDoctor()
{
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Add Doctor", sf::Style::Fullscreen);
    sf::Font font;
    font.loadFromFile("C:/Windows/Fonts/arial.ttf");
    char n[50], sp[50], con[12], pa[20];
    float f;
    cout << "Enter name: ";
    std::string name = sfmlInput(window, font, "Enter Name: ", 50);
    strcpy_s(n, name.c_str());

    cout << endl << "Enter specialization: ";
    std::string spec = sfmlInput(window, font, "Enter specialization: ", 50);
    strcpy_s(sp, spec.c_str());

    cout << endl << "Enter contact(must be exactly 11 numeric digits): ";
    std::string co = sfmlInput(window, font, "Contact: ", 12);
    strcpy_s(con, co.c_str());

    if (!Validator::isContactNo(con))
    {
        showErrorWindow("Invalid contact format");
        cout << "Invalid contact format." << endl;
        return;
    }
    cout << endl << "Enter password (must be atleast of 6 characters): ";
    std::string pass = sfmlInput(window, font, "Enter password (must be atleast of 6 characters) ", 20);
    strcpy_s(pa, pass.c_str());

    if (!Validator::isPassword(pa))
    {
        showErrorWindow("Password should have\natleast 6 characters");
        cout << "Password should have atleast 6 characters" << endl;
        return;
    }
    cout << endl << "Enter consultation fee: ";
    std::string fee = sfmlInput(window, font, "Enter consultation fee ", 20);
    f = std::stof(fee);

    if (!Validator::isPositiveFloat(f))
    {
        showErrorWindow("Not a positive number");
        cout << "Not a positive number.";
        return;
    }
    int maxId = 0;
    for (int i = 0; i < doctorStorage->getSize(); i++)
    {
        if (maxId < (*doctorStorage)[i].getID())
        {
            maxId = (*doctorStorage)[i].getID();
        }
    }
    int newId;
    newId = maxId + 1;
    Doctor newDoc(newId, n, pa, sp, con, f);
    doctorStorage->add(newDoc);
    FileHandler::saveDoctors(*doctorStorage);
    cout << "Doctor added successfully. ID: " << newId << endl;
    showSuccessWindow("Doctor added successfully");
}

void Admin::AddPatient()
{
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Add Patient", sf::Style::Fullscreen);
    sf::Font font;
    font.loadFromFile("C:/Windows/Fonts/arial.ttf");

    char n[50], con[12], pa[20];
    int age;
    char g;
    float b;
    cout << "Enter name: ";
    std::string name = sfmlInput(window, font, "Enter name: ", 50);
    strcpy_s(n, name.c_str());

    cout << "Enter age: ";
    std::string a = sfmlInput(window, font, "Enter age: ", 50);
    age = std::stoi(a);

    cout << endl << "Enter contact(must be exactly 11 numeric digits): ";
    std::string co = sfmlInput(window, font, "Enter contact(must be exactly 11 numeric digits): ", 12);
    strcpy_s(con, co.c_str());

    if (!Validator::isContactNo(con))
    {
        showErrorWindow("Invalid contact format");
        cout << "Invalid contact format." << endl;
        return;
    }
    cout << endl << "Enter password (must be atleast of 6 characters): ";
    std::string pass = sfmlInput(window, font, "Enter password(must be atleast of 6 characetrs): ", 20);
    strcpy_s(pa, pass.c_str());

    if (!Validator::isPassword(pa))
    {
        showErrorWindow("Password should have atleast 6 characters");
        cout << "Password should have atleast 6 characters" << endl;
        return;
    }
    cout << endl << "Enter initial balance: ";
    std::string bal = sfmlInput(window, font, "Enter initial balance: ", 20);
    b = std::stof(bal);

    cout << "Enter Gender ";
    std::string gen = sfmlInput(window, font, "Enter Gender: ", 1);
    g = gen[0];
    int maxId = 0;
    for (int i = 0; i < patientStorage->getSize(); i++)
    {
        if (maxId < (*patientStorage)[i].getID())
        {
            maxId = (*patientStorage)[i].getID();
        }
    }
    int newId;
    newId = maxId + 1;
    Patient newpat(newId,n,pa,age,g,con,b);
    patientStorage->add(newpat);
    FileHandler::savePatients(*patientStorage);
    cout << "Patient added successfully. ID: " << newId << endl;
    showSuccessWindow("Patient added successfully. ID: " + std::to_string(newId));
}
void Admin::RemoveDoctor()
{
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Remove Doctor", sf::Style::Fullscreen);
    sf::Font font;
    font.loadFromFile("C:/Windows/Fonts/arial.ttf");
    int did;
    Doctor temp[100];
    int count = 0;
    for (int i = 0; i < doctorStorage->getSize(); i++)
    {
        temp[count] = (*doctorStorage)[i];
        count++;
        cout << (*doctorStorage)[i];
    }
    showDoctors(window, font, temp, count);
    cout << "Enter Doctor ID to remove: ";
    std::string id = sfmlInput(window, font, "Enter Doctor ID to remove: ", 20);
    did = std::stoi(id);

    if (!Validator::isId(did))
    {
        showErrorWindow("Invalid ID input");
        cout << "Invalid ID input" << endl;
        return;
    }
    bool found = false;
    for (int i = 0; i < doctorStorage->getSize(); i++)
    {
        if ((*doctorStorage)[i].getID() == did)
        {
            found = true;
            break;
        }
    }
    if (!found)
    {
        showErrorWindow("No doctor with this ID exists");
        cout << "No doctor with this ID exists" << endl;
        return;
    }
    for (int i = 0; i < appointmentStorage->getSize(); i++)
    {
        if ((*appointmentStorage)[i].getDoctorID() == did && strcmp((*appointmentStorage)[i].getStatus(), "pending")==0)
        {
            showErrorWindow("   Cannot remove doctor with\n   pending appointments.\nCancel or re-assign them first.");
            cout << "Cannot remove doctor with pending appointments. Cancel or re-assign them first." << endl;
            return;
        }
    }
    doctorStorage->remove(did);
    FileHandler::saveDoctors(*doctorStorage);
    cout << "Doctor removed." << endl;
    showSuccessWindow("Doctor removed");
}
void Admin::ViewAllPatients()
{
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "View all patient", sf::Style::Fullscreen);
    sf::Font font;
    font.loadFromFile("C:/Windows/Fonts/arial.ttf");
    Patient temp[100];
    int count = 0;
    bool found = false;
    for (int i = 0; i < patientStorage->getSize(); i++)
    {
        temp[count] = (*patientStorage)[i];
        count++;
        found = true;
        cout << (*patientStorage)[i];
    }
    if (!found)
    {
        showErrorWindow("No Record Found");
        cout << "No record found" << endl;
    }
    showPatients(window, font, temp, count);
}
void Admin::ViewAllDoctors()
{
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "View all Doctor", sf::Style::Fullscreen);
    sf::Font font;
    font.loadFromFile("C:/Windows/Fonts/arial.ttf");
    Doctor temp[100];
    int count=0;
    bool found = false;
    for (int i = 0; i < doctorStorage->getSize(); i++)
    {
        temp[count] = (*doctorStorage)[i];
        count++;
        found = true;
        cout << (*doctorStorage)[i];
    }
    if (!found)
    {
        showErrorWindow("No Record Found");
        cout << "No record found" << endl;
    }
    showDoctors(window, font, temp, count);
}
void Admin::ViewAllAppointments()
{
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "View all appointments", sf::Style::Fullscreen);
    sf::Font font;
    font.loadFromFile("C:/Windows/Fonts/arial.ttf");
    Appointment temp[100];
    int count = 0;

    for (int i = 0; i < appointmentStorage->getSize(); i++)
    {
        if (count < 100)
        {
            temp[count] = (*appointmentStorage)[i];
            count++;
        }

    }
    for (int i = 0; i < count - 1; i++)
    {
        for (int j = i + 1; j < count; j++)
        {
            int d1, m1, y1;
            int d2, m2, y2;

            sscanf_s(temp[i].getDate(), "%d-%d-%d", &d1, &m1, &y1);
            sscanf_s(temp[j].getDate(), "%d-%d-%d", &d2, &m2, &y2);

            bool swapFlag = false;

            if (y2 > y1) swapFlag = true;
            else if (y2 == y1 && m2 > m1) swapFlag = true;
            else if (y2 == y1 && m2 == m1 && d2 > d1) swapFlag = true;

            if (swapFlag)
            {
                Appointment t = temp[i];
                temp[i] = temp[j];
                temp[j] = t;
            }
        }
    }
    for (int i = 0; i < count; i++) 
    {
        Patient* p = patientStorage->findbyID(temp[i].getPatientID());
        Doctor*d = doctorStorage->findbyID(temp[i].getDoctorID());

        cout << temp[i].getID() << " | ";

        if (p != nullptr)
        {
            cout << p->getName();
        }
        else
        {
            cout << "Unknown";
        }

        cout << " | ";
        if (d != nullptr)
        {
            cout << d->getName()<<" | ";
        }
        else
        {
            cout << "Unknown";
        }

           cout <<temp[i].getDate()<<" | "<< temp[i].getTimeSlot()
            << " | "
            << temp[i].getStatus()
            << endl;
    }
    showAppointments(window, font, temp, count,*doctorStorage,*patientStorage);
}
void Admin::ViewUnpaidBills()
{
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "View unpaid bills", sf::Style::Fullscreen);
    sf::Font font;
    font.loadFromFile("C:/Windows/Fonts/arial.ttf");
    Bills temp[100];
    int count = 0;
    bool found = true;
    for (int i = 0; i < billStorage->getSize(); i++)
    {
        if (strcmp((*billStorage)[i].getStatus(), "unpaid") == 0)
        {
            Patient* p = patientStorage->findbyID((*billStorage)[i].getPatientID());
            cout << (*billStorage)[i].getID() << " | ";

            if (p != nullptr)
            {
                cout << p->getName();
            }
            else
            {
                cout << "Unknown";
            }
            cout << " | ";
            float amount=(*billStorage)[i].getAmount();
            cout << amount << " | "; 

            const char* date = (*billStorage)[i].getDate();

            int d, m, y;

            sscanf_s(date, "%d-%d-%d", &d, &m, &y);

            tm billTime = {};

            billTime.tm_mday = d;
            billTime.tm_mon = m - 1;
            billTime.tm_year = y - 1900;

            time_t bill_date = mktime(&billTime);
            time_t now = time(0);

            double seconds = difftime(now, bill_date);
            double days = seconds / (60 * 60 * 24);

            if (days >= 7)
            {
                cout << date << " [OVERDUE]";
            }
            else
            {
                cout << date;
            }        
            temp[count] = (*billStorage)[i];
            count++;
        }
        found = false;
        cout << "No unpaid bills." << endl;
    }
    if (!found)
    {
        showErrorWindow("No Unpaid Bills");
        return;
    }
    showBills(window, font, temp, count);
}
void Admin::DischargePatient()
{
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Discharge Patient", sf::Style::Fullscreen);
    sf::Font font;
    font.loadFromFile("C:/Windows/Fonts/arial.ttf");

    int pid;
    cout << "Enter patient id: ";
    std::string id = sfmlInput(window, font, "Enter patient ID: ", 20);
    pid = std::stoi(id);

    Patient* p = patientStorage->findbyID(pid);
    if (p == nullptr)
    {
        showErrorWindow("Patient Not Found");
        cout << "Patient not found." << endl;
        return;
    }
    for (int i = 0; i < billStorage->getSize(); i++)
    {
        if ((*billStorage)[i].getPatientID() == pid && strcmp((*billStorage)[i].getStatus(), "unpaid") == 0)
        {
            showErrorWindow("Can not discharge\npatient with unpaid bills");
            cout << "Can not discharge patient with unpaid bills" << endl;
            return;
        }
    }
    for (int i = 0; i < appointmentStorage->getSize(); i++)
    {
        if ((*appointmentStorage)[i].getPatientID() == pid && strcmp((*appointmentStorage)[i].getStatus(), "pending") == 0)
        {
            showErrorWindow("Can not discharge patient\nwith pending appointments");
            cout << "Can not discharge patient with pending appointments" << endl;
            return;
        }
    }
    ofstream fout("discharged.txt", ios::app);

    if (!fout)
    {
        cout << "Unable to open discharged.txt" << endl;
        return;
    }
   
    fout << *p << "\n";
    for (int i = 0; i < appointmentStorage->getSize(); i++)
    {
        if ((*appointmentStorage)[i].getPatientID() == pid)
        {
            fout << (*appointmentStorage)[i] << "\n";
        }
    }
    for (int i = 0; i < prescriptionStorage->getSize(); i++)
    {
        if ((*prescriptionStorage)[i].getPatientId() == pid)
        {
            fout << (*prescriptionStorage)[i] << "\n";
        }
    }
    for (int i = 0; i < billStorage->getSize(); i++)
    {
        if ((*billStorage)[i].getPatientID() == pid)
        {
            fout << (*billStorage)[i] << "\n";
        }
    }
    for (int i = 0; i < appointmentStorage->getSize();)
    {
        if ((*appointmentStorage)[i].getPatientID() == pid)
        {
            int aid = (*appointmentStorage)[i].getID();
            appointmentStorage->remove(aid);
        }
        else
        {
            i++;
        }
       
    }    
    for (int i = 0; i < prescriptionStorage->getSize();)
    {
        if ((*prescriptionStorage)[i].getPatientId() == pid)
        {
            int prid = (*prescriptionStorage)[i].getID();
            prescriptionStorage->remove(prid);
        }
        else
        {
            i++;
        }

    }
    for (int i = 0; i < billStorage->getSize(); )
    {
        if ((*billStorage)[i].getPatientID() == pid)
        {
            int bid = (*billStorage)[i].getID();
            billStorage->remove(bid);
        }
        else
        {
            i++;
        }
    }
    patientStorage->remove(pid);
    FileHandler::saveAppointments(*appointmentStorage);
    FileHandler::savePrescriptions(*prescriptionStorage);
    FileHandler::savePatients(*patientStorage);
    FileHandler::saveBills(*billStorage);
    fout.close();
    cout << "Patient discharged." << endl;
    showSuccessWindow("Patient discharged");
}
void Admin::viewSecurityLog()    //not working
{
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Security log", sf::Style::Fullscreen);
    sf::Font font;
    font.loadFromFile("C:/Windows/Fonts/arial.ttf");
    sf::Texture blurr;
    blurr.loadFromFile("imageblurr.png");

    sf::Sprite bgSprite;
    bgSprite.setTexture(blurr);

    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    sf::Vector2u texSize = blurr.getSize();

    bgSprite.setScale(
        (float)desktop.width / texSize.x,
        (float)desktop.height / texSize.y
    );

    ifstream fin("security_log.txt");

    if (!fin)
    {
        showErrorWindow("No security events logged");
        cout << "No security events logged." << endl;
        return;
    }

    bool empty = true;
    char logs[100][200];
    int count = 0;

    char line[200];

    while (fin.getline(line, 200))
    {
        empty = false;
        strcpy_s(logs[count], line);
        count++;
    }

    if (empty)
    {
        showErrorWindow("No security events logged");
        cout << "No security events logged." << endl;
    }
    sf::Text texts;
    texts.setFont(font);
    texts.setString("Security logs:");
    texts.setCharacterSize(30);
    texts.setFillColor(sf::Color::Black);
    texts.setPosition(100, 150);
    texts.setStyle(sf::Text::Bold);
    fin.close();
    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed &&
                event.key.code == sf::Keyboard::Enter)
            {
                window.close();
            }

        }

        window.clear(sf::Color::Black);
        window.draw(bgSprite);
        window.draw(texts);
        float y = 200;

        for (int i = 0; i < count; i++)
        {
            sf::Text text;
            text.setFont(font);
            text.setString(logs[i]);
            text.setCharacterSize(26);
            text.setFillColor(sf::Color::White);
            text.setPosition(100, y);

            y += 35;

            window.draw(text);
        }

        window.display();
    }
}
void Admin::GenerateDailyReport()
{
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Daily Report", sf::Style::Fullscreen);
    sf::Font font;
    font.loadFromFile("C:/Windows/Fonts/arial.ttf");
    time_t now = time(0);
    tm localTime;
    localtime_s(&localTime, &now);

    char today[11];
    strftime(today, 11, "%d-%m-%Y", &localTime);

    
    int total = 0, pending = 0, completed = 0, noshow = 0, cancelled = 0;
    for (int i = 0; i < appointmentStorage->getSize(); i++)
    {
        Appointment a = (*appointmentStorage)[i];
        if (strcmp(a.getDate(), today) == 0)
        {
            total++;

            if (strcmp(a.getStatus(), "pending") == 0)
                pending++;

            else if (strcmp(a.getStatus(), "completed") == 0)
                completed++;

            else if (strcmp(a.getStatus(), "no-show") == 0)
                noshow++;

            else if (strcmp(a.getStatus(), "cancelled") == 0)
                cancelled++;
        }
    }

    cout << "\n===== TODAY'S APPOINTMENT REPORT =====\n";
    cout << "Total appointments today: " << total << endl;
    cout << "(Pending: " << pending
        << " Completed: " << completed
        << " No-show: " << noshow
        << " Cancelled: " << cancelled << ")\n";


   
    float revenue = 0;

    for (int i = 0; i < billStorage->getSize(); i++)
    {
        Bills b = (*billStorage)[i];

        if (strcmp(b.getDate(), today) == 0 &&
            strcmp(b.getStatus(), "paid") == 0)
        {
            revenue += b.getAmount();
        }
    }

    cout << "\nRevenue collected today: PKR " << revenue << endl;

    char unpaidText[50][200];
    int unpaidCount = 0;

   
    cout << "\nPatients with outstanding unpaid bills:\n";

    for (int i = 0; i < billStorage->getSize(); i++)
    {
        Bills b = (*billStorage)[i];

        if (strcmp(b.getStatus(), "unpaid") == 0)
        {
            Patient* p = patientStorage->findbyID(b.getPatientID());

            if (p != nullptr)
            {
                cout << p->getName() << " | " << b.getAmount() << endl;
                sprintf_s(
                    unpaidText[unpaidCount],
                    "%s | %.2f PKR",
                    p->getName(),
                    b.getAmount()
                );
                unpaidCount++;
            }
        }
    }

    char doctorSummary[50][200];
    int doctorCount = 0;

   
    cout << "\nDoctor-wise summary for today:\n";

    for (int i = 0; i < doctorStorage->getSize(); i++)
    {
        Doctor d = (*doctorStorage)[i];

        int docCompleted = 0, docPending = 0, docNoShow = 0;

        for (int j = 0; j < appointmentStorage->getSize(); j++)
        {
            Appointment a = (*appointmentStorage)[j];

            if (a.getDoctorID() == d.getID() &&
                strcmp(a.getDate(), today) == 0)
            {
                if (strcmp(a.getStatus(), "completed") == 0)
                    docCompleted++;

                else if (strcmp(a.getStatus(), "pending") == 0)
                    docPending++;

                else if (strcmp(a.getStatus(), "no-show") == 0)
                    docNoShow++;
            }
        }

        cout << d.getName()
            << " | Completed: " << docCompleted
            << " | Pending: " << docPending
            << " | No-show: " << docNoShow
            << endl;
        sprintf_s(
            doctorSummary[doctorCount],
            "%s | Completed:%d Pending:%d No-show:%d",
            d.getName(),
            docCompleted,
            docPending,
            docNoShow
        );
        doctorCount++;

    }
    showDailyReportUI(window,font,
        today,
        total,
        pending,
        completed,
        noshow,
        cancelled,
        revenue,
        unpaidText,
        unpaidCount,
        doctorSummary,
        doctorCount
    );
}
char* Admin:: getPassword()
{
    return password;
}
