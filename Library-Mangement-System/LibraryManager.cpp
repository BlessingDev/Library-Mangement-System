#include "LibraryManager.h"

/**
* @��: �ʱ�ȭ�� Book ����Ʈ, �߰��� BookInfo ��ü
* @��: å �߰�
**/
void LibraryManager::AddBook(BookInfo* book)
{
	mBooks.Add(book);
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
* @��: �˻��� isbn�� string ���·� ���޹޴´�. å ������ ��ȯ���� BookInfo ��ü�� �����Ѵ�.
* @��: ISBN �˻��� �����ϰ�, �˻��� �����ϸ� �˻��� å�� ���� BookInfo& ��ü�� ����ִ´�.
* @��ȯ: å �˻��� �����ϸ� true, �����ϸ� false�� ��ȯ
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
* @��: �˻��� ���ڿ��� string ���·� ���޹޴´�. å ������ ��ȯ���� LinkedList<BookInfo> ��ü�� �����Ѵ�.
* @��: ��� ���ڿ� �Ӽ��� ���� ���� �˻��� �����ϰ�, �˻��� �����ϸ� �˻��� å�� ������ LinkedList�� Add�Ѵ�
* @��ȯ: �˻��� å�� �� ���̶� �ִٸ� true, ���ٸ� false�� ��ȯ
**/
bool LibraryManager::SearchBookWithString(std::string search, LinkedList<BookInfo>& searchList)
{

}

/**
* @��: �������� �ϴ� å�� ISBN�� �������� �ϴ� ����� UserID�� ����. �������� �ϴ� å�� ������ ���ų� ���޵� ����� ������ ��.
* @��: å�� ����
* @��ȯ: ���⿡ �����ϸ� true, �����ϸ� false�� ��ȯ
**/
bool LibraryManager::BorrowBook(std::string, std::string)
{

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
* @��: ��ü�� ������ ������ ��
* @��: ��ü�� ������ ���
**/
void LibraryManager::DisplayDelayedBooks()
{
	BorrowInfo* dummy;

	mBorrows.ResetList();
	int length = mBorrows.GetLength();

	for (int i = 0; i < length; i++)
	{
		mBorrows.GetNextItem(dummy);
		//��ü�� ���⿡ ���� � ���� ���?
	}

}

/**
* @��: �߰��� UserInfo ��ü�� �����͸� �����Ѵ�.
* @��: UserInfo ��ü�� �ý��ۿ� �߰��ȴ�.
**/
void LibraryManager::AddUser(UserInfo* user)
{
	mUsers.Add(user);
}

/**
* @��: �˻��� ���ڿ��� string ���·� ���޹޴´�. ����� ������ ��ȯ���� LinkedList<UserInfo> ��ü�� �����Ѵ�.
* @��: ����� ������ LinkedList�� �߰��Ѵ�
* @��ȯ: �˻��� ����ڰ� �ִٸ� true, ���ٸ� false�� ��ȯ
**/
bool LibraryManager::SearchUserWithString(std::string, LinkedList<UserInfo>&)
{

}

/**
* @��: ã�� ������� ID�� ���޹޴´�. ����� ������ ��ȯ���� UserInfo ��ü�� �����Ѵ�.
* @��: ����� ������ ã���� UserInfo ��ü�� �ִ´�
* @��ȯ: �˻��� ����ڰ� �ִٸ� true, ���ٸ� false�� ��ȯ
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
* @��: ������ ������� ID�� ���޹޴´�.
* @��: ����� ������ ã���� �ý��ۿ��� �����Ѵ�
* @��ȯ: ������ �����ϸ� true, �����ϸ� false�� ��ȯ
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