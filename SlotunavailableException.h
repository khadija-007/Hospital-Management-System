#pragma once
#include "Hospitalexception.h"
class SlotUnavailableException :public HospitalException
{
public:
	SlotUnavailableException() :HospitalException("Sorry, this slot has already been booked.") {}
};