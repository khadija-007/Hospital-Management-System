#include "Bills.h"
#include <iostream>
using namespace std;
Bills::Bills()
{
	billId = 0;
	AppointmentId = 0;
	patientId = 0;
	amount = 0;

	status[0] = '\0';
	date[0] = '\0';
}
Bills::Bills(int bi, int ai,int pi, float am, const char* st, const char* date)
{
	billId = bi;
	AppointmentId = ai;
	patientId = pi;
	amount = am;
	int i = 0;
	while (st[i] != 0)
	{
		status[i] = st[i];
		i++;
	}
	status[i] = '\0';
	i = 0;
	while (date[i] != 0)
	{
		this->date[i] = date[i];
		i++;
	}
	this->date[i] = '\0';
}

int Bills::getID() const
{
	return billId;
}
int Bills:: getAppointmentID() const
{
	return AppointmentId;
}
int Bills:: getPatientID() const
{
	return patientId;
}
float Bills::getAmount() const
{
	return amount;
}
const char* Bills::getStatus() const
{
	return status;
}
const char* Bills:: getDate() const
{
	return date;
}

void Bills::markAsPaid()
{
	setStatus("paid");
}
void Bills::markAsCancelled()
{
	setStatus("cancelled");
}

std::istream& operator>>(std::istream& in, Bills& p)
{
	char pipe;

	in >> p.billId >> pipe;
	in >> p.AppointmentId >> pipe;
	in >> p.patientId >> pipe;
	in >> p.amount >> pipe;

	in.getline(p.date, 11, '|');
	in.getline(p.status, 20);

	return in;
}
std::ostream& operator<<(std::ostream& out, const Bills& rhs)
{
	out << rhs.billId << "|"
		<< rhs.AppointmentId << "|"
		<< rhs.patientId << "|"
		<< rhs.amount << "|"
		<< rhs.date << "|"
		<< rhs.status
		<< endl;

	return out;
}
void Bills::setStatus(const char* newStatus)
{
	int i = 0;
	while (newStatus[i] != 0)
	{
		status[i] = newStatus[i];
		i++;
	}
	status[i] = '\0';
}
