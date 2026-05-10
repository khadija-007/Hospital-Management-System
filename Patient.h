#pragma once
#include <iostream>
#include "Person.h"
#include "Storage.h"
#include <SFML/Graphics.hpp>
class Doctor;
class Appointment;
class Prescription;
class Bills; 

class Patient : public Person 
{
private:
    Storage<Doctor>* doctorStorage;
    Storage<Patient>* patientStorage;
    Storage<Appointment>* appointmentStorage;
    Storage<Prescription>* prescriptionStorage;
    Storage<Bills>* billStorage;
protected:
    int age;
    char gender;
    char contact[12];
    float balance;
    int countofUnpaidBills;
    bool log;
public:
    Patient();
    Patient(int id, const char* name, const char* password,
        int age, char gender, const char* contact, float balance);
    void menusfml(sf::RenderWindow& window, sf::Event& event);
    void setStorages(Storage<Doctor>* d, Storage<Appointment>* a,Storage<Patient>* p, Storage<Prescription>* pr,Storage<Bills>* b)
    {
        billStorage = b;
        doctorStorage = d;
        appointmentStorage = a;
        patientStorage = p;
        prescriptionStorage = pr;
    }
    void display() override;
    void menu() override;
    char* getPassword();
    int getID();
    float getBalance();
    char* getPatientName();
    void bookAppointment();
    void cancelAppointment();
    void displayAppointments() const;
    void displayMedicalRecords() const;
    void displayBills() const;
    void payBill();
    void topUpBalance();

    void operator+=(float amount);
    void operator-=(float amount);
    bool operator==(const Patient& other) const;
    bool isloggedout();
    friend std::ostream& operator<<(std::ostream& out, const Patient& p);
    friend std::istream& operator>>(std::istream& in, Patient& p);
};
