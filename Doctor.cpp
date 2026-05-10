#include <iostream>
#include <ctime>
#include "Doctor.h"
#include "Validator.h"
#include "Patient.h"
#include "InvalidInputException.h"
#include "Filehandler.h"
#include "errorpage.h"
#include "inputsfml.h"
#include "text.h"
using namespace std;
Doctor::Doctor()
    : Person()
{
    specialization[0] = '\0';
    contact[0] = '\0';
    fee = 0;
}
Doctor::Doctor(int id, const char* name, const char* password, const char* s, const char* c, float f)
    : Person(id, name, password)
{
    int j = 0;
    while (s[j] != '\0')
    {
        this->specialization[j] = s[j];
        j++;
    }
    specialization[j] = '\0';
    this->fee = f;

    int i = 0;
    while (c[i] != '\0')
    {
        this->contact[i] = c[i];
        i++;
    }
    this->contact[i] = '\0';
}

void Doctor::menu()
{
    cout << "Welcome,Dr ";
    for (int i = 0; name[i] != '\0'; i++)
    {
        cout << name[i];
    }

    cout << " Specialization: ";
    int j = 0;
    while (specialization[j] != '\0')
    {
        cout << specialization[j];
        j++;
    }
    cout << endl<<"==============================\n";
    int choice;

    do
    {
        try
        {
            cout << "\n===== Doctor Menu =====\n";
            cout << "1. View Today's Appointment\n";
            cout << "2. Mark Appointment Complete\n";
            cout << "3. Mark Appointment No-show\n";
            cout << "4. Write Prescriptions\n";
            cout << "5. View Patient Medical History\n";
            cout << "6. Logout\n";
            cout << "Enter your choice: ";

            if (!(cin >> choice))
            {
                cin.clear();
                cin.ignore(1000, '\n');
                throw InvalidInputException("Invalid input type");
            }

            if (!Validator::isMenuChoice(choice, 6))
            {
                throw InvalidInputException("The menu choice is invalid");
            }

            switch (choice)
            {
            case 1:
                displayTodayAppointment();
                break;

            case 2:
                markAppointmentComplete();
                break;

            case 3:
                markAppointmentNoshow();
                break;

            case 4:
                writePrescription();
                break;

            case 5:
                displayPatientHistory();
                break;

            case 6:
                cout << "Logging out...\n";
                return;
            }

        }
        catch (exception& e)
        {
            cout << e.what() << endl;
        }

    } while (choice != 6);
}
void Doctor::display()
{
    cout << id << " |";
    for (int i = 0; name[i] != 0; i++)
    {
        cout << name[i];
    }
    cout << " | ";
    for (int i = 0; specialization[i] != 0; i++)
    {
        cout << specialization[i];
    }
    cout << "| ";
    for (int i = 0; contact[i] != 0; i++)
    {
        cout << contact[i];
    }
    cout << "| " << fee <<endl;
}

bool Doctor::operator==(const Doctor& other) const
{
    if (this->id == other.id)
    {
        return true;
    }
    return false;
}
int Doctor::getFee()
{
    return fee;
}
void Doctor::displayTodayAppointment()
{
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Display Appointments", sf::Style::Fullscreen);
    sf::Font font;
    font.loadFromFile("C:/Windows/Fonts/arial.ttf");
    Appointment temp[100];
    int count = 0;
    time_t now = time(0);

    tm localTime;
    localtime_s(&localTime, &now);

    char today[11];

    strftime(today, 11, "%d-%m-%Y", &localTime);
    for (int i = 0; i < appointmentStorage->getSize(); i++)
    {
        if ((*appointmentStorage)[i].getDoctorID() == this->id && strcmp((*appointmentStorage)[i].getDate(), today) == 0) //time thinge
        {
            temp[count] = (*appointmentStorage)[i];
            count++;
        }
    }

    if (count == 0)
    {
        showErrorWindow("No appointments found");
        cout << "No appointments found" << endl;
        return;
    }

    for (int i = 0; i < count - 1; i++)
    {
        for (int j = i + 1; j < count; j++)
        {
            if (strcmp(temp[i].getTimeSlot(),
                temp[j].getTimeSlot()) > 0)
            {
                Appointment t = temp[i];
                temp[i] = temp[j];
                temp[j] = t;
            }
        }
    }
    for (int i = 0; i < count; i++) //<count, chcek it
    {
        Patient* p = patientStorage->findbyID(temp[i].getPatientID());

        cout << temp[i].getID() << " | ";

        if (p != nullptr)
        {
            cout << p->getName();
        }
        else
        {
            cout << "Unknown";
        }

        cout << " | "
            << temp[i].getTimeSlot()
            << " | "
            << temp[i].getStatus()
            << endl;
    }
    showAppointments(window, font, temp, count,*doctorStorage,*patientStorage);

}
void Doctor:: markAppointmentComplete()
{
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Display Appointments", sf::Style::Fullscreen);
    sf::Font font;
    font.loadFromFile("C:/Windows/Fonts/arial.ttf");
    time_t now = time(0);

    tm localTime;
    localtime_s(&localTime, &now);

    char today[11];
    Appointment temp[100];
    int count = 0;
    strftime(today, 11, "%d-%m-%Y", &localTime);
    int aid;
    bool found = false;
    for (int i = 0; i < appointmentStorage->getSize(); i++)
    {
        if ((*appointmentStorage)[i].getDoctorID() == this->id && strcmp((*appointmentStorage)[i].getStatus(), "pending") == 0 && strcmp((*appointmentStorage)[i].getDate(), today) == 0)
        {
            temp[count] = (*appointmentStorage)[i];
            count++;
            cout << (*appointmentStorage)[i];
            found = true;
        }
    }
    if (!found)
    {
        showErrorWindow("No appointment found");
        cout << "No appointment found" << endl;
        return;
    }
    showAppointments(window, font, temp, count, *doctorStorage, *patientStorage);
    cout << "Enter appointment ID: ";
    std::string app = sfmlInput(window, font, "Enter appointment ID to mark as complete:", 10);
    aid = std::stoi(app);
    if (!Validator::isId(aid))
    {
        showErrorWindow("Invalid ID");
        cout << "Invalid id" << endl;
        return;
    }
    int index = -1;
    for (int i = 0; i < appointmentStorage->getSize(); i++)
    {
        if ((*appointmentStorage)[i].getID() == aid &&
            (*appointmentStorage)[i].getDoctorID() == this->id)
        {
            index = i;
            break;
        }
    }
    if (index==-1)
    {
        showErrorWindow("ID is not correct");
        cout << "ID is not correct. " << endl;
        return;
    }
    (*appointmentStorage)[index].setStatus("completed");
    FileHandler::saveAppointments(*appointmentStorage);
    showSuccessWindow("Appointment marked as complete.");
    cout << "Appointment marked as completed." << endl;
}
void Doctor::markAppointmentNoshow()
{
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Display Appointments", sf::Style::Fullscreen);
    sf::Font font;
    font.loadFromFile("C:/Windows/Fonts/arial.ttf");
    time_t now = time(0);

    tm localTime;
    localtime_s(&localTime, &now);

    char today[11];

    strftime(today, 11, "%d-%m-%Y", &localTime);
    int aid;
    bool found = false;
    Appointment temp[100];
    int count = 0;
    for (int i = 0; i < appointmentStorage->getSize(); i++)
    {
        if ((*appointmentStorage)[i].getDoctorID() == this->id && strcmp((*appointmentStorage)[i].getStatus() , "pending")==0 && strcmp((*appointmentStorage)[i].getDate(), today) == 0)
        {
            temp[count] = (*appointmentStorage)[i];
            count++;
            cout << (*appointmentStorage)[i];
            found = true;
        }
    }
    if (!found)
    {
        showErrorWindow("No appointment found");
        cout << "No appointment found" << endl;
        return;
    }
    showAppointments(window, font, temp, count, *doctorStorage, *patientStorage);
    cout << "Enter appointment ID: ";
    std::string app = sfmlInput(window, font, "Enter appointment ID", 10);
    aid = std::stoi(app);
    if (!Validator::isId(aid))
    {
        showErrorWindow("Invalid ID");
        cout << "Invalid id" << endl;
        return;
    }
    int index = -1;
    for (int i = 0; i < appointmentStorage->getSize(); i++)
    {
        if ((*appointmentStorage)[i].getDoctorID() == this->id && (*appointmentStorage)[i].getID() == aid && strcmp((*appointmentStorage)[i].getStatus(), "pending") == 0 && strcmp((*appointmentStorage)[i].getDate(), today) == 0)
        {
            index = i;
            break;
        }
    }
    if (index == -1)
    {
        showErrorWindow("ID is not correct");
        cout << "ID is not correct. " << endl;
        return;
    }
    (*appointmentStorage)[index].setStatus("no-show");
    for (int i = 0; i < billStorage->getSize(); i++)
    {
        if ((*billStorage)[i].getAppointmentID() == aid)
        {
            (*billStorage)[i].setStatus("cancelled");
            break;
        }
    }
    FileHandler::saveBills(*billStorage);
    FileHandler::saveAppointments(*appointmentStorage);
    cout << "Appointment marked as no show." << endl;
    showSuccessWindow("Appointment marked as no show.");
}
void Doctor::writePrescription()
{
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Display Appointments", sf::Style::Fullscreen);
    sf::Font font;
    font.loadFromFile("C:/Windows/Fonts/arial.ttf");
    char notes[300];
    char medicines[500];
    int aid;
    cout << "Enter appointment id: ";
    std::string app = sfmlInput(window, font, "Enter appointment ID", 10);
    aid = std::stoi(app);   
    bool exists = false;
    try
    {
        if (!Validator::isId(aid))
        {
            throw InvalidInputException("Not a correct id");
        }
    }
    catch (InvalidInputException& e)
    {
        showErrorWindow(e.what());
        cout << e.what() << endl;
        return;
    }
    for (int i = 0; i < appointmentStorage->getSize(); i++)
    {
        if ((*appointmentStorage)[i].getID() == aid && (*appointmentStorage)[i].getDoctorID() == this->id && strcmp((*appointmentStorage)[i].getStatus(), "completed")==0)
        {
            exists = true;
            break;
        }
    }
    if (!exists)
    {
        showErrorWindow("Invalid ID.");
        cout << "invalid id" << endl;
        return;
    }
    for (int i = 0; i < prescriptionStorage->getSize(); i++)
    {
        if ((*prescriptionStorage)[i].getAppointmentId() == aid)
        {
            showErrorWindow("Prescription already\n written for this appointment.");
            cout << "Prescription already written for this appointment." << endl;
            return;
        }
    }
    cout << "Enter Medicines (format: MedicineName Dosage; e.g.Paracetamol 500mg; Amoxicillin 250mg): " << endl;
    std::string med = sfmlInput(window, font, "Enter Medicines (format: MedicineName Dosage; e.g.Paracetamol 500mg):", 500);
    strcpy_s(medicines, med.c_str());
    cout << "Enter notes: " << endl;
    std::string note = sfmlInput(window, font, "Enter Notes:", 300);
    strcpy_s(notes, note.c_str());
    int maxId = 0;

    for (int i = 0; i < prescriptionStorage->getSize(); i++)
    {
        if ((*prescriptionStorage)[i].getID() > maxId)
        {
            maxId = (*prescriptionStorage)[i].getID();
        }
    }
    int newId = maxId + 1;
    time_t now = time(0);

    tm localTime;
    localtime_s(&localTime, &now);

    char today[11];

    strftime(today, 11, "%d-%m-%Y", &localTime);
    Appointment* appo = appointmentStorage->findbyID(aid);
    if (!appo)
    {
        showErrorWindow("Appointment not found");
        cout << "Appointment not found" << endl;
        return;
    }
    int paid = appo->getPatientID();
    Prescription newpres(newId,id,aid,paid,medicines,notes,this->getName(),today);
    prescriptionStorage->add(newpres);
    FileHandler::savePrescriptions(*prescriptionStorage);
    cout << "Prescription saved" << endl;
    showSuccessWindow("Prescription saved!");
}
void Doctor::displayPatientHistory()
{
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Display Patient History", sf::Style::Fullscreen);
    sf::Font font;
    font.loadFromFile("C:/Windows/Fonts/arial.ttf");
    int pid;
    cout << "Enter Patient ID: ";
    std::string pa = sfmlInput(window, font, "Enter patient ID:", 10);
    pid = std::stoi(pa);
    if (!Validator::isId(pid))
    {
        showErrorWindow("Not a valid ID");
        cout << "Not a valid id." << endl;
        return;
    }
    bool patientFound = false;

    for (int i = 0; i < patientStorage->getSize(); i++)
    {
        if ((*patientStorage)[i].getID() == pid)
        {
            patientFound = true;
            break;
        }
    }

    if (!patientFound)
    {
        showErrorWindow("Patient not found");
        cout << "Patient not found." << endl;
        return;
    }
    bool hasCompletedAppointment = false;

    for (int i = 0; i < appointmentStorage->getSize(); i++)
    {
        Appointment a = (*appointmentStorage)[i];

        if (a.getDoctorID() == this->getID() &&
            a.getPatientID() == pid &&
           strcmp(a.getStatus(),"completed")==0)
        {
            hasCompletedAppointment = true;
            break;
        }
    }

    if (!hasCompletedAppointment)
    {
        showErrorWindow("      Access denied.\n No completed appointment\n with this patient.");
        cout << "Access denied. No completed appointment with this patient." << endl;
        return;
    }
    Prescription temp[100];
    int count = 0;
    for (int i = 0; i < prescriptionStorage->getSize(); i++)
    {
        Prescription p = (*prescriptionStorage)[i];

        if (p.getDoctorId() == this->getID() &&
            p.getPatientId() == pid)
        {
            if (count < 100)
            { 
                temp[count] = p;
                count++;
            }
            else
            {
                showErrorWindow("Warning\nprescription limit reached (100).");
                cout << "Warning: prescription limit reached (100)." << endl;
                break;
            }
        }
    }
    if (count == 0)
    {
        showErrorWindow("No Record Found");
        cout << "no record found" << endl;
        return;
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
                Prescription t = temp[i];
                temp[i] = temp[j];
                temp[j] = t;
            }
        }
    }
    for (int i = 0; i < count; i++)
    {
        cout << temp[i] << endl;
    }
    showPrescriptions(window, font, temp, count);
}

int Doctor:: getID()
{
    return id;
}
const char* Doctor::getSpecialization()const
{
    return specialization;
}
std::istream& operator>>(std::istream& in, Doctor& d)
{
    char pipe;

    in >> d.id >> pipe;                      

    in.getline(d.name, 50, '|');           

    in.getline(d.specialization, 50, '|');  

    in.getline(d.password, 20, '|');        

    in.getline(d.contact, 12, '|');         

    in >> d.fee;                            

    in.ignore(1000,'\n'); 
    return in;
}
std::ostream& operator<<(std::ostream& out, const Doctor& d)
{
    out << d.id << "|";
    for (int i = 0; d.name[i] != 0; i++)
    {
        out << d.name[i];
    }
    out << "|";
    for (int i = 0; d.specialization[i] != 0; i++)
    {
        out << d.specialization[i];
    }
    out << "|";
    for (int i = 0; d.password[i] != 0; i++)
    {
        out << d.password[i];
    }
    out << "|";
    for (int i = 0; d.contact[i] != '\0'; i++)
    {
        out << d.contact[i];
    }
    out << "|" << d.fee << endl;
    return out;
}

char* Doctor::getPassword()
{
    return password;
}
char* Doctor::getNumber()
{
    return contact;
}
