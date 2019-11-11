#include <iostream>
#include <string>
using namespace std;

class BookInfo
{
public:
	string GetAuthor();
	string GetTitle();
	int GetISBN();
	int GetCategoryNum();

	void SetAuthor();
	void SetTitle();
	void SetISBN();
	void SetCategoryNum();

	//EnQueue
	//bool BorrowBook();

	//DeQueue
	//bool ReturnBook(); 
	

private:
	string author;
	string publisher;
	string title;

	int ISBN;
	int CategoryNum;
	//Queue BorrowedBooks;

};

