#pragma once
#include <functional>

#include "LinkedList.h"
#include "RelationType.h"

/**
*	Simple unsorted list class for managing items.
*/
template <typename T>
class SortedLinkedList
{
public:
	/**
	*	default constructor.
	*/
	SortedLinkedList();

	/**
	*	@요약	비교 함수를 이용한 생성자
	*	@전		첫번째 인자를 기준으로 비교를 수행하여 RelationType을 반환하는 함수를 전달할 것
	*/
	SortedLinkedList(std::function<RelationType(T&, T&)>);

	/**
	*	destructor.
	*/
	~SortedLinkedList();

	/**
	*	@brief	Initialize list to empty state.
	*	@pre	None
	*	@post	List is empty.
	*/
	void MakeEmpty();

	/**
	*	@brief	Get number of elements in the list.
	*	@pre	None.
	*	@post	Function value = number of elements in list.
	*	@return	Number of elements in this list.
	*/
	int GetLength() const;
	
	void InsertItem(T item);

	/**
	*	@brief	Retrieve list element whose key matches item's key (if present).
	*	@pre	Key member of item is initialized.
	*	@post	If there is an element whose key matches with item's key then the element's record is copied to the item.
	*	@return	1 if any element's primary key matches with item's, otherwise 0.
	*/
	int Get(T& item);

	/**
	*	@brief	키 값이 같은 요소를 삭제하는 기능
	*	@pre	리스트가 초기화돼 있을 것
	*	@post	키 값이 맞는 요소가 삭제됨
	*	@return 1이면 올바르게 삭제, 0이면 해당 요소를 찾지 못함
	*/
	int Delete(T);

	/**
	*	@brief	Initialize current pointer for an iteration through the list.
	*	@pre	None.
	*	@post	current pointer is prior to list. current pointer has been initialized.
	*/
	void ResetList();

	/**
	*	@brief	Get the next element in list.
	*	@pre	current pointer is defined. Element at current pointer is not last in list.
	*	@post	current pointer is updated to next position. item is a copy of element at current pointer.
	*/
	int GetNextItem(T& item);

private:
	std::function<RelationType(T&, T&)> mCompFunc;
	NodeType<T>* m_pList;	///< Pointer for pointing a first node.
	NodeType<T>* m_pCurPointer;	///< Node pointer for pointing current node to use iteration.
	int m_nLength;	///< Number of node in the list.
};

// Class constructor
template <typename T>
SortedLinkedList<T>::SortedLinkedList()
{
	m_nLength = 0;
	m_pList = nullptr;
	m_pCurPointer = nullptr;
	mCompFunc = [](T& a, T&b)->RelationType {
		if (a == b)
			return RelationType::EQUAL;
		else if (a > b)
			return RelationType::GREATER;
		else
			return RelationType::LESS;
	};
}

template <typename T>
SortedLinkedList<T>::SortedLinkedList(std::function<RelationType(T&, T&)> func)
	: mCompFunc(func)
{
	m_nLength = 0;
	m_pList = nullptr;
	m_pCurPointer = nullptr;
}

// Class destructor
template <typename T>
SortedLinkedList<T>::~SortedLinkedList()
{
	//리스트내의 모든 node 제거
	MakeEmpty();
}


// Initialize list to empty state.
template <typename T>
void SortedLinkedList<T>::MakeEmpty()
// Post: List is empty; all items have been deallocated.
{
	// 리스트내의 모든 노드 제거 하고 리스트의 length를 초기화
	NodeType<T>* tempPtr;

	while (m_pList != nullptr)
	{
		tempPtr = m_pList;
		m_pList = m_pList->next;
		delete tempPtr;
	}

	m_nLength = 0;
}


// Get number of elements in the list.
template <typename T>
int SortedLinkedList<T>::GetLength() const
{
	return m_nLength;
}


// Add item into this list.
template <typename T>
void SortedLinkedList<T>::InsertItem(T item)
{
	// 리스트 초기화
	ResetList();

	// 리스트에 추가할 새로운 node 객체와 이전 노드를 가리킬 포인터 선언
	NodeType<T>* node = new NodeType<T>;
	NodeType<T>* pre;
	T dummy;
	bool bFound = false;

	// node 객체에 입력받은 데이터 설정 및 초기화
	node->data = item;
	node->next = nullptr;

	// list 에 node 가 존재하지 않는 경우
	if (!m_nLength)
	{
		m_pList = node;
	}
	// list 에 node 가 하나 이상 존재하는 경우
	else
	{
		// 가장 마지막 node 로 이동 후 삽입
		while (1)
		{
			// 이전 노드를 가리키는 포인터 갱신
			pre = m_pCurPointer;

			// iteration 을 이용해 node 포인터 갱신.
			GetNextItem(dummy);

			RelationType result = mCompFunc(dummy, node->data);
			if (result == RelationType::EQUAL || result == RelationType::GREATER)
			{
				if (pre == nullptr)
				{
					m_pList = node;
					node->next = m_pCurPointer;
				}
				else
				{
					pre->next = node;
					node->next = m_pCurPointer;
				}
				break;
			}

			// node 포인터가 마지막 node 를 가리키면 그 뒤에 새로운 node 삽입.
			if (m_pCurPointer->next == nullptr)
			{
				// 마지막 node 와 새로운 node 연결
				m_pCurPointer->next = node;
				break;
			}
		}
	}

	m_nLength++;
}


// Retrieve list element whose key matches item's key (if present).
template <typename T>
int SortedLinkedList<T>::Get(T& item)
{
	bool moreToSearch, found;
	NodeType<T>* location;

	location = m_pList;
	found = false;
	moreToSearch = (location != nullptr);

	while (moreToSearch && !found)
	{
		if (item == location->data)
		{
			found = true;
			item = location->data;
		}
		else
		{
			location = location->next;
			moreToSearch = (location != NULL);
		}
	}

	if (found)
		return 1;
	else
		return 0;
}


// Initializes current pointer for an iteration through the list.
template <typename T>
void SortedLinkedList<T>::ResetList()
{
	// current pointer 초기화
	m_pCurPointer = nullptr;
}


// Gets the next element in list.
template <typename T>
int SortedLinkedList<T>::GetNextItem(T & item)
{
	// current pointer 이 NULL이라면 처음 node를 가리킴.
	if (m_pCurPointer == nullptr)
	{
		m_pCurPointer = m_pList;
	}
	else
		//current position 을 다음 노드로 이동
		m_pCurPointer = m_pCurPointer->next;

	if (m_pCurPointer == nullptr)
	{
		return -1;
	}
	else
	{
		//item 에 current position 의 info 를 삽입
		item = m_pCurPointer->data;
		return 1;
	}
}

template <typename T>
int SortedLinkedList<T>::Delete(T item)
{
	// 리스트 초기화
	ResetList();

	NodeType<T>* pre;
	T dummy;
	bool bFound = false;

	// list 에 node 가 존재하지 않는 경우
	if (m_nLength)
	{
		// 가장 마지막 node 로 이동 후 삽입
		while (1)
		{
			// 이전 노드를 가리키는 포인터 갱신
			pre = m_pCurPointer;

			// iteration 을 이용해 node 포인터 갱신.
			GetNextItem(dummy);

			if (dummy == item)
			{
				if (pre == nullptr)
				{
					m_pList = m_pCurPointer->next;
					delete m_pCurPointer;
				}
				else
				{
					pre->next = m_pCurPointer->next;
					delete m_pCurPointer;
				}

				m_pCurPointer = pre;
				m_nLength--;
				return 1;
			}

			if (m_pCurPointer->next == nullptr)
			{
				return 0;
			}
		}
	}

}