#include "LibraryManager.h"

/**
* @전: 초기화된 Book 리스트, 추가할 BookInfo 객체
* @후: 책 추가
**/
void LibraryManager::AddBook(BookInfo* book)
{
	mBooks.Add(book);
}

/**
* @전: 초기화된 Book 리스트, 검색할 문자열
* @후: 책 추가
**/
void LibraryManager::AddBookFromWeb(std::string)
{

}

/**
* @전: Book List에 해당 책이 들어있을 것, 책의 ISBN을 알고 있을 것
* @후: 입력된 ISBN에 해당하는 책을 삭제
* @반환: 책 삭제에 성공하면 true, 실패하면 false를 반환
**/
bool LibraryManager::DeleteBook(int isbn)
{
	BookInfo temp;
	BookInfo* book = &temp;
	book->SetISBN(isbn);
	
	mBooks.Get(book);

	if (mBooks.Delete(book))
		return true;
	else
		return false;
}

/**
* @전: 검색할 isbn을 string 형태로 전달받는다. 책 정보를 반환받을 BookInfo 객체를 전달한다.
* @후: ISBN 검색을 수행하고, 검색에 성공하면 검색된 책의 정보 BookInfo& 객체에 집어넣는다.
* @반환: 책 검색에 성공하면 true, 실패하면 false를 반환
**/
bool LibraryManager::SearchBookWithIsbn(int isbn, BookInfo& book)
{
	BookInfo temp;
	BookInfo* curbook = &temp;
	curbook->SetISBN(isbn);

	if (mBooks.Get(curbook))
	{
		book = *curbook;
		return true;
	}
	else
		return false;
}

/**
* @전: 검색할 문자열을 string 형태로 전달받는다. 책 정보를 반환받을 LinkedList<BookInfo> 객체를 전달한다.
* @후: 모든 문자열 속성에 대해 통합 검색을 수행하고, 검색에 성공하면 검색된 책의 정보를 LinkedList에 Add한다
* @반환: 검색된 책이 한 권이라도 있다면 true, 없다면 false를 반환
**/
bool LibraryManager::SearchBookWithString(std::string search, LinkedList<BookInfo>& searchList)
{

}

/**
* @전: 빌리고자 하는 책의 ISBN과 빌리고자 하는 사람의 UserID를 전달. 빌리고자 하는 책의 예약이 없거나 전달된 사람의 예약일 것.
* @후: 책을 대출
* @반환: 대출에 성공하면 true, 실패하면 false를 반환
**/
bool LibraryManager::BorrowBook(std::string, std::string)
{

}

/**
* @전: 빌리고자 하는 책의 ISBN과 빌리고자 하는 사람의 UserID를 전달. 빌리고자 하는 책의 예약이 꽉 차있거나 이미 예약큐에 들어있지 않을 것. 몇 번째 예약인지를 반환받을 int 변수
* @후: 책 대출을 예약
* @반환: 대출에 성공하면 true, 실패하면 false를 반환
**/
bool LibraryManager::ReserveBook(std::string, std::string, int&)
{

}

/**
* @전: 연체된 대출이 존재할 것
* @후: 연체된 대출을 출력
**/
void LibraryManager::DisplayDelayedBooks()
{
	BorrowInfo* dummy;

	mBorrows.ResetList();
	int length = mBorrows.GetLength();

	for (int i = 0; i < length; i++)
	{
		mBorrows.GetNextItem(dummy);
		//연체된 대출에 대한 어떤 정보 출력?
	}

}

/**
* @전: 추가할 UserInfo 객체의 포인터를 전달한다.
* @후: UserInfo 객체가 시스템에 추가된다.
**/
void LibraryManager::AddUser(UserInfo* user)
{
	mUsers.Add(user);
}

/**
* @전: 검색할 문자열을 string 형태로 전달받는다. 사용자 정보를 반환받을 LinkedList<UserInfo> 객체를 전달한다.
* @후: 사용자 정보를 LinkedList에 추가한다
* @반환: 검색된 사용자가 있다면 true, 없다면 false를 반환
**/
bool LibraryManager::SearchUserWithString(std::string, LinkedList<UserInfo>&)
{

}

/**
* @전: 찾을 사용자의 ID를 전달받는다. 사용자 정보를 반환받을 UserInfo 객체를 전달한다.
* @후: 사용자 정보를 찾으면 UserInfo 객체에 넣는다
* @반환: 검색된 사용자가 있다면 true, 없다면 false를 반환
**/
bool LibraryManager::SearchUserById(int id, UserInfo& user)
{
	UserInfo temp;
	UserInfo* curuser = &temp;
	curuser->SetID(id);

	if (mUsers.Get(curuser))
	{
		user = *curuser;
		return true;
	}
	else
		return false;
}

/**
* @전: 제거할 사용자의 ID를 전달받는다.
* @후: 사용자 정보를 찾으면 시스템에서 삭제한다
* @반환: 삭제에 성공하면 true, 실패하면 false를 반환
**/
bool LibraryManager::DeleteUser(int id)
{
	UserInfo temp;
	UserInfo* user = &temp;
	user->SetID(id);

	mUsers.Get(user);

	if (mUsers.Delete(user))
		return true;
	else
		return false;
}