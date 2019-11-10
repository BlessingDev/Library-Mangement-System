#pragma once
#include <string>

#include "LinkedList.h"
#include "SortedLinkedList.hpp"

class LibraryManager
{
private:
	LinkedList<UserInfo*> mUsers;
	LinkedList<BookInfo*> mBooks;
	SortedLinkedList<BorrowInfo*> mBorrows;
	int mBookNum;
	int mUserNum;
	int mNextUserId;	// 다음에 추가되는 사용자에게 부여할 ID
	int mBorrowDay;		// 대출 기간
	int mPossBorrowNum;	// 한 사람이 최대 대출 가능한 권수

public:
	LibraryManager();

	~LibraryManager();

	/**
	* @전: 초기화된 Book 리스트, 추가할 BookInfo 객체
	* @후: 책 추가
	**/
	void AddBook(BookInfo);

	/**
	* @전: 초기화된 Book 리스트, 검색할 문자열
	* @후: 책 추가
	**/
	void AddBookFromWeb(std::string);

	/**
	* @전: Book List에 해당 책이 들어있을 것, 책의 ISBN을 알고 있을 것
	* @후: 입력된 ISBN에 해당하는 책을 삭제
	* @반환: 책 삭제에 성공하면 true, 실패하면 false를 반환
	**/
	bool DeleteBook(std::string);

	/**
	* @전: 검색할 isbn을 string 형태로 전달받는다. 책 정보를 반환받을 BookInfo 객체를 전달한다.
	* @후: ISBN 검색을 수행하고, 검색에 성공하면 검색된 책의 정보 BookInfo& 객체에 집어넣는다.
	* @반환: 책 검색에 성공하면 true, 실패하면 false를 반환
	**/
	bool SearchBookWithIsbn(std::string, BookInfo&);

	/**
	* @전: 검색할 문자열을 string 형태로 전달받는다. 책 정보를 반환받을 LinkedList<BookInfo> 객체를 전달한다.
	* @후: 모든 문자열 속성에 대해 통합 검색을 수행하고, 검색에 성공하면 검색된 책의 정보를 LinkedList에 Add한다
	* @반환: 검색된 책이 한 권이라도 있다면 true, 없다면 false를 반환
	**/
	bool SearchBookWithString(std::string, LinkedList<BookInfo>&);

	/**
	* @전: 빌리고자 하는 책의 ISBN과 빌리고자 하는 사람의 UserID를 전달. 빌리고자 하는 책의 예약이 없거나 전달된 사람의 예약일 것.
	* @후: 책을 대출
	* @반환: 대출에 성공하면 true, 실패하면 false를 반환
	**/
	bool BorrowBook(std::string, std::string);

	/**
	* @전: 빌리고자 하는 책의 ISBN과 빌리고자 하는 사람의 UserID를 전달. 빌리고자 하는 책의 예약이 꽉 차있거나 이미 예약큐에 들어있지 않을 것. 몇 번째 예약인지를 반환받을 int 변수
	* @후: 책 대출을 예약
	* @반환: 대출에 성공하면 true, 실패하면 false를 반환
	**/
	bool ReserveBook(std::string, std::string, int&);

	/**
	* @전: 연체된 대출
	* @후: 연체된 대출을 출력
	**/
	void DisplayDelayedBooks();
};