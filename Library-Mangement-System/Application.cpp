#include "Application.h"

Application()
{
	m_Command = 0;
	m_Mode = 0;
}


void Run()
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
				ReturnBook();//�����ʿ�
				break;
			case 7:
				DisplayDelayedBook();//�����ʿ�
				break;
			case 0:
				return;
			default:
				cout << "\t�߸��?�Է��Դϴ�...\n";
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
			case 0:
				return;
			default:
				cout << "\t�߸��?�Է��Դϴ�...\n";
				break;
			}
		case 3:
			DayPassed();
		}
}

int GetMode()
{
	int mode;
	cout << endl << endl;
	cout << "\t---ID -- Select Mode ----- " << endl;
	cout << "\t   1 : ���� ��" << endl;
	cout << "\t   2 : �̿��� ��" << endl;
	cout << "\t   3 : ��¥ ��" << endl;
	cout << "\t   0 : ���" << endl;

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
	cout << "\t   2 : ���� ���" << endl;
	cout << "\t   3 : ���� �˻�" << endl;
	cout << "\t   4 : ���� �뿩" << endl;
	cout << "\t   5 : ���� ����" << endl;
	cout << "\t   6 : ���� �ݳ�" << endl;
	cout << "\t   7 : ��ü���� ���" << endl;
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
	cout << "\t   2 : �̿��� ���" << endl;
	cout << "\t   3 : �̿��� �˻�" << endl;
	cout << "\t   0 : Quit" << endl;

	cout << endl << "\t Choose a Command--> ";
	cin >> command;
	cout << endl;

	return command;
}


void ShowMenu(std::string)
{

}


int AddBook()
{
	BookInfo newbook;
	newbook.SetBookInfoByKB();

	LibraryManager.AddBook(newbook);

	return 1;
}


int DeleteBook()
{
	string isbn;
	cout << "�����?å�� ISBN �Է�	:	";
	cin >> isbn;

	if (LibraryManager.DeleteBook(isbn))
	{
		cout << "���?����";
		return 1;
	}
	else
	{
		cout << "���?����";
		return 0;
	}
}


int BorrowBook()
{
	string isbn;
	int id;
	cout << "�����?ID �Է�	:	";
	cin >> id;
	cout << "ISBN �Է�	:	";
	cin >> isbn;

	if (LibraryManager.BorrowBook(isbn, id))
	{
		cout << "�뿩 ����";
		return 1;
	}
	else
	{
		cout << "�뿩 ����";
		return 0;
	}
}


int ReserveBook()
{
	string isbn;
	string id;
	int nReserve = 0;

	cout << "�����?ID �Է�	:	";
	cin >> id;
	cout << "ISBN	:	";
	cin >> isbn;
	
	//����ó���� �� ���̽� �з� �ʿ�
	if (LibraryManager.ReserveBook(isbn, id, nReserve))
	{
		cout << "���� ����" << endl;
		cout << "���� ���?" << nReserve << "��° �Դϴ�";
		return 1;
	}
	else
	{
		cout << "���� ����! �����ο��?�ʰ��߽�ϴ�?" << endl;
	}
}

int Application::ReturnBook()
{
	string isbn;
	int id;
	if (LibraryManager.ReturnBook(isbn, id))
		return 1;
	else
	{
		cout << "�ݳ� ����! ������ ��ü�Ǿ��ϴ�" << endl;
	}
}

int Application::DisplayDelayedBook()
{
	LibraryManager.DispalyDelayedBooks();
}

void Application::SearchBook()
{
	LinkedList<BookInfo> searchList;
	BookInfo book;
	string search;
	cout << "\tSearch book by (ISBN, Title, Author, Publisher): ";
	cin >> search;
	if (mLibraryManager.SearchBookWithString(search, searchList, book) == true)
	{
		book.DisplayBookInfo();
	}
	else
	{
		cout << "Search failed." << endl;
	}
}

void Application::AddUser()
{
	UserInfo user;
	mLibraryManager.AddUser(user);
}

void Application::SearchUser()
{
	UserInfo user;
	int id;
	cout << "\tEnter ID : ";
	cin >> id;
	if (mLibraryManager.SearchUserById(id, user) == true)
	{
		user.DisplayUserInfo();
	}
	else
	{
		cout << "\tCould't find user with such ID." << endl;
	}
}

void Application::DeleteUser()
{
	int id;
	cout << "\tEnter ID : ";
	cin >> id;
	if (mLibraryManager.DeleteUser(id) == true)
	{
		cout << "\tUser successfully deleted!" << endl;
	}
	else
	{
		cout << "\tDelete failed." << endl;
	}
}

void Application::DayPassed()
{
	TimeForm nextDay;
	string time;
	cout << "Enter date (yyyyMMddhhmmss) : ";
	cin >> time;
	nextDay.FromString(time);
	mCurrentTime.operator+(nextDay);
}
