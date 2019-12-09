#include "Application.h"

TimeForm Application::mProgramTime = TimeForm();

Application::Application()
{
	m_Command = 0;
	m_Mode = 0;
}


void Application::Run()
{
	while (1)
	{
		m_Mode = GetMode();

		switch (m_Mode)
		{
		case 1:
		{
			m_Command = GetBookCommand();

			switch (m_Command)
			{
			case 1:
				AddBook();
				break;
			case 2:
				DeleteBook();
				break;
			case 3:
				SearchBook();
				break;
			case 4:
				BorrowBook();
				break;
			case 5:
				ReserveBook();
				break;
			case 6:
				ReturnBook();
				break;
			case 7:
				DisplayDelayedBook();
				break;
			case 8:
				DisplayBookList();
				break;
			case 0:
				return;
			default:
				cout << "\t�߸��� �Է��Դϴ�...\n";
				break;
			}
		}

		case 2:
			m_Command = GetUserCommand();
			switch (m_Command)
			{
			case 1:
				AddUser();
				break;
			case 2:
				DeleteUser();
				break;
			case 3:
				SearchUser();
				break;
			case 4:
				DisplayUserList();
				break;
			case 0:
				return;
			default:
				cout << "\t�߸��� �Է��Դϴ�...\n";
				break;
			}
		case 3:
			DayPassed();
		}
	}
}

int GetMode()
{
	int mode;
	cout << endl << endl;
	cout << "\t---ID -- Select Mode ----- " << endl;
	cout << "\t   1 : ���� ����" << endl;
	cout << "\t   2 : �̿��� ����" << endl;
	cout << "\t   3 : ��¥ ����" << endl;
	cout << "\t   0 : ����" << endl;

	cout << endl << "\t Choose a Mode--> ";
	cin >> mode;
	cout << endl;

	return mode;
}

int GetBookCommand()
{
	int command;
	cout << endl << endl;
	cout << "\t---ID -- Command ----- " << endl;
	cout << "\t   1 : ���� �߰�" << endl;
	cout << "\t   2 : ���� ����" << endl;
	cout << "\t   3 : ���� �˻�" << endl;
	cout << "\t   4 : ���� �뿩" << endl;
	cout << "\t   5 : ���� ����" << endl;
	cout << "\t   6 : ���� �ݳ�" << endl;
	cout << "\t   7 : ��ü���� ���" << endl;
	cout << "\t   8 : ��ü���� ���" << endl;
	cout << "\t   0 : Quit" << endl;

	cout << endl << "\t Choose a Command--> ";
	cin >> command;
	cout << endl;

	return command;
}

int GetUserCommand()
{
	int command;
	cout << endl << endl;
	cout << "\t---ID -- Command ----- " << endl;
	cout << "\t   1 : �̿��� �߰�" << endl;
	cout << "\t   2 : �̿��� ����" << endl;
	cout << "\t   3 : �̿��� �˻�" << endl;
	cout << "\t   4 : ��ü�̿��� ���" << endl;
	cout << "\t   0 : Quit" << endl;

	cout << endl << "\t Choose a Command--> ";
	cin >> command;
	cout << endl;

	return command;
}


int Application::AddBook()
{
	BookInfo newbook;
	newbook.SetBookInfoByKB();

	mLibraryManager.AddBook(newbook);

	return 1;
}


int Application::DeleteBook()
{
	string isbn;
	cout << "������ å�� ISBN �Է�	:	";
	cin >> isbn;

	if (mLibraryManager.DeleteBook(isbn))
	{
		cout << "���� ����";
		return 1;
	}
	else
	{
		cout << "���� ����";
		return 0;
	}
}


int Application::BorrowBook()
{
	string isbn;
	int id;
	cout << "����� ID �Է�	:	";
	cin >> id;
	cout << "ISBN �Է�	:	";
	cin >> isbn;

	switch (mLibraryManager.BorrowBook(isbn, id))
	{
	case 1:
		cout << "���⿡ �����߽��ϴ�";
		break;
	case 2:
		cout << "���� ����! ���� ������ ����� �����մϴ�";
		break;
	case 3:
		cout << "���� �Ұ�! �г�Ƽ�� �����ϰų� �ִ� ����Ǽ��� �ʰ��Ͽ����ϴ�";
		break;
	default:
		return 0;
	}
	return 1;
}


int Application::ReserveBook()
{
	string isbn;
	int id;
	int nReserve = 0;

	cout << "����� ID �Է�	:	";
	cin >> id;
	cout << "ISBN	:	";
	cin >> isbn;
	
	switch (mLibraryManager.ReserveBook(isbn, id, nReserve))
	{
	case 1:
		cout << "���࿡ �����Ͽ����ϴ�";
		break;
	case 2:
		cout << "���� ����! �����ο��� �ʰ��Ͽ����ϴ�";
		break;
	case 3:
		cout << "���� �Ұ�! �г�Ƽ�� �����ϰų� �ִ� ����Ǽ��� �ʰ��Ͽ����ϴ�";
		break;
	default:
		return 0;
	}
	return 1;
}

int Application::ReturnBook()
{
	string isbn;
	int id;
	BorrowInfo retInfo;
	BorrowInfo resInfo;

	cout << "�ݳ��ϰ��� �ϴ� �̿����� ID�� �Է��ϼ���	:	";
	cin >> id;
	cout << "�ݳ��ϰ��� �ϴ� å�� ISBN�� �Է��ϼ���	:	";
	cin >> isbn;

	UserInfo* next;
	switch (mLibraryManager.ReturnBook(isbn, id, retInfo, resInfo))
	{
	case 1:
		cout << "�ݳ� ����";
		break;
	case 2:
		cout << "�ݳ� ����! ���� ��ü�� ���� �г�Ƽ�� �ο��˴ϴ�";
		break;
	case 3:
		cout << "�ݳ� ����!" << endl;
		next = resInfo.GetUserInfo();
		cout << "���� ������ ����	:	";
		(*next).DisplayUserInfo();
		break;
	case 4:
		cout << "�ݳ� ����! ���� ��ü�� ���� �г�Ƽ�� �ο��˴ϴ�" << endl;
		next = resInfo.GetUserInfo();
		cout << "���� ������ ����	:	";
		(*next).DisplayUserInfo();
		break;
	case 5:
		cout << "�ݳ�����";
		break;
	default:
		return 0;
	}
	return 1;
}

int Application::DisplayDelayedBook()
{
	mLibraryManager.DisplayDelayedBooks();

	return 1;
}

int Application::DisplayBookList()
{
	mLibraryManager.DisplayBooks();
	return 1;
}

int Application::DisplayUserList()
{
	mLibraryManager.DisplayUser();
	return 1;
}

int Application::SearchBook()
{
	int command;
	cout << endl << endl;
	cout << "\t---ID -- Command ----- " << endl;
	cout << "\t   1 : ISBN �˻�" << endl;
	cout << "\t   2 : ���� �˻�" << endl;
	cout << "\t   3 : �Ӽ� �˻�" << endl;
	cin >> command;

	LinkedList<BookInfo> searchList;
	BookInfo curbook;
	int check;

	switch (command)
	{
	case 1:
		check=SearchBookWithISBN(curbook);
		break;
	case 2:
		check = SearchBookWithString(curbook, searchList);
		break;
	case 3:
		check = SearchBookWithAttribute(curbook);
		break;
	default:				
		cout << "\t�߸��� �Է��Դϴ�...\n";
		return 0;
	}

	if (!check)
	{
		cout << "�˻� ����";
		return 0;
	}
	else
		return 1;
}

int Application::SearchBookWithISBN(BookInfo& curbook)
{
	string isbn;
	cout << "�˻��� å�� ISBN�� �Է��ϼ���	:	";
	cin >> isbn;
	if (mLibraryManager.SearchBookWithIsbn(isbn, curbook))
	{
		curbook.DisplayBookInfo();
		return 1;
	}
	else
		return 0;
}

int Application::SearchBookWithString(BookInfo& curbook, LinkedList<BookInfo>& searchList)
{
	string search;
	cout << "�˻��� ������ �Է��ϼ���	:	";
	cin >> search;
	if (mLibraryManager.SearchBookWithString(search, searchList))
	{
		BookInfo dummy;
		searchList.ResetList();
		int index = searchList.GetNextItem(dummy);
		while (index)
		{
			dummy.DisplayBookInfo();
			index = searchList.GetNextItem(dummy);
		}
		return 1;
	}
	else
		return 0;
}

int Application::SearchBookWithAttribute(BookInfo& curbook)
{
	string search;
	string attribute;
	cout << "�˻� ����� �Է��ϼ���" << endl;
	cout << "\t   Author	:	�۰� �˻�" << endl;
	cout << "\t   Publisher	:	���ǻ� �˻�" << endl;
	cout << "\t   Title		:	���� �˻�" << endl;
	cout << "\t   ISBN		:	ISBN �˻�" << endl;
	cin >> attribute;

	cout << "�˻� ������ �Է��ϼ���	:	";
	cin >> search;

	if (mLibraryManager.SearchBookWithAttribute(search, curbook, attribute))
	{
		curbook.DisplayBookInfo();
		return 1;
	}
	else
		return 0;
}

int Application::AddUser()
{
	UserInfo user;
	mLibraryManager.AddUser(user);
	return 1;
}

int Application::SearchUser()
{
	int command;
	cout << endl << endl;
	cout << "\t---ID -- Command ----- " << endl;
	cout << "\t   1 : ID �˻�" << endl;
	cout << "\t   2 : ���� �˻�" << endl;
	cin >> command;

	UserInfo curUser;
	UserInfo dummy;
	LinkedList<UserInfo> searchList;
	string search;
	bool check;
	int id;
	int index;

	switch (command)
	{
	case 1:
		cout << "�˻��� ID�� �Է��ϼ���	:	";
		cin >> id;
		check = mLibraryManager.SearchUserById(id, curUser);
		curUser.DisplayUserInfo();
		break;
	case 2:
		cout << "�˻� ������ �Է��ϼ���	:	";
		cin >> search;
		check = mLibraryManager.SearchUserWithString(search, searchList);

		searchList.ResetList();
		index = searchList.GetNextItem(dummy);
		while (index)
		{
			dummy.DisplayUserInfo();
			index = searchList.GetNextItem(dummy);
		}
	default:
		cout << "\t�߸��� �Է��Դϴ�...\n";
		return 0;
	}

	if (!check)
	{
		cout << "�˻� ����";
		return 0;
	}
	else
		return 1;
}

int Application::DeleteUser()
{
	int id;
	cout << "\t������ ID�� �Է��ϼ���	:	";
	cin >> id;
	if (mLibraryManager.DeleteUser(id) == true)
	{
		cout << "\t���� ����" << endl;
		return 1;
	}
	else
	{
		cout << "\t���� ����" << endl;
		return 0;
	}
}

void Application::DayPassed()
{
	int time = 1;
	cout << "���� �ѱ�ðڽ��ϱ�? : ";
	cin >> time;
	mProgramTime = mProgramTime.timeStamp() + TimeForm::ONEDAY * time;

	LinkedList<BorrowInfo> delayed;
	LinkedList<BorrowInfo> expired;
	mLibraryManager.DayPassed(delayed, expired);

	std::cout << "������ ������ ��ü�Ǿ����ϴ�." << std::endl;
	delayed.ResetList();
	int length = delayed.GetLength();
	for (int i = 0; i < length; ++i)
	{
		BorrowInfo t;
		delayed.GetNextItem(t);
		t.DisplayInfo();
		std::cout << "----------" << std::endl;
	}
	std::cout << std::endl << std::endl;
	std::cout << "������ ������ ����Ǿ����ϴ�." << std::endl;
	expired.ResetList();
	length = expired.GetLength();
	for (int i = 0; i < length; ++i)
	{
		BorrowInfo t;
		expired.GetNextItem(t);
		t.DisplayInfo();
		std::cout << "-----" << std::endl;
		std::cout << "�� å�� ���� ���� �������Դϴ�." << std::endl;
		t.GetBookInfo()->GetCurrentBorrowInfo(t);
		t.DisplayInfo();
		std::cout << "----------" << std::endl;
	}
	std::cout << std::endl << std::endl;
}