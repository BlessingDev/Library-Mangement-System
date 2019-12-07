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
* @?? ์ด๊ธฐ?๋ Book ๋ฆฌ์ค?? ์ถ๊???BookInfo ๊ฐ์ฒด
* @?? ์ฑ?์ถ๊?
**/
void LibraryManager::AddBook(BookInfo book)
{
	mBooks.Add(book);
	mBookNum++;
}

/**
* @?? ์ด๊ธฐ?๋ Book ๋ฆฌ์ค?? ๊ฒ?ํ  ๋ฌธ์??
* @?? ์ฑ?์ถ๊?
**/
void LibraryManager::AddBookFromWeb(std::string)
{

}

/**
* @?? Book List???ด๋น ์ฑ์ด ?ค์ด?์ ๊ฒ? ์ฑ์ ISBN???๊ณ  ?์ ๊ฒ?
* @?? ?๋ ฅ??ISBN???ด๋น?๋ ์ฑ์ ?? 
* @๋ฐํ: ์ฑ??? ???ฑ๊ณต?๋ฉด true, ?คํจ?๋ฉด false๋ฅ?๋ฐํ
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
* @?? ๊ฒ?ํ  isbn??string ?ํ๋ก??๋ฌ๋ฐ๋?? ์ฑ??๋ณด๋ฅ?๋ฐํ๋ฐ์ BookInfo ๊ฐ์ฒด๋ฅ??๋ฌ?๋ค.
* @?? ISBN ๊ฒ?์ ?ํ?๊ณ , ๊ฒ?์ ?ฑ๊ณต?๋ฉด ๊ฒ?๋ ์ฑ์ ?๋ณด BookInfo& ๊ฐ์ฒด??์ง์ด?ฃ๋??
* @๋ฐํ: ์ฑ?๊ฒ?์ ?ฑ๊ณต?๋ฉด true, ?คํจ?๋ฉด false๋ฅ?๋ฐํ
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
* @?? ๊ฒ?ํ  ๋ฌธ์?ด์ string ?ํ๋ก??๋ฌ๋ฐ๋?? ์ฑ??๋ณด๋ฅ?๋ฐํ๋ฐ์ LinkedList<BookInfo> ๊ฐ์ฒด๋ฅ??๋ฌ?๋ค.
* @?? ๋ชจ๋  ๋ฌธ์???์ฑ??????ตํฉ ๊ฒ?์ ?ํ?๊ณ , ๊ฒ?์ ?ฑ๊ณต?๋ฉด ๊ฒ?๋ ์ฑ์ ?๋ณด๋ฅ?LinkedList??Add?๋ค
* @๋ฐํ: ๊ฒ?๋ ์ฑ์ด ??๊ถ์ด?ผ๋ ?๋ค๋ฉ?true, ?๋ค๋ฉ?false๋ฅ?๋ฐํ
**/
bool LibraryManager::SearchBookWithString(std::string search, LinkedList<BookInfo>& searchList, BookInfo& book)
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
		book = dummy;
		searchList.Add(dummy);
	}

	if (found)
		return true;
	else
		return false;
}

/**
* @?? ๋น๋ฆฌ๊ณ ์ ?๋ ์ฑ์ ISBN๊ณ?๋น๋ฆฌ๊ณ ์ ?๋ ?ฌ๋??UserID๋ฅ??๋ฌ. ๋น๋ฆฌ๊ณ ์ ?๋ ์ฑ์ ?์ฝ???๊ฑฐ???๋ฌ???ฌ๋???์ฝ??๊ฒ?
* @?? ์ฑ์ ?์ถ?
* @๋ฐํ: ?์ถ์ ?ฑ๊ณต?๋ฉด true, ?คํจ?๋ฉด false๋ฅ?๋ฐํ
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
* @?? ๋น๋ฆฌ๊ณ ์ ?๋ ์ฑ์ ISBN๊ณ?๋น๋ฆฌ๊ณ ์ ?๋ ?ฌ๋??UserID๋ฅ??๋ฌ. ๋น๋ฆฌ๊ณ ์ ?๋ ์ฑ์ ?์ฝ??๊ฝ?์ฐจ์๊ฑฐ๋ ?ด๋? ?์ฝ?์ ?ค์ด?์? ?์ ๊ฒ? ๋ช?๋ฒ์งธ ?์ฝ?ธ์?๋ฅ?๋ฐํ๋ฐ์ int ๋ณ??
* @?? ์ฑ??์ถ์ ?์ฝ
* @๋ฐํ: ?์ถ์ ?ฑ๊ณต?๋ฉด true, ?คํจ?๋ฉด false๋ฅ?๋ฐํ
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
* @??: ๋ฐ๋ฉ?๊ณ ???๋ ์ฑ์ ISBN๊ณ?๋ฐ๋ฉ?๊ณ ???๋ ?ฌ๋??User ID๋ฅ??๋ฌ
* @??: ์ฑ์ ๋ฐ๋ฉ
* @๋ฐํ : ๋ฐ๋ฉ???ฑ๊ณต?๋ฉด true. ์ฑ์ด ?ฐ์ฒด?์??๊ฒฝ์ฐ ?ฐ์ฒด?์?ค๋ ๋ฉ์ธ์ง๋ฅ?์ถ๋ ฅ?๊ณ , ?ด๋น ?ฌ๋??penalty๋ฅ??ฐ์ฒด? ์ง๋งํผ ์ถ๊?
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

	if (/*?ฐ์ฒด?์????*/)
	{
		//?ค๋? ์ง๊ณ์ฐ?จ์?
	}
	else
	{
		for (int i = 0; i < length; i++)
		{
			mBorrows.GetNextItem(newReturn);
			returnbook = newReturn.GetBookInfo();//?ผ๋จ isbn?ผ๋ก ?ค์ 
			if (returnbook == curBook)
			{
				mBorrows.Delete(newReturn);
			}
		}
	}
}

/**
* @?? ?ฐ์ฒด???์ถ์ด ์กด์ฌ??๊ฒ?
* @?? ?ฐ์ฒด???์ถ์ ์ถ๋ ฅ
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
* @?? ์ถ๊???UserInfo ๊ฐ์ฒด???ฌ์ธ?ฐ๋? ?๋ฌ?๋ค.
* @?? UserInfo ๊ฐ์ฒด๊ฐ ?์ค?์ ์ถ๊??๋ค.
**/
void LibraryManager::AddUser(UserInfo user)
{
	user.SetID(mNextUserId);
	mUsers.Add(user);
	mUserNum++;
}

/**
* @?? ๊ฒ?ํ  ๋ฌธ์?ด์ string ?ํ๋ก??๋ฌ๋ฐ๋?? ?ฌ์ฉ???๋ณด๋ฅ?๋ฐํ๋ฐ์ LinkedList<UserInfo> ๊ฐ์ฒด๋ฅ??๋ฌ?๋ค.
* @?? ?ฌ์ฉ???๋ณด๋ฅ?LinkedList??์ถ๊??๋ค
* @๋ฐํ: ๊ฒ?๋ ?ฌ์ฉ?๊? ?๋ค๋ฉ?true, ?๋ค๋ฉ?false๋ฅ?๋ฐํ
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
* @?? ์ฐพ์ ?ฌ์ฉ?์ ID๋ฅ??๋ฌ๋ฐ๋?? ?ฌ์ฉ???๋ณด๋ฅ?๋ฐํ๋ฐ์ UserInfo ๊ฐ์ฒด๋ฅ??๋ฌ?๋ค.
* @?? ?ฌ์ฉ???๋ณด๋ฅ?์ฐพ์ผ๋ฉ?UserInfo ๊ฐ์ฒด???ฃ๋??
* @๋ฐํ: ๊ฒ?๋ ?ฌ์ฉ?๊? ?๋ค๋ฉ?true, ?๋ค๋ฉ?false๋ฅ?๋ฐํ
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
* @?? ?๊ฑฐ???ฌ์ฉ?์ ID๋ฅ??๋ฌ๋ฐ๋??
* @?? ?ฌ์ฉ???๋ณด๋ฅ?์ฐพ์ผ๋ฉ??์ค?์???? ?๋ค
* @๋ฐํ: ?? ???ฑ๊ณต?๋ฉด true, ?คํจ?๋ฉด false๋ฅ?๋ฐํ
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
//		cout << "์๋ชป๋ Attribute" << endl;
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
//		cout << "์๋ชป๋ Attribute"<<endl;
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
