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
	* @전: time 문자열은 시간 정보를 전달합니다. "yyyyMMddhhmmss"의 형태여야 합니다.
	* @후:
	**/
	TimeForm(std::string time);

	/**
	* @전: time stamp로 객체를 생성합니다. timestamp는 특정 시점으로부터의 시간을 초로 표시한 수치입니다.
	* @후:
	**/
	TimeForm(std::time_t time);

	/**
	* @전: time 문자열은 시간 정보를 전달합니다. "yyyyMMddhhmmss"의 형태여야 합니다.
	* @후: 
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
	* @요약: +, - 연산자 오퍼레이터는 두 TimeForm의 합, 차를 timestamp로 반환합니다.
	*/
	std::time_t operator-(const TimeForm&);
	std::time_t operator+(const TimeForm&);
};


/*
int main()
{
	TimeForm curTime;

	std::cout << curTime.year() << curTime.month() << curTime.day() << std::endl;
	TimeForm afTime(curTime.timeStamp() + TimeForm::ONEDAY * 30); curTime에 30일 더한 시간이 afTime
	std::cout << (curTime - afTime) / TimeForm::ONEDAY << std::endl; curTime - afTime해서 -30일
}
*/