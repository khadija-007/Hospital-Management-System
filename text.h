#pragma once

#include <SFML/Graphics.hpp>
#include "storage.h"
#include "Doctor.h"
#include "Patient.h"
#include "Bills.h"
#include "Appointment.h"
#include "Prescription.h"


using namespace std;

void showDoctors(sf::RenderWindow&, sf::Font&, Doctor doctor[], int);
void showPatients(sf::RenderWindow&, sf::Font&, Patient patient[], int);
void showBills(sf::RenderWindow&, sf::Font&, Bills bill[], int);
void showPrescriptions(sf::RenderWindow&, sf::Font&, Prescription pres[], int);
void showAppointments(sf::RenderWindow&, sf::Font&, Appointment app[], int, Storage<Doctor> &doctorStorage,Storage<Patient> &patientStorage);
void showDailyReportUI(sf::RenderWindow&, sf::Font&, const char today[], int total, int pending, int completed, int noshow, int cancelled, float revenue, char (*unpaidText)[200], int unpaidCount, char (*doctorSummary)[200], int doctorCount);
