#pragma once
class Validator
{
public:
	static bool isId(int num)
	{
		if (num <= 0)
		{
			return false;
		}
		return true;
	}
	static bool isMenuChoice(int mc,int max)
	{
		if (mc <= 0 || mc > max)
		{
			
			return false;
		}
		return true;
	}
	static bool isDate(const char* date)
	{
		if (date[2] != '-' || date[5] != '-' || date[10] != '\0')
		{
			
			return false;

		}
		int day = (date[0] - '0') * 10 + (date[1] - '0');
		int month = (date[3] - '0') * 10 + (date[4] - '0');
		int year = (date[6] - '0') * 1000 +
			(date[7] - '0') * 100 +
			(date[8] - '0') * 10 +
			(date[9] - '0');

		if (day < 1 || day > 31)
		{
			

			return false;

		}
		if (month < 1 || month > 12)
		{
			

			return false;

		}
		if (year < 2026)   
		{
			

			return false;

		}
		return true;
	}
	static bool isTimeslot(const char* slot)
	{
		if (slot[2] != ':'||slot[5]!='\0')
		{
			return false;
		}
		int hour = (slot[0] - '0') * 10 + (slot[1] - '0');
		int minutes = (slot[3] - '0') * 10 + (slot[4] - '0');
		if(hour<9||hour>16)
		{
			return false;
		}
		if (minutes != 0)
		{
			return false;
		}
		return true;
	}
	static bool isContactNo(const char* phone)
	{
		int len = 0;
		for (int i = 0; phone[i] != '\0'; i++)
		{
			len++;
			if (phone[i] < '0' || phone[i] > '9')
			{
				return false;
			}
		}
		if (len != 11)
		{
			return false;
		}
		return true;
	}
	static bool isPassword(const char* password)
	{
		int len = 0;

		for (int i = 0; password[i] != '\0'; i++)
			len++;

		if (len < 6)
		{
			return false;
		}
		return true;
	}
	static bool isPositiveFloat(float val)
	{
		if (val <= 0.0)
		{
			return false;
		}		
		return true;
	}
	static bool isEqualIgnoreCase(const char* a, const char* b)
	{
		int i = 0;

		while (a[i] != '\0' && b[i] != '\0')
		{
			char c1 = a[i];
			char c2 = b[i];

			if (c1 >= 'A' && c1 <= 'Z') c1 += 32;
			if (c2 >= 'A' && c2 <= 'Z') c2 += 32;

			if (c1 != c2)
				return false;

			i++;
		}

		return a[i] == '\0' && b[i] == '\0';
	}
};