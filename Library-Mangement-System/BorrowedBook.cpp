#include "BorrowedBook.h"
#include <iostream>
#include <string>


//Setting borrowed date.
void BorrowedBook::SetBorrowedDate()
{
	time_t rawtime;
	struct tm* timeinfo;
	char buffer[80];

	time(&rawtime);
	timeinfo = localtime(&rawtime);

	strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo);
	string str(buffer);
	m_borrowedDate = str;
}

//Setting book info.
void BorrowedBook::SetBookInfo(const BookInfo& book)
{
	m_bookInfo = book;
}

//Setting user info.
void BorrowedBook::SetUserInfo(const UserInfo& user)
{
	m_userInfo = user;
}

//Returns borrowed date.
string BorrowedBook::GetBorrowedDate()
{
	return m_borrowedDate;
}


RelationType BorrowedBook::CompareByDate(const BorrowedBook& data)
{
	if (this->m_borrowedDate > data.m_borrowedDate)
		return GREATER;
	else if (this->m_borrowedDate < data.m_borrowedDate)
		return LESS;
	else
		return EQUAL;
}