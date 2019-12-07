#include "Application.h"

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
			case 0:
				return;
			default:
				cout << "\t잘못된 입력입니다...\n";
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
				cout << "\t잘못된 입력입니다...\n";
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
	cout << "\t   1 : 도서 관리" << endl;
	cout << "\t   2 : 이용자 관리" << endl;
	cout << "\t   3 : 날짜 관리" << endl;
	cout << "\t   0 : 종료" << endl;

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
	cout << "\t   1 : 도서 추가" << endl;
	cout << "\t   2 : 도서 삭제" << endl;
	cout << "\t   3 : 도서 검색" << endl;
	cout << "\t   4 : 도서 대여" << endl;
	cout << "\t   5 : 도서 예약" << endl;
	cout << "\t   6 : 도서 반납" << endl;
	cout << "\t   7 : 연체도서 목록" << endl;
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
	cout << "\t   1 : 이용자 추가" << endl;
	cout << "\t   2 : 이용자 삭제" << endl;
	cout << "\t   3 : 이용자 검색" << endl;
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
	cout << "삭제할 책의 ISBN 입력	:	";
	cin >> isbn;

	if (mLibraryManager.DeleteBook(isbn))
	{
		cout << "삭제 성공";
		return 1;
	}
	else
	{
		cout << "삭제 실패";
		return 0;
	}
}


int Application::BorrowBook()
{
	string isbn;
	int id;
	cout << "사용자 ID 입력	:	";
	cin >> id;
	cout << "ISBN 입력	:	";
	cin >> isbn;

	if (mLibraryManager.BorrowBook(isbn, id))
	{
		cout << "대여 성공";
		return 1;
	}
	else
	{
		cout << "대여 성공";
		return 0;
	}
}


int Application::ReserveBook()
{
	string isbn;
	string id;
	int nReserve = 0;

	cout << "사용자 ID 입력	:	";
	cin >> id;
	cout << "ISBN	:	";
	cin >> isbn;
	
	//예외처리에 따른 케이스 분류 필요
	if (mLibraryManager.ReserveBook(isbn, id, nReserve))
	{
		cout << "예약 성공" << endl;
		cout << "예약 순위 " << nReserve << "번째 입니다";
		return 1;
	}
	else
	{
		cout << "예약 실패! 예약인원을 초과했습니다" << endl;
	}
}

int Application::ReturnBook()
{
	string isbn;
	int id;
	if (mLibraryManager.ReturnBook(isbn, id))
		return 1;
	else
	{
		cout << "반납 실패! 도서가 연체되었습니다";
	}
}

int Application::DisplayDelayedBook()
{
	mLibraryManager.DisplayDelayedBooks();
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
