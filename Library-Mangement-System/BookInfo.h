#pragma once
#ifndef _BOOKINFO_H
#define _BOOKINFO_H

#include "CircularQueue.h"
#include "BorrowedInfo.h"

using namespace std;

class BookInfo
{
public:
	BookInfo();
	~BookInfo();

	void SetAuthor(string author);
	void SetTitle(string title);
	void SetISBN(string  ISBN);
	void SetCategoryNum(int CategoryNum);

	string GetAuthor();
	string GetTitle();
	string GetISBN();
	int GetCategoryNum();

	void SetAuthorByKB();
	void SetTitleByKB();
	void SetISBNByKB();
	void SetCategoryNumByKB();
	void SetBookInfoByKB();

	void DisplayAuthor();
	void DisplayTitle();
	void DisplayISBN();
	void DisplayCategoryNum();
	void DisplayBookInfo();

	/**
	*	@brief	EnQueue BorrowedInfoQ.
	*	@pre	Queue has been initialized.
	*	@post	If (queue is full), FullQueue exception is thrown; otherwise, newItem is at the last.
	*/
	void EnQueueBorrowed(BorrowedInfo bInfo);

	/**
	*	@brief	DeQueue BorrowedInfoQ.
	*	@pre	Queue has been initialized.
	*	@post	If (queue is empty), EmptyQueue exception is thrown; otherwise, first element has been removed from queue. item gets value of removed item.
	*/
	void DeQueueBorrowed(BorrowedInfo bInfo);

	BorrowedInfo GetFrontBorrowed();

	/**
	*	@brief if borrowedQ is empty, return true. if not empty, return false.
	*/
	bool IsNoReservation();

	/**
	*	@brief if borrowedQ is full, return true. if not full, return false.
	*/
	bool IsFullReservation();

private:
	string m_Author;
	string m_Publisher;
	string m_Title;

	string m_ISBN;
	int m_CategoryNum;
	CircularQueueType<BorrowedInfo> BorrowedBooks;
};

#endif // !_BOOKINFO_H