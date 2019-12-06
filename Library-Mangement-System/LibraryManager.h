#pragma once
#include <string>

#include "LinkedList.h"
#include "SortedLinkedList.hpp"
#include "SortedPointerVector.hpp"

#include "UserInfo.h"
#include "BookInfo.h"
#include "BorrowInfo.h"

class LibraryManager
{
private:

	SortedPointerVector<UserInfo> mUsers;
	SortedPointerVector<BookInfo> mBooks;
	SortedLinkedList<BorrowInfo> mBorrows;
	int mBookNum;
	int mUserNum;
	int mNextUserId;	// ������ �߰��Ǵ� ����ڿ��� �ο��� ID
	int mBorrowDay;		// ���� �Ⱓ
	int mPossBorrowNum;	// �� ����� �ִ� ���� ������ �Ǽ�

public:

	LibraryManager();

	~LibraryManager();

	/**
	* @��: �ʱ�ȭ�� Book ����Ʈ, �߰��� BookInfo ��ü
	* @��: å �߰�
	**/
	void AddBook(BookInfo);

	/**
	* @��: �ʱ�ȭ�� Book ����Ʈ, �˻��� ���ڿ�
	* @��: å �߰�
	**/
	void AddBookFromWeb(std::string);

	/**
	* @��: Book List�� �ش� å�� ������� ��, å�� ISBN�� �˰� ���� ��
	* @��: �Էµ� ISBN�� �ش��ϴ� å�� ����
	* @��ȯ: å ������ �����ϸ� true, �����ϸ� false�� ��ȯ
	**/
	bool DeleteBook(std::string);

	/**
	* @��: �˻��� isbn�� string ���·� ���޹޴´�. å ������ ��ȯ���� BookInfo ��ü�� �����Ѵ�.
	* @��: ISBN �˻��� �����ϰ�, �˻��� �����ϸ� �˻��� å�� ���� BookInfo& ��ü�� ����ִ´�.
	* @��ȯ: å �˻��� �����ϸ� true, �����ϸ� false�� ��ȯ
	**/
	bool SearchBookWithIsbn(std::string, BookInfo&);

	/**
	* @��: �˻��� ���ڿ��� string ���·� ���޹޴´�. å ������ ��ȯ���� LinkedList<BookInfo> ��ü�� �����Ѵ�.
	* @��: ��� ���ڿ� �Ӽ��� ���� ���� �˻��� �����ϰ�, �˻��� �����ϸ� �˻��� å�� ������ LinkedList�� Add�Ѵ�
	* @��ȯ: �˻��� å�� �� ���̶� �ִٸ� true, ���ٸ� false�� ��ȯ
	**/
	bool SearchBookWithString(std::string, LinkedList<BookInfo>&);

	/**
	* @��: �������� �ϴ� å�� ISBN�� �������� �ϴ� ����� UserID�� ����. �������� �ϴ� å�� ������ ���ų� ���޵� ����� ������ ��.
	* @��: å�� ����
	* @��ȯ: ���⿡ �����ϸ� true, �����ϸ� false�� ��ȯ. å�� �������� �ϴ� ����� penalty, nbook�� Ȯ���ϰ� ���ǿ� ���� �ʴ´ٸ� �������
	**/
	bool BorrowBook(std::string, int);

	/**
	* @��: �������� �ϴ� å�� ISBN�� �������� �ϴ� ����� UserID�� ����. �������� �ϴ� å�� ������ �� ���ְų� �̹� ����ť�� ������� ���� ��. �� ��° ���������� ��ȯ���� int ����
	* @��: å ������ ����
	* @��ȯ: ���⿡ �����ϸ� true, �����ϸ� false�� ��ȯ
	**/
	bool ReserveBook(std::string, std::string, int&);

	/**
	* @�� : �ݳ��ϰ��� �ϴ� å�� ISBN�� �ݳ��ϰ��� �ϴ� ����� User ID�� ����
	* @�� : å�� �ݳ�
	* @��ȯ : �ݳ��� �����ϸ� true. å�� ��ü�Ǿ��� ��� ��ü�Ǿ��ٴ� �޼����� ����ϰ�, �ش� ����� penalty�� ��ü��¥��ŭ �߰�
	*/
	bool ReturnBook(std::string, int);

	/**
	* @��: ��ü�� ������ ������ ��
	* @��: ��ü�� ������ ���
	**/
	void DisplayDelayedBooks();

	/**
	* @��: �߰��� UserInfo ��ü�� �����͸� �����Ѵ�.
	* @��: UserInfo ��ü�� �ý��ۿ� �߰��ȴ�.
	**/
	void AddUser(UserInfo);

	/**
	* @��: �˻��� ���ڿ��� string ���·� ���޹޴´�. ����� ������ ��ȯ���� LinkedList<UserInfo> ��ü�� �����Ѵ�.
	* @��: ����� ������ LinkedList�� �߰��Ѵ�
	* @��ȯ: �˻��� ����ڰ� �ִٸ� true, ���ٸ� false�� ��ȯ
	**/
	bool SearchUserWithString(std::string, LinkedList<UserInfo>&);

	/**
	* @��: ã�� ������� ID�� ���޹޴´�. ����� ������ ��ȯ���� UserInfo ��ü�� �����Ѵ�.
	* @��: ����� ������ ã���� UserInfo ��ü�� �ִ´�
	* @��ȯ: �˻��� ����ڰ� �ִٸ� true, ���ٸ� false�� ��ȯ
	**/
	bool SearchUserById(int, UserInfo&);

	/**
	* @��: ������ ������� ID�� ���޹޴´�.
	* @��: ����� ������ ã���� �ý��ۿ��� �����Ѵ�
	* @��ȯ: ������ �����ϸ� true, �����ϸ� false�� ��ȯ
	**/
	bool DeleteUser(int);
};