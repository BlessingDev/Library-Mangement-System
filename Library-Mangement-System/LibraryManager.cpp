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
* @��: �ʱ�ȭ�� Book ����Ʈ, �߰��� BookInfo ��ü
* @��: å �߰�
**/
void LibraryManager::AddBook(BookInfo book)
{
	mBooks.Add(book);
	mBookNum++;
}

/**
* @��: �ʱ�ȭ�� Book ����Ʈ, �˻��� ���ڿ�
* @��: å �߰�
**/
void LibraryManager::AddBookFromWeb(std::string)
{

}

/**
* @��: Book List�� �ش� å�� ������� ��, å�� ISBN�� �˰� ���� ��
* @��: �Էµ� ISBN�� �ش��ϴ� å�� ����
* @��ȯ: å ������ �����ϸ� true, �����ϸ� false�� ��ȯ
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
* @��: �˻��� isbn�� string ���·� ���޹޴´�. å ������ ��ȯ���� BookInfo ��ü�� �����Ѵ�.
* @��: ISBN �˻��� �����ϰ�, �˻��� �����ϸ� �˻��� å�� ���� BookInfo& ��ü�� ����ִ´�.
* @��ȯ: å �˻��� �����ϸ� true, �����ϸ� false�� ��ȯ
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
* @��: �˻��� ���ڿ��� string ���·� ���޹޴´�. å ������ ��ȯ���� LinkedList<BookInfo> ��ü�� �����Ѵ�.
* @��: ��� ���ڿ� �Ӽ��� ���� ���� �˻��� �����ϰ�, �˻��� �����ϸ� �˻��� å�� ������ LinkedList�� Add�Ѵ�
* @��ȯ: �˻��� å�� �� ���̶� �ִٸ� true, ���ٸ� false�� ��ȯ
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
		publisher = dummy.GetPublisher(); //getpublisher�Լ� �����ʿ�
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
* @��: �������� �ϴ� å�� ISBN�� �������� �ϴ� ����� UserID�� ����. �������� �ϴ� å�� ������ ���ų� ���޵� ����� ������ ��.
* @��: å�� ����
* @��ȯ: ���⿡ �����ϸ� true, �����ϸ� false�� ��ȯ
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
		//������ �ο��� ������ Ȯ���ϴ� �ڵ� �߰��ʿ�.
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
* @��: �������� �ϴ� å�� ISBN�� �������� �ϴ� ����� UserID�� ����. �������� �ϴ� å�� ������ �� ���ְų� �̹� ����ť�� ������� ���� ��. �� ��° ���������� ��ȯ���� int ����
* @��: å ������ ����
* @��ȯ: ���⿡ �����ϸ� true, �����ϸ� false�� ��ȯ
**/
bool LibraryManager::ReserveBook(std::string, std::string, int&)
{

}

/**
* @�� : �ݳ��ϰ��� �ϴ� å�� ISBN�� �ݳ��ϰ��� �ϴ� ����� User ID�� ����
* @�� : å�� �ݳ�
* @��ȯ : �ݳ��� �����ϸ� true. å�� ��ü�Ǿ��� ��� ��ü�Ǿ��ٴ� �޼����� ����ϰ�, �ش� ����� penalty�� ��ü��¥��ŭ �߰�
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
	//template type=borrowInfo�϶� Get���� ����?
	//��ü��Ȯ���ϱ� ���� ��¥������ ������ �Լ� �ʿ�.
	
}

/**
* @��: ��ü�� ������ ������ ��
* @��: ��ü�� ������ ���
**/
void LibraryManager::DisplayDelayedBooks()
{
	BorrowInfo dummy;
	mBorrows.ResetList();
	int length = mBorrows.GetLength();

	for (int i = 0; i < length; i++)
	{
		mBorrows.GetNextItem(dummy);
		cout<<"Borrowed Date	:	"<<dummy.GetBorrowedDate();
		//å�̸�, ��������� ǥ���ϴ� get�Լ� �ʿ�.
	}
}

/**
* @��: �߰��� UserInfo ��ü�� �����͸� �����Ѵ�.
* @��: UserInfo ��ü�� �ý��ۿ� �߰��ȴ�.
**/
void LibraryManager::AddUser(UserInfo user)
{
	mUsers.Add(user);
	mUserNum++;
}

/**
* @��: �˻��� ���ڿ��� string ���·� ���޹޴´�. ����� ������ ��ȯ���� LinkedList<UserInfo> ��ü�� �����Ѵ�.
* @��: ����� ������ LinkedList�� �߰��Ѵ�
* @��ȯ: �˻��� ����ڰ� �ִٸ� true, ���ٸ� false�� ��ȯ
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
* @��: ã�� ������� ID�� ���޹޴´�. ����� ������ ��ȯ���� UserInfo ��ü�� �����Ѵ�.
* @��: ����� ������ ã���� UserInfo ��ü�� �ִ´�
* @��ȯ: �˻��� ����ڰ� �ִٸ� true, ���ٸ� false�� ��ȯ
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
* @��: ������ ������� ID�� ���޹޴´�.
* @��: ����� ������ ã���� �ý��ۿ��� �����Ѵ�
* @��ȯ: ������ �����ϸ� true, �����ϸ� false�� ��ȯ
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