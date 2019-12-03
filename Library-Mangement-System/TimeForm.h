#pragma once
#include <string>
#include <ctime>

class TimeForm
{
private:
	std::tm mTime;

public:
	const static std::time_t ONEDAY = 24 * 60 * 60;

public:
	TimeForm();

	/**
	* @��: time ���ڿ��� �ð� ������ �����մϴ�. "yyyyMMddhhmmss"�� ���¿��� �մϴ�.
	* @��:
	**/
	TimeForm(std::string time);

	/**
	* @��: time stamp�� ��ü�� �����մϴ�. timestamp�� Ư�� �������κ����� �ð��� �ʷ� ǥ���� ��ġ�Դϴ�.
	* @��:
	**/
	TimeForm(std::time_t time);

	/**
	* @��: time ���ڿ��� �ð� ������ �����մϴ�. "yyyyMMddhhmmss"�� ���¿��� �մϴ�.
	* @��: 
	**/
	void FromString(std::string time);

	void FromTimeStamp(std::time_t time);

	int year() const;
	int month() const;
	int day() const;
	int hour() const;
	int minute() const;
	int second() const;

	std::time_t timeStamp() const;

	bool operator<(const TimeForm&);
	bool operator<=(const TimeForm&);
	bool operator>(const TimeForm&);
	bool operator>=(const TimeForm&);
	bool operator==(const TimeForm&);

	/*
	* @���: +, - ������ ���۷����ʹ� �� TimeForm�� ��, ���� timestamp�� ��ȯ�մϴ�.
	*/
	std::time_t operator-(const TimeForm&);
	std::time_t operator+(const TimeForm&);
};


/*
int main()
{
	TimeForm curTime;

	std::cout << curTime.year() << curTime.month() << curTime.day() << std::endl;
	TimeForm afTime(curTime.timeStamp() + TimeForm::ONEDAY * 30); curTime�� 30�� ���� �ð��� afTime
	std::cout << (curTime - afTime) / TimeForm::ONEDAY << std::endl; curTime - afTime�ؼ� -30��
}
*/