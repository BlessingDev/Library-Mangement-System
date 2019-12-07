#include "LibraryManager.h"

LibraryManager::LibraryManager()
{
	mBookNum = 0;
	mUserNum = 0;
	mNextUserId = -1;
	mBorrowDay = 14;
	mPossBorrowNum = 5;
}

LibraryManager::~LibraryManager(){}
/**
* @?? 초기?�된 Book 리스?? 추�???BookInfo 객체
* @?? �?추�?
**/
void LibraryManager::AddBook(BookInfo book)
{
	mBooks.Add(book);
	mBookNum++;
}

/**
* @?? 초기?�된 Book 리스?? 검?�할 문자??
* @?? �?추�?
**/
void LibraryManager::AddBookFromWeb(std::string)
{

}

/**
* @?? Book List???�당 책이 ?�어?�을 �? 책의 ISBN???�고 ?�을 �?
* @?? ?�력??ISBN???�당?�는 책을 ??��
* @반환: �???��???�공?�면 true, ?�패?�면 false�?반환
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
* @?? 검?�할 isbn??string ?�태�??�달받는?? �??�보�?반환받을 BookInfo 객체�??�달?�다.
* @?? ISBN 검?�을 ?�행?�고, 검?�에 ?�공?�면 검?�된 책의 ?�보 BookInfo& 객체??집어?�는??
* @반환: �?검?�에 ?�공?�면 true, ?�패?�면 false�?반환
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
* @?? 검?�할 문자?�을 string ?�태�??�달받는?? �??�보�?반환받을 LinkedList<BookInfo> 객체�??�달?�다.
* @?? 모든 문자???�성???�???�합 검?�을 ?�행?�고, 검?�에 ?�공?�면 검?�된 책의 ?�보�?LinkedList??Add?�다
* @반환: 검?�된 책이 ??권이?�도 ?�다�?true, ?�다�?false�?반환
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

		if (isbn.find(search) == string:npos)
			if (author.find(search) == string:npos)
				if (publisher.find(search) == string:npos)
					if (title.find(search) == string:npos)
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
* @?? 빌리고자 ?�는 책의 ISBN�?빌리고자 ?�는 ?�람??UserID�??�달. 빌리고자 ?�는 책의 ?�약???�거???�달???�람???�약??�?
* @?? 책을 ?��?
* @반환: ?�출에 ?�공?�면 true, ?�패?�면 false�?반환
**/
bool LibraryManager::BorrowBook(std::string isbn, int id)
{
	UserInfo curUser;
	curUser.SetID(id);
	mUsers.GetItem(curUser);

	char curPenalty = curUser.GetUserPenalty();
	char curNBorrow = curUser.GetUserNBorrow();

	BookInfo curBook;
	curBook.SetISBN(isbn);
	mBooks.GetItem(curBook);

	BorrowInfo newBorrow;
	newBorrow.SetBookInfo(curBook);
	newBorrow.SetUserInfo(curUser);
	newBorrow.SetBorrowedDate();

	if (curPenalty>0 || curNBorrow<=0)
	{
		cout << "Borrow Failed";
		return false;
	}
	else
	{
		curUser.SetUserNBorrow(--curNBorrow);
		mBorrows.InsertItem(newBorrow);
		return true;
	}
}

/**
* @?? 빌리고자 ?�는 책의 ISBN�?빌리고자 ?�는 ?�람??UserID�??�달. 빌리고자 ?�는 책의 ?�약??�?차있거나 ?��? ?�약?�에 ?�어?��? ?�을 �? �?번째 ?�약?��?�?반환받을 int 변??
* @?? �??�출을 ?�약
* @반환: ?�출에 ?�공?�면 true, ?�패?�면 false�?반환
**/

bool LibraryManager::ReserveBook(std::string isbn, int id, int& borrowedNum)
{
	UserInfo curUser;
	curUser.SetID(id);
	mUsers.Get(curUser);

	char curNBorrow = curUser.GetUserNBorrow();

	BookInfo curBook;
	curBook.SetISBN(isbn);
	mBooks.Get(curBook);

	BorrowInfo newBorrow;
	newBorrow.SetBookInfo(const curBook);
	newBorrow.SetUserInfo(const curUser);
	newBorrow.SetBorrowedDate();

	try
	{
		curUser.SetUserNBorrow(--curNBorrow);
		curBook.EnQueueBorrowed(newBorrow);
		borrowedNum = curBook.GetNumReservation()
		return true;
	}
	catch
	{
		return false;
	}
}

/**
* @??: 반납?�고???�는 책의 ISBN�?반납?�고???�는 ?�람??User ID�??�달
* @??: 책을 반납
* @반환 : 반납???�공?�면 true. 책이 ?�체?�었??경우 ?�체?�었?�는 메세지�?출력?�고, ?�당 ?�람??penalty�??�체?�짜만큼 추�?
*/
bool LibraryManager::ReturnBook(std::string isbn, int id)
{
	UserInfo curUser;
	curUser.SetID(id);
	mUsers.GetItem(curUser);

	char curPenalty = curUser.GetUserPenalty();
	char curNBorrow = curUser.GetUserNBorrow();

	BookInfo curBook;
	curBook.SetISBN(isbn);
	mBooks.Get(curBook);

	BorrowInfo newReturn;
	BookInfo returnbook;

	int length = mBorrows.GetLength();

	if (/*?�체?�었????/)
	{
		//?�늘?�짜계산?�수?
	}
	else
	{
		for (int i = 0; i < length; i++)
		{
			mBorrows.GetNextItem(newReturn);
			returnbook = newReturn.GetBookInfo();//?�단 isbn?�로 ?�정
			if (returnbook == curBook)
			{
				mBorrows.Delete(newReturn);
			}
		}
	}
}

/**
* @?? ?�체???�출이 존재??�?
* @?? ?�체???�출을 출력
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
		cout<<"Borrowed Date	:	"<<dummy.GetBorrowedDate();
		cout << "Book Info	:	" << endl;
		curbook = dummy.GetBookInfo();
		curbook.DisplayBookInfo();
		cout << "User Info	:	" << endl;
		curuser = dummy.GetUserInfo();
		curuser.DisplayUserInfo();
	}
}

/**
* @?? 추�???UserInfo 객체???�인?��? ?�달?�다.
* @?? UserInfo 객체가 ?�스?�에 추�??�다.
**/
void LibraryManager::AddUser(UserInfo user)
{
	user.SetID(mNextUserId);
	mUsers.Add(user);
	mUserNum++;
}

/**
* @?? 검?�할 문자?�을 string ?�태�??�달받는?? ?�용???�보�?반환받을 LinkedList<UserInfo> 객체�??�달?�다.
* @?? ?�용???�보�?LinkedList??추�??�다
* @반환: 검?�된 ?�용?��? ?�다�?true, ?�다�?false�?반환
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

		if (name.find(search) == string:npos)
			if (address.find(search == string:npos))
				if (id.find(search == string:npos))
					if (number.find(search) == string:npos)
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
* @?? 찾을 ?�용?�의 ID�??�달받는?? ?�용???�보�?반환받을 UserInfo 객체�??�달?�다.
* @?? ?�용???�보�?찾으�?UserInfo 객체???�는??
* @반환: 검?�된 ?�용?��? ?�다�?true, ?�다�?false�?반환
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
* @?? ?�거???�용?�의 ID�??�달받는??
* @?? ?�용???�보�?찾으�??�스?�에????��?�다
* @반환: ??��???�공?�면 true, ?�패?�면 false�?반환
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