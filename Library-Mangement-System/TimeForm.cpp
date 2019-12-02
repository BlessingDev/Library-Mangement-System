#include "TimeForm.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <cstdlib>

TimeForm::TimeForm()
	: mTime{ 0 }
{
	auto timer = std::time(nullptr);

	localtime_s(&mTime, &timer);
}

TimeForm::TimeForm(std::string timeStr)
	: mTime{ 0 }
{
	FromString(timeStr);
}

TimeForm::TimeForm(std::time_t ts)
	: mTime{ 0 }
{
	FromTimeStamp(ts);
}

void TimeForm::FromString(std::string timeStr)
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


	int year = atoi(timeStr.substr(0, 4).c_str());
	int month = atoi(timeStr.substr(4, 2).c_str());
	int day = atoi(timeStr.substr(6, 2).c_str());
	int hour = atoi(timeStr.substr(8, 2).c_str());
	int min = atoi(timeStr.substr(10, 2).c_str());
	int sec = atoi(timeStr.substr(12, 2).c_str());

	std::ostringstream oss;
	oss << year << "-" << month << "-" << day << " " << hour << ":" << min << ":" << sec;
	std::istringstream iss(oss.str());
	iss >> std::get_time(&mTime, "%Y-%m-%d %H:%M:%S");
}

void TimeForm::FromTimeStamp(std::time_t ts)
{
	localtime_s(&mTime, &ts);
}

int TimeForm::year() const
{
	return 1900 + mTime.tm_year;
}

int TimeForm::month() const
{
	return mTime.tm_mon + 1;
}

int TimeForm::day() const
{
	return mTime.tm_mday;
}

int TimeForm::hour() const
{
	return mTime.tm_hour;
}

int TimeForm::minute() const
{
	return mTime.tm_min;
}

int TimeForm::second() const
{
	return mTime.tm_sec;
}

std::time_t TimeForm::timeStamp() const
{
	std::tm tTm = this->mTime;
	auto stamp = std::mktime(std::addressof(tTm));
	return stamp;
}

bool TimeForm::operator<(const TimeForm& other)
{
	return (this->timeStamp() < other.timeStamp());
}

bool TimeForm::operator<=(const TimeForm& other)
{
	return ((*this) < other) || ((*this) == other);
}

bool TimeForm::operator>(const TimeForm& other)
{
	return (this->timeStamp() > other.timeStamp());
}

bool TimeForm::operator>=(const TimeForm& other)
{
	return ((*this) > other) || ((*this) == other);
}

bool TimeForm::operator==(const TimeForm& other)
{
	return (this->timeStamp() == other.timeStamp());
}

std::time_t TimeForm::operator-(const TimeForm& other)
{
	int diff = this->timeStamp() - other.timeStamp();
	return diff;
}

std::time_t TimeForm::operator+(const TimeForm& other)
{
	std::time_t sum = this->timeStamp() + other.timeStamp();
	return sum;
}