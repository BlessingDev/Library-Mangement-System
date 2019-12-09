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
			case 4:
				DisplayUserList();
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
	cout << "\t   8 : 전체도서 목록" << endl;
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
	cout << "\t   4 : 전체이용자 목록" << endl;
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

	switch (mLibraryManager.BorrowBook(isbn, id))
	{
	case 1:
		cout << "대출에 성공했습니다";
		break;
	case 2:
		cout << "대출 실패! 먼저 예약한 사람이 존재합니다";
		break;
	case 3:
		cout << "대출 불가! 패널티가 존재하거나 최대 대출권수를 초과하였습니다";
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

	cout << "사용자 ID 입력	:	";
	cin >> id;
	cout << "ISBN	:	";
	cin >> isbn;
	
	switch (mLibraryManager.ReserveBook(isbn, id, nReserve))
	{
	case 1:
		cout << "예약에 성공하였습니다";
		break;
	case 2:
		cout << "예약 실패! 예약인원을 초과하였습니다";
		break;
	case 3:
		cout << "예약 불가! 패널티가 존재하거나 최대 대출권수를 초과하였습니다";
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

	cout << "반납하고자 하는 이용자의 ID를 입력하세요	:	";
	cin >> id;
	cout << "반납하고자 하는 책의 ISBN을 입력하세요	:	";
	cin >> isbn;

	UserInfo* next;
	switch (mLibraryManager.ReturnBook(isbn, id, retInfo, resInfo))
	{
	case 1:
		cout << "반납 성공";
		break;
	case 2:
		cout << "반납 성공! 도서 연체로 인한 패널티가 부여됩니다";
		break;
	case 3:
		cout << "반납 성공!" << endl;
		next = resInfo.GetUserInfo();
		cout << "다음 대출자 정보	:	";
		(*next).DisplayUserInfo();
		break;
	case 4:
		cout << "반납 성공! 도서 연체로 인한 패널티가 부여됩니다" << endl;
		next = resInfo.GetUserInfo();
		cout << "다음 대출자 정보	:	";
		(*next).DisplayUserInfo();
		break;
	case 5:
		cout << "반납실패";
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
	cout << "\t   1 : ISBN 검색" << endl;
	cout << "\t   2 : 통합 검색" << endl;
	cout << "\t   3 : 속성 검색" << endl;
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
		cout << "\t잘못된 입력입니다...\n";
		return 0;
	}

	if (!check)
	{
		cout << "검색 실패";
		return 0;
	}
	else
		return 1;
}

int Application::SearchBookWithISBN(BookInfo& curbook)
{
	string isbn;
	cout << "검색할 책의 ISBN을 입력하세요	:	";
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
	cout << "검색할 내용을 입력하세요	:	";
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
	cout << "검색 방법을 입력하세요" << endl;
	cout << "\t   Author	:	작가 검색" << endl;
	cout << "\t   Publisher	:	출판사 검색" << endl;
	cout << "\t   Title		:	제목 검색" << endl;
	cout << "\t   ISBN		:	ISBN 검색" << endl;
	cin >> attribute;

	cout << "검색 내용을 입력하세요	:	";
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
	cout << "\t   1 : ID 검색" << endl;
	cout << "\t   2 : 통합 검색" << endl;
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
		cout << "검색할 ID를 입력하세요	:	";
		cin >> id;
		check = mLibraryManager.SearchUserById(id, curUser);
		curUser.DisplayUserInfo();
		break;
	case 2:
		cout << "검색 내용을 입력하세요	:	";
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
		cout << "\t잘못된 입력입니다...\n";
		return 0;
	}

	if (!check)
	{
		cout << "검색 실패";
		return 0;
	}
	else
		return 1;
}

int Application::DeleteUser()
{
	int id;
	cout << "\t삭제할 ID를 입력하세요	:	";
	cin >> id;
	if (mLibraryManager.DeleteUser(id) == true)
	{
		cout << "\t삭제 성공" << endl;
		return 1;
	}
	else
	{
		cout << "\t삭제 실패" << endl;
		return 0;
	}
}

void Application::DayPassed()
{
	int time = 1;
	cout << "몇일 넘기시겠습니까? : ";
	cin >> time;
	mProgramTime = mProgramTime.timeStamp() + TimeForm::ONEDAY * time;

	LinkedList<BorrowInfo> delayed;
	LinkedList<BorrowInfo> expired;
	mLibraryManager.DayPassed(delayed, expired);

	std::cout << "이하의 대출이 연체되었습니다." << std::endl;
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
	std::cout << "이하의 예약이 만료되었습니다." << std::endl;
	expired.ResetList();
	length = expired.GetLength();
	for (int i = 0; i < length; ++i)
	{
		BorrowInfo t;
		expired.GetNextItem(t);
		t.DisplayInfo();
		std::cout << "-----" << std::endl;
		std::cout << "위 책에 대한 다음 예약자입니다." << std::endl;
		t.GetBookInfo()->GetCurrentBorrowInfo(t);
		t.DisplayInfo();
		std::cout << "----------" << std::endl;
	}
	std::cout << std::endl << std::endl;
}