#include <iostream>
#include <string>
#include "Patient.h"
#include "Doctor.h"
#include "Validator.h"
#include "InvalidInputException.h"
#include "InsufficientFundsException.h"
#include "storage.h"
#include "Appointment.h"
#include "SlotunavailableException.h"
#include <fstream>
#include "Filehandler.h"
#include "Bills.h"
#include <SFML/Graphics.hpp>
#include "inputsfml.h"
#include "errorpage.h"
#include "text.h"
using namespace std;

Patient::Patient()
    : Person()
{
    age = 0;
    gender = ' ';
    contact[0] = '\0';
    balance = 0;
    countofUnpaidBills = 0;
}
Patient::Patient(int id, const char* name, const char* password,
    int age, char gender, const char* contact, float balance)
    : Person(id, name, password)  
{
    this->age = age;
    this->gender = gender;

    int i = 0;
    while (contact[i] != '\0')
    {
        this->contact[i] = contact[i];
        i++;
    }
    this->contact[i] = '\0';

    this->balance = balance;
    this->countofUnpaidBills = 0;
}
bool Patient::isloggedout()
{
    return log;
}
void Patient::display()
{
    cout << id << "|";
    for (int i = 0; name[i] != 0; i++)
    {
        cout << name[i];
    }
    cout << " |" << age << " |" << gender << " |";
    for (int i = 0; contact[i] != '\0'; i++)
    {
        cout << contact[i];
    }
    cout << " |" << balance << " |" << countofUnpaidBills << endl;
}

void Patient::operator+=(float amount) 
{
    if (Validator::isPositiveFloat(amount))
    {
        balance = balance + amount;
    }
    else
    {
        throw InvalidInputException("The amount is not positive float.");
    }
}
void Patient::operator-=(float amount)
{
    if (balance >= amount&& Validator::isPositiveFloat(amount))
    {
        balance = balance - amount;
    }
    else if (!Validator::isPositiveFloat(amount))
    {
        throw InvalidInputException("The amount is not a positive float.");
    }
    else
    {
        throw InsufficientFundsException();
    }

}
bool Patient::operator==(const Patient& other) const
{
    if (this->id == other.id)
    {
        return true;
    }
    return false;
}
std::ostream& operator<<(std::ostream& out, const Patient& p)
{
    out << p.id << "|";
    
        out << p.name;

    out << "|" << p.age << "|" << p.gender << "|";
   
    out << p.contact;
    out << "|" << p.password;
    out << "|" << p.balance << "|" << p.countofUnpaidBills << endl;
    return out;
}
std::istream& operator>>(std::istream& in, Patient& p)
{
    char pipe;

    in >> p.id >> pipe;                     

    in.getline(p.name, 50, '|');            

    in >> p.age >> pipe;

    in >> p.gender >> pipe;
    in.getline(p.contact, 12, '|');         
    in.getline(p.password, 20, '|');         

    in >> p.balance>>pipe;                            
    in >> p.countofUnpaidBills;

    return in;
}
int Patient::getID()
{
    return id;
}
void Patient::bookAppointment()
{
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Book Appointment", sf::Style::Fullscreen);
    sf::Font font;
    font.loadFromFile("C:/Windows/Fonts/arial.ttf");
    bool found = false;
    Doctor temp[100];
    int dcount = 0;
    int id;
    std::string spec = sfmlInput(window, font, "Enter specialisation:");
    for (int i = 0; i < doctorStorage->getSize(); i++)
    {
        if (Validator::isEqualIgnoreCase((*doctorStorage)[i].getSpecialization(), spec.c_str()))
        {
            cout << (*doctorStorage)[i] << endl;
            temp[dcount] = (*doctorStorage)[i];
            dcount++;
            found = true;
        }
    }
    if (!found)
    {
        cout << "No doctor found with this specialization" << endl;
        showErrorWindow("No doctor found with this specialization");
        return;
    }
    else
    {
        showDoctors(window, font, temp, dcount);
    }

    std::string ID = sfmlInput(window, font, "Enter Doctor id: ");
    id = std::stoi(ID);
    if (!Validator::isId(id))
    {
        cout << "Invalid id format" << endl;
        showErrorWindow("Invalid id format");
        return;
    }
    dcount = 0;
    Doctor* doc = doctorStorage->findbyID(id);
    if (!doc)
    {
        showErrorWindow("Doctor not found");
        cout << "Doctor not found" << endl;
        return;
    }
    std::string date = sfmlInput(window, font, "Enter date(DD-MM-YYYY):",10);

    int attempt = 0;
    while (attempt < 3)
    {
        if (Validator::isDate(date.c_str()))
            break;
        showErrorWindow("Invalid format. Re-enter.");
        date = sfmlInput(window, font, "Enter date(DD-MM-YYYY):", 10);
        attempt++;
    }

    if (attempt == 3)
    {
        showErrorWindow("Too many invalid attempts. Returning to menu.");
        cout << "Too many invalid attempts. Returning to menu.\n";
        return;
    }
    cout << "The available slots for the doctor are: " << endl;
    string slots[8] = {
        "09:00","10:00","11:00","12:00",
        "13:00","14:00","15:00","16:00"
    };
    string tslot[8];
    int tcount = 0;
    for (int i = 0; i < 8; i++)
    {
        bool exists = false;
        for (int j = 0; j < appointmentStorage->getSize(); j++)
        {
            if ((*appointmentStorage)[j].getDoctorID() == id && strcmp((*appointmentStorage)[j].getDate(), date.c_str()) == 0 && (*appointmentStorage)[j].getTimeSlot() == slots[i] && (*appointmentStorage)[j].getStatus() != "cancelled")
            {
                exists = true;
                break;
            }
        }
        if (!exists)
        {
            tslot[tcount] = slots[i];
            tcount++;
            cout << slots[i] << " ";
        }
    }
    bool isSlotValid = false;
    std::string slot;
   
    while (!isSlotValid)
    {
        try
        {
            slot=displaySlotsSFML(tslot, tcount);

            if (!Validator::isTimeslot(slot.c_str()))
            {
                throw InvalidInputException("Invalid time slot");
            }
            for (int j = 0; j < appointmentStorage->getSize(); j++)
            {
                if ((*appointmentStorage)[j].getDoctorID() == id && strcmp((*appointmentStorage)[j].getDate(), date.c_str()) == 0 && strcmp ((* appointmentStorage)[j].getTimeSlot(), slot.c_str())==0  && (*appointmentStorage)[j].getStatus() != "cancelled")
                {
                    throw SlotUnavailableException();
                }
            }
            isSlotValid = true;
        }
        catch (InvalidInputException& e)
        {
            showErrorWindow(e.what());
            cout << e.what() << endl;
        }
        catch (SlotUnavailableException& e)
        {
            showErrorWindow(std::string(e.what()) + "\nAvailable slots are:");
            cout << e.what() << endl;

            cout << "Available slots are:\n";
            string tslot[8];
            int tcount = 0;
            for (int i = 0; i < 8; i++)
            {
                bool exists = false;

                for (int j = 0; j < appointmentStorage->getSize(); j++)
                {
                    if ((*appointmentStorage)[j].getDoctorID() == id &&
                        strcmp((*appointmentStorage)[j].getDate(), date.c_str()) == 0 &&
                        (*appointmentStorage)[j].getTimeSlot() == slots[i] &&
                        (*appointmentStorage)[j].getStatus() != "cancelled")
                    {
                        exists = true;
                        break;
                    }
                }

                if (!exists)
                {
                    tslot[tcount] = slots[i];
                    tcount++;
                    cout << slots[i] << " ";
                }
            }

            cout << endl;
        }
    }
    try
    {
        if (balance < doc->getFee())
        {
            throw InsufficientFundsException();
        }
    }
    catch (InsufficientFundsException& e)
    {
        showErrorWindow(e.what());
        cout << e.what() << endl;
        return;
    }
    float DocFee = doc->getFee();
    *this -= DocFee;
    int maxId = 0;

    for (int i = 0; i < appointmentStorage->getSize(); i++)
    {
        if ((*appointmentStorage)[i].getID() > maxId)
        {
            maxId = (*appointmentStorage)[i].getID();
        }
    }

    int newId = maxId + 1;
    int maxbId = 0;

    for (int i = 0; i < billStorage->getSize(); i++)   
    {
        if ((*billStorage)[i].getID() > maxbId)
            maxbId = (*billStorage)[i].getID();
    }

    int newbId = maxbId + 1;

    Appointment newApp(newId, this->getID(), doc->getID(),
        date.c_str(), slot.c_str(), "pending");

    appointmentStorage->add(newApp);
    Bills b(newbId, newId, id, DocFee, "paid", date.c_str());
    billStorage->add(b);
    FileHandler::saveBills(*billStorage);
    FileHandler::savePatients(*patientStorage);
    FileHandler::saveAppointments(*appointmentStorage);
    cout << "Appointment has been booked. ID: "<<newId << endl;
    showSuccessWindow("Appointment has been booked. ID: " + std::to_string(newId));
}

void Patient::cancelAppointment()
{
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Cancel Appointment", sf::Style::Fullscreen);
    sf::Font font;
    font.loadFromFile("C:/Windows/Fonts/arial.ttf");
    bool found = false;
    int aid;
    bool belongs = false;
    Appointment temp[100];
    int acount = 0;
    for (int i = 0; i < appointmentStorage->getSize(); i++)
    {
        if ((*appointmentStorage)[i].getPatientID() == this->getID() && strcmp((*appointmentStorage)[i].getStatus(), "pending") == 0)
        {
            cout << (*appointmentStorage)[i];
            temp[acount] = (*appointmentStorage)[i];
            acount++;
            found = true;
        }
    }
    if (!found)
    {
        showErrorWindow("You have no pending appointments");
        cout << "You have no pending appointments" << endl;
        return;
    }
    showAppointments(window, font,temp, acount,*doctorStorage,*patientStorage);
    std::string ID = sfmlInput(window,font,"Enter appointment ID to cancel:",50);
    aid = std::stoi(ID);
    cout << "Enter appointment ID to cancel: ";
    int index = -1;
    for (int i = 0; i < appointmentStorage->getSize(); i++)
    {
        if ((*appointmentStorage)[i].getID() == aid && (*appointmentStorage)[i].getPatientID() == this->getID() && strcmp((*appointmentStorage)[i].getStatus(), "pending") == 0)
        {
            belongs = true;
            index = i;
            break;
        }
    }
    try
    {
        if (!belongs)
        {
            throw InvalidInputException("Invalid appointment id");
        }
    }
    catch (InvalidInputException& e)
    {
        showErrorWindow(e.what());
        cout << e.what() << endl;
        return;
    }
    if (belongs)
    {
        int did = (*appointmentStorage)[index].getDoctorID();
        Doctor* d = doctorStorage->findbyID(did);
        if (d == nullptr)
        {
            showErrorWindow("Doctor not found");
            cout << "Doctor not found." << endl;
            return;
        }
        double fee = d->getFee();
        *this += fee;
        (*appointmentStorage)[index].setStatus("cancelled");
        FileHandler::saveAppointments(*appointmentStorage);
        FileHandler::savePatients(*patientStorage);
        cout << "Appointment cancelled" << endl;
        showSuccessWindow("Appointment canceled\n    PKR: " + std::to_string(d->getFee()) + " \n    refunded to your balance");
        cout << "PKR. " << d->getFee() << " refunded to your balance." << endl;
    }
}

void Patient::displayAppointments() const
{
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Display Appointment", sf::Style::Fullscreen);
    sf::Font font;
    font.loadFromFile("C:/Windows/Fonts/arial.ttf");
    Appointment temp[100];
    int count = 0;

    for (int i = 0; i < appointmentStorage->getSize(); i++)
    {
        if ((*appointmentStorage)[i].getPatientID() == this->id)
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
            int d1, m1, y1;
            int d2, m2, y2;

            sscanf_s(temp[i].getDate(), "%d-%d-%d", &d1, &m1, &y1);
            sscanf_s(temp[j].getDate(), "%d-%d-%d", &d2, &m2, &y2);

            bool swapFlag = false;

            if (y2 < y1) swapFlag = true;
            else if (y2 == y1 && m2 < m1) swapFlag = true;
            else if (y2 == y1 && m2 == m1 && d2 < d1) swapFlag = true;

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
        cout << temp[i] << endl;
    }
    showAppointments(window, font, temp, count, *doctorStorage, *patientStorage);

}
void Patient::displayMedicalRecords() const
{
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Display Medical Record", sf::Style::Fullscreen);
    sf::Font font;
    font.loadFromFile("C:/Windows/Fonts/arial.ttf");
    Prescription temp[100];
    int count = 0;

    for (int i = 0; i < prescriptionStorage->getSize(); i++)
    {
        if ((*prescriptionStorage)[i].getPatientId() == this->id)
        {
            temp[count] = (*prescriptionStorage)[i];
            count++;
        }
    }

    if (count == 0)
    {
        showErrorWindow("No medical records found.");
        cout << "No medical records found" << endl;
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
        bool alreadyPrinted = false;

        for (int k = 0; k < i; k++)
        {
            if (temp[k].getAppointmentId() == temp[i].getAppointmentId())
            {
                alreadyPrinted = true;
                break;
            }
        }

        if (!alreadyPrinted)
        {
            cout << "\n=================================\n";
            cout << "Appointment ID: " << temp[i].getAppointmentId() << endl;
            cout << "Date: " << temp[i].getDate() << endl;
            cout << "Doctor: " << temp[i].getDrname() << endl;
            cout << "---------------------------------\n";

            for (int j = 0; j < count; j++)
            {
                if (temp[j].getAppointmentId() == temp[i].getAppointmentId())
                {
                    cout << "Medicines: " << temp[j].getMedicines() << endl;
                    cout << "Notes: " << temp[j].getNotes() << endl;
                    cout << "---------------------------------\n";
                }
            }
        }
    }
    showPrescriptions(window, font, temp, count);

}
void Patient::displayBills() const
{
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Display Bill", sf::Style::Fullscreen);
    sf::Font font;
    font.loadFromFile("C:/Windows/Fonts/arial.ttf");
    float unpaid = 0;
    bool found = false;
    Bills temp[100];
    int bcount = 0;
    for (int i = 0; i < billStorage->getSize(); i++)
    {
        if ((*billStorage)[i].getPatientID() == this->id)
        {
            found = true;
            cout << (*billStorage)[i];
            temp[bcount] = (*billStorage)[i];
            bcount++;
            if ((*billStorage)[i].getStatus() == "unpaid")
            {
                unpaid = unpaid + (*billStorage)[i].getAmount();
            }
        }
    }
    if (!found)
    {
        showErrorWindow("No bills found");
        cout << "No bills found" << endl;
        return;
    }
    showBills(window, font, temp, bcount);
    showSuccessWindow("Outstanding amount is \n      PKR " + std::to_string(unpaid));
    cout << "Outstanding amount is ";
    cout << unpaid << endl;

}
void Patient::payBill()
{
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Pay Bill", sf::Style::Fullscreen);
    sf::Font font;
    font.loadFromFile("C:/Windows/Fonts/arial.ttf");
    bool found = false;
    Bills temp[100];
    int count = 0;
    for (int i = 0; i < billStorage->getSize(); i++)
    {
        if ((*billStorage)[i].getPatientID() == this->id && (*billStorage)[i].getStatus() == "unpaid")
        {
            temp[count] = (*billStorage)[i];
            count++;
            cout << (*billStorage)[i];
            found = true;
        }
    }
    if (!found)
    {
        showErrorWindow("No unpaid bill");
        cout << "No unpaid bill" << endl;
        return;
    }
    showBills(window, font, temp, count);
    int bid;
    cout << "Enter bill ID to pay: ";
    std::string bill = sfmlInput(window, font, "Enter bill Id to pay: ", 50);
    bid = std::stoi(bill);
    int index = -1;
    for (int i = 0; i < billStorage->getSize(); i++)
    {
        if ((*billStorage)[i].getPatientID() == this->id && (*billStorage)[i].getID()== bid && (*billStorage)[i].getStatus() == "unpaid")
        {
             index = i;
             break;
        }
    }
    if (index==-1)
    {
        showErrorWindow("Invalid id");
        cout << "Invalid id" << endl;
        return;
    }
    float amount = (*billStorage)[index].getAmount();
    try
    {
        if (balance < amount)
        {
            throw InsufficientFundsException();
        }
    }
    catch (InsufficientFundsException& e)
    {
        showErrorWindow(e.what());
        cout << e.what() << endl;
        return;
    }
    *this -= amount;
    (*billStorage)[index].markAsPaid();
    FileHandler::saveBills(*billStorage);
    FileHandler::savePatients(*patientStorage);
    cout << "Bill paid successfully" << endl;
    cout << "Remaining Balance: PKR " << balance << endl;
    showSuccessWindow("Bill paid successfully\nRemaining Balance PKR: " + std::to_string(balance));
}
void Patient::topUpBalance()
{
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Top Up Balance", sf::Style::Fullscreen);
    sf::Font font;
    font.loadFromFile("C:/Windows/Fonts/arial.ttf");
    float amount;
    int attempt = 0;
    bool valid = false;
    while (attempt < 3 && !valid)
    {
        try
        {
            cout << "Enter amount to add (PKR): ";
            std::string am = sfmlInput(window, font, "Enter amount to add (PKR)", 50);
            amount = std::stof(am);
            if (!Validator::isPositiveFloat(amount))
            {
                attempt++;
                throw InvalidInputException("Not a positive float.");
            }
            valid = true;

        }
        catch (InvalidInputException& e)
        {
            showErrorWindow(e.what());
            cout << e.what() << endl;
        }
    }
    if (!valid)
    {
        showErrorWindow("Too many invalid attempts. Returning to menu.");
        cout << "Too many invalid attempts. Returning to menu." << endl;
        return;
    }
    *this += amount;
    FileHandler::savePatients(*patientStorage);
    cout << "Balance updated" << endl;
    cout << "New Balance: PKR " << balance << endl;
    showSuccessWindow("Balance updated\n New Balance: PKR " + std::to_string(balance));
}
char* Patient::getPassword()
{
    return password;
}
float Patient::getBalance()
{
    return balance;
}
char* Patient::getPatientName()
{
    return name;
}
void Patient::menu()
{
    cout << "Welcome, ";
    for (int i = 0; name[i] != '\0'; i++)
    {
        cout << name[i];
    }
    Patient* p;
    cout << "\nBalance: PKR " << balance << endl;
    cout << "==============================\n";

    int choice;

    do
    {
        try
        {
            cout << "\n===== Patient Menu =====\n";
            cout << "1. Book Appointment\n";
            cout << "2. Cancel Appointment\n";
            cout << "3. View My Appointments\n";
            cout << "4. View My Medical Records\n";
            cout << "5. View My Bills\n";
            cout << "6. Pay Bill\n";
            cout << "7. Top Up Balance\n";
            cout << "8. Logout\n";
            cout << "Enter your choice: ";

            if (!(cin >> choice))
            {
                cin.clear();
                cin.ignore(1000, '\n');
                throw InvalidInputException("Invalid input type");
            }

            if (!Validator::isMenuChoice(choice, 8))
            {
                throw InvalidInputException("The menu choice is invalid");
            }

            switch (choice)
            {
            case 1:
                bookAppointment();
                break;

            case 2:
                cancelAppointment();
                break;

            case 3:
                displayAppointments();
                break;

            case 4:
                displayMedicalRecords();
                break;

            case 5:
                displayBills();
                break;

            case 6:
                payBill();
                break;

            case 7:
                topUpBalance();
                break;

            case 8:
                cout << "Logging out...\n";
                return;
            }

        }
        catch (exception& e)
        {
            cout << e.what() << endl;
        }

    } while (choice != 8);
}