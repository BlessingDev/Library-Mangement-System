#pragma once
#ifndef _USERINFO_H
#define _USERINFO_H

#include <iostream>
#include <fstream>
#include <string>

#include "RelationType.h"
#include "TimeForm.h"

using namespace std;

class UserInfo {
private:
	int m_userID;
	string m_userName;
	string m_userAddress;
	string m_userNumber;
	//list<BorrowedBookList>* m_borrowedBookList;

	TimeForm mPaneltyEndDay;
	int mDelayedNum;	// 이 사용자의 연체된 책 권수
	char m_nReserve;
	char m_nBorrow;

public:
	UserInfo();
	~UserInfo();

	void SetID(int ID);
	void SetUserName(string name);
	void SetUserAddress(string address);
	void SetUserNumber(string number);
	/*
	@요약: 사용자의 대출 제한을 입력할 때는 끝나는 날자를 입력한다.
	*/
	void SetPenaltyDay(TimeForm);
	void SetUserNReserve(char);
	void SetUserNBorrow(char);
	void AddDelayedNum(int);

	void SetIDByKB();
	void SetUserNameByKB();
	void SetUserAddressByKB();
	void SetUserNumberByKB();
	void SetRecordByKB();

	int GetUserID();
	string GetUserName();
	string GetUserAddress();
	string GetUserNumber();
	TimeForm GetUserPenalty();
	char GetUserNReserve();
	char GetUserNBorrow();
	bool IsDelayed() const;

	void DisplayUserID();
	void DisplayUserName();
	void DisplayUserAddress();
	void DisplayUserNumber();
	void DisplayUserInfo();

	void StartPenalty();

	int ReadDataFromFile(ifstream& fin);
	int WriteDataToFile(ofstream& fout);

	RelationType CompareByID(const UserInfo& info);

	bool operator<(const UserInfo&);
	bool operator>(const UserInfo&);
	bool operator==(const UserInfo&);
};

#endif // !_USERINFO_H