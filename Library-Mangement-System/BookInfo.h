#include <iostream>
#include <string>
using namespace std;

class BookInfo
{
public:
	BookInfo();
	~BookInfo();

	void SetAuthor(string author);
	void SetTitle(string title);
	void SetISBN(int ISBN);
	void SetCategoryNum(int CategoryNum);

	string GetAuthor();
	string GetTitle();
	int GetISBN();
	int GetCategoryNum();

	void SetAuthorByKB();
	void SetTitleByKB();
	void SetISBNByKB();
	void SetCategoryNumByKB();

	void SetBookInfo();

	void DisplayAuthor();
	void DisplayTitle();
	void DisplayISBN();
	void DisplayCategoryNum();
	void DisplayBookInfo();

	//EnQueue
	//bool BorrowBook();

	//DeQueue
	//bool ReturnBook(); 
	

private:
	string m_Author;
	string m_Publisher;
	string m_Title;

	int m_ISBN;
	int m_CategoryNum;
//	Queue BorrowedBooks;
};

