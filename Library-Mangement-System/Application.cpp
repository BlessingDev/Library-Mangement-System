#include "Application.h"

void Application::AddBook()
{
	BookInfo mbook;
	mbook.SetBookInfoByKB();
	mLibraryManager.AddBook(mbook);
}

void Application::DeleteBook()
{
	string isbn;
	cout << "\tEnter ISBN : ";
	cin >> isbn;
	if (mLibraryManager.DeleteBook(isbn) == true)
	{
		cout << "Successfully deleted!" << endl;
	}
	else
	{
		cout << "Book with such ISBN doesn't exist." << endl;
	}
}

void Application::BorrowBook()
{
	string isbn;
	int id;
	cout << "\tEnter ISBN : ";
	cin >> isbn;
	cout << "\tEnter ID : ";
	cin >> id;
	if (mLibraryManager.BorrowBook(isbn, id) == true)
	{
		cout << "\tBook successfully borrowed!" << endl;
	}
	else
	{
		cout << "\tBorrow failed." << endl;
	}
}

void Application::ReserveBook()
{
	string isbn;
	int id;
	int borrowedNum;
	cout << "\tEnter ISBN : ";
	cin >> isbn;
	cout << "\tEnter ID : ";
	cin >> id;
	if (mLibraryManager.ReserveBook(isbn, id, borrowedNum) == true)
	{
		cout << "\tBook successfully reserved!" << endl;
	}
	else
	{
		cout << "\tReservation failed" << endl;
	}
}

void Application::SearchBook()
{
	BookInfo mbook;
	string isbn;
	cout << "\tEnter ISBN : ";
	cin >> isbn;
	if (mLibraryManager.SearchBookWithIsbn(isbn, mbook) == true)
	{
		mbook.DisplayBookInfo();
	}
	else
	{
		cout << "Could't find book with such ISBN." << endl;
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