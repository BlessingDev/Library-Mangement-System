#include "BookInfo.h"

BookInfo::BookInfo()
{
	m_ISBN = 0;
	m_CategoryNum = 0;

	m_Title = "";
	m_Publisher = "";
	m_Author = "";	
	//	Queue BorrowedBooks = NULL;
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

void BookInfo::SetISBN(int ISBN)
{
	m_ISBN = ISBN;
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

int BookInfo::GetISBN()
{
	return m_ISBN;
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

void BookInfo::SetBookInfo()
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