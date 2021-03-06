#pragma once
#ifndef _BOOKINFO_H
#define _BOOKINFO_H

#include "CircularQueue.h"
#include "BorrowInfo.h"

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
	void SetPublisherByKB();
	void SetBookInfoByKB();

	void DisplayAuthor();
	void DisplayTitle();
	void DisplayISBN();
	void DisplayCategoryNum();
	void DisplayPublisher();
	void DisplayBookInfo();

	/**
	*	@brief	EnQueue BorrowedInfoQ.
	*	@pre	Queue has been initialized.
	*	@post	예약/대출이 완료되면 true, 큐가 가득차 있어 더이상 예약할 수 없으면 false를 반환합니다.
	*/
	bool EnQueueBorrowed(BorrowInfo bInfo);

	/**
	*	@brief	DeQueue BorrowedInfoQ.
	*	@pre	Queue has been initialized.
	*	@post	현재 대출/예약 중인 정보가 있다면 deque한 후 true를, 없다면 false를 반환합니다.
	*/
	bool DeQueueBorrowed(BorrowInfo& bInfo);

	/**
	*	@brief	현재 대출/예약 중인 정보를 확인합니다.
	*	@pre	Queue has been initialized.
	*	@post	현재 대출/예약 중인 정보가 있다면 해당 정보를 bInfo에 복사하고 true를, 없다면 false를 반환합니다.
	*/
	bool GetCurrentBorrowInfo(BorrowInfo& bInfo);

	/**
	*	@요약	현재 예약 중인 정보를 대출 중으로 전환합니다.
	*	@이전	현재 큐의 front에 예약중인 정보가 있어야 합니다.
	*	@후		front에 있는 예약 중 BorrowInfo가 대출 중으로 전환됩니다.
	*/
	bool SetBorrowCurrentInfo();

	/**
	*	@요약	현재 예약 중인 정보의 날짜를 갱신합니다.
	*	@이전	현재 큐의 front에 예약중인 정보가 있어야 합니다.
	*	@후		front에 있는 예약 중 BorrowInfo의 날짜가 갱신됩니다.
	*/
	bool SetDateCurrentInfo();

	/**
	*	@brief if borrowedQ is empty, return true. if not empty, return false.
	*/
	bool IsNoReservation();

	/**
	*	@brief if borrowedQ is full, return true. if not full, return false.
	*/
	bool IsFullReservation();

	int GetNumReservation();

	bool operator==(const BookInfo&);
	bool operator<(const BookInfo&);
	bool operator>(const BookInfo&);

private:
	string m_Author;
	string m_Publisher;
	string m_Title;

	string m_ISBN;
	int m_CategoryNum;
	CircularQueueType<BorrowInfo> mBorrowingInfo;
};

#endif // !_BOOKINFO_H