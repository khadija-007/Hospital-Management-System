#pragma once
#include <iostream>
class Appointment
{
protected:
    int appointmentID;
    int patientID;
    int doctorID;
    char date[11];     
    char timeSlot[6];   
    char status[12];
public:
    Appointment();
    Appointment(int appID, int pID, int dID,
        const char* dt, const char* time,
        const char* stat);

    int getID() const;
    int getPatientID() const;
    int getDoctorID() const;
    const char* getDate() const;
    const char* getTimeSlot() const;
    const char* getStatus() const;

    void setStatus(const char* newStatus);
    void setDate(const char* dt);
    void setTimeSlot(const char* time);

	bool operator==(const Appointment& rhs);
	friend std::ostream& operator<<(std::ostream& out, const Appointment& rhs);
    friend std::istream& operator>>(std::istream& in, Appointment& p);
   
   
};