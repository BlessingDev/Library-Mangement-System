#pragma once
#include <string>

struct TimeForm
{
	int year;
	int month;
	int day;
	int hour;
	int min;
	int sec;

	TimeForm() = default;

	/**
	* @전: std::string 문자열은 "yyyyMMddhhmmss"의 형태여야 합니다.
	* @후: TimeForm 객체 생성
	**/
	TimeForm(std::string);

	bool operator<(const TimeForm&);
	bool operator<=(const TimeForm&);
	bool operator>(const TimeForm&);
	bool operator>=(const TimeForm&);
	bool operator==(const TimeForm&);

};