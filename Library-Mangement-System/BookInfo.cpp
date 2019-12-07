#include "BookInfo.h"
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
	//	delete[] BorrowedBooks;
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
	cout << "Input Author:	";
	cin >> m_Author;
}

void BookInfo::SetTitleByKB()
{
	cout << "Input Title:	";
	cin>>m_Title;
}

void BookInfo::SetISBNByKB()
{
	cout << "Input ISBN:	";
	cin >> m_ISBN;
}

void BookInfo::SetCategoryNumByKB()
{
	cout << "Input CategoryNum:	";
	cin >> m_CategoryNum;
}

void BookInfo::SetBookInfoByKB()
{
	SetAuthorByKB();
	SetTitleByKB();
	SetISBNByKB();
	SetCategoryNumByKB();
}

void BookInfo::DisplayAuthor()
{
	cout << m_Author << endl;
}

void BookInfo::DisplayTitle()
{
	cout << m_Title<<endl;
}

void BookInfo::DisplayISBN()
{
	cout << m_ISBN << endl;
}

void BookInfo::DisplayCategoryNum()
{
	cout << m_CategoryNum<<endl;
}

void BookInfo::DisplayBookInfo()
{
	DisplayAuthor();
	DisplayTitle();
	DisplayISBN();
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

