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
	* @��: std::string ���ڿ��� "yyyyMMddhhmmss"�� ���¿��� �մϴ�.
	* @��: TimeForm ��ü ����
	**/
	TimeForm(std::string);

	bool operator<(const TimeForm&);
	bool operator<=(const TimeForm&);
	bool operator>(const TimeForm&);
	bool operator>=(const TimeForm&);
	bool operator==(const TimeForm&);

};