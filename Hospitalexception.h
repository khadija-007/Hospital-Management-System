#pragma once
#include <exception>
class HospitalException : public std::exception
{
protected:
    char message[200];

public:
    HospitalException(const char* msg = "Hospital system error")
    {
        int i = 0;
        for (; msg[i] != '\0' && i < 199; i++)
        {
            message[i] = msg[i];
        }
        message[i] = '\0';
    }

    virtual const char* what() const noexcept override
    {
        return message;
    }

    virtual ~HospitalException() {}
};
