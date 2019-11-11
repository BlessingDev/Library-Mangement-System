#pragma once
#ifndef _USERINFO_H
#define _USERINFO_H

#include <iostream>
#include <fstream>
#include <string>
#include <list>
using namespace std;

enum RelationType {LESS, GREATER, EQUAL};

class UserInfo {
private:
	int m_userID;
	string m_userName;
	string m_userAddress;
	int m_userNumber;
	list<BorrowedBookList>* m_borrowedBookList;

public:
	UserInfo();
	~UserInfo();

	void SetID(int ID);
	void SetUserName(string name);
	void SetUserAddress(string address);
	void SetUserNumber(int number);

	void SetIDByKB();
	void SetUserNameByKB();
	void SetUserAddressByKB();
	void SetUserNumberByKB();
	void SetRecordByKB();

	int GetUserID();
	string GetUserName();
	string GetUserAddress();
	int GetUserNumber();

	void DisplayUserID();
	void DisplayUserName();
	void DisplayUserAddress();
	void DisplayUserNumber();
	void DisplayUserInfo();

	int ReadDataFromFile(ifstream& fin);
	int WriteDataToFile(ofstream& fout);

	RelationType CompareByID(const UserInfo& info);
};

#endif // !_USERINFO_H