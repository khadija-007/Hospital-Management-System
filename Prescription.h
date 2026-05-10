#pragma once
#include <iostream>
class Prescription
{
protected:
	int PrescriptionID;
	int AppointmentId;
	char medicines[500];
	char notes[300];
	char DrName[30];
	char date[11];
	int PatientId;
	int doctorID;
public:
	Prescription();
	Prescription(int pid,int did, int appID,int paid,const char* med,const char* notes, const char* drName, const char* dt);
	int getID() const;
	int getAppointmentId() const;
	const char* getDrname();
	const char* getNotes();
	const char* getMedicines();
	int getPatientId()const;
	int getDoctorId()const;
	const char* getDate() const;

	void displayPrescription() const;
	friend std::istream& operator>>(std::istream& in, Prescription& p);
	friend std::ostream& operator<<(std::ostream& out, const Prescription& p);

};