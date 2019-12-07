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
	int m_userNumber;
	//list<BorrowedBookList>* m_borrowedBookList;

	TimeForm m_penalty;
	char m_nReserve;
	char m_nBorrow;

public:
	UserInfo();
	~UserInfo();

	void SetID(int ID);
	void SetUserName(string name);
	void SetUserAddress(string address);
	void SetUserNumber(int number);
	void SetUserPenalty(TimeForm);
	void SetUserNReserve(char);
	void SetUserNBorrow(char);

	void SetIDByKB();
	void SetUserNameByKB();
	void SetUserAddressByKB();
	void SetUserNumberByKB();
	void SetRecordByKB();

	int GetUserID();
	string GetUserName();
	string GetUserAddress();
	int GetUserNumber();
	TimeForm GetUserPenalty();
	char GetUserNReserve();
	char GetUserNBorrow();

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