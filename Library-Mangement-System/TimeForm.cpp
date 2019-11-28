#include "TimeForm.h"
#include <iostream>
#include <cstdlib>

TimeForm::TimeForm(std::string timeStr)
{
	try
	{
		atoi(timeStr.c_str());
		if (timeStr.length() != 14)
		{
			throw std::exception("yyyymmddttmmss 형식이 아닙니다.");
		}
	}
	catch (std::exception e)
	{
		std::cout << "sendTime이 올바른 날짜 형식이 아닙니다.";
		throw e;
	}


	year = atoi(timeStr.substr(0, 4).c_str());
	month = atoi(timeStr.substr(4, 2).c_str());
	day = atoi(timeStr.substr(6, 2).c_str());
	hour = atoi(timeStr.substr(8, 2).c_str());
	min = atoi(timeStr.substr(10, 2).c_str());
	sec = atoi(timeStr.substr(12, 2).c_str());
}

bool TimeForm::operator<(const TimeForm& other)
{
	if (this->year < other.year)
	{
		return true;
	}
	else if (this->year == other.year)
	{
		if (this->month < other.month)
		{
			return true;
		}
		else if (this->month == other.month)
		{
			if (this->day > other.day)
			{
				return true;
			}
			else if (this->day == other.day)
			{
				if (this->hour < other.hour)
				{
					return true;
				}
				else if (this->hour == other.hour)
				{
					if (this->min < other.min)
					{
						return true;
					}
					else if (this->min == other.min)
					{
						if (this->sec < other.sec)
						{
							return true;
						}
						else
						{
							return false;
						}
					}
					else
					{
						return false;
					}
				}
				else
				{
					return false;
				}
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}

bool TimeForm::operator<=(const TimeForm& other)
{
	return ((*this) < other) || ((*this) == other);
}

bool TimeForm::operator>(const TimeForm& other)
{
	if (this->year > other.year)
	{
		return true;
	}
	else if (this->year == other.year)
	{
		if (this->month > other.month)
		{
			return true;
		}
		else if (this->month == other.month)
		{
			if (this->day > other.day)
			{
				return true;
			}
			else if (this->day == other.day)
			{
				if (this->hour > other.hour)
				{
					return true;
				}
				else if (this->hour == other.hour)
				{
					if (this->min > other.min)
					{
						return true;
					}
					else if (this->min == other.min)
					{
						if (this->sec > other.sec)
						{
							return true;
						}
						else
						{
							return false;
						}
					}
					else
					{
						return false;
					}
				}
				else
				{
					return false;
				}
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}

bool TimeForm::operator>=(const TimeForm& other)
{
	return ((*this) > other) || ((*this) == other);
}

bool TimeForm::operator==(const TimeForm& other)
{
	return (
		this->year == other.year &&
		this->month == other.month &&
		this->day == other.month &&
		this->hour == other.hour &&
		this->min == other.min &&
		this->sec == other.sec
		);
}