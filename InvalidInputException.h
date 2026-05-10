#pragma once
#include "Hospitalexception.h"
class InvalidInputException :public HospitalException
{
public:
	InvalidInputException(const char* msg) :HospitalException(msg) {}
};