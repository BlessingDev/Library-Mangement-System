#pragma once
#include <iostream>
#include <list>
using namespace std;

class UserInfo {
private:
	int m_userID;
	string m_userName;
	string m_userAddress;
	int m_userNumber;
	list<BorrowedBookList>* m_borrowedBookList;

public:
	UserInfo();

	void SetID(int ID);
	void SetUserName(string name);
	void SetUserAddress(string address);
	int SetUserNumber(int number);

	void SetIDByKB();
	void SetUserNameByKB();
	void SetUserAddressByKB();
	void SetUserNumberByKB();

	int GetUserID();
	string GetUserName();
	string GetUserAddress();
	int GetUserNumber();

	void DisplayUserInfo();
	void DisplayUserBorrowedBook();
};
