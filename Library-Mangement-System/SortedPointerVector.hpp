#pragma once
#include <iostream>
#include <functional>
#include <string>
#include <cstring>

using namespace std;

enum RelationType { LESS, GREATER, EQUAL };

template <typename T>
class SortedPointerVector
{
public:
	/**
	*	default constructor.
	*/
	SortedPointerVector()
	{
		cap = 2;
		m_Array = new T*[cap];
		m_Length = 0;

		memset(m_Array, 0, sizeof(T*) * cap);

		mCompFunc = [](const T& a, const T&b)->RelationType {
			if (a == b)
				return RelationType::EQUAL;
			else if (a > b)
				return RelationType::GREATER;
			else
				return RelationType::LESS;
		};
	}

	SortedPointerVector(std::function<RelationType(const T&, const T&)> comp)
		: mCompFunc(comp)
	{
		cap = 10;
		m_Array = new T*[cap];
		m_Length = 0;
		memset(m_Array, 0, sizeof(T*) * cap);
	}

	/**
	*	destructor.
	*/
	~SortedPointerVector()
	{
		MakeEmpty();
		delete[] m_Array;
	}

	/**
	*	@brief	Make list empty.
	*	@pre	none.
	*	@post	clear list.
	*/
	void MakeEmpty()
	{
		for (int i = 0; i < m_Length; ++i)
		{
			delete[] m_Array[i];
			m_Array[i] = nullptr;
		}
		m_Length = 0;
	}

	/**
	*	@brief	Get a number of records in current list.
	*	@pre	none.
	*	@post	none.
	*	@return	number of records in current list.
	*/
	int GetLength()
	{
		return m_Length;
	}

	/**
	*	@brief	add a new data into list.
	*	@pre	list should be initialized.
	*	@post	added the new record into the list.
	*	@param	data	new data.
	*	@return	return 1 if this function works well, otherwise 0.
	*/
	int Add(T elem)
	{
		int location = 0;
		if (m_Length >= cap - 1) {
			expand();
		}
		T t = elem;
		bool result = this->GetItem(t);

		T* node = new T(elem);

		if (result)
		{
			for (int i = m_CurPointer + 1; i <= m_Length; i++)
			{
				m_Array[i] = m_Array[i - 1];
			}
			m_Array[m_CurPointer] = node;
		}
		else
		{
			if (m_Array[m_CurPointer] == nullptr)
			{
				m_Array[m_CurPointer] = node;
			}
			else
			{
				T val = (*m_Array[m_CurPointer]);
				if (mCompFunc(val, elem) == RelationType::GREATER)
				{
					for (int i = m_Length; i > m_CurPointer; --i)
					{
						m_Array[i] = m_Array[i - 1];
					}
					m_Array[m_CurPointer] = node;
				}
				else if (mCompFunc(val, elem) == RelationType::LESS)
				{
					for (int i = m_CurPointer + 1; i < m_Length; i++)
					{
						m_Array[i + 1] = m_Array[i];
					}
					m_Array[m_CurPointer + 1] = node;
				}
			}
		}

		m_Length += 1;
		return 1;
	}

	/**
	*	@brief	Deletes the element whose key's matches item's key.
	*	@pre	list should be initialized.
	*	@post	No elements in list has key matching item's key.
	*	@return	return 1 if this function works well, otherwise 0.
	*/
	int Delete(T item)
	{
		bool result = this->GetItem(item);
		if (result)
		{
			delete[] m_Array[m_CurPointer];
			for (int i = m_CurPointer; i < m_Length; i++)
			{
				m_Array[i] = m_Array[i + 1];
			}
			m_Length--;
			m_Array[m_Length] = nullptr;

			return 1;
		}
		else
		{
			return 0;
		}
	}

	/**
	*	@brief	Retrieves list element whose key matches item's key. BinarySearch
	*	@pre	List has been initialized.
	*	@post	If there is an element someItem whose key matches item's key,
	*			then item returned.
	*	@return	key�� �´� �������� ã�Ҵ����� ���� ���θ� ��ȯ.
	*/
	bool GetItem(T& item)
	{
		int first = 0;
		int last = m_Length - 1;
		m_CurPointer = (first + last) / 2;
		bool found = false;
		bool moreToSearch = (first <= last);

		while (moreToSearch && !found)
		{
			m_CurPointer = (first + last) / 2;
			T val = (*m_Array[m_CurPointer]);
			if (mCompFunc(item, val) == RelationType::LESS)
			{
				last = m_CurPointer - 1;
				moreToSearch = (first <= last);
				continue;
			}
			if (mCompFunc(item, val) == RelationType::GREATER)
			{
				first = m_CurPointer + 1;
				moreToSearch = (first <= last);
				continue;
			}
			if (mCompFunc(item, val) == RelationType::EQUAL)
			{
				found = true;
				item = val;
				break;
			}
		}

		return found;
	}

	/**
	*	@brief	Retrieves list element whose key matches item's key. BinarySearch. Get Pointer
	*	@pre	List has been initialized.
	*	@post	If there is an element someItem whose key matches item's key,
	*			then item returned.
	*	@return	return item.
	*/
	bool GetPointer(T*& item)
	{
		T key = (*item);

		bool result = this->GetItem(key);
		if (result)
		{
			item = m_Array[m_CurPointer];
		}

		return result;
	}

	T& operator[](int idx)
	{
		if (idx < 0 || idx >= m_Length)
		{
			throw std::out_of_range("Index out of range: SortedPointerVector");
		}

		return (*m_Array[idx]);
	}
private:
	T** m_Array;  ///< list array.
	int m_Length;		///< number of elements in list.
	int cap;		    ///< capacity of array.
	int m_CurPointer;   ///< iterator pointer.
	std::function<RelationType(const T&, const T&)> mCompFunc;



	void expand()
	{
		cap *= 2;
		T** tempArr = new T*[cap];
		memset(tempArr, 0, sizeof(T*) * cap);
		memcpy(tempArr, m_Array, m_Length * sizeof(T*));
		delete[] m_Array;
		m_Array = tempArr;
	}
};