#pragma once

#include <string>

#include "LibraryManager.h"
#include "TimeForm.h"


class Application
{
public:
	static TimeForm mProgramTime;

private:
	LibraryManager mLibraryManager;
	TimeForm mCurrentTime;
	int m_Command;
	int m_Mode;

public:
	/**
	* @요약: Application의 생성자. 멤버변수를 초기화한다.
	**/
	Application();

	/**
	* @요약: Application을 실행하는 함수
	**/
	void Run();

	/**
	* @요약: 명령을 입력받는 함수
	* @반환: 입력된 명령을 반환
	**/
	//int GetCommand();

	/**
	* @요약: 명령을 입력받는 함수
	* @전: 보여줄 메뉴의 이름을 std::string 인자로 전달받는다
	* @후: 이름에 해당하는 메뉴를 출력한다.
	**/
	//void ShowMenu(std::string);

	/**
	* @요약: 책을 추가하는 함수. 책을 추가하는데 필요한 과정 전체를 담당한다.
	* @후: 책을 추가한다.
	**/
	int AddBook();

	/**
	* @요약: 책을 추가하는 함수. 책을 삭제하는 과정 전체를 담당한다.
	* @후: 책을 삭제한다.
	**/
	int DeleteBook();

	/**
	* @요약: 책을 대출하는 함수. 책을 대출하는 과정 전체를 담당한다.
	* @후: 사용자가 책을 대출한다.
	**/
	int BorrowBook();

	/**
	* @요약: 책 대출을 예약하는 함수.
	* @후: 사용자가 책을 예약한다.
	**/
	int ReserveBook();

	/**
	* @요약: 책을 검색하는 함수. (ISBN/통합)
	* @후: 책을 검색해 정보를 출력한다.
	**/
	int SearchBook();

	int ReturnBook();

	int DisplayDelayedBook();

	/**
	* @요약: 사용자를 추가하는 함수.
	* @후: 입력된 사용자가 추가된다.
	**/
	void AddUser();

	/**
	* @요약: 사용자를 검색하는 함수.(사용자 ID/통합)
	* @후: 사용자를 검색한다.
	**/
	void SearchUser();

	/**
	* @요약: 사용자를 삭제하는 함수.
	* @후: 입력된 사용자가 삭제된다.
	**/
	void DeleteUser();

	/**
	* @요약: Application의 시간을 1일 후로 변경하는 함수.
	* @후: currentTime 멤버의 날짜가 1일 증가한다.
	**/
	void DayPassed();
};
