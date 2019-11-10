#pragma once
#include <string>

#include "LinkedList.h"
#include "SortedLinkedList.hpp"

class LibraryManager
{
private:
	LinkedList<UserInfo*> mUsers;
	LinkedList<BookInfo*> mBooks;
	SortedLinkedList<BorrowInfo*> mBorrows;
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
	* @��ȯ: ���⿡ �����ϸ� true, �����ϸ� false�� ��ȯ
	**/
	bool BorrowBook(std::string, std::string);

	/**
	* @��: �������� �ϴ� å�� ISBN�� �������� �ϴ� ����� UserID�� ����. �������� �ϴ� å�� ������ �� ���ְų� �̹� ����ť�� ������� ���� ��. �� ��° ���������� ��ȯ���� int ����
	* @��: å ������ ����
	* @��ȯ: ���⿡ �����ϸ� true, �����ϸ� false�� ��ȯ
	**/
	bool ReserveBook(std::string, std::string, int&);

	/**
	* @��: ��ü�� ����
	* @��: ��ü�� ������ ���
	**/
	void DisplayDelayedBooks();
};