#pragma once
#include "Patient.h"
#include "Doctor.h"
#include "Admin.h"
#include "storage.h"
#include "loginpage.h"
class Authentication
{
public:
	static Patient* loginPatient(Storage<Patient>& patientStorage,LoginData &d);
	static Doctor* loginDoctor(Storage<Doctor>& doctorStorage,LoginData &d);
	static bool loginAdmin(LoginData& d);
};