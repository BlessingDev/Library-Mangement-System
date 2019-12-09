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
* @전:
* @후: 하루가 지날 때 일어나야하는 계산을 실행합니다.
**/
void LibraryManager::AddBook(BookInfo book)
{
	mBooks.Add(book);
	mBookNum++;
}


void LibraryManager::AddBookFromWeb(std::string)
{

}


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
	bool delayed = mDelayedBorrows.Get(ret);

	if (!delayed)
	{
		int result = mBorrows.Delete(ret);
		if (result == 0)
			return 5;
	}
	else
		// 연체가 발생했다면
	{
		int delayDay = (Application::mProgramTime.timeStamp() - (ret.GetBorrowDate() + TimeForm::ONEDAY * mBorrowDay)) / TimeForm::ONEDAY;
		pCurUser->SetUserPenalty(Application::mProgramTime.timeStamp() + delayDay * TimeForm::ONEDAY);
		mDelayedBorrows.Delete(ret);
		delayed = true;
	}
	int result = pCurBook->DeQueueBorrowed(ret);
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


void LibraryManager::DisplayDelayedBooks()
{
	BorrowInfo dummy;
	mDelayedBorrows.ResetList();
	int length = mDelayedBorrows.GetLength();
	BookInfo* curbook;
	UserInfo* curuser;

	for (int i = 0; i < length; i++)
	{
		mDelayedBorrows.GetNextItem(dummy);
		dummy.DisplayInfo();
	}
}

void LibraryManager::DisplayBooks()
{
	for (int i = 0; i < mBookNum; ++i)
	{
		mBooks[i].DisplayBookInfo();
		std::cout << "------" << std::endl;
	}
}

void LibraryManager::AddUser(UserInfo user)
{
	user.SetID(mNextUserId);
	mUsers.Add(user);
	mUserNum++;
}


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

void LibraryManager::DisplayUser()
{
	for (int i = 0; i < mUserNum; ++i)
	{
		mUsers[i].DisplayUserInfo();
	}
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
		return false;
	}
}

bool LibraryManager::ImportBookInfo()
{
	ifstream fin;
	try
	{
		fin.open("BookInfo_in.txt");
		char achar;
		std::string astr;
		int flag = 0;
		BookInfo dummy;
		
		while (fin.get(achar))
		{

			if (achar == '\n') continue;

			if (achar == ',') //딜리미터 
			{
				switch (flag)
				{
				case(0):
					dummy.SetAuthor(astr);
					astr.clear();
					flag++;
					continue;

				case(1):
					dummy.SetPublisher(astr);
					astr.clear();
					flag++;
					continue;

				case(2):
					dummy.SetTitle(astr);
					astr.clear();
					flag++;
					continue;

				case(3):
					dummy.SetISBN(astr);
					astr.clear();
					flag++;
					continue;

				case(4):
					int num = stoi(astr);
					dummy.SetCategoryNum(num);
					mBooks.Add(dummy);
					astr.clear();
					flag = 0;
					continue;
				}
			}
			else 	astr += achar;
		}
		return true;
	}
	catch (exception)
	{
		return false;
	}
}

bool LibraryManager::ImportUserInfo()
{
	ifstream fin;
	try 
	{
		fin.open("UserInfo_in.txt");
		char achar;
		std::string astr;
		int flag = 0;
		UserInfo dummy;

		while (fin.get(achar))
		{

			if (achar == '\n') continue;

			if (achar == ',') //딜리미터 
			{
				switch (flag)
				{
				case(0):
					dummy.SetUserID(astr);
					astr.clear();
					flag++;
					continue;

				case(1):
					dummy.SetUserName(astr);
					astr.clear();
					flag++;
					continue;

				case(2):
					dummy.SetUserAddress(astr);
					astr.clear();
					flag++;
					continue;

				case(3):
					int num = stoi(astr);
					dummy.SetUserNumber(num);
					mUsers.Add(dummy);
					astr.clear();
					flag++;
					continue;
				}
			}
			else 	astr += achar;
		}
		return true;
	}

	catch (exception)
	{
		return false;
	}
}

bool LibraryManager::ExportBookInfo()
{
	BookInfo dummy;
	ofstream fout;
	try
	{
		fout.open("BookInfo_out.txt");
		for (int i = 0; i < mBooks.GetLength(); i++)
		{
			dummy = mBooks[0];
			fout << dummy.GetAuthor<<"," << dummy.GetPublisher << ","<< dummy.GetTitle << ","<<dummy.GetISBN<< "," << dummy.GetCategoryNum<<endl;
		}
		return true;
	}
	catch (exception)
	{
		return false;
	}
}

bool LibraryManager::ExportUserInfo()
{
	UserInfo dummy;
	ofstream fout;
	try
	{
		fout.open("UserInfo_out.txt");
		for (int i = 0; i < mBooks.GetLength(); i++)
		{
			dummy = mUsers[0];
			fout << dummy.GetUserID << "," << dummy.GetUserName<< "," << dummy.GetUserAddress << "," << dummy.GetUserNumber << endl;
		}
		return true;
	}
	catch (exception)
	{
		return false;
	}
}


void LibraryManager::DayPassed(LinkedList<BorrowInfo>& delayedList, LinkedList<BorrowInfo>& expiredResList)
{
	int length = mBorrows.GetLength();
	mBorrows.ResetList();
	for (int i = 0; i < length; ++i)
	{
		BorrowInfo t;
		mBorrows.GetNextItem(t);

		if (TimeForm(t.GetBorrowDate().timeStamp() + TimeForm::ONEDAY * mBorrowDay) < Application::mProgramTime)
		{
			mDelayedBorrows.Add(t);
			mBorrows.Delete(t);
			delayedList.Add(t);
		}
		else
		{
			// Sorted된 리스트이기 때문에 연체되지 않았다면 그 밑으로는 연체된 대출이 없다.
			break;
		}
	}

	mReservedTop.ResetList();
	length = mReservedTop.GetLength();
	for (int i = 0; i < length; ++i)
	{
		BorrowInfo t;
		mReservedTop.GetNextItem(t);

		// 예약 유효기간 7일
		if (TimeForm(t.GetBorrowDate().timeStamp() + TimeForm::ONEDAY * 7) < Application::mProgramTime)
		{
			mReservedTop.Delete(t);
			auto pCurBook = t.GetBookInfo();
			pCurBook->DeQueueBorrowed(t);
			if (pCurBook->GetNumReservation() > 0)
				// 예약 정보가 있다면
			{
				BorrowInfo nextInfo;
				pCurBook->SetDateCurrentInfo();
				pCurBook->GetCurrentBorrowInfo(nextInfo);
				mReservedTop.InsertItem(nextInfo);
			}
			// 예약 만료를 출력하고, 다음 예약을 출력하는 작업이 필요
			expiredResList.Add(t);
		}
		else
		{
			break;
		}
	}
}

void SPVToBST(SortedPointerVector<BookInfo>& SPV, BinarySearchTree<BookInfo>& BST)
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