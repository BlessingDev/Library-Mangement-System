#include "LibraryManager.h"

#include "Application.h"

LibraryManager::LibraryManager()
{
	mBookNum = 0;
	mUserNum = 0;
	mNextUserId = -1;
	mBorrowDay = 14;
	mPossBorrowNum = 5;
	mPossResNum = 5;
}

LibraryManager::~LibraryManager(){}
/**
* @전: 초기화된 Book 리스트, 추가할 BookInfo 객체
* @후: 책 추가
**/
void LibraryManager::AddBook(BookInfo book)
{
	mBooks.Add(book);
	mBookNum++;
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
bool LibraryManager::DeleteBook(std::string isbn)
{
	BookInfo temp;
	temp.SetISBN(isbn);

	if (mBooks.Delete(temp))
	{
		mBookNum--;
		return true;
	}
	else
		return false;
}

/**
* @전: 검색할 isbn을 string 형태로 전달받는다. 책 정보를 반환받을 BookInfo 객체를 전달한다.
* @후: ISBN 검색을 수행하고, 검색에 성공하면 검색된 책의 정보 BookInfo& 객체에 집어넣는다.
* @반환: 책 검색에 성공하면 true, 실패하면 false를 반환
**/
bool LibraryManager::SearchBookWithIsbn(std::string isbn, BookInfo& book)
{
	BookInfo temp;
	temp.SetISBN(isbn);

	if (mBooks.GetItem(temp))
	{
		book = temp;
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
	BookInfo dummy;
	int length = mBooks.GetLength();

	string title, publisher, isbn, author;
	bool found = false;

	for (int i = 0; i < length; i++)
	{

		dummy = mBooks[i];
		isbn = dummy.GetISBN();
		author = dummy.GetAuthor();
		publisher = dummy.GetPublisher();
		title = dummy.GetTitle();

		if (isbn.find(search) == string::npos)
			if (author.find(search) == string::npos)
				if (publisher.find(search) == string::npos)
					if (title.find(search) == string::npos)
						break;

		found = true;
		searchList.Add(dummy);
	}

	if (found)
		return true;
	else
		return false;
}

/**
* @전: 빌리고자 하는 책의 ISBN과 빌리고자 하는 사람의 UserID를 전달. 빌리고자 하는 책의 예약이 없거나 전달된 사람의 예약일 것.
* @후: 책을 대출
* @반환: 대출에 성공하면 true, 실패하면 false를 반환
**/
int LibraryManager::BorrowBook(std::string isbn, int id)
{
	BorrowInfo newBorrow;

	BookInfo curBook;
	BookInfo* pCurBook = std::addressof(curBook);
	curBook.SetISBN(isbn);
	mBooks.GetPointer(pCurBook);

	UserInfo curUser;
	UserInfo* pCurUser = std::addressof(curUser);
	curUser.SetID(id);
	mUsers.GetPointer(pCurUser);

	TimeForm curPenalty = pCurUser->GetUserPenalty();
	char curNBorrow = pCurUser->GetUserNBorrow();

	if (pCurBook->GetNumReservation() >= 1) 
		// 현재 책을 빌린 사람이 있는지, 예약한 사람이 있는지 확인
	{
		pCurBook->GetCurrentBorrowInfo(newBorrow);
		if (newBorrow.GetUserInfo()->GetUserID() != id)
			// 예약한 사람이 있고, 현재 대출하려고 하는 사람이 예약한 사람이 아니다.
		{
			return 2;
		}
		else
		{
			// 현재 대출하려는 사람이 예약한 사람이다.
			pCurUser->SetUserNBorrow(curNBorrow + 1);
			pCurUser->SetUserNReserve(pCurUser->GetUserNReserve() - 1); // 예약했던 게 대출로 전환됐으니 예약수는 -1
			pCurBook->SetBorrowCurrentInfo();
			pCurBook->GetCurrentBorrowInfo(newBorrow); // 대출로 전환된 정보를 다시 newBorrow에 받아온다.
			mBorrows.InsertItem(newBorrow);
			return 1;
		}
	}

	newBorrow.SetBookInfo(pCurBook);
	newBorrow.SetUserInfo(pCurUser);
	newBorrow.SetBorrowDate();

	if (curPenalty > Application::mProgramTime || curNBorrow >= mPossBorrowNum)
	{
		return 3;
	}
	else
	{
		pCurUser->SetUserNBorrow(curNBorrow + 1);
		mBorrows.InsertItem(newBorrow);
		return 1;
	}
}

/**
* @전: 빌리고자 하는 책의 ISBN과 빌리고자 하는 사람의 UserID를 전달. 빌리고자 하는 책의 예약이 꽉 차있거나 이미 예약큐에 들어있지 않을 것. 몇 번째 예약인지를 반환받을 int 변수
* @후: 책 대출을 예약
* @반환: 대출에 성공하면 true, 실패하면 false를 반환
**/

int LibraryManager::ReserveBook(std::string isbn, int id, int& borrowedNum)
{

	BookInfo curBook;
	BookInfo* pCurBook = std::addressof(curBook);
	curBook.SetISBN(isbn);
	mBooks.GetPointer(pCurBook);

	UserInfo curUser;
	UserInfo* pCurUser = std::addressof(curUser);
	curUser.SetID(id);
	mUsers.GetPointer(pCurUser);

	TimeForm curPenalty = pCurUser->GetUserPenalty();
	char curNReserve = pCurUser->GetUserNReserve();

	BorrowInfo newBorrow;
	newBorrow.SetBookInfo(pCurBook);
	newBorrow.SetUserInfo(pCurUser);
	newBorrow.SetBorrowDate();


	if (!pCurBook->IsFullReservation())
	{
		return 2;
	}
	if (curPenalty > Application::mProgramTime || curNReserve >= mPossResNum)
	{
		return 3;
	}

	// 앞서서 아무 문제 없었을 때 예약 프로세스 진행
	curUser.SetUserNBorrow(curNReserve + 1);
	pCurBook->EnQueueBorrowed(newBorrow);
	borrowedNum = pCurBook->GetNumReservation();
	return 1;
}

/**
* @전 : 반납하고자 하는 책의 ISBN과 반납하고자 하는 사람의 User ID를 전달
* @후 : 책을 반납
* @반환 : 반납에 성공하면 true. 책이 연체되었을 경우 연체되었다는 메세지를 출력하고, 해당 사람의 penalty를 연체날짜만큼 추가
*/
int LibraryManager::ReturnBook(std::string isbn, int id, BorrowInfo& retInfo, BorrowInfo& resInfo)
{
	BookInfo curBook;
	BookInfo* pCurBook = std::addressof(curBook);
	curBook.SetISBN(isbn);
	mBooks.GetPointer(pCurBook);

	UserInfo curUser;
	UserInfo* pCurUser = std::addressof(curUser);
	curUser.SetID(id);
	mUsers.GetPointer(pCurUser);

	char curNBorrow = pCurUser->GetUserNBorrow();

	BorrowInfo ret;

	pCurBook->GetCurrentBorrowInfo(ret);
	if (ret.IsBorrowing() && ret.GetUserInfo()->GetUserID() != id)
		// 반납하려는 정보가 올바른 정보인지 확인
	{
		return 5;
	}

	// 반납에 따른 자료구조 처리
	int result = mBorrows.Delete(ret);
	if (result == 0)
		return 5;
	result = pCurBook->DeQueueBorrowed(ret);
	if (result == 0)
		return 5;
	pCurUser->SetUserNBorrow(pCurUser->GetUserNBorrow() - 1);
	//

	retInfo = ret;

	bool reserved = false;
	if (pCurBook->GetNumReservation() > 0)
		// 예약 정보가 있다면
	{
		pCurBook->SetDateCurrentInfo();
		BorrowInfo t;
		pCurBook->GetCurrentBorrowInfo(t);
		mReservedTop.InsertItem(t);
		resInfo = t;
		reserved = true;
	}

	bool delayed = false;
	if (Application::mProgramTime > (ret.GetBorrowDate().timeStamp() + TimeForm::ONEDAY * mBorrowDay))
		// 연체가 발생했다면
	{
		int delayDay = (Application::mProgramTime - (ret.GetBorrowDate() + TimeForm::ONEDAY * mBorrowDay)) / TimeForm::ONEDAY;
		pCurUser->SetUserPenalty(Application::mProgramTime + delayDay * TimeForm::ONEDAY);
		delayed = true;
	}

	if (reserved == false)
	{
		if (delayed == false)
			return 1;
		else
			return 2;
	}
	else
	{
		if (delayed == false)
			return 3;
		else
			return 4;
	}
}

/**
* @전: 연체된 대출이 존재할 것
* @후: 연체된 대출을 출력
**/
void LibraryManager::DisplayDelayedBooks()
{
	BorrowInfo dummy;
	mBorrows.ResetList();
	int length = mBorrows.GetLength();
	BookInfo curbook;
	UserInfo curuser;

	for (int i = 0; i < length; i++)
	{
		mBorrows.GetNextItem(dummy);
		cout<<"Borrowed Date	:	" << dummy.GetBorrowDate();
		cout << "Book Info	:	" << endl;
		curbook = dummy.GetBookInfo();
		curbook.DisplayBookInfo();
		cout << "User Info	:	" << endl;
		curuser = dummy.GetUserInfo();
		curuser.DisplayUserInfo();
	}
}

/**
* @전: 추가할 UserInfo 객체의 포인터를 전달한다.
* @후: UserInfo 객체가 시스템에 추가된다.
**/
void LibraryManager::AddUser(UserInfo user)
{
	user.SetID(mNextUserId);
	mUsers.Add(user);
	mUserNum++;
}

/**
* @전: 검색할 문자열을 string 형태로 전달받는다. 사용자 정보를 반환받을 LinkedList<UserInfo> 객체를 전달한다.
* @후: 사용자 정보를 LinkedList에 추가한다
* @반환: 검색된 사용자가 있다면 true, 없다면 false를 반환
**/
bool LibraryManager::SearchUserWithString(std::string search, LinkedList<UserInfo>& searchList)
{
	UserInfo dummy;
	int length = mUsers.GetLength();

	string name, address, id, number;
	bool found = false;

	for (int i = 0; i < length; i++)
	{
		dummy = mUsers[i];
		name = dummy.GetUserName();
		address = dummy.GetUserAddress();
		id = to_string(dummy.GetUserID());
		number = to_string(dummy.GetUserNumber());

		if (name.find(search) == string::npos)
			if (address.find(search) == string::npos)
				if (id.find(search) == string::npos)
					if (number.find(search) == string::npos)
						break;

		found = true;
		searchList.Add(dummy);
	}

	if (found)
		return true;
	else
		return false;
}

/**
* @전: 찾을 사용자의 ID를 전달받는다. 사용자 정보를 반환받을 UserInfo 객체를 전달한다.
* @후: 사용자 정보를 찾으면 UserInfo 객체에 넣는다
* @반환: 검색된 사용자가 있다면 true, 없다면 false를 반환
**/
bool LibraryManager::SearchUserById(int id, UserInfo& user)
{
	UserInfo temp;
	temp.SetID(id);

	if (mUsers.GetItem(temp))
	{
		user = temp;
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
	temp.SetID(id);

	if (mUsers.Delete(temp))
	{
		mUserNum--;
		return true;
	}
	else
		return false;
}