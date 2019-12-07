#include "BorrowInfo.h"
#include <iostream>
#include <string>

#include "Application.h"

//Setting book info.
void BorrowInfo::SetBookInfo(BookInfo* book)
{
	m_bookInfo = book;
}

//Setting user info.
void BorrowInfo::SetUserInfo(UserInfo* user)
{
	m_userInfo = user;
}

UserInfo* BorrowInfo::GetUserInfo() const
{
	return m_userInfo;
}

BookInfo* BorrowInfo::GetBookInfo() const
{
	return m_bookInfo;
}

//Returns borrowed date.
TimeForm BorrowInfo::GetBorrowDate()
{
	return m_borrowedDate;
}

bool BorrowInfo::IsBorrowing() const
{
	return m_borrowed;
}

void BorrowInfo::Borrow()
{
	m_borrowed = true;
	SetBorrowDate();
}

void BorrowInfo::SetBorrowDate()
{
	m_borrowedDate = Application::mProgramTime;
}

RelationType BorrowInfo::CompareByDate(const BorrowInfo& data)
{
	if (this->m_borrowedDate > data.m_borrowedDate)
		return RelationType::GREATER;
	else if (this->m_borrowedDate < data.m_borrowedDate)
		return RelationType::LESS;
	else
		return RelationType::EQUAL;
}

