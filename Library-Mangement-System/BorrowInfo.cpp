#include "BorrowInfo.h"
#include <iostream>
#include <string>


//Setting borrowed date.
void BorrowInfo::SetBorrowedDate()
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
void BorrowInfo::SetBookInfo(const BookInfo& book)
{
	m_bookInfo = book;
}

//Setting user info.
void BorrowInfo::SetUserInfo(const UserInfo& user)
{
	m_userInfo = user;
}

//Returns borrowed date.
string BorrowInfo::GetBorrowedDate()
{
	return m_borrowedDate;
}



