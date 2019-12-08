#pragma once
#include <iostream>
#include <string>
#include <ctime>
#include <iomanip>
#include "TimeForm.h"
#include "RelationType.h"

using namespace std;

class BookInfo;
class UserInfo;

class BorrowInfo
{
public:

	/**
	*	default constructor.
	*/
	BorrowInfo()
	{
		m_borrowed = false;
	}

	/**
	*	@brief	Setting borrowed date.
	*	@pre	None.
	*	@post	Borrowed time is set.
	*/
	void SetBorrowDate();

	/**
	*	@brief	Setting book info.
	*	@pre	None.
	*	@post	Book info has been set.
	*/
	void SetBookInfo(BookInfo* book);

	/**
	*	@brief	Setting user info.
	*	@pre	None.
	*	@post	User info has been set.
	*/
	void SetUserInfo(UserInfo* user);

	void DisplayInfo() const;

	UserInfo* GetUserInfo() const;

	BookInfo* GetBookInfo() const;

	bool IsBorrowing() const;

	/**
	*	@brief	Getting borrowed date.
	*	@pre	None.
	*	@post	Borrowed time is returned.
	*/
	TimeForm GetBorrowDate();

	/**
	*	@brief	Setting m_borrowed to true and setting borrowed date.
	*	@pre	None.
	*	@post	Borrowed status has been set to true and borrowed date has been set.
	*/
	void Borrow();

	/**
	Compare two itemtypes.
	@brief	Compare two item types by item borrowed date.
	@pre	two item types should be initialized.
	@post	the target file is included the new item record.
	@param	data	target item for comparing.
	@return	return LESS if this.m_borrowedDate < data.m_borrowedDate,
			return GREATER if this.m_borrowedDate > data.m_borrowedDate then,
			otherwise return EQUAL.
	*/
	RelationType CompareByDate(const BorrowInfo& data);

	bool operator==(const BorrowInfo&);
	bool operator<(const BorrowInfo&);
	bool operator>(const BorrowInfo&);
	bool operator<=(const BorrowInfo&);
	bool operator>=(const BorrowInfo&);
private:
	BookInfo* m_bookInfo;
	UserInfo* m_userInfo;
	bool m_borrowed;
	TimeForm m_borrowedDate;
};