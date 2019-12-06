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
	void SetPublisher(string Publisher);
	void SetCategoryNum(int CategoryNum);

	string GetAuthor();
	string GetTitle();
	string GetISBN();
	string GetPublisher();
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
	*	@post	����/������ �Ϸ�Ǹ� true, ť�� ������ �־� ���̻� ������ �� ������ false�� ��ȯ�մϴ�.
	*/
	bool EnQueueBorrowed(BorrowedInfo bInfo);

	/**
	*	@brief	DeQueue BorrowedInfoQ.
	*	@pre	Queue has been initialized.
	*	@post	���� ����/���� ���� ������ �ִٸ� deque�� �� true��, ���ٸ� false�� ��ȯ�մϴ�.
	*/
	bool DeQueueBorrowed(BorrowedInfo& bInfo);

	/**
	*	@brief	���� ����/���� ���� ������ Ȯ���մϴ�.
	*	@pre	Queue has been initialized.
	*	@post	���� ����/���� ���� ������ �ִٸ� �ش� ������ bInfo�� �����ϰ� true��, ���ٸ� false�� ��ȯ�մϴ�.
	*/
	bool GetCurrentBorrowInfo(BorrowedInfo& bInfo);

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
	CircularQueueType<BorrowedInfo> mBorrowingInfo;
};

#endif // !_BOOKINFO_H