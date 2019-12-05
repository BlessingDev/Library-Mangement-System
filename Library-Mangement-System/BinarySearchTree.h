#pragma once

#ifndef mBINARYSEARCHmTREEmH
#define mBINARYSEARCHmTREEmH
#include <iostream>
using namespace std;


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

public:
	BinarySearchTree()
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

	int CountNodes(TreeNode<T>* tree)
	{
		if (tree == NULL)
			return 0;
		else
			return CountNodes(tree->left) + CountNodes(tree->right) + 1;
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

		else if (item < treePtr->mData)
		{
			InternalInsert(treePtr->mLeft, item);
		}
		else if (item > treePtr->mData)
		{
			InternalInsert(treePtr->mRight, item);
		}
	}
	/**
	*	@brief	Delete node from tree
	*/
	void InternalDelete(TreeNode<T>*& treePtr, T item)
	{
		if (item < treePtr->mData)
			InternalDelete(treePtr->mLeft, item);
		else if (item > treePtr->mData)
			InternalDelete(treePtr->mRight, item);
		else
			DeleteNode(treePtr); // node found.
	}

	void DeleteNode(TreeNode<T>*& tree)
	{
		T tempItem;
		TreeNode<T>* tempPtr;
		tempPtr = tree;
		if (tree->mLeft == NULL)
		{
			tree = tree->mRight;
			delete tempPtr;
		}
		else if (tree->mRight == NULL)
		{
			tree = tree->mLeft;
			delete tempPtr;
		}
		else
		{
			//������� ����� �ڽĳ�忡�� �ִ� ã�� �� �װɷ� ��ü�� ���� ���� �ִ� ����
			GetPredecessor(tree->mLeft, tempItem);
			tree->mData = tempItem;
			InternalDelete(tree->mLeft, tempItem);
		}
	}

	void GetPredecessor(TreeNode<T>* tree, T& data)
	{
		while (tree->mRight != NULL)
			tree = tree->mRight;
		data = tree->mData;
	}

	bool InternalRetrieve(TreeNode<T>* root, T& item)
	{
		if (root == NULL)
		{
			return false;
		}
		else if (item < root->mData)
		{
			InternalRetrieve(root->mLeft, item);
		}
		else if (item > root->mData)
			InternalRetrieve(root->mRight, item);
		else
		{
			item = root->mData;
			return true;
		}
	}

	void InternalPrint(TreeNode<T>* treePtr) //, ofstream& outFile
	{
		if (treePtr != NULL)
		{
			InternalPrint(treePtr->mLeft);
			cout << treePtr->mData.GetId() << " - ";
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





#endif