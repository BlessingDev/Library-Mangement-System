#pragma once
#include <string>
#include <iostream>
#include "LinkedList.h"
#include "SortedLinkedList.hpp"
#include "SortedPointerVector.hpp"
#include "BinarySearchTree.h"

#include "UserInfo.h"
#include "BookInfo.h"
#include "BorrowInfo.h"
#include "TimeForm.h"
#include "RelationType.h"

class LibraryManager
{

private:

	SortedPointerVector<UserInfo> mUsers;
	SortedPointerVector<BookInfo> mBooks;
	SortedLinkedList<BorrowInfo> mBorrows;		// 연체된 것을 제외한 대출
	SortedLinkedList<BorrowInfo> mReservedTop;	// 예약 정보 중 대출되지 않은 것
	LinkedList<BorrowInfo> mDelayedBorrows;		// 연체된 대출
	int mBookNum;
	int mUserNum;
  
	int mNextUserId;	// 다음에 추가되는 사용자에게 부여할 ID
	int mBorrowDay;		// 대출 기간
	int mPossBorrowNum;	// 한 사람이 최대 대출 가능한 권수
	int mPossResNum;	

public:

	LibraryManager();

	~LibraryManager();

	/**
	* @전: 초기화된 Book 리스트, 추가할 BookInfo 객체
	* @후: 책 추가
	**/
	void AddBook(BookInfo&);

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
	* @반환:
	> 1: 대출 성공
	> 2: 책에 대해 예약이 이미 있는 경우
	> 3: 대출 제한에 걸린 경우(대출 권수, 대출 연체)
	**/
	int BorrowBook(std::string, int);

	/**
	* @전: 빌리고자 하는 책의 ISBN과 빌리고자 하는 사람의 UserID를 전달. 빌리고자 하는 책의 예약이 꽉 차있거나 이미 예약큐에 들어있지 않을 것. 몇 번째 예약인지를 반환받을 int 변수
	* @후: 책 대출을 예약
	* @반환:
	> 1: 예약 성공
	> 2: 책의 예약이 가득 찬 경우
	> 3: 대출 제한, 예약 제한에 걸린 경우
	**/
	int ReserveBook(std::string, int, int&);

	/**
	* @전 : 반납하고자 하는 책의 ISBN과 반납하고자 하는 사람의 User ID를 전달
	* @매개변수 :
	> 반납된대출: 반납된 대출 정보를 반환
	> 예약정보: 예약 정보가 있을 때 예약 정보를 반환
	* @후 : 책을 반납
	* @반환 :
	> 1: 반납 성공, 예약 없음, 연체 안 됨
	> 2: 반납 성공, 예약 없음, 연체됨
	> 3: 반납 성공, 예약 있음, 연체 안 됨
	> 4: 반납 성공, 예약 있음, 연체됨
	> 5: 반납 실패
	*/
	int ReturnBook(std::string, int, BorrowInfo& returned, BorrowInfo& resInfo);

	/**
	* @전: 연체된 대출이 존재할 것
	* @후: 연체된 대출을 출력
	**/
	void DisplayDelayedBooks();

	/**
	* @전: 
	* @후: 현재 리스트에 있는 책이 출력됩니다.
	**/
	void DisplayBooks();

	/**
	* @전: 추가할 UserInfo 객체의 포인터를 전달한다.
	* @후: UserInfo 객체가 시스템에 추가된다.
	**/
	void AddUser(UserInfo);

	/**
	* @전: 검색할 문자열을 string 형태로 전달받는다. 사용자 정보를 반환받을 LinkedList<UserInfo> 객체를 전달한다.
	* @후: 사용자 정보를 LinkedList에 추가한다
	* @반환: 검색된 사용자가 있다면 true, 없다면 false를 반환
	**/
	bool SearchUserWithString(std::string, LinkedList<UserInfo>&);


	/**
	* @전: 찾을 사용자의 ID를 전달받는다. 사용자 정보를 반환받을 UserInfo 객체를 전달한다.
	* @후: 사용자 정보를 찾으면 UserInfo 객체에 넣는다
	* @반환: 검색된 사용자가 있다면 true, 없다면 false를 반환
	**/
	bool SearchUserById(int, UserInfo&);

	/**
	* @전: 찾을 도서의 값, 도서 정보를 반환받을 BookInfo 객체, 값의 Attirbute를 전달한다.
	* @ Attributes : Author, Publisher, Title, ISBN, CategoryNum
	* @후: 도서 정보를 찾으면 BookInfo 객체에 넣는다
	* @반환: 검색된 책이 있다면 true, 없다면 false를 반환
	**/
	bool SearchBookWithAttribute(string , BookInfo&, string );

	bool SearchBookWithAttribute(int , BookInfo&, string);


	/**
	* @전: 제거할 사용자의 ID를 전달받는다.
	* @후: 사용자 정보를 찾으면 시스템에서 삭제한다
	* @반환: 삭제에 성공하면 true, 실패하면 false를 반환
	**/
	bool DeleteUser(int);

	/**
	* @전:
	* @후: 현재 리스트에 있는 사용자가 출력됩니다.
	**/
	void DisplayUser();

	/**
	* @전: BookInfo_in.txt 파일에 bookinfo들이 저장되어 있음. bookinfo들의 요소들은 ',' 로 구분, bookinfo 끼리는 '\n'으로 구분
	* @후: 파일에 저장된 bookinfo 데이터를 mbooks에 추가합니다.
	* @반환: 불러오기에 성공하면 true, 실패하면 false를 반환
	**/
	bool ImportBookInfo();

	/**
	* @전: UserInfo_in.txt 파일에 userinfo들이 저장되어 있음. userinfo들의 요소들은 ',' 로 구분, userinfo 끼리는 '\n'으로 구분
	* @후: 파일에 저장된 bookinfo 데이터를 mbooks에 추가합니다.
	* @반환: 불러오기에 성공하면 true, 실패하면 false를 반환
	**/
	bool ImportUserInfo();


	/**
	* @전: mBooks 에 bookinfo들이 저장되어 있음.
	* @후: 파일에 bookinfo 데이터를 저장합니다. bookinfo들의 요소들은 ',' 로 구분, bookinfo 끼리는 '\n'으로 구분
	* @반환: 저장 성공하면 true, 실패하면 false를 반환
	**/
	bool ExportBookInfo();

	/**
	* @전: mUsers 에 userinfo들이 저장되어 있음.
	* @후: 파일에 userinfo 데이터를 저장합니다. userinfo들의 요소들은 ',' 로 구분, userinfo 끼리는 '\n'으로 구분
	* @반환: 저장 성공하면 true, 실패하면 false를 반환
	**/
	bool ExportUserInfo();


	void DayPassed(LinkedList<BorrowInfo>& delayed, LinkedList<BorrowInfo>& expired);
};

void SPVToBST(SortedPointerVector<BookInfo>& SPV, BinarySearchTree<BookInfo>& BST);

RelationType CompByAuthor(BookInfo myBook, BookInfo other);
RelationType CompByISBN(BookInfo myBook, BookInfo other);
RelationType CompByTitle(BookInfo myBook, BookInfo other);
RelationType CompByPublisher(BookInfo myBook, BookInfo other);
RelationType CompByCategoryNum(BookInfo myBook, BookInfo other);