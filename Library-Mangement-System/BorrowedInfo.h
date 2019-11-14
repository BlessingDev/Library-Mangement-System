#pragma once
#include <iostream>
#include <string>
#include <ctime>
#include <iomanip>
#include "BookInfo"
#include "UserInfo"

using namespace std;

/**
*	Relation between two items.
*/
enum RelationType { LESS, GREATER, EQUAL };


class BorrowedInfo
{
public:

	/**
	*	default constructor.
	*/
	BorrowedInfo()
	{
		m_borrowed = false;  
		m_reserverd = false;
	}

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

	/**
	*	@brief	Setting m_borrowed to true and setting borrowed date.
	*	@pre	None.
	*	@post	Borrowed status has been set to true and borrowed date has been set.
	*/
	void Borrow();

	/**
	*	@brief	Setting m_reserved to true.
	*	@pre	None.
	*	@post	Reserved status has been set to true.
	*/
	void Reserve();

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
	RelationType CompareByDate(const BorrowedInfo& data);
private:
	BookInfo m_bookInfo;
	UserInfo m_userInfo;
	bool m_borrowed;
	bool m_reserverd;
	string m_borrowedDate;
};