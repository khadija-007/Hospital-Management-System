#include <iostream>
#include <cstring>
#include "Authentication.h"
#include "FileHandler.h"
#include "Validator.h"
#include "loginpage.h"
#include "errorpage.h"
using namespace std;
Patient* Authentication::loginPatient(
    Storage<Patient>& patientStorage,
    LoginData& d)
{
    if (!Validator::isId(atoi(d.id)) ||
        !Validator::isPassword(d.password))
    {
        return nullptr;
    }

    for (int i = 0; i < patientStorage.getSize(); i++)
    {
        if (patientStorage[i].getID() == atoi(d.id) &&
            strcmp(patientStorage[i].getPassword(),
                d.password) == 0)
        {
            return &(patientStorage[i]);
        }
    }

    return nullptr;
}
Doctor* Authentication::loginDoctor(Storage<Doctor>& doctorStorage, LoginData& d)
{
    if (!Validator::isId(atoi(d.id)) ||
        !Validator::isPassword(d.password))
    {
        return nullptr;
    }

    for (int i = 0; i < doctorStorage.getSize(); i++)
    {
        if (doctorStorage[i].getID() == atoi(d.id) &&
            strcmp(doctorStorage[i].getPassword(), d.password) == 0)
        {
            d.success = true;
            cout << "Login successful.\n";
            return &(doctorStorage[i]);
        }
    }

    return nullptr;
}

bool Authentication::loginAdmin(LoginData& d)
{
    if (!Validator::isId(atoi(d.id)) ||
        !Validator::isPassword(d.password))
    {
        return false;
    }

    if (atoi(d.id) == 100 && strcmp(d.password, "admin123") == 0)
    {
        d.success = true;
        cout << "Login successful.\n";
        return true;
    }

    return false;
}