#pragma once
#include <iostream>
class Bills
{
protected:
	int billId;
	int AppointmentId;
    int patientId;
	float amount;
	char status[10];
	char date[11];
public:
	Bills();
    Bills(int bi, int ai, int pi, float am, const char* st, const char* date);

    int getID() const;
    int getAppointmentID() const;
    int getPatientID() const;
    float getAmount() const;
    const char* getStatus() const;
    const char* getDate() const;
    void setStatus(const char* newStatus);

    void markAsPaid();
    void markAsCancelled();

    friend std::istream& operator>>(std::istream& in, Bills& p);
    friend std::ostream& operator<<(std::ostream& out, const Bills& p);

};