#include "BorrowedInfo.h"
#include <iostream>
#include <string>


//Setting borrowed date.
void BorrowedInfo::SetBorrowedDate()
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
void BorrowedInfo::SetBookInfo(const BookInfo& book)
{
	m_bookInfo = book;
}

//Setting user info.
void BorrowedInfo::SetUserInfo(const UserInfo& user)
{
	m_userInfo = user;
}

//Returns borrowed date.
string BorrowedInfo::GetBorrowedDate()
{
	return m_borrowedDate;
}

void BorrowedInfo::Borrow()
{
	m_borrowed = true;
	SetBorrowedDate();
}

void BorrowedInfo::Reserve()
{
	m_reserverd = true;
}


RelationType BorrowedInfo::CompareByDate(const BorrowedInfo& data)
{
	if (this->m_borrowedDate > data.m_borrowedDate)
		return GREATER;
	else if (this->m_borrowedDate < data.m_borrowedDate)
		return LESS;
	else
		return EQUAL;
}