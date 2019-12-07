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
* @?? ì´ˆê¸°?”ëœ Book ë¦¬ìŠ¤?? ì¶”ê???BookInfo ê°ì²´
* @?? ì±?ì¶”ê?
**/
void LibraryManager::AddBook(BookInfo book)
{
	mBooks.Add(book);
	mBookNum++;
}

/**
* @?? ì´ˆê¸°?”ëœ Book ë¦¬ìŠ¤?? ê²€?‰í•  ë¬¸ì??
* @?? ì±?ì¶”ê?
**/
void LibraryManager::AddBookFromWeb(std::string)
{

}

/**
* @?? Book List???´ë‹¹ ì±…ì´ ?¤ì–´?ˆì„ ê²? ì±…ì˜ ISBN???Œê³  ?ˆì„ ê²?
* @?? ?…ë ¥??ISBN???´ë‹¹?˜ëŠ” ì±…ì„ ?? œ
* @ë°˜í™˜: ì±??? œ???±ê³µ?˜ë©´ true, ?¤íŒ¨?˜ë©´ falseë¥?ë°˜í™˜
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
* @?? ê²€?‰í•  isbn??string ?•íƒœë¡??„ë‹¬ë°›ëŠ”?? ì±??•ë³´ë¥?ë°˜í™˜ë°›ì„ BookInfo ê°ì²´ë¥??„ë‹¬?œë‹¤.
* @?? ISBN ê²€?‰ì„ ?˜í–‰?˜ê³ , ê²€?‰ì— ?±ê³µ?˜ë©´ ê²€?‰ëœ ì±…ì˜ ?•ë³´ BookInfo& ê°ì²´??ì§‘ì–´?£ëŠ”??
* @ë°˜í™˜: ì±?ê²€?‰ì— ?±ê³µ?˜ë©´ true, ?¤íŒ¨?˜ë©´ falseë¥?ë°˜í™˜
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
* @?? ê²€?‰í•  ë¬¸ì?´ì„ string ?•íƒœë¡??„ë‹¬ë°›ëŠ”?? ì±??•ë³´ë¥?ë°˜í™˜ë°›ì„ LinkedList<BookInfo> ê°ì²´ë¥??„ë‹¬?œë‹¤.
* @?? ëª¨ë“  ë¬¸ì???ì„±???€???µí•© ê²€?‰ì„ ?˜í–‰?˜ê³ , ê²€?‰ì— ?±ê³µ?˜ë©´ ê²€?‰ëœ ì±…ì˜ ?•ë³´ë¥?LinkedList??Add?œë‹¤
* @ë°˜í™˜: ê²€?‰ëœ ì±…ì´ ??ê¶Œì´?¼ë„ ?ˆë‹¤ë©?true, ?†ë‹¤ë©?falseë¥?ë°˜í™˜
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
* @?? ë¹Œë¦¬ê³ ì ?˜ëŠ” ì±…ì˜ ISBNê³?ë¹Œë¦¬ê³ ì ?˜ëŠ” ?¬ëŒ??UserIDë¥??„ë‹¬. ë¹Œë¦¬ê³ ì ?˜ëŠ” ì±…ì˜ ?ˆì•½???†ê±°???„ë‹¬???¬ëŒ???ˆì•½??ê²?
* @?? ì±…ì„ ?€ì¶?
* @ë°˜í™˜: ?€ì¶œì— ?±ê³µ?˜ë©´ true, ?¤íŒ¨?˜ë©´ falseë¥?ë°˜í™˜
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
* @?? ë¹Œë¦¬ê³ ì ?˜ëŠ” ì±…ì˜ ISBNê³?ë¹Œë¦¬ê³ ì ?˜ëŠ” ?¬ëŒ??UserIDë¥??„ë‹¬. ë¹Œë¦¬ê³ ì ?˜ëŠ” ì±…ì˜ ?ˆì•½??ê½?ì°¨ìˆê±°ë‚˜ ?´ë? ?ˆì•½?ì— ?¤ì–´?ˆì? ?Šì„ ê²? ëª?ë²ˆì§¸ ?ˆì•½?¸ì?ë¥?ë°˜í™˜ë°›ì„ int ë³€??
* @?? ì±??€ì¶œì„ ?ˆì•½
* @ë°˜í™˜: ?€ì¶œì— ?±ê³µ?˜ë©´ true, ?¤íŒ¨?˜ë©´ falseë¥?ë°˜í™˜
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
* @??: ë°˜ë‚©?˜ê³ ???˜ëŠ” ì±…ì˜ ISBNê³?ë°˜ë‚©?˜ê³ ???˜ëŠ” ?¬ëŒ??User IDë¥??„ë‹¬
* @??: ì±…ì„ ë°˜ë‚©
* @ë°˜í™˜ : ë°˜ë‚©???±ê³µ?˜ë©´ true. ì±…ì´ ?°ì²´?˜ì—ˆ??ê²½ìš° ?°ì²´?˜ì—ˆ?¤ëŠ” ë©”ì„¸ì§€ë¥?ì¶œë ¥?˜ê³ , ?´ë‹¹ ?¬ëŒ??penaltyë¥??°ì²´? ì§œë§Œí¼ ì¶”ê?
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

	if (/*?°ì²´?˜ì—ˆ????/)
	{
		//?¤ëŠ˜? ì§œê³„ì‚°?¨ìˆ˜?
	}
	else
	{
		for (int i = 0; i < length; i++)
		{
			mBorrows.GetNextItem(newReturn);
			returnbook = newReturn.GetBookInfo();//?¼ë‹¨ isbn?¼ë¡œ ?¤ì •
			if (returnbook == curBook)
			{
				mBorrows.Delete(newReturn);
			}
		}
	}
}

/**
* @?? ?°ì²´???€ì¶œì´ ì¡´ì¬??ê²?
* @?? ?°ì²´???€ì¶œì„ ì¶œë ¥
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
* @?? ì¶”ê???UserInfo ê°ì²´???¬ì¸?°ë? ?„ë‹¬?œë‹¤.
* @?? UserInfo ê°ì²´ê°€ ?œìŠ¤?œì— ì¶”ê??œë‹¤.
**/
void LibraryManager::AddUser(UserInfo user)
{
	user.SetID(mNextUserId);
	mUsers.Add(user);
	mUserNum++;
}

/**
* @?? ê²€?‰í•  ë¬¸ì?´ì„ string ?•íƒœë¡??„ë‹¬ë°›ëŠ”?? ?¬ìš©???•ë³´ë¥?ë°˜í™˜ë°›ì„ LinkedList<UserInfo> ê°ì²´ë¥??„ë‹¬?œë‹¤.
* @?? ?¬ìš©???•ë³´ë¥?LinkedList??ì¶”ê??œë‹¤
* @ë°˜í™˜: ê²€?‰ëœ ?¬ìš©?ê? ?ˆë‹¤ë©?true, ?†ë‹¤ë©?falseë¥?ë°˜í™˜
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
* @?? ì°¾ì„ ?¬ìš©?ì˜ IDë¥??„ë‹¬ë°›ëŠ”?? ?¬ìš©???•ë³´ë¥?ë°˜í™˜ë°›ì„ UserInfo ê°ì²´ë¥??„ë‹¬?œë‹¤.
* @?? ?¬ìš©???•ë³´ë¥?ì°¾ìœ¼ë©?UserInfo ê°ì²´???£ëŠ”??
* @ë°˜í™˜: ê²€?‰ëœ ?¬ìš©?ê? ?ˆë‹¤ë©?true, ?†ë‹¤ë©?falseë¥?ë°˜í™˜
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
* @?? ?œê±°???¬ìš©?ì˜ IDë¥??„ë‹¬ë°›ëŠ”??
* @?? ?¬ìš©???•ë³´ë¥?ì°¾ìœ¼ë©??œìŠ¤?œì—???? œ?œë‹¤
* @ë°˜í™˜: ?? œ???±ê³µ?˜ë©´ true, ?¤íŒ¨?˜ë©´ falseë¥?ë°˜í™˜
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