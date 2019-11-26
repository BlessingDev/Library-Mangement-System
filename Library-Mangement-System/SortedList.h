#pragma once
#include <iostream>
#include <string>
#include <cstring>

using namespace std;

template <typename T>
class SortedList
{
public:
	/**
	*	default constructor.
	*/
	SortedList()
	{
		cap = 10;
		m_Array = new T[cap];
		m_Length = 0;
		ResetList();
	}

	/**
	*	destructor.
	*/
	~SortedList()
	{
		delete[] m_Array;
	}

	/**
	*	@brief	Initialize list iterator.
	*	@pre	list should be initialized.
	*	@post	iterator is reset.
	*/
	void ResetList()
	{
		m_CurPointer = -1;
	}

	/**
	*	@brief	Make list empty.
	*	@pre	none.
	*	@post	clear list.
	*/
	void MakeEmpty()
	{
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
	*	@brief	Retrieves list element whose key matches item's key.
	*	@pre	List has been initialized.
	*	@post	If there is an element someItem whose key matches item's key,
	*			then item returned.
	*	@return	return item.
	*/
	ItemType GetItem(T& item)
	{
		for (int i = 0; i < m_Length; i++)
		{
			if (item > m_Array[i])
			{
				continue;
			}
			if (item < m_Array[i])
			{
				cout << "\tNot Existing item." << endl;
				break;
			}
			if (item == m_Array[i])
			{
				item = m_Array[i];
				item.Display();
				break;
			}
		}
		return item;
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
		if (m_Length >= cap) {
			expand();
		}
		if (m_Length == 0)
		{
			m_Array[location] = elem;
			m_Length++;
		}
		else
		{
			for (int i = 0; i < m_Length; i++)
			{
				if (elem < m_Array[i])
					break;
				else if (m_Array[i] == elem)
				{
					cout << "\tItem already exist in List!" << endl;
					return 0;
				}
				location++;
			}
			for (int i = m_Length; i > location; i--)
			{
				m_Array[i] = m_Array[i - 1];
			}
			m_Array[location] = elem;
			m_Length++;
		}
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
		int location = 0;
		for (int i = 0; i < m_Length; i++)
		{

			if (item > m_Array[i])
			{
				location++;
				continue;
			}
			if (item < m_Array[i])
			{
				cout << "\tWrong ID" << endl;
				return 0;
			}
			if (item == m_Array[i])
			{
				break;
			}
		}

		if (location == m_Length - 1)
		{
			m_Length--;
			cout << "\n\tSuccessfully deleted!" << endl;
			return 1;
		}
		else if (location < m_Length)
		{
			for (int i = location; i < m_Length; i++)
			{
				m_Array[i] = m_Array[i + 1];
			}
			cout << "\n\tSuccessfully deleted!" << endl;
			m_Length--;
			return 1;
		}
	}

	/**
	*	@brief	move list iterator to the next item in list and get that item.
	*	@pre	list and list iterator should not be initialized.
	*	@post	iterator is moved to next item.
	*	@param	data	get current iterator's item. it does not need to be initialized.
	*	@return	index of current iterator's item if is not end of list, oterwise return -1.
	*/
	int GetNextItem(T& item)
	{
		m_CurPointer++;
		if (m_CurPointer == cap)
			return -1;
		item = m_Array[m_CurPointer];
		return m_CurPointer;
	}

	T GetBinarySearch(T item) 
	{
		int midpoint;
		int first = 0;
		int last = m_Length - 1;
		bool found = false;
		bool moreToSearch = (first <= last);

		while (moreToSearch && !found)
		{
			midpoint = (first + last) / 2;
			if (item < m_Array[midpoint])
			{
				last = midpoint - 1;
				moreToSearch = (first <= last);
				continue;
			}
			if (item > m_Array[midpoint])
			{
				first = midpoint + 1;
				moreToSearch = (first <= last);
				continue;
			}
			if (item == m_Array[midpoint])
			{
				found = true;
				item = m_Array[midpoint];
				break;
			}
		}
		return item;
	}


private:
	T* m_Array;  ///< list array.
	int m_Length;		///< number of elements in list.
	int cap;		    ///< capacity of array.
	int m_CurPointer;   ///< iterator pointer.



	void expand()
	{
		cap *= 2;
		T* tempArr = new T[cap];
		memcpy(tempArr, m_Array, m_Length * sizeof(T));
		delete[] m_Array;
		m_Array = tempArr;
	}
};