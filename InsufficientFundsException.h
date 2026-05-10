#pragma once
#include "Hospitalexception.h"
class InsufficientFundsException :public HospitalException
{
public:
	InsufficientFundsException():HospitalException("The patient's balance is less than the required amount"){}
};