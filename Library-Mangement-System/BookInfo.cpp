#include "BookInfo.h"




BookInfo::BookInfo()
	: mBorrowingInfo(10)
{
	m_ISBN = "";
	m_CategoryNum = 0;

	m_Title = "";
	m_Publisher = "";
	m_Author = "";	
}

BookInfo::~BookInfo()
{
	//delete[] BorrowedBooks;
}

void BookInfo::SetAuthor(string author)
{
	m_Author = author;
}

void BookInfo::SetTitle(string title)
{
	m_Title = title;
}

void BookInfo::SetISBN(string ISBN)
{
	m_ISBN = ISBN;
}

void BookInfo::SetPublisher(string Publisher)
{
	m_Publisher = Publisher;
}

void BookInfo::SetCategoryNum(int CategoryNum)
{
	m_CategoryNum = CategoryNum;
}

string BookInfo::GetAuthor()
{
	return m_Author;
}

string BookInfo::GetTitle()
{
	return m_Title;
}

string BookInfo::GetISBN()
{
	return m_ISBN;
}

string BookInfo::GetPublisher()
{
	return m_Publisher;
}

int BookInfo::GetCategoryNum()
{
	return m_CategoryNum;
}

void BookInfo::SetAuthorByKB()
{
	cout << "작가: ";
	std::getline(std::cin, m_Author);
}

void BookInfo::SetTitleByKB()
{
	cout << "제목: ";
	std::getline(std::cin, m_Title);
}

void BookInfo::SetISBNByKB()
{
	cout << "ISBN: ";
	cin >> m_ISBN;
	cin.ignore();
}

void BookInfo::SetCategoryNumByKB()
{
	cout << "분류번호: ";
	cin >> m_CategoryNum;
	cin.ignore();
}

void BookInfo::SetPublisherByKB()
{
	cout << "출판사: ";
	std::getline(std::cin, m_Publisher);
}

void BookInfo::SetBookInfoByKB()
{
	SetISBNByKB();
	SetTitleByKB();
	SetAuthorByKB();
	SetPublisherByKB();
	SetCategoryNumByKB();
}

void BookInfo::DisplayAuthor()
{
	cout << "작가:" << m_Author << endl;
}

void BookInfo::DisplayTitle()
{
	cout << "제목:" << m_Title<<endl;
}

void BookInfo::DisplayISBN()
{
	cout << "ISBN:" << m_ISBN << endl;
}

void BookInfo::DisplayCategoryNum()
{
	cout << "분류번호:" << m_CategoryNum<<endl;
}

void BookInfo::DisplayPublisher()
{
	cout << "출판사:" << m_Publisher << endl;
}

void BookInfo::DisplayBookInfo()
{
	DisplayISBN();
	DisplayTitle();
	DisplayAuthor();
	DisplayPublisher();
	DisplayCategoryNum();
}

bool BookInfo::EnQueueBorrowed(BorrowInfo bInfo)
{
	try
	{
		mBorrowingInfo.EnQueue(bInfo);
		return true;
	}
	catch (FullQueue e)
	{
		return false;
	}
}

bool BookInfo::DeQueueBorrowed(BorrowInfo& bInfo)
{
	try
	{
		mBorrowingInfo.DeQueue(bInfo);
		return true;
	}
	catch (EmptyQueue e)
	{
		return false;
	}
}

bool BookInfo::GetCurrentBorrowInfo(BorrowInfo& bInfo)
{
	try
	{
		bInfo = mBorrowingInfo.GetFront();
		return true;
	}
	catch (EmptyQueue e)
	{
		return false;
	}
}

bool BookInfo::SetBorrowCurrentInfo()
{
	BorrowInfo* pbi = nullptr;
	try
	{
		mBorrowingInfo.GetFrontPointer(pbi);
	}
	catch (EmptyQueue e)
	{
		return false;
	}
	pbi->Borrow();

	return true;
}

bool BookInfo::SetDateCurrentInfo()
{
	BorrowInfo* pbi = nullptr;
	try
	{
		mBorrowingInfo.GetFrontPointer(pbi);
	}
	catch (EmptyQueue e)
	{
		return false;
	}
	pbi->SetBorrowDate();
	
	return true;
}

bool BookInfo::IsNoReservation()
{
	return mBorrowingInfo.IsEmpty();
}

bool BookInfo::IsFullReservation()
{
	return mBorrowingInfo.IsFull();
}

int BookInfo::GetNumReservation()
{
	return mBorrowingInfo.GetLength();
}

bool BookInfo::operator==(const BookInfo& other)
{
	return (this->m_ISBN == other.m_ISBN);
}

bool BookInfo::operator<(const BookInfo& other)
{
	return (this->m_ISBN < other.m_ISBN);
}

bool BookInfo::operator>(const BookInfo& other)
{
	return (this->m_ISBN > other.m_ISBN);
}

