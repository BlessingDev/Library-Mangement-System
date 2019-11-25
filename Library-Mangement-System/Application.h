#pragma once

#include <string>

#include "LibraryManager.h"
#include "TimeForm.h"

class Application
{
private:
	LibraryManager mLibraryManager;
	TimeForm mCurrentTime;

public:
	/**
	* @���: Application�� ������. ��������� �ʱ�ȭ�Ѵ�.
	**/
	Application();

	/**
	* @���: Application�� �����ϴ� �Լ�
	**/
	void Run();

	/**
	* @���: ����� �Է¹޴� �Լ�
	* @��ȯ: �Էµ� ����� ��ȯ
	**/
	int GetCommand();

	/**
	* @���: ����� �Է¹޴� �Լ�
	* @��: ������ �޴��� �̸��� std::string ���ڷ� ���޹޴´�
	* @��: �̸��� �ش��ϴ� �޴��� ����Ѵ�.
	**/
	void ShowMenu(std::string);

	/**
	* @���: å�� �߰��ϴ� �Լ�. å�� �߰��ϴµ� �ʿ��� ���� ��ü�� ����Ѵ�.
	* @��: å�� �߰��Ѵ�.
	**/
	void AddBook();

	/**
	* @���: å�� �߰��ϴ� �Լ�. å�� �����ϴ� ���� ��ü�� ����Ѵ�.
	* @��: å�� �����Ѵ�.
	**/
	void DeleteBook();

	/**
	* @���: å�� �����ϴ� �Լ�. å�� �����ϴ� ���� ��ü�� ����Ѵ�.
	* @��: ����ڰ� å�� �����Ѵ�.
	**/
	void BorrowBook();

	/**
	* @���: å ������ �����ϴ� �Լ�.
	* @��: ����ڰ� å�� �����Ѵ�.
	**/
	void ReserveBook();

	/**
	* @���: å�� �˻��ϴ� �Լ�. (ISBN/����)
	* @��: å�� �˻��� ������ ����Ѵ�.
	**/
	void SearchBook();

	/**
	* @���: ����ڸ� �߰��ϴ� �Լ�.
	* @��: �Էµ� ����ڰ� �߰��ȴ�.
	**/
	void AddUser();

	/**
	* @���: ����ڸ� �˻��ϴ� �Լ�.(����� ID/����)
	* @��: ����ڸ� �˻��Ѵ�.
	**/
	void SearchUser();

	/**
	* @���: ����ڸ� �����ϴ� �Լ�.
	* @��: �Էµ� ����ڰ� �����ȴ�.
	**/
	void DeleteUser();

	/**
	* @���: Application�� �ð��� 1�� �ķ� �����ϴ� �Լ�.
	* @��: currentTime ����� ��¥�� 1�� �����Ѵ�.
	**/
	void DayPassed();
};