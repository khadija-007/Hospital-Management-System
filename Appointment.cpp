#include "Appointment.h"
#include <iostream>
using namespace std;
Appointment::Appointment()
{
    appointmentID = 0;
    patientID = 0;
    doctorID = 0;

    date[0] = '\0';
    timeSlot[0] = '\0';
    status[0] = '\0';
}
Appointment::Appointment(int appID, int pID, int dID,
    const char* dt, const char* time,
    const char* stat)
{
    appointmentID = appID;
    patientID = pID;
    doctorID = dID;
    int i = 0;
    while( dt[i] != 0)
    {
        date[i] = dt[i];
        i++;
    }
    date[i] = '\0';
    i = 0;
    while(time[i] != 0)
    {
        timeSlot[i] = time[i];
        i++;
    }
    timeSlot[i] = '\0';
    i = 0;
    while(stat[i] != 0)
    {
        status[i] = stat[i];
        i++;
    }
    status[i] = '\0';
}

int Appointment::getID() const
{
    return appointmentID;
}
int Appointment::getPatientID() const
{
    return patientID;
}
int Appointment::getDoctorID() const
{
    return doctorID;
}
const char* Appointment::getDate() const
{
    return date;
}
const char* Appointment:: getTimeSlot() const
{
    return timeSlot;
}
const char* Appointment:: getStatus() const
{
    return status;
}

void Appointment::setStatus(const char* newStatus)
{
    int i = 0;
    while (newStatus[i] != 0)
    {
        status[i] = newStatus[i];
        i++;
    }
    status[i] = '\0';
}
void Appointment:: setDate(const char* dt)
{
    int i = 0;
    while (dt[i] != 0)
    {
        date[i] = dt[i];
    }
    date[i] = '\0';
}
void Appointment::setTimeSlot(const char* time)
{
    int i = 0;
    while (time[i] != 0)
    {
        timeSlot[i] = time[i];
    }
    timeSlot[i] = '\0';
}

bool Appointment::operator==(const Appointment& rhs)
{
    if (appointmentID == rhs.appointmentID)
    {
        return true;
    }
    return false;
}
std::ostream& operator<<(std::ostream& out, const Appointment& rhs)
{
    out << rhs.appointmentID << "|"
        << rhs.patientID << "|"
        << rhs.doctorID << "|"
        << rhs.date << "|"
        << rhs.timeSlot << "|"
        << rhs.status
        << endl;

    return out;
}
std::istream& operator>>(std::istream& in, Appointment& rhs)
{
    char pipe;

    in >> rhs.appointmentID >> pipe;
    in >> rhs.patientID >> pipe;
    in >> rhs.doctorID >> pipe;

    in.getline(rhs.date, 11, '|');
    in.getline(rhs.timeSlot, 6, '|');
    in.getline(rhs.status, 20);

    return in;
}