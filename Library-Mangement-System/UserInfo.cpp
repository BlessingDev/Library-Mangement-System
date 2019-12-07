#include "UserInfo.h"


#include "Application.h"

UserInfo::UserInfo()
	: m_penalty()
{
	m_userID = -1;
	m_userName = "";
	m_userAddress = "";
	m_userNumber = -1;

	m_nReserve = 4;
	m_nBorrow = 5;
}

UserInfo::~UserInfo()
{
//	delete m_borrowedBookList;
}

void UserInfo::SetID(int ID)
{
	m_userID = ID;
}

void UserInfo::SetUserName(string name)
{
	m_userName = name;
}

void UserInfo::SetUserAddress(string address)
{
	m_userAddress = address;
}

void UserInfo::SetUserNumber(int number)
{
	m_userNumber = number;
}

void UserInfo::SetUserNBorrow(char nborrow)
{
	m_nBorrow = nborrow;
}

void UserInfo::SetUserNReserve(char nreserve)
{
	m_nReserve = nreserve;
}

void UserInfo::SetIDByKB()
{
	cout << "Input User ID	:	";
	cin >> m_userID;
}

void UserInfo::SetUserNameByKB()
{
	cout << "Input User Name	:	";
	cin >> m_userName;
}

void UserInfo::SetUserAddressByKB()
{
	cout << "Input User Address	:	";
	cin >> m_userAddress;
}

void UserInfo::SetUserNumberByKB()
{
	cout << "Input User Number	:	";
	cin >> m_userNumber;
}

void UserInfo::SetRecordByKB()
{
	SetIDByKB();
	SetUserNameByKB();
	SetUserAddressByKB();
	SetUserNumberByKB();
}

int UserInfo::GetUserID()
{
	return m_userID;
}

string UserInfo::GetUserName()
{
	return m_userName;
}

string UserInfo::GetUserAddress()
{
	return m_userAddress;
}

int UserInfo::GetUserNumber()
{
	return m_userNumber;
}

TimeForm UserInfo::GetUserPenalty()
{
	return m_penalty;
}

char UserInfo::GetUserNReserve()
{
	return m_nReserve;
}

char UserInfo::GetUserNBorrow()
{
	return m_nBorrow;
}

void UserInfo::DisplayUserID()
{
	cout << "User ID	:	" << m_userID << endl;
}

void UserInfo::DisplayUserName()
{
	cout << "User Name	:	" << m_userName << endl;
}

void UserInfo::DisplayUserAddress()
{
	cout << "User Address	:	" << m_userAddress << endl;
}

void UserInfo::DisplayUserNumber()
{
	cout << "User Number	:	" << m_userNumber << endl;
}

void UserInfo::DisplayUserInfo()
{
	DisplayUserID();
	DisplayUserName();
	DisplayUserAddress();
	DisplayUserNumber();
}

void UserInfo::StartPenalty()
{
	m_penalty = Application::mProgramTime;
}

int UserInfo::ReadDataFromFile(ifstream& fin)
{
	fin >> m_userID;
	fin >> m_userName;
	fin >> m_userNumber;
	fin >> m_userAddress;

	return 1;
}

int UserInfo::WriteDataToFile(ofstream& fout)
{
	fout << endl;
	fout << m_userID << " ";
	fout << m_userName << " ";
	fout << m_userNumber << " ";
	fout << m_userAddress;

	return 1;
}

RelationType UserInfo::CompareByID(const UserInfo& info)
{
	if (this->m_userID > info.m_userID)
		return RelationType::GREATER;
	else if (this->m_userID < info.m_userID)
		return RelationType::LESS;
	else
		return RelationType::EQUAL;
}

bool UserInfo::operator<(const UserInfo& comp)
{
	if (this->m_userID < comp.m_userID)
		return true;
	else
		return false;
}

bool UserInfo::operator>(const UserInfo& comp)
{
	if (this->m_userID > comp.m_userID)
		return true;
	else
		return false;
}

bool UserInfo::operator==(const UserInfo& comp)
{
	if (this->m_userID == comp.m_userID)
		return true;
	else
		return false;
}