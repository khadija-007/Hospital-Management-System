#pragma once
#include <iostream>
#include "Person.h"
#include "storage.h"
#include "Appointment.h"
#include "Patient.h"
#include "Prescription.h"
#include "Bills.h"
#include "Doctor.h"
class Admin:public Person
{
private:
	Storage<Doctor>* doctorStorage;
	Storage<Patient>* patientStorage;
	Storage<Appointment>* appointmentStorage;
	Storage<Prescription>* prescriptionStorage;
	Storage<Bills>* billStorage;

public:
	Admin();
	Admin(int id, const char* n, const char* pass);
	void setStorages(Storage<Doctor>* d, Storage<Appointment>* a, Storage<Patient>* p, Storage<Prescription>* pr, Storage<Bills>* b)
	{
		billStorage = b;
		doctorStorage = d;
		appointmentStorage = a;
		patientStorage = p;
		prescriptionStorage = pr;
	}
	void AddDoctor();
	void AddPatient();
	void RemoveDoctor();
	void ViewAllPatients();
	void ViewAllDoctors();
	void ViewAllAppointments();    
	void ViewUnpaidBills();   
	void DischargePatient();
	void viewSecurityLog();        
	void GenerateDailyReport();
	char* getPassword();

	void display() override;
	void menu() override;

	
};
