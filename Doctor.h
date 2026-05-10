#pragma once
#include <iostream>
#include "storage.h"
#include "Person.h"
#include "Appointment.h"
#include "Patient.h"
#include "Prescription.h"
#include "Bills.h"
class Doctor:public Person
{
private:
	Storage<Doctor>* doctorStorage;
	Storage<Patient>* patientStorage;
	Storage<Appointment>* appointmentStorage;
	Storage<Prescription>* prescriptionStorage;
    Storage<Bills>* billStorage; 
protected:
	char specialization[50];
	char contact[12];
	float fee;
public:
	Doctor();
	void setStorages(Storage<Doctor>* d, Storage<Appointment>* a, Storage<Patient>* p, Storage<Prescription>* pr, Storage<Bills>* b)
	{
		billStorage = b;
		doctorStorage = d;
		appointmentStorage = a;
		patientStorage = p;
		prescriptionStorage = pr;
	}
	Doctor(int id, const char* name, const char* password, const char* s,const char* c, float f);
	void displayTodayAppointment();
	void markAppointmentComplete();
	void markAppointmentNoshow();
	void writePrescription();
	void displayPatientHistory();
	char* getPassword();
	char* getNumber();
	

	int getID();
	const char* getSpecialization()const;
	int getFee();
	void display() override;
	void menu() override;


	bool operator==(const Doctor& rhs)const;
	friend std::ostream& operator<<(std::ostream& out, const Doctor& rhs);
	friend std::istream& operator>>(std::istream& in, Doctor& d);
	
};

