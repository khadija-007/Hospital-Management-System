#include "Prescription.h"
#include <iostream>
using namespace std;
Prescription::Prescription()
{
	PrescriptionID = 0;
	AppointmentId = 0;
	doctorID = 0;
	medicines[0] = '\0';
	notes[0] = '\0';
	DrName[0] = '\0';
	date[0] = '\0';
}
Prescription::Prescription(int pid,int did, int appID,int paid, const char* med, const char* notes, const char* drName, const char* dt)
{
	PrescriptionID = pid;
	AppointmentId = appID;
	doctorID = did;
	PatientId = paid;
	int i = 0;
	while (med[i] != 0)
	{
		medicines[i] = med[i];
		i++;
	}
	medicines[i] = '\0';
	i = 0;
	while (notes[i] != 0)
	{
		this->notes[i] = notes[i];
		i++;
	}
	this->notes[i] = '\0';
	i = 0;
	while (drName[i] != 0)
	{
		DrName[i] = drName[i];
		i++;
	}
	DrName[i] = '\0';
	i = 0;
	while (dt[i] != 0)
	{
		date[i] = dt[i];
		i++;
	}
	date[i] = '\0';
}
int Prescription::getID() const
{
	return PrescriptionID;
}
int Prescription::getPatientId() const
{
	return PatientId;
}
int Prescription::getDoctorId() const
{
	return doctorID;
}

int Prescription::getAppointmentId() const
{
	return AppointmentId;
}
const char* Prescription::getDrname()
{
	return DrName;
}
const char* Prescription::getDate() const 
{
	return date;
}

const char* Prescription::getMedicines()
{
	return medicines;
}
const char* Prescription::getNotes()
{
	return notes;
}

void Prescription::displayPrescription() const
{
	cout << "Prescription ID: " << PrescriptionID << endl;
	cout << "Appointment ID: " << AppointmentId << endl;

	cout << "Medicines: ";
	for (int i = 0; medicines[i] != '\0'; i++)
	{
		cout << medicines[i];
	}

	cout << endl;

	cout << "Notes: ";
	for (int i = 0; notes[i] != '\0'; i++)
	{
		cout << notes[i];
	}

	cout << endl;
}

std::istream& operator>>(std::istream& in, Prescription& p)
{
	char pipe;

	in >> p.PrescriptionID >> pipe;                      
	in >> p.AppointmentId>>pipe;                             

	in.getline(p.date, 11, '|');            

	in.getline(p.medicines, 500, '|');  

	in.getline(p.notes, 200, '|');         
	in.getline(p.DrName, 50, '|');        
	return in;
}
std::ostream& operator<<(std::ostream& out, const Prescription& p)
{
	out << p.PrescriptionID << "|"
		<< p.AppointmentId << "|"
		<< p.date << "|"
		<< p.medicines << "|"
		<< p.notes << "|"
		<< p.DrName << endl;

	return out;
}