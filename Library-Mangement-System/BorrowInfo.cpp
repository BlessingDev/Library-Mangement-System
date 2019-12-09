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

void BorrowInfo::DisplayInfo() const
{
	cout << "Borrowed Date	:	" << m_borrowedDate;
	cout << "Book Info	:	" << endl;
	m_bookInfo->DisplayBookInfo();
	cout << "User Info	:	" << endl;
	m_userInfo->DisplayUserInfo();
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


bool BorrowInfo::operator==(const BorrowInfo& other)
{
	return (CompareByDate(other) == RelationType::EQUAL &&
		this->m_bookInfo->GetISBN() == other.m_bookInfo->GetISBN() &&
		this->m_userInfo->GetUserID() == other.m_userInfo->GetUserID());
}

bool BorrowInfo::operator<(const BorrowInfo& other)
{
	return (CompareByDate(other) == RelationType::LESS);
}

bool BorrowInfo::operator>(const BorrowInfo& other)
{
	return (CompareByDate(other) == RelationType::GREATER);
}

bool BorrowInfo::operator<=(const BorrowInfo& other)
{
	return ((*this) == other || (*this) < other);
}

bool BorrowInfo::operator>=(const BorrowInfo& other)
{
	return ((*this) == other || (*this) > other);
}
