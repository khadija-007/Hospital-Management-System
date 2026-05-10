#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "Patient.h"
#include "Doctor.h"
#include "Admin.h"
using namespace std;

void showPatientMenu(Patient& p,string name, float balance);

void showDoctorMenu(Doctor& d);

void showAdminMenu(Admin &admin);