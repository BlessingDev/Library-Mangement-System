#include "UserInfo.h"
#include <sstream>

#include "Application.h"

UserInfo::UserInfo()
	: mPaneltyEndDay(Application::mProgramTime), mDelayedNum(0)
{
	m_userID = -1;
	m_userName = "";
	m_userAddress = "";
	m_userNumber = -1;

	m_nReserve = 0;
	m_nBorrow = 0;
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

void UserInfo::SetUserNumber(string number)
{
	m_userNumber = number;
}

void UserInfo::SetPenaltyDay(TimeForm t)
{
	mPaneltyEndDay = t;
}

void UserInfo::SetUserNBorrow(char nborrow)
{
	m_nBorrow = nborrow;
}

void UserInfo::AddDelayedNum(int val)
{
	mDelayedNum += val;
}

void UserInfo::SetUserNReserve(char nreserve)
{
	m_nReserve = nreserve;
}

void UserInfo::SetIDByKB()
{
	cout << "Input User ID: ";
	cin >> m_userID;
	cin.ignore();
}

void UserInfo::SetUserNameByKB()
{

	cout << "이름: ";
	std::getline(std::cin, m_userName);
}

void UserInfo::SetUserAddressByKB()
{

	cout << "주소: ";
	std::getline(std::cin, m_userAddress);
}

void UserInfo::SetUserNumberByKB()
{
	cout << "전화번호: ";
	cin >> m_userNumber;
	cin.ignore();
}

void UserInfo::SetRecordByKB()
{
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

string UserInfo::GetUserNumber()
{
	return m_userNumber;
}

TimeForm UserInfo::GetUserPenalty()
{
	return mPaneltyEndDay;
}

char UserInfo::GetUserNReserve()
{
	return m_nReserve;
}

char UserInfo::GetUserNBorrow()
{
	return m_nBorrow;
}

bool UserInfo::IsDelayed() const
{
	return (mDelayedNum > 0);
}

void UserInfo::DisplayUserID()
{
	cout << "사용자 ID: " << m_userID << endl;
}

void UserInfo::DisplayUserName()
{
	cout << "이름: " << m_userName << endl;
}

void UserInfo::DisplayUserAddress()
{
	cout << "주소: " << m_userAddress << endl;
}

void UserInfo::DisplayUserNumber()
{
	cout << "전화번호: " << m_userNumber << endl;
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
	mPaneltyEndDay = Application::mProgramTime;
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