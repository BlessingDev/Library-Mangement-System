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
* @?? ì´ˆê¸°?”ëœ Book ë¦¬ìŠ¤?? ì¶”ê???BookInfo ê°ì²´
* @?? ì±?ì¶”ê?
**/
void LibraryManager::AddBook(BookInfo book)
{
	mBooks.Add(book);
	mBookNum++;
}

/**
* @?? ì´ˆê¸°?”ëœ Book ë¦¬ìŠ¤?? ê²€?‰í•  ë¬¸ìž??
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
* @?? ê²€?‰í•  ë¬¸ìž?´ì„ string ?•íƒœë¡??„ë‹¬ë°›ëŠ”?? ì±??•ë³´ë¥?ë°˜í™˜ë°›ì„ LinkedList<BookInfo> ê°ì²´ë¥??„ë‹¬?œë‹¤.
* @?? ëª¨ë“  ë¬¸ìž???ì„±???€???µí•© ê²€?‰ì„ ?˜í–‰?˜ê³ , ê²€?‰ì— ?±ê³µ?˜ë©´ ê²€?‰ëœ ì±…ì˜ ?•ë³´ë¥?LinkedList??Add?œë‹¤
* @ë°˜í™˜: ê²€?‰ëœ ì±…ì´ ??ê¶Œì´?¼ë„ ?ˆë‹¤ë©?true, ?†ë‹¤ë©?falseë¥?ë°˜í™˜
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

		if (isbn.find(search) == string::npos)
			if (author.find(search) == string::npos)
				if (publisher.find(search) == string::npos)
					if (title.find(search) == string::npos)
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
* @?? ë¹Œë¦¬ê³ ìž ?˜ëŠ” ì±…ì˜ ISBNê³?ë¹Œë¦¬ê³ ìž ?˜ëŠ” ?¬ëžŒ??UserIDë¥??„ë‹¬. ë¹Œë¦¬ê³ ìž ?˜ëŠ” ì±…ì˜ ?ˆì•½???†ê±°???„ë‹¬???¬ëžŒ???ˆì•½??ê²?
* @?? ì±…ì„ ?€ì¶?
* @ë°˜í™˜: ?€ì¶œì— ?±ê³µ?˜ë©´ true, ?¤íŒ¨?˜ë©´ falseë¥?ë°˜í™˜
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
		// í˜„ìž¬ ì±…ì„ ë¹Œë¦° ì‚¬ëžŒì´ ìžˆëŠ”ì§€, ì˜ˆì•½í•œ ì‚¬ëžŒì´ ìžˆëŠ”ì§€ í™•ì¸
	{
		pCurBook->GetCurrentBorrowInfo(newBorrow);
		if (newBorrow.GetUserInfo()->GetUserID() != id)
			// ì˜ˆì•½í•œ ì‚¬ëžŒì´ ìžˆê³ , í˜„ìž¬ ëŒ€ì¶œí•˜ë ¤ê³  í•˜ëŠ” ì‚¬ëžŒì´ ì˜ˆì•½í•œ ì‚¬ëžŒì´ ì•„ë‹ˆë‹¤.
		{
			return 2;
		}
		else
		{
			// í˜„ìž¬ ëŒ€ì¶œí•˜ë ¤ëŠ” ì‚¬ëžŒì´ ì˜ˆì•½í•œ ì‚¬ëžŒì´ë‹¤.
			pCurUser->SetUserNBorrow(curNBorrow + 1);
			pCurUser->SetUserNReserve(pCurUser->GetUserNReserve() - 1); // ì˜ˆì•½í–ˆë˜ ê²Œ ëŒ€ì¶œë¡œ ì „í™˜ëìœ¼ë‹ˆ ì˜ˆì•½ìˆ˜ëŠ” -1
			pCurBook->SetBorrowCurrentInfo();
			pCurBook->GetCurrentBorrowInfo(newBorrow); // ëŒ€ì¶œë¡œ ì „í™˜ëœ ì •ë³´ë¥¼ ë‹¤ì‹œ newBorrowì— ë°›ì•„ì˜¨ë‹¤.
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
* @?? ë¹Œë¦¬ê³ ìž ?˜ëŠ” ì±…ì˜ ISBNê³?ë¹Œë¦¬ê³ ìž ?˜ëŠ” ?¬ëžŒ??UserIDë¥??„ë‹¬. ë¹Œë¦¬ê³ ìž ?˜ëŠ” ì±…ì˜ ?ˆì•½??ê½?ì°¨ìžˆê±°ë‚˜ ?´ë? ?ˆì•½?ì— ?¤ì–´?ˆì? ?Šì„ ê²? ëª?ë²ˆì§¸ ?ˆì•½?¸ì?ë¥?ë°˜í™˜ë°›ì„ int ë³€??
* @?? ì±??€ì¶œì„ ?ˆì•½
* @ë°˜í™˜: ?€ì¶œì— ?±ê³µ?˜ë©´ true, ?¤íŒ¨?˜ë©´ falseë¥?ë°˜í™˜
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

	// ì•žì„œì„œ ì•„ë¬´ ë¬¸ì œ ì—†ì—ˆì„ ë•Œ ì˜ˆì•½ í”„ë¡œì„¸ìŠ¤ ì§„í–‰
	curUser.SetUserNBorrow(curNReserve + 1);
	pCurBook->EnQueueBorrowed(newBorrow);
	borrowedNum = pCurBook->GetNumReservation();
	return 1;
}

/**
* @??: ë°˜ë‚©?˜ê³ ???˜ëŠ” ì±…ì˜ ISBNê³?ë°˜ë‚©?˜ê³ ???˜ëŠ” ?¬ëžŒ??User IDë¥??„ë‹¬
* @??: ì±…ì„ ë°˜ë‚©
* @ë°˜í™˜ : ë°˜ë‚©???±ê³µ?˜ë©´ true. ì±…ì´ ?°ì²´?˜ì—ˆ??ê²½ìš° ?°ì²´?˜ì—ˆ?¤ëŠ” ë©”ì„¸ì§€ë¥?ì¶œë ¥?˜ê³ , ?´ë‹¹ ?¬ëžŒ??penaltyë¥??°ì²´? ì§œë§Œí¼ ì¶”ê?
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
		// ë°˜ë‚©í•˜ë ¤ëŠ” ì •ë³´ê°€ ì˜¬ë°”ë¥¸ ì •ë³´ì¸ì§€ í™•ì¸
	{
		return 5;
	}

	// ë°˜ë‚©ì— ë”°ë¥¸ ìžë£Œêµ¬ì¡° ì²˜ë¦¬
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
		// ì˜ˆì•½ ì •ë³´ê°€ ìžˆë‹¤ë©´
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
		// ì—°ì²´ê°€ ë°œìƒí–ˆë‹¤ë©´
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
* @?? ?°ì²´???€ì¶œì´ ì¡´ìž¬??ê²?
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
* @?? ê²€?‰í•  ë¬¸ìž?´ì„ string ?•íƒœë¡??„ë‹¬ë°›ëŠ”?? ?¬ìš©???•ë³´ë¥?ë°˜í™˜ë°›ì„ LinkedList<UserInfo> ê°ì²´ë¥??„ë‹¬?œë‹¤.
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
//		cout << "ìž˜ëª»ëœ Attribute" << endl;
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
//		cout << "ìž˜ëª»ëœ Attribute"<<endl;
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
