#pragma once
#include "Node.h"

class BinarySearchTree
{
public:
	BinarySearchTree();
	void SetSize(int size);
	void SetRoot(Node* root);
	int GetSize();
	Node* GetRoot();
	bool IsEmpty();
	Node* Search(int keyToSearch, Node* nodeToSearchAt);
	Node* Insert(int keyToInsert, std::string valueToInsert, Node* nodeToInsertAt);
	void Rebalance(Node* newlyInsertedNode);
	Node* BalancedInsert(int keyToInsert, std::string valueToInsert);
private:
	Node* _root;
	int _size;
	void InsertAtExternal(Node* externalNode, int keyToInsert, std::string valueToInsert);
	int Height(Node* nodeToReturnHeight);
	bool IsBalanced(Node* nodeToCheck);
	Node* TallGrandchild(Node* unbalancedNode);
	void Restructure(Node* grandchild);
};