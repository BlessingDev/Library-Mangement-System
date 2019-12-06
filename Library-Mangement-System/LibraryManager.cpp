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
* @전: 빌리고자 하는 책의 ISBN과 빌리고자 하는 사람의 UserID를 전달. 빌리고자 하는 책의 예약이 없거나 전달된 사람의 예약일 것.
* @후: 책을 대출
* @반환: 대출에 성공하면 true, 실패하면 false를 반환
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
* @전: 빌리고자 하는 책의 ISBN과 빌리고자 하는 사람의 UserID를 전달. 빌리고자 하는 책의 예약이 꽉 차있거나 이미 예약큐에 들어있지 않을 것. 몇 번째 예약인지를 반환받을 int 변수
* @후: 책 대출을 예약
* @반환: 대출에 성공하면 true, 실패하면 false를 반환
**/

bool LibraryManager::ReserveBook(std::string isbn, std::string id, int& borrowedNum)
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
* @전 : 반납하고자 하는 책의 ISBN과 반납하고자 하는 사람의 User ID를 전달
* @후 : 책을 반납
* @반환 : 반납에 성공하면 true. 책이 연체되었을 경우 연체되었다는 메세지를 출력하고, 해당 사람의 penalty를 연체날짜만큼 추가
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

	if (/*연체되었을 때*/)
	{
		//오늘날짜계산함수?
	}
	else
	{
		for (int i = 0; i < length; i++)
		{
			mBorrows.GetNextItem(newReturn);
			returnbook = newReturn.GetBookInfo();//일단 isbn으로 설정
			if (returnbook == curBook)
			{
				mBorrows.Delete(newReturn);
			}
		}
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

bool LibraryManager::SearchBookWithAttribute(string search, BookInfo& book, string attribute)
{
	BookInfo dummy;

	//Author, Publisher, Title, ISBN
	if (attribute == "Author")
	{
		dummy.SetAuthor(search);
		BinarySearchTree<BookInfo> BST(CompByAuthor);
		SPVToBST(mBooks, BST);
		if (BST.GetItem(dummy))
		{
			book = dummy;
			return true;
		}
		return false;
	}

	else if (attribute == "Publisher")
	{
		dummy.SetPublisher(search);
		BinarySearchTree<BookInfo> BST(CompByPublisher);
		SPVToBST(mBooks, BST);
		if (BST.GetItem(dummy))
		{
			book = dummy;
			return true;
		}
		return false;
	}

	else if (attribute == "Title")
	{
		dummy.SetTitle(search);
		BinarySearchTree<BookInfo> BST(CompByTitle);
		SPVToBST(mBooks, BST);
		if (BST.GetItem(dummy))
		{
			book = dummy;
			return true;
		}
		return false;
	}
	else if (attribute == "ISBN")
	{
		dummy.SetISBN(search);
		BinarySearchTree<BookInfo> BST(CompByISBN);
		SPVToBST(mBooks, BST);
		if (BST.GetItem(dummy))
		{
			book = dummy;
			return true;
		}
		return false;
	}
	else
	{
//		cout << "잘못된 Attribute" << endl;
		return false;
	}
}


bool LibraryManager::SearchBookWithAttribute(int search, BookInfo& book, string attribute)
{
	BookInfo dummy;

	if (attribute == "CategoryNum")
	{
		dummy.SetCategoryNum(search);
		BinarySearchTree<BookInfo> BST(CompByAuthor);
		SPVToBST(mBooks, BST);
		if (BST.GetItem(dummy))
		{
			book = dummy;
			return true;
		}
		return false;
	}
	else
	{ 
//		cout << "잘못된 Attribute"<<endl;
		return false;
	}
}


void LibraryManager::SPVToBST(SortedPointerVector<BookInfo>& SPV, BinarySearchTree<BookInfo>& BST)
{
	for (int i = 0; i < SPV.GetLength(); i++)
	{
		BST.Insert(SPV[i]);
	}
}


//Compare Function
RelationType CompByAuthor(BookInfo myBook, BookInfo other)
{
	if (myBook.GetAuthor() == other.GetAuthor())
		return RelationType::EQUAL;
	else if (myBook.GetAuthor() > other.GetAuthor())
		return RelationType::GREATER;
	else
		return RelationType::LESS;
}

RelationType CompByISBN(BookInfo myBook, BookInfo other)
{
	if (myBook.GetISBN() == other.GetISBN())
		return RelationType::EQUAL;
	else if (myBook.GetISBN() > other.GetISBN())
		return RelationType::GREATER;
	else
		return RelationType::LESS;
}

RelationType CompByTitle(BookInfo myBook, BookInfo other)
{
	if (myBook.GetTitle() == other.GetTitle())
		return RelationType::EQUAL;
	else if (myBook.GetTitle() > other.GetTitle())
		return RelationType::GREATER;
	else
		return RelationType::LESS;
}

RelationType CompByPublisher(BookInfo myBook, BookInfo other)
{
	if (myBook.GetPublisher() == other.GetPublisher())
		return RelationType::EQUAL;
	else if (myBook.GetPublisher() > other.GetPublisher())
		return RelationType::GREATER;
	else
		return RelationType::LESS;
}

RelationType CompByCategoryNum(BookInfo myBook, BookInfo other)
{
	if (myBook.GetCategoryNum() == other.GetCategoryNum())
		return RelationType::EQUAL;
	else if (myBook.GetCategoryNum() > other.GetCategoryNum())
		return RelationType::GREATER;
	else
		return RelationType::LESS;
}
