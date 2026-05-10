#pragma once
#include <fstream>
#include "Storage.h"
#include "Patient.h"
#include "Doctor.h"
#include "Appointment.h"
#include "Bills.h"
#include "Prescription.h"
class FileHandler
{
public:

    static void loadPatients(Storage<Patient>& s)
    {
        std::ifstream fin("patients.txt");
        if (!fin)
        {
            return;
        }
        Patient p;
        while (fin >> p)
        {
            s.add(p);
        }

        fin.close();
    }

    static void loadDoctors(Storage<Doctor>& s)
    {
        std::ifstream fin("doctors.txt");
        if (!fin) return;

        Doctor d;
        while (fin >> d)
        {
            s.add(d);
        }

        fin.close();
    }
    
    static void loadAppointments(Storage<Appointment>& s)
    {
        std::ifstream fin("appointments.txt");
        if (!fin) return;

        Appointment a;
        while (fin >> a)
        {
            s.add(a);
        }

        fin.close();
    }

    static void loadBills(Storage<Bills>& s)
    {
        std::ifstream fin("bills.txt");
        if (!fin) return;

        Bills b;
        while (fin >> b)
        {
            s.add(b);
        }

        fin.close();
    }

    static void loadPrescriptions(Storage<Prescription>& s)
    {
        std::ifstream fin("prescriptions.txt");
        if (!fin) return;

        Prescription p;
        while (fin >> p)
        {
            s.add(p);
        }

        fin.close();
    }

  
    static void savePatients(Storage<Patient>& s)
    {
        std::ofstream fout("patients.txt");

        for (int i = 0; i < s.getSize(); i++)
        {
            fout << s[i] << "\n";
        }

        fout.close();
    }

    static void saveDoctors(Storage<Doctor>& s)
    {

        std::ofstream fout("doctors.txt");
        if (!fout)
        {
            std::cout << "Error: could not open doctors.txt\n";
            return;
        }
        for (int i = 0; i < s.getSize(); i++)
        {
            fout << s[i] << "\n";
        }

        fout.close();
    }

    static void saveAppointments(Storage<Appointment>& s)
    {
        std::ofstream fout("appointments.txt");

        for (int i = 0; i < s.getSize(); i++)
        {
            fout << s[i] << "\n";
        }

        fout.close();
    }

    static void saveBills(Storage<Bills>& s)
    {
        std::ofstream fout("bills.txt");

        for (int i = 0; i < s.getSize(); i++)
        {
            fout << s[i] << "\n";
        }

        fout.close();
    }

    static void savePrescriptions(Storage<Prescription>& s)
    {
        std::ofstream fout("prescriptions.txt");

        for (int i = 0; i < s.getSize(); i++)
        {
            fout << s[i] << "\n";
        }

        fout.close();
    }

   
    static void addPatient(const Patient& p)
    {
        std::ofstream fout("patients.txt", std::ios::app);
        fout << p << "\n";
        fout.close();
    }

    static void addDoctor(const Doctor& d)
    {
        std::ofstream fout("doctors.txt", std::ios::app);
        fout << d << "\n";
        fout.close();
    }

    static void addAppointment(const Appointment& a)
    {
        std::ofstream fout("appointments.txt", std::ios::app);
        fout << a << "\n";
        fout.close();
    }

    static void addBill(const Bills& b)
    {
        std::ofstream fout("bills.txt", std::ios::app);
        fout << b << "\n";
        fout.close();
    }

    static void addPrescription(const Prescription& p)
    {
        std::ofstream fout("prescriptions.txt", std::ios::app);
        fout << p << "\n";
        fout.close();
    }
   
  
    static void logEvent(const char* role, int id, const char* result)
    {
        std::ofstream fout("security_log.txt", std::ios::app);
        fout << role << "," << id << "," << result << "\n";
        fout.close();
    }
};