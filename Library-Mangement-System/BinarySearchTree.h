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
	//brief: 현재 root 노드 비었는지 확인
	//post: 비었으면 return true, 아니면 return false
	bool IsEmpty() const
	{
		return mRoot == NULL;
	}

	//brief: 현재 root 노드 차있는지 확인
	//post: 꽉 찼으면 return true, 아니면 return false
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

	//brief: root 노드 비우기
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
			//지우려는 노드의 자식노드에서 최댓값 찾은 후 그걸로 대체한 다음 본래 최댓값 지움
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

	//수정 해야함
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
	//post: 성공 return true, 실패 return false
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


