#pragma once
#include "Hospitalexception.h"
class FileNotFound :public HospitalException
{
public:
	FileNotFound() :HospitalException("Required file not found.") {};
};