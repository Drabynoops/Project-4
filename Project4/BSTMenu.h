#pragma once
#include "BinarySearchTree.h"

class BSTMenu
{
public:
	BSTMenu();
	BSTMenu(BinarySearchTree bst);
	~BSTMenu();
	void SetBST(BinarySearchTree bst);
	void PrintMenu();
	bool SelectMenuOption();

private:
	BinarySearchTree _bst;

	void Insert();
	void Delete();
	void Search();
	void Display();
};