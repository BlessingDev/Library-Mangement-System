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


class BorrowedBook
{
public:
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
	Compare two itemtypes.
	@brief	Compare two item types by item borrowed date.
	@pre	two item types should be initialized.
	@post	the target file is included the new item record.
	@param	data	target item for comparing.
	@return	return LESS if this.m_borrowedDate < data.m_borrowedDate,
			return GREATER if this.m_borrowedDate > data.m_borrowedDate then,
			otherwise return EQUAL.
	*/
	RelationType CompareByDate(const BorrowedBook& data);
private:
	BookInfo m_bookInfo;
	UserInfo m_userInfo;
	string m_borrowedDate;
};