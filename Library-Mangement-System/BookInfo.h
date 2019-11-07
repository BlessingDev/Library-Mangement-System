#include <iostream>
#include <string>
using namespace std;

class BookInfo
{
public:
	string GetAuthor();
	string GetISBN();
	string GetTitle();
	int GetISBN();
	int GetCategoryNum();

	void SetAuthor();
	void SetISBN();
	void SetTitle();
	void SetISBN();
	void SetCategoryNum();

private:
	string author;
	string publisher;
	string title;
	string BorrowedBookQueue;

	int ISBN;
	int CategoryNum;

};

