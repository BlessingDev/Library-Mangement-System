#pragma once
#include <iostream>

#include <functional>
using namespace std;
enum RelationType { LESS, GREATER, EQUAL };


template <typename T>
struct TreeNode
{
	T mData;
	TreeNode* mLeft;
	TreeNode* mRight;
};


template<typename T>
class BinarySearchTree
{
private:
	TreeNode<T>* mRoot;
	std::function<RelationType(const T&, const T&)> mCompFunc;


public:
	BinarySearchTree()
	{
		mRoot = NULL;
		mCompFunc = [](const T& a, const T& b)->RelationType {
			if (a == b)
				return RelationType::EQUAL;
			else if (a > b)
				return RelationType::GREATER;
			else
				return RelationType::LESS;
		};
	}

	BinarySearchTree(std::function<RelationType(const T&, const T&)> comp)
		: mCompFunc(comp)
	{
		mRoot = NULL;
	}


	~BinarySearchTree()
	{
		Destroy(mRoot);
	}

	void Destroy(TreeNode<T>* treePtr)
	{
		if (treePtr != NULL)
		{
			Destroy(treePtr->mLeft);
			Destroy(treePtr->mRight);
			delete treePtr;
		}
	}
	//brief: ���� root ��� ������� Ȯ��
	//post: ������� return true, �ƴϸ� return false
	bool IsEmpty() const
	{
		return mRoot == NULL;
	}

	//brief: ���� root ��� ���ִ��� Ȯ��
	//post: �� á���� return true, �ƴϸ� return false
	bool IsFull() const
	{
		TreeNode* location;
		try
		{
			location = new TreeNode;
			delete location;
			return false;
		}
		catch (exception)
		{
			return true;
		}
	}

	//brief: root ��� ����
	void MakeEmpty()
	{
		mRoot = NULL;
	}

	int CountNodes(TreeNode<T>* treePtr)
	{
		if (treePtr == NULL)
			return 0;
		else
			return CountNodes(treePtr->left) + CountNodes(treePtr->right) + 1;
	}

	/**
	*	@brief	Insert node to tree
	*/
	void InternalInsert(TreeNode<T>*& treePtr, T item)
	{
		if (treePtr == NULL)
		{
			treePtr = new TreeNode<T>;
			treePtr->mRight = NULL;
			treePtr->mLeft = NULL;
			treePtr->mData = item;
		}
		else if (mCompFunc(treePtr->mData, item) == RelationType::GREATER)
		{
			InternalInsert(treePtr->mLeft, item);
		}
		else if (mCompFunc(treePtr->mData, item) == RelationType::LESS)
		{
			InternalInsert(treePtr->mRight, item);
		}
	}
	/**
	*	@brief	Delete node from tree
	*/
	void InternalDelete(TreeNode<T>*& treePtr, T item)
	{
		if (mCompFunc(treePtr->mData, item) == RelationType::GREATER)
			InternalDelete(treePtr->mLeft, item);
		else if (mCompFunc(treePtr->mData, item) == RelationType::LESS)
			InternalDelete(treePtr->mRight, item);
		else
			DeleteNode(treePtr); // node found.
	}

	void DeleteNode(TreeNode<T>*& treePtr)
	{
		T tempItem;
		TreeNode<T>* tempPtr;
		tempPtr = treePtr;
		if (treePtr->mLeft == NULL)
		{
			treePtr = treePtr->mRight;
			delete tempPtr;
		}
		else if (treePtr->mRight == NULL)
		{
			treePtr = treePtr->mLeft;
			delete tempPtr;
		}
		else
		{
			//������� ����� �ڽĳ�忡�� �ִ� ã�� �� �װɷ� ��ü�� ���� ���� �ִ� ����
			GetPredecessor(treePtr->mLeft, tempItem);
			treePtr->mData = tempItem;
			InternalDelete(treePtr->mLeft, tempItem);
		}
	}

	void GetPredecessor(TreeNode<T>* treePtr, T& data)
	{
		while (treePtr->mRight != NULL)
			treePtr = treePtr->mRight;
		data = treePtr->mData;
	}

	bool InternalRetrieve(TreeNode<T>* treePtr, T& item)
	{
		if (treePtr == NULL)
		{
			return false;
		}
		else if (mCompFunc(treePtr->mData, item) == RelationType::GREATER)
		{
			InternalRetrieve(treePtr->mLeft, item);
		}
		else if (mCompFunc(treePtr->mData, item) == RelationType::LESS)
			InternalRetrieve(treePtr->mRight, item);
		else if (mCompFunc(treePtr->mData, item) == RelationType::EQUAL)
		{
			item = treePtr->mData;
			return true;
		}
		return false;
	}

	//���� �ؾ���
	void InternalPrint(TreeNode<T>* treePtr) //, ofstream& outFile
	{
		if (treePtr != NULL)
		{
			InternalPrint(treePtr->mLeft);
			cout << treePtr->mData.GetAuthor() << " - ";
			InternalPrint(treePtr->mRight);
		}
	}


	//wraper


	void Insert(T item)
	{
		InternalInsert(mRoot, item);
	}

	void Delete(T item)
	{
		InternalDelete(mRoot, item);
	}

	//brief: get item
	//post: ���� return true, ���� return false
	bool GetItem(T& item)
	{
		return InternalRetrieve(mRoot, item);
	}

	//post: return tree length
	int GetLength() const
	{
		return CountNodes(mRoot);
	}

	//brief: Internal retrieve
	//post: print items
	void Print()
	{
		InternalPrint(mRoot);
		cout << "\n";
	}

};


