#pragma once
#include <iostream>
#include <string>
#include <ctime>
#include <iomanip>
#include "BookInfo"
#include "UserInfo"

using namespace std;




class BorrowInfo
{
public:

	/**
	*	default constructor.
	*/
	BorrowInfo()
	{}

	/**
	*	@brief	Setting borrowed date.
	*	@pre	None.
	*	@post	Borrowed time is set.
	*/
	void SetBorrowedDate();

	/**
	*	@brief	Setting book info.
	*	@pre	None.
	*	@post	Book info has been set.
	*/
	void SetBookInfo(const BookInfo& book);

	/**
	*	@brief	Setting user info.
	*	@pre	None.
	*	@post	User info has been set.
	*/
	void SetUserInfo(const UserInfo& user);

	/**
	*	@brief	Getting borrowed date.
	*	@pre	None.
	*	@post	Borrowed time is returned.
	*/
	string GetBorrowedDate();

private:
	BookInfo m_bookInfo;
	UserInfo m_userInfo;
	string m_borrowedDate;
};