#pragma once
#include "Node.h"
#include <vector>

class BinarySearchTree
{
public:
	BinarySearchTree();
	void SetSize(int size);
	void SetRoot(Node* root);
	int GetSize();
	Node* GetRoot();
	int GetNodeDepth(Node* nodeToFindDepthOf);
	bool IsEmpty();
	Node* Search(int keyToSearch, Node* nodeToSearchAt);
	Node* Insert(int keyToInsert, std::string valueToInsert, Node* nodeToInsertAt);
	void Rebalance(Node* newlyInsertedNode);
	Node* BalancedInsert(int keyToInsert, std::string valueToInsert);
	Node* Delete(Node* nodeToDelete);
	Node* BalancedDelete(Node* nodeToDelete);
	void PrintTree();
	
private:
	Node* _root;
	int _size;
	void InsertAtExternal(Node* externalNode, int keyToInsert, std::string valueToInsert);
	int GetNodeHeight(Node* nodeToReturnHeight);
	bool IsBalanced(Node* nodeToCheck);
	Node* TallGrandchild(Node* unbalancedNode);
	void Restructure(Node* grandchild);
	void AssignCoordinates(Node* nodeToStartAt, std::vector<std::vector<std::string>>& grid, int& counter);
};